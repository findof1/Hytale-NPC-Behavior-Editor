#include "vectorEditorWidget.hpp"

VectorEditor::VectorEditor(ItemFactory factory, QWidget *parent) : QWidget(parent), factory(factory)
{
  list = new QListWidget;
  list->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
  list->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
  list->setSpacing(15);

  addBtn = new QPushButton("Add");
  removeBtn = new QPushButton("Remove");

  auto *btnLayout = new QHBoxLayout;
  btnLayout->addWidget(addBtn);
  btnLayout->addWidget(removeBtn);

  auto *mainLayout = new QVBoxLayout(this);
  mainLayout->setContentsMargins(0, 0, 0, 0);
  mainLayout->addWidget(list);
  mainLayout->addLayout(btnLayout);

  connect(addBtn, &QPushButton::clicked, this, &VectorEditor::addItem);
  connect(removeBtn, &QPushButton::clicked, this, &VectorEditor::removeItem);
}

int VectorEditor::count() const
{
  return list->count();
}

QWidget *VectorEditor::itemAt(int index) const
{
  return qobject_cast<QWidget *>(list->itemWidget(list->item(index)));
}

void VectorEditor::clear()
{
  list->clear();
}

void VectorEditor::addItem()
{
  auto *item = new QListWidgetItem;
  QWidget *inner = factory();

  auto *frame = new QFrame;
  frame->setFrameShape(QFrame::StyledPanel);
  frame->setFrameShadow(QFrame::Raised);
  frame->setStyleSheet(
      "QFrame {"
      "  border: 1px solid #555;"
      "  border-radius: 6px;"
      "  background: #2b2b2b;"
      "}");

  auto *layout = new QVBoxLayout(frame);
  layout->setContentsMargins(8, 6, 8, 6);
  layout->addWidget(inner);

  item->setSizeHint(frame->sizeHint());

  list->addItem(item);
  list->setItemWidget(item, frame);
}

void VectorEditor::removeItem()
{
  delete list->currentItem();
}