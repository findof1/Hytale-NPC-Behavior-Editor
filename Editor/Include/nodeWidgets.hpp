#pragma once

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QGraphicsPathItem>
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QGraphicsProxyWidget>
#include <QVBoxLayout>

#include <nlohmann/json.hpp>

class NodeView;
class NodeItem;
class SocketItem;
class NodeScene;

class EdgeItem : public QGraphicsPathItem
{
public:
  EdgeItem(QPointF start, QPointF end)
  {
    setFlags(ItemIsSelectable | ItemIsFocusable);
    setAcceptHoverEvents(true);
    setZValue(-1);
    updatePath(start, end);
  }

  void updatePath(QPointF start, QPointF end);

protected:
  void hoverEnterEvent(QGraphicsSceneHoverEvent *) override
  {
    QPen p = pen();
    p.setWidth(3);
    setPen(p);
  }

  void hoverLeaveEvent(QGraphicsSceneHoverEvent *) override
  {
    QPen p = pen();
    p.setWidth(2);
    setPen(p);
  }

  void mousePressEvent(QGraphicsSceneMouseEvent *event) override
  {
    setSelected(true);
    QGraphicsPathItem::mousePressEvent(event);
  }
};

class NodeView : public QGraphicsView
{
  Q_OBJECT
public:
  NodeView(QWidget *parent = nullptr) : QGraphicsView(parent), zoomFactor(1.15)
  {
    setRenderHint(QPainter::Antialiasing);
    setDragMode(QGraphicsView::NoDrag);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
  }

  void drawBackground(QPainter *painter, const QRectF &rect) override;

protected:
  void wheelEvent(QWheelEvent *event) override;

  void mousePressEvent(QMouseEvent *event) override;

  void mouseReleaseEvent(QMouseEvent *event) override;

  void mouseMoveEvent(QMouseEvent *event) override;

private:
  QPoint lastPanPoint;
  double zoomFactor;
};

class SocketItem : public QGraphicsObject
{
  Q_OBJECT
public:
  bool isOutput = false;

  SocketItem(const QString &name, const QColor &color, bool isOutput, bool drawLabel = true) : name(name), color(color), isOutput(isOutput), drawLabel(drawLabel)
  {
    setAcceptHoverEvents(true);
    setToolTip(name);
  }

  QRectF boundingRect() const override;

  void paint(QPainter *p, const QStyleOptionGraphicsItem *, QWidget *) override;

  void setOutput(bool value) { isOutput = value; }
  QString getName() const { return name; }

signals:
  void dragStarted(SocketItem *socket);
  void dragFinished(SocketItem *socket, QPointF scenePos);

protected:
  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
  QString name;
  QColor color;
  bool drawLabel = true;
};

class NodeItem : public QGraphicsObject
{
  Q_OBJECT
public:
  bool deletable = true;
  bool hasFields;
  int baseHeight = 60;
  int baseWidth = 200;
  int fieldsHeight = 60;
  int id = -1;
  std::vector<std::unique_ptr<SocketItem>> inputs;
  std::vector<std::unique_ptr<SocketItem>> outputs;

  virtual QString nodeType() const = 0;
  virtual nlohmann::json serializeNode() const = 0;          // for serializing the scene, not the final NPCRole json
  virtual void deserializeNode(const nlohmann::json &j) = 0; // for serializing the scene, not the final NPCRole json

  NodeItem(QString title, bool hasFields = false, int baseWidth = 200) : title(title), hasFields(hasFields), baseWidth(baseWidth)
  {
    setFlags(ItemIsMovable | ItemIsSelectable | ItemSendsGeometryChanges);
    if (hasFields)
    {
      propertiesContainer = new QWidget;

      auto *layout = new QVBoxLayout;
      layout->setContentsMargins(4, 4, 4, 4);
      layout->setSpacing(3);
      propertiesContainer->setLayout(layout);
      propertiesContainer->setAttribute(Qt::WA_TranslucentBackground);
      propertiesContainer->setObjectName("propertiesContainer");

      proxy = new QGraphicsProxyWidget(this);
      proxy->setWidget(propertiesContainer);
      proxy->setMinimumWidth(baseWidth - 2);
      proxy->setMaximumWidth(baseWidth - 2);
    }
  }

  QWidget *propertiesWidget() { return propertiesContainer; }

  QRectF boundingRect() const override;

  void paint(QPainter *p, const QStyleOptionGraphicsItem *, QWidget *) override;

  void addInputSocket(const std::string &name, const NodeScene *context, bool optional = false);

  void addOutputSocket(const std::string &name, const NodeScene *context, bool optional = false);

  void clearInputs();

  void removeInputSocket();

  void clearOutputs();

  void removeOutputSocket();

  QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private:
  QString title;
  QGraphicsProxyWidget *proxy;
  QWidget *propertiesContainer = nullptr;
};

struct Link
{
  SocketItem *startNode;
  SocketItem *endNode;
  EdgeItem *line;

  void update()
  {
    if (!startNode || !endNode)
      return;
    line->updatePath(startNode->scenePos(), endNode->scenePos());
  }
};

class RootNode;
class NodeScene : public QGraphicsScene
{
  Q_OBJECT
public:
  std::vector<Link> links;
  std::vector<std::shared_ptr<NodeItem>> nodes;

  inline int generateId()
  {
    return nextId++;
  }

  using NodeFactoryFn = std::function<std::shared_ptr<NodeItem>(NodeScene *)>;
  QMap<QString, NodeFactoryFn> nodeFactory; // for creating ui out of all of the node types systematicially

  NodeScene(QObject *parent = nullptr) : QGraphicsScene(parent), tempEdge(nullptr), draggingSocket(nullptr) {}

  void initNodeFactory(); // defined in nodeFactory.cpp

  void updateLinks();

  void keyPressEvent(QKeyEvent *event) override;

  std::shared_ptr<NodeItem> spawnNode(const QString &type, QPointF pos);

  void removeNode(NodeItem *node);

  void removeEdge(EdgeItem *edge);

  nlohmann::json serializeScene();
  RootNode *deserializeScene(const nlohmann::json &j); // returns root node for attributes editor to store until serialziation

public slots:
  void
  startDrag(SocketItem *socket);

  void updateDrag(QPointF pos);

  void finishDrag(SocketItem * /*socket*/, QPointF pos);

protected:
  void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

private:
  EdgeItem *tempEdge;
  SocketItem *draggingSocket;
  int nextId = 0;
};
