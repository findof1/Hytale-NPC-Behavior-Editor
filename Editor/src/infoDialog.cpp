#include "infoDialog.hpp"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QStackedWidget>
#include <QLineEdit>
#include <QLabel>

InfoDialog::InfoDialog(QWidget *parent)
    : QDialog(parent)
{
  setWindowTitle("Info");
  setModal(true);
  resize(500, 350);

  QVBoxLayout *mainLayout = new QVBoxLayout(this);

  QLineEdit *searchBar = new QLineEdit(this);
  searchBar->setPlaceholderText("Search...");
  mainLayout->addWidget(searchBar);

  QHBoxLayout *contentLayout = new QHBoxLayout();
  mainLayout->addLayout(contentLayout);

  QListWidget *tabList = new QListWidget(this);
  tabList->addItem("Root Node");
  tabList->addItem("Instruction Node");
  tabList->addItem("Comment Node");
  tabList->addItem("Adjust Position Node");
  tabList->setFixedWidth(140);

  contentLayout->addWidget(tabList);

  QStackedWidget *stack = new QStackedWidget(this);
  contentLayout->addWidget(stack);

  QWidget *rootPage = new QWidget();
  QVBoxLayout *rootLayout = new QVBoxLayout(rootPage);
  rootLayout->addWidget(new QLabel("Root Node: The start point for all other nodes. Connections: Instructions - takes in multiple instruction nodes"));
  stack->addWidget(rootPage);

  QWidget *instructionPage = new QWidget();
  QVBoxLayout *instructionLayout = new QVBoxLayout(instructionPage);
  instructionLayout->addWidget(new QLabel("Instruction Node"));
  stack->addWidget(instructionPage);

  QWidget *adjustPositionPage = new QWidget();
  QVBoxLayout *adjustPositionLayout = new QVBoxLayout(adjustPositionPage);
  adjustPositionLayout->addWidget(new QLabel("Adjust Position Node"));
  stack->addWidget(adjustPositionPage);

  connect(tabList, &QListWidget::currentRowChanged,
          stack, &QStackedWidget::setCurrentIndex);

  tabList->setCurrentRow(0);

  connect(searchBar, &QLineEdit::textChanged, this,
          [tabList](const QString &text)
          {
            for (int i = 0; i < tabList->count(); ++i)
            {
              auto *item = tabList->item(i);
              bool match = item->text().contains(text, Qt::CaseInsensitive);
              item->setHidden(!match);
            }
          });
}