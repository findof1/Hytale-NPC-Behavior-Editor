#include <QApplication>
#include "attributesEditor.hpp"

int main(int argc, char **argv)
{
  QApplication app(argc, argv);

  QPalette darkPalette;
  darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
  darkPalette.setColor(QPalette::WindowText, Qt::white);
  darkPalette.setColor(QPalette::Base, QColor(42, 42, 42));
  darkPalette.setColor(QPalette::AlternateBase, QColor(66, 66, 66));
  darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
  darkPalette.setColor(QPalette::ToolTipText, Qt::white);
  darkPalette.setColor(QPalette::Text, Qt::white);
  darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
  darkPalette.setColor(QPalette::ButtonText, Qt::white);
  darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
  darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
  darkPalette.setColor(QPalette::HighlightedText, Qt::black);

  app.setPalette(darkPalette);

  // Make sure all widgets automatically inherit the palette
  app.setStyleSheet(R"(
    * {
        background: #1f1f1f;
        background-color: #242424;
        padding: 3px;
    }

    QTabWidget, QFormLayout, QScrollArea {
        background-color: #353535;
        color: #ffffff; 
        border: 1px solid #1a1a1a;   
    }

    QTabBar::tab {
        background-color: #353535;
        color: #ffffff;
        border: 1px solid #1a1a1a;
        padding: 3px 6px;
    }

    QTabBar::tab:selected {
        background-color: #454545;
    }

    QTabBar::tab:disabled {
        background-color: #2a2a2a;
        color: #777777;
        border: 1px solid #1a1a1a;
    }

    QLineEdit, QTextEdit, QPlainTextEdit {
        background-color: #353535;
        color: #ffffff;
        border: 1px solid #1a1a1a;   
    }

    QLineEdit:disabled, QTextEdit:disabled, QPlainTextEdit:disabled {
        background-color: #2a2a2a;
        color: #777777;
        border: 1px solid #1a1a1a;
    }

    QComboBox {
        background-color: #353535;
        color: #ffffff;
        border: 1px solid #1a1a1a;   
    }

    QComboBox:disabled {
        background-color: #2a2a2a;
        color: #777777;
        border: 1px solid #1a1a1a;
    }

    QComboBox QAbstractItemView {
        background-color: #353535;
        selection-background-color: #2a82da;
        color: #ffffff;
        border: 2px solid #1a1a1a;   
    }

    QPushButton, QRadioButton {
        color: #ffffff;   
        background-color: #353535; 
        background: none; 
        border: 1px solid #1a1a1a;       
    }

    QPushButton:disabled, QRadioButton:disabled {
        color: #777777;
        background-color: #2a2a2a;
        border: 1px solid #1a1a1a;
    }

    QCheckBox {
        color: #ffffff;   
        background-color: #353535; 
        background: none;   
    }

    QCheckBox:disabled {
        color: #777777;
    }

    QListWidget {
        color: #ffffff;   
        background-color: #353535; 
        background: none;   
        border: 3px solid #1a1a1a;  
    }

    QListWidget:disabled {
        color: #777777;
        background-color: #2a2a2a;
    }

    QPushButton, QCheckBox, QRadioButton, QLineEdit, QTextEdit, QComboBox, QListWidget {
        border-radius: 6px;
    }
)");

  AttributesEditor editor;
  editor.show();

  General::Attributes attr;
  attr.requiredAttributes.maxHealth = 100;
  attr.requiredAttributes.appearance = "Deer_Stag";
  attr.requiredAttributes.nameTranslationKey = "server.npcRoles.Template.name";
  attr.initialMotionController = "walk";
  attr.defaultPlayerAttitude = General::AttitudeFlag::Neutral;
  attr.defaultNPCAttitude = General::AttitudeFlag::Neutral;
  attr.invulnerable = false;
  attr.inventorySize = 5;

  editor.loadAttributes(attr);

  return app.exec();
}