#pragma once
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

#include "typeUtils.hpp"
#include "types.hpp"
#include <qmainwindow.h>
#include "vectorEditorWidget.hpp"
#include "optionalWidget.hpp"

class StateTransitionEditor : public QWidget
{
public:
  StateTransitionEditor(QWidget *parent = nullptr);

  General::StateTransition value() const;

  void setValue(const General::StateTransition &t);

private:
  QSpinBox *prioritySpin;
  VectorEditor *fromEditor;
  VectorEditor *toEditor;
  QCheckBox *enabledCheck;
  OptionalWidget *enabledOptional;
};