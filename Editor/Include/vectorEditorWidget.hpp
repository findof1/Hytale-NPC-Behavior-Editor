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

class VectorEditor : public QWidget
{
public:
  using ItemFactory = std::function<QWidget *()>;

  VectorEditor(ItemFactory factory, QWidget *parent = nullptr);

  int count() const;

  QWidget *itemAt(int index) const;

  void clear();

private slots:
  void addItem();

  void removeItem();

private:
  QListWidget *list;
  QPushButton *addBtn;
  QPushButton *removeBtn;
  ItemFactory factory;
};