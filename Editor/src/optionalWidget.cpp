#include "optionalWidget.hpp"
#include <QApplication>
#include <QWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QPushButton>
#include <QToolButton>
#include <QListWidget>
#include <QInputDialog>
#include <QVector>
#include <QScrollArea>
#include <string>
#include <optional>
#include <iostream>

OptionalWidget::OptionalWidget(QWidget *editor, QWidget *parent) : QWidget(parent), editor(editor)
{
  check = new QCheckBox("Enabled");
  editor->setEnabled(false);

  auto *layout = new QHBoxLayout(this);
  layout->setContentsMargins(0, 0, 0, 0);
  layout->addWidget(check);
  layout->addWidget(editor, 1);

  connect(check, &QCheckBox::toggled, editor, &QWidget::setEnabled);
}

bool OptionalWidget::isEnabled() const
{
  return check->isChecked();
}

void OptionalWidget::setEnabledValue(bool enabled)
{
  check->setChecked(enabled);
  editor->setEnabled(enabled);
}
