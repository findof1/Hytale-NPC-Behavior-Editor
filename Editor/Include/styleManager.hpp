#include <QApplication>
#include <QPalette>

class StyleManager
{
public:
  StyleManager()
  {
  }

  void setDefaultStyle(QApplication *app)
  {
    app->setStyle("Fusion");

    QPalette palette;

    palette.setColor(QPalette::Active, QPalette::Window, QColor("#1e1e1e"));
    palette.setColor(QPalette::Active, QPalette::Base, QColor("#2a2a2a"));
    palette.setColor(QPalette::Active, QPalette::AlternateBase, QColor("#242424"));

    palette.setColor(QPalette::Active, QPalette::Text, QColor("#ffffff"));
    palette.setColor(QPalette::Active, QPalette::WindowText, QColor("#ffffff"));
    palette.setColor(QPalette::Active, QPalette::ButtonText, QColor("#ffffff"));
    palette.setColor(QPalette::Active, QPalette::PlaceholderText, QColor("#888888"));

    palette.setColor(QPalette::Active, QPalette::Button, QColor("#2d2d2d"));

    palette.setColor(QPalette::Active, QPalette::Highlight, QColor("#3a82f7"));
    palette.setColor(QPalette::Active, QPalette::HighlightedText, QColor("#ffffff"));

    palette.setColor(QPalette::Active, QPalette::Link, QColor("#3a82f7"));
    palette.setColor(QPalette::Active, QPalette::LinkVisited, QColor("#a57aff"));

    palette.setColor(QPalette::Active, QPalette::ToolTipBase, QColor("#2a2a2a"));
    palette.setColor(QPalette::Active, QPalette::ToolTipText, QColor("#ffffff"));

    palette.setColor(QPalette::Active, QPalette::BrightText, QColor("#ff5555"));
    palette.setColor(QPalette::Active, QPalette::Accent, QColor("#3a82f7"));

    palette.setColor(QPalette::Inactive, QPalette::Window, palette.color(QPalette::Active, QPalette::Window));
    palette.setColor(QPalette::Inactive, QPalette::Base, palette.color(QPalette::Active, QPalette::Base));
    palette.setColor(QPalette::Inactive, QPalette::AlternateBase, palette.color(QPalette::Active, QPalette::AlternateBase));

    palette.setColor(QPalette::Inactive, QPalette::Text, palette.color(QPalette::Active, QPalette::Text));
    palette.setColor(QPalette::Inactive, QPalette::WindowText, palette.color(QPalette::Active, QPalette::WindowText));
    palette.setColor(QPalette::Inactive, QPalette::ButtonText, palette.color(QPalette::Active, QPalette::ButtonText));
    palette.setColor(QPalette::Inactive, QPalette::PlaceholderText, palette.color(QPalette::Active, QPalette::PlaceholderText));

    palette.setColor(QPalette::Inactive, QPalette::Button, palette.color(QPalette::Active, QPalette::Button));

    palette.setColor(QPalette::Inactive, QPalette::Highlight, palette.color(QPalette::Active, QPalette::Highlight));
    palette.setColor(QPalette::Inactive, QPalette::HighlightedText, palette.color(QPalette::Active, QPalette::HighlightedText));

    palette.setColor(QPalette::Inactive, QPalette::Link, palette.color(QPalette::Active, QPalette::Link));
    palette.setColor(QPalette::Inactive, QPalette::LinkVisited, palette.color(QPalette::Active, QPalette::LinkVisited));

    palette.setColor(QPalette::Inactive, QPalette::ToolTipBase, palette.color(QPalette::Active, QPalette::ToolTipBase));
    palette.setColor(QPalette::Inactive, QPalette::ToolTipText, palette.color(QPalette::Active, QPalette::ToolTipText));

    palette.setColor(QPalette::Disabled, QPalette::Window, QColor("#1e1e1e"));
    palette.setColor(QPalette::Disabled, QPalette::Base, QColor("#252525"));
    palette.setColor(QPalette::Disabled, QPalette::AlternateBase, QColor("#202020"));

    palette.setColor(QPalette::Disabled, QPalette::Text, QColor("#777777"));
    palette.setColor(QPalette::Disabled, QPalette::WindowText, QColor("#777777"));
    palette.setColor(QPalette::Disabled, QPalette::ButtonText, QColor("#777777"));
    palette.setColor(QPalette::Disabled, QPalette::PlaceholderText, QColor("#555555"));

    palette.setColor(QPalette::Disabled, QPalette::Button, QColor("#2a2a2a"));

    palette.setColor(QPalette::Disabled, QPalette::Highlight, QColor("#444444"));
    palette.setColor(QPalette::Disabled, QPalette::HighlightedText, QColor("#aaaaaa"));

    palette.setColor(QPalette::Disabled, QPalette::ToolTipBase, QColor("#2a2a2a"));
    palette.setColor(QPalette::Disabled, QPalette::ToolTipText, QColor("#777777"));

    app->setPalette(palette);

    app->setStyleSheet(R"()");
  }
};