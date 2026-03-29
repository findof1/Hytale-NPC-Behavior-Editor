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

#include <nlohmann/json.hpp>

class VectorEditor : public QWidget
{
public:
  QListWidget *list;
  using ItemFactory = std::function<QWidget *()>;

  VectorEditor(ItemFactory factory, QWidget *parent = nullptr);

  int count() const;

  QWidget *itemAt(int index) const;

  void clear();

public slots:
  void addItem();

  void removeItem();

private:
  QPushButton *addBtn;
  QPushButton *removeBtn;
  ItemFactory factory;
};

nlohmann::json serializeVectorEditor(VectorEditor *editor);
void deserializeVectorEditor(VectorEditor *editor, const nlohmann::json &arr);