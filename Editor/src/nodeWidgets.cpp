#include "nodeWidgets.hpp"
#include "nodes.hpp"
#include <fstream>
#include "styleGlobals.hpp"

void EdgeItem::updatePath(QPointF start, QPointF end)
{
  QPainterPath path(start);
  qreal dx = (end.x() - start.x()) * 0.5;
  path.cubicTo(start.x() + dx, start.y(),
               end.x() - dx, end.y(),
               end.x(), end.y());
  setPath(path);

  QPen pen(QColor(200, 200, 200), 2);
  pen.setCapStyle(Qt::RoundCap);
  setPen(pen);
}

void NodeView::wheelEvent(QWheelEvent *event)
{
  if (event->modifiers() & Qt::ControlModifier)
  {
    if (event->angleDelta().y() > 0)
      scale(zoomFactor, zoomFactor);
    else
      scale(1.0 / zoomFactor, 1.0 / zoomFactor);
  }
  else
  {
    QGraphicsView::wheelEvent(event);
  }
}

void NodeView::mousePressEvent(QMouseEvent *event)
{
  if (event->button() == Qt::MiddleButton)
  {
    setCursor(Qt::ClosedHandCursor);
    lastPanPoint = event->pos();
  }

  if (event->button() == Qt::LeftButton)
    QGraphicsView::mousePressEvent(event);
}

void NodeView::mouseReleaseEvent(QMouseEvent *event)
{
  if (event->button() == Qt::MiddleButton)
  {
    setCursor(Qt::ArrowCursor);
    lastPanPoint = QPoint();
  }
  QGraphicsView::mouseReleaseEvent(event);
}

void NodeView::mouseMoveEvent(QMouseEvent *event)
{
  if (!lastPanPoint.isNull())
  {
    QPointF delta = mapToScene(lastPanPoint) - mapToScene(event->pos());
    lastPanPoint = event->pos();
    setSceneRect(sceneRect().translated(delta.x(), delta.y()));
  }
  QGraphicsView::mouseMoveEvent(event);
}

void NodeView::drawBackground(QPainter *painter, const QRectF &rect)
{
  QGraphicsView::drawBackground(painter, rect);

  const int gridSize = 20;
  const int boldGridSize = gridSize * 5;

  QPalette p = palette();

  QColor base = p.color(QPalette::Base);
  QColor accent = p.color(QPalette::Accent);

  QColor lightColor = base.darker(110);
  QColor darkColor = accent;

  int left = int(std::floor(rect.left()));
  int right = int(std::ceil(rect.right()));
  int top = int(std::floor(rect.top()));
  int bottom = int(std::ceil(rect.bottom()));

  int firstLeft = left - (left % gridSize);
  int firstTop = top - (top % gridSize);

  for (int x = firstLeft; x < right; x += gridSize)
  {
    if (x % boldGridSize == 0)
      painter->setPen(darkColor);
    else
      painter->setPen(lightColor);

    painter->drawLine(x, top, x, bottom);
  }

  for (int y = firstTop; y < bottom; y += gridSize)
  {
    if (y % boldGridSize == 0)
      painter->setPen(darkColor);
    else
      painter->setPen(lightColor);

    painter->drawLine(left, y, right, y);
  }
}

QRectF SocketItem::boundingRect() const
{
  return QRectF(-5, -5, 80, 10);
}

void SocketItem::paint(QPainter *p, const QStyleOptionGraphicsItem *, QWidget *)
{
  p->setRenderHint(QPainter::Antialiasing);
  p->setBrush(color);
  p->setPen(Qt::black);
  p->drawEllipse(QRectF(-5, -5, 10, 10));

  if (drawLabel)

  {
    QColor textColor = gStyleManager.getCurrentStyle().nodeText;
    p->setPen(textColor);
    if (!isOutput)
      p->drawText(10, 4, name);
    else
      p->drawText(-p->fontMetrics().horizontalAdvance(name) - 10, 4, name);
  }
}

void SocketItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  if (event->button() == Qt::LeftButton)
  {
    emit dragStarted(this);
    event->accept();
  }
  else
    QGraphicsObject::mousePressEvent(event);
}

void SocketItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
  if (event->button() == Qt::LeftButton)
  {
    emit dragFinished(this, event->scenePos());
    event->accept();
  }
  else
    QGraphicsObject::mouseReleaseEvent(event);
}

QRectF NodeItem::boundingRect() const
{
  int height = hasFields ? baseHeight + fieldsHeight : baseHeight;
  int errorHeight = hasError ? errorMsg.size() * 25 + 25 : 0;

  return QRectF(0, 0, baseWidth, height + std::max(inputs.size(), outputs.size()) * 20 + errorHeight);
}

void NodeItem::paint(QPainter *p, const QStyleOptionGraphicsItem *, QWidget *)
{
  StyleData style = gStyleManager.getCurrentStyle();
  p->setRenderHint(QPainter::Antialiasing);
  p->setBrush(style.nodeBackground);
  p->setPen(Qt::NoPen);
  p->drawRoundedRect(boundingRect(), 8, 8);

  p->setBrush(style.nodeHeader);
  p->drawRoundedRect(0, 0, baseWidth, 24, 8, 8);

  p->setPen(style.nodeText);
  p->drawText(10, 17, title);

  if (hasFields)
  {
    p->setBrush(style.nodeDivider);
    p->setPen(Qt::NoPen);
    p->drawRoundedRect(2, 60 + std::max(inputs.size(), outputs.size()) * 20, baseWidth - 4, 2, 1, 1);

    proxy->setPos(2, 80 + std::max(inputs.size(), outputs.size()) * 20);
  }

  if (!hasError) // skip error display
    return;

  QPen pen(Qt::red);
  pen.setWidth(2);
  p->setPen(pen);
  p->setBrush(Qt::NoBrush);
  p->drawRoundedRect(boundingRect(), 8, 8);

  if (!errorMsg.empty())
  {
    p->setPen(Qt::red);

    QRectF rect = boundingRect();

    int lineHeight = 25;
    int totalHeight = errorMsg.size() * lineHeight + 25;

    QFontMetrics fm(p->font());

    int y = rect.height() - totalHeight - 5;

    QRectF headerRect(10, y, baseWidth - 20, lineHeight);
    p->drawText(headerRect, Qt::AlignLeft | Qt::TextWordWrap, "Errors:");
    y += fm.height();

    for (const auto &msg : errorMsg)
    {
      QString text = QString::fromStdString(msg);

      QRectF msgRect = fm.boundingRect(0, 0, baseWidth - 20, 1000, Qt::AlignLeft | Qt::TextWordWrap, text);

      msgRect.moveTop(y);

      p->drawText(msgRect, Qt::AlignLeft | Qt::TextWordWrap, text);

      y += msgRect.height();
    }
  }
}

QVariant NodeItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
  if (change == ItemPositionHasChanged && scene())
  {
    auto nodeScene = static_cast<NodeScene *>(scene());
    nodeScene->updateLinks();
  }
  return QGraphicsItem::itemChange(change, value);
}

void NodeItem::addInputSocket(const std::string &name, const NodeScene *context, bool optional)
{
  int yOffset = 40 + inputs.size() * 20;
  auto socket = std::make_unique<SocketItem>(QString::fromStdString(name), optional ? Qt::blue : Qt::cyan, false);
  socket->setParentItem(this);
  socket->setPos(0, yOffset);

  if (context)
  {
    QObject::connect(socket.get(), &SocketItem::dragStarted, context, &NodeScene::startDrag);
    QObject::connect(socket.get(), &SocketItem::dragFinished, context, &NodeScene::finishDrag);
  }

  inputs.push_back(std::move(socket));
}

void NodeItem::addOutputSocket(const std::string &name, const NodeScene *context, bool optional)
{
  int yOffset = 40 + outputs.size() * 20;
  auto socket = std::make_unique<SocketItem>(QString::fromStdString(name), optional ? Qt::darkYellow : Qt::yellow, true);
  socket->setParentItem(this);
  socket->setPos(baseWidth, yOffset);

  if (context)
  {
    QObject::connect(socket.get(), &SocketItem::dragStarted, context, &NodeScene::startDrag);
    QObject::connect(socket.get(), &SocketItem::dragFinished, context, &NodeScene::finishDrag);
  }

  outputs.push_back(std::move(socket));
}

void NodeItem::clearInputs()
{
  for (auto &socket : inputs)
  {
    if (scene() && socket)
      scene()->removeItem(socket.get());
    socket.reset();
  }
  inputs.clear();
}

void NodeItem::removeInputSocket()
{
  if (inputs.empty())
    return;
  auto &socket = inputs.back();
  scene()->removeItem(socket.get());
  socket.reset();
  inputs.pop_back();
  for (size_t i = 0; i < inputs.size(); ++i)
    inputs[i]->setPos(0, 40 + i * 20);
}

void NodeItem::clearOutputs()
{
  for (auto &socket : outputs)
  {
    if (scene() && socket)
      scene()->removeItem(socket.get());
    socket.reset();
  }
  outputs.clear();
}

void NodeItem::removeOutputSocket()
{
  if (outputs.empty())
    return;
  auto &socket = outputs.back();
  scene()->removeItem(socket.get());
  socket.reset();
  outputs.pop_back();
  for (size_t i = 0; i < outputs.size(); ++i)
    outputs[i]->setPos(140, 40 + i * 20);
}

void NodeScene::startDrag(SocketItem *socket)
{
  draggingSocket = socket;
  tempEdge = new EdgeItem(socket->scenePos(), socket->scenePos());
  addItem(tempEdge);
}

void NodeScene::updateDrag(QPointF pos)
{
  if (tempEdge && draggingSocket)
    tempEdge->updatePath(draggingSocket->scenePos(), pos);
}

void NodeScene::finishDrag(SocketItem * /*socket*/, QPointF pos)
{
  if (!tempEdge || !draggingSocket)
    return;

  QList<QGraphicsItem *> itemsAtPos = items(pos);
  for (auto item : itemsAtPos)
  {
    auto target = dynamic_cast<SocketItem *>(item);
    if (target && target != draggingSocket && target->isOutput != draggingSocket->isOutput)
    {
      Link link;

      // This is to make sure the endNode is the input to the next one when serializing links
      if (draggingSocket->isOutput)
      {
        link.startNode = draggingSocket;
        link.endNode = target;
      }
      else
      {
        link.startNode = target;
        link.endNode = draggingSocket;
      }
      //

      link.line = new EdgeItem(draggingSocket->scenePos(), target->scenePos());
      addItem(link.line);
      links.emplace_back(link);
      break;
    }
  }

  removeItem(tempEdge);
  delete tempEdge;
  tempEdge = nullptr;
  draggingSocket = nullptr;
}

void NodeScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
  if (tempEdge)
    updateDrag(event->scenePos());
  QGraphicsScene::mouseMoveEvent(event);
}

void NodeScene::updateLinks()
{
  for (auto &link : links)
    link.update();
}

void NodeScene::keyPressEvent(QKeyEvent *event)
{
  auto key = event->key();
  if (key == Qt::Key_Delete)
  {
    auto selected = selectedItems();

    for (auto *item : selected)
    {
      if (auto node = dynamic_cast<NodeItem *>(item))
      {
        if (node && node->scene() == this)
          removeNode(node);
      }

      if (auto edge = dynamic_cast<EdgeItem *>(item))
      {
        if (edge && edge->scene() == this)
          removeEdge(edge);
      }
    }
  }

  QGraphicsScene::keyPressEvent(event);
}

std::shared_ptr<NodeItem> NodeScene::spawnNode(const QString &type, QPointF pos)
{
  auto node = nodeFactory[type](this);

  node->id = generateId();
  node->setPos(pos);

  addItem(node.get());
  nodes.emplace_back(node);

  return node;
}

void NodeScene::removeNode(NodeItem *node)
{
  if (!node || !node->deletable)
    return;

  std::vector<EdgeItem *> edgesToRemove;

  for (auto &link : links)
  {
    if (!link.startNode || !link.endNode)
      continue;

    NodeItem *startParent = static_cast<NodeItem *>(link.startNode->parentItem());
    NodeItem *endParent = static_cast<NodeItem *>(link.endNode->parentItem());

    if (startParent == node || endParent == node)
    {
      if (link.line)
        edgesToRemove.push_back(link.line);
    }
  }

  for (auto *edge : edgesToRemove)
    removeEdge(edge);

  links.erase(
      std::remove_if(links.begin(), links.end(),
                     [&](const Link &l)
                     {
                       if (!l.startNode || !l.endNode)
                         return true;

                       NodeItem *sp =
                           static_cast<NodeItem *>(l.startNode->parentItem());
                       NodeItem *ep =
                           static_cast<NodeItem *>(l.endNode->parentItem());

                       return sp == node || ep == node;
                     }),
      links.end());

  if (node->scene())
    node->scene()->removeItem(node);

  nodes.erase(
      std::remove_if(nodes.begin(), nodes.end(),
                     [&](const std::shared_ptr<NodeItem> &n)
                     { return n.get() == node; }),
      nodes.end());
}

void NodeScene::removeEdge(EdgeItem *edge)
{
  if (!edge)
    return;

  links.erase(
      std::remove_if(links.begin(), links.end(),
                     [&](const Link &l)
                     { return l.line == edge; }),
      links.end());

  if (edge->scene())
    edge->scene()->removeItem(edge);

  delete edge;
}

nlohmann::json NodeScene::serializeScene()
{
  nlohmann::json j;

  for (auto &node : nodes)
  {
    j["nodes"].push_back({{"id", node->id},
                          {"type", node->nodeType().toStdString()},
                          {"x", node->pos().x()},
                          {"y", node->pos().y()},
                          {"data", node->serializeNode()}});
  }

  for (auto &link : links)
  {
    NodeItem *fromNode = dynamic_cast<NodeItem *>(link.startNode->parentItem());
    NodeItem *toNode = dynamic_cast<NodeItem *>(link.endNode->parentItem());

    if (!fromNode || !toNode)
      continue;

    j["links"].push_back({{"fromNode", fromNode->id},
                          {"fromSocket", link.startNode->getName().toStdString()},
                          {"toNode", toNode->id},
                          {"toSocket", link.endNode->getName().toStdString()}});
  }

  return j;
}

RootNode *NodeScene::deserializeScene(const nlohmann::json &j)
{
  clear();
  nodes.clear();
  links.clear();
  std::unordered_map<int, std::shared_ptr<NodeItem>> idMap;
  RootNode *rootNode;
  int maxId = 0;

  if (j.contains("nodes"))
  {
    for (const auto &n : j["nodes"])
    {
      int id = n["id"];
      QString type = QString::fromStdString(n["type"]);

      auto it = nodeFactory.end();

      // Kinda a bad fix for converting from node type to the one in node factory, should fix at some point
      for (auto iter = nodeFactory.begin(); iter != nodeFactory.end(); ++iter)
      {
        QString key = iter.key();

        QString namePart;
        int slashIndex = key.indexOf('/');
        if (slashIndex != -1)
          namePart = key.mid(slashIndex + 1);
        else
          namePart = key;

        QString normalized = namePart;
        normalized.remove(' ');

        if (normalized == type)
        {
          it = iter;
          break;
        }
      }

      //

      if (it == nodeFactory.end())
      {
        if (type == "Root") // root node isn't in nodeFactory because nodeFactory gets converted into UI and root cannot be spawned in via the UI
        {
          rootNode = new RootNode(this);
          rootNode->id = id;
          rootNode->setPos(n["x"], n["y"]);
          addItem(rootNode);
          nodes.emplace_back(rootNode);

          idMap[id] = nodes.back(); // this returns the correct type for the rootNode, same item, different type
          maxId = std::max(maxId, id);
        }
        continue;
      }

      auto node = it.value()(this);

      node->id = id;
      node->setPos(n["x"], n["y"]);

      if (n.contains("data"))
        node->deserializeNode(n["data"]);

      addItem(node.get());
      nodes.emplace_back(node);

      idMap[id] = node;
      maxId = std::max(maxId, id);
    }
  }

  nextId = maxId + 1;

  if (j.contains("links"))
  {
    for (const auto &l : j["links"])
    {
      int fromId = l["fromNode"];
      int toId = l["toNode"];

      if (!idMap.count(fromId) || !idMap.count(toId))
        continue;

      auto fromNode = idMap[fromId];
      auto toNode = idMap[toId];

      std::string fromSocketName = l["fromSocket"];
      std::string toSocketName = l["toSocket"];

      SocketItem *outSocket = nullptr;
      SocketItem *inSocket = nullptr;

      for (auto &s : fromNode->outputs)
      {
        if (s->getName().toStdString() == fromSocketName)
        {
          outSocket = s.get();
          break;
        }
      }

      for (auto &s : toNode->inputs)
      {
        if (s->getName().toStdString() == toSocketName)
        {
          inSocket = s.get();
          break;
        }
      }

      if (!outSocket || !inSocket)
        continue;

      auto edge = new EdgeItem(outSocket->scenePos(), inSocket->scenePos());
      addItem(edge);

      links.push_back({outSocket, inSocket, edge});
    }
  }

  if (!rootNode)
  {
    rootNode = new RootNode(this);
    rootNode->id = generateId();
    rootNode->setPos(0, 0);

    addItem(rootNode);
    nodes.emplace_back(rootNode);
  }

  updateLinks();

  return rootNode;
}

void NodeScene::clearAllNodeErrors()
{
  for (auto &node : nodes)
  {
    node->hasError = false;
    node->errorMsg.clear();
    node->update();
  }
}