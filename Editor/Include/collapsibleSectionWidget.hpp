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

class CollapsibleSection : public QWidget
{
public:
  CollapsibleSection(const QString &title, QWidget *parent = nullptr);

  QVBoxLayout *contentLayout();

private:
  QToolButton *toggle;
  QWidget *content;
};