#pragma once

#include <QWidget>
#include <QString>
#include <QDialog>
#include <QPushButton>

class InfoDialog : public QDialog
{
public:
  explicit InfoDialog(QWidget *parent = nullptr);
};