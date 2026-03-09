#include <QApplication>
#include "attributesEditor.hpp"

int main(int argc, char **argv)
{
  QApplication app(argc, argv);

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