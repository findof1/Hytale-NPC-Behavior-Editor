#pragma once

#include <QWidget>
#include <QString>
#include <QDialog>
#include <QPushButton>

class ProjectSelector : public QDialog
{
  Q_OBJECT

public:
  QString selectedPath;
  explicit ProjectSelector(QWidget *parent = nullptr);

signals:
  void projectSelected(const QString &path);

private:
  QPushButton *openButton;
  QPushButton *newButton;
};