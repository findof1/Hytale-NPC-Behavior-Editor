#include "collapsibleSectionWidget.hpp"

CollapsibleSection::CollapsibleSection(const QString &title, QWidget *parent) : QWidget(parent)
{
  toggle = new QToolButton;
  toggle->setText(title);
  toggle->setCheckable(true);
  toggle->setChecked(false);
  toggle->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
  toggle->setArrowType(Qt::RightArrow);

  content = new QWidget;
  content->setVisible(false);

  auto *mainLayout = new QVBoxLayout(this);
  mainLayout->setContentsMargins(0, 0, 0, 0);
  mainLayout->addWidget(toggle);
  mainLayout->addWidget(content);

  connect(toggle, &QToolButton::toggled, this, [this](bool open)
          {
      toggle->setArrowType(open ? Qt::DownArrow : Qt::RightArrow);
      content->setVisible(open); });
}

QVBoxLayout *CollapsibleSection::contentLayout()
{
  auto *layout = qobject_cast<QVBoxLayout *>(content->layout());
  if (!layout)
  {
    layout = new QVBoxLayout(content);
    layout->setContentsMargins(16, 4, 4, 4);
  }
  return layout;
}
