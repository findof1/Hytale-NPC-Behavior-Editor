#include "nodeWidgets.hpp"

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
    p->setPen(Qt::white);
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
  return QRectF(0, 0, baseWidth, height + std::max(inputs.size(), outputs.size()) * 20);
}

void NodeItem::paint(QPainter *p, const QStyleOptionGraphicsItem *, QWidget *)
{
  p->setRenderHint(QPainter::Antialiasing);
  p->setBrush(QColor(25, 25, 28));
  p->setPen(Qt::NoPen);
  p->drawRoundedRect(boundingRect(), 8, 8);

  p->setBrush(QColor(70, 70, 75));
  p->drawRoundedRect(0, 0, baseWidth, 24, 8, 8);

  p->setPen(Qt::white);
  p->drawText(10, 17, title);

  if (hasFields)
  {
    p->setBrush(QColor(35, 35, 38));
    p->setPen(Qt::NoPen);
    p->drawRoundedRect(2, 60 + std::max(inputs.size(), outputs.size()) * 20, baseWidth - 4, 2, 1, 1);

    proxy->setPos(2, 80 + std::max(inputs.size(), outputs.size()) * 20);
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
      link.startNode = draggingSocket;
      link.endNode = target;
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