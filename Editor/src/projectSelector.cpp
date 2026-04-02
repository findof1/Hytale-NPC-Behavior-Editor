#include "projectSelector.hpp"
#include <QPushButton>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QInputDialog>
#include <QLineEdit>
#include <QMessageBox>

ProjectSelector::ProjectSelector(QWidget *parent) : QDialog(parent)
{
  setWindowTitle("Select Project");
  resize(300, 150);

  openButton = new QPushButton("Open Project", this);
  newButton = new QPushButton("New Project", this);

  auto *layout = new QVBoxLayout(this);
  layout->addWidget(openButton);
  layout->addWidget(newButton);

  connect(openButton, &QPushButton::clicked, this, [this]()
          {
    QString path = QFileDialog::getExistingDirectory(
        this,
        "Open Project",
        "./projects",  // optional default directory
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
    );

    if (!path.isEmpty())
    {
        selectedPath = path;
        accept();
    } });

  connect(newButton, &QPushButton::clicked, this, [this]()
          {
    QDir baseDir("./projects");

    if (!baseDir.exists())
        baseDir.mkpath(".");

    bool ok;
    QString projectName = QInputDialog::getText(
        this,
        "New Project",
        "Enter project name:",
        QLineEdit::Normal,
        "",
        &ok
    );

    if (!ok || projectName.isEmpty())
        return;

    QString path = baseDir.filePath(projectName);
    QDir projectDir(path);

    if (projectDir.exists())
    {
        QMessageBox::warning(
            this,
            "Error",
            "A project with that name already exists!"
        );
        return;
    }

    if (!projectDir.mkpath("."))
    {
        QMessageBox::critical(
            this,
            "Error",
            "Failed to create project folder."
        );
        return;
    }

    selectedPath = path;
    accept(); });
}