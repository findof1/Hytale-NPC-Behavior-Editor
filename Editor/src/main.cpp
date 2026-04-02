#include <QApplication>
#include "attributesEditor.hpp"
#include "styleGlobals.hpp"
#include "projectSelector.hpp"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    gStyleManager.init(&app);
    gStyleManager.setDarkStyle();

    ProjectSelector selector;

    if (selector.exec() != QDialog::Accepted)
        return 0;

    AttributesEditor editor(selector.selectedPath);
    editor.show();

    editor.setupScene();
    app.exec();
    editor.serializeEditorToDisk();

    return 0;
}