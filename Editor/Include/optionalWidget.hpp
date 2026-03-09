#pragma once
#include <QCheckBox>
#include <QWidget>

class OptionalWidget : public QWidget
{

public:
  OptionalWidget(QWidget *editor, QWidget *parent = nullptr);

  bool isEnabled() const;
  void setEnabledValue(bool enabled);

  QWidget *editor;
  QCheckBox *check;
};