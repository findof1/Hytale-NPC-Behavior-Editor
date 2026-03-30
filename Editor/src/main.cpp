#include <QApplication>
#include "attributesEditor.hpp"
#include "styleManager.hpp"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    StyleManager styles;
    styles.setDefaultStyle(&app);

    AttributesEditor editor;
    editor.show();

    editor.setupScene();
    app.exec();
    editor.serializeEditorToDisk();

    return 0;
}