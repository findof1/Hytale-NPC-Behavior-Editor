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
#include <memory>

#include "typeUtils.hpp"
#include "types.hpp"
#include <qmainwindow.h>
#include "vectorEditorWidget.hpp"
#include "optionalWidget.hpp"
#include "collapsibleSectionWidget.hpp"
#include "stateTransitionEditor.hpp"
#include "nodeWidgets.hpp"
#include "nodes.hpp"
#include "serialization.hpp"
#include "print.hpp"

class AttributesEditor : public QWidget
{
public:
  SerializerValues serializer;

  AttributesEditor(QWidget *parent = nullptr);

  void loadAttributes(const General::Attributes &attr);

  QMenu *buildAddMenu(NodeScene *scene, QWidget *parent);

  General::Attributes getAttributes();

private:
  void printValues();

  NodeScene *scene;
  RootNode *rootNode;

  QSpinBox *maxHealthSpin;
  QLineEdit *appearanceEdit;
  QLineEdit *nameKeyEdit;
  VectorEditor *busyStatesEditor;
  VectorEditor *motionControllerEditor;

  QComboBox *motionCombo;
  OptionalWidget *motionComboOptional;

  VectorEditor *displayNamesEditor;
  OptionalWidget *displayNamesOptional;

  QLineEdit *opaqueBlockSet;
  OptionalWidget *opaqueBlockSetOptional;

  QSpinBox *knockbackScale;
  OptionalWidget *knockbackScaleOptional;

  QSpinBox *inventorySpin;
  OptionalWidget *inventorySpinOptional;

  QSpinBox *hotbarSize;
  OptionalWidget *hotbarSizeOptional;

  QSpinBox *offhandSlots;
  OptionalWidget *offhandSlotsOptional;

  VectorEditor *offhandItems;
  OptionalWidget *offhandItemsOptional;

  QLineEdit *possibleInventoryItems;
  OptionalWidget *possibleInventoryItemsOptional;

  QSpinBox *defaultOffhandSlot;
  OptionalWidget *defaultOffhandSlotOptional;

  QLineEdit *dropList;
  OptionalWidget *dropListOptional;

  QLineEdit *startState;
  OptionalWidget *startStateOptional;

  QLineEdit *defaultSubState;
  OptionalWidget *defaultSubStateOptional;

  QDoubleSpinBox *collisionDistance;
  OptionalWidget *collisionDistanceOptional;

  QLineEdit *combatConfig;
  OptionalWidget *combatConfigOptional;

  QCheckBox *invulnerableCheck;
  OptionalWidget *invulnerableCheckOptional;

  QCheckBox *pickupDropOnDeath;
  OptionalWidget *pickupDropOnDeathOptional;

  QLineEdit *deathInteraction;
  OptionalWidget *deathInteractionOptional;

  QComboBox *playerAttitudeCombo;
  OptionalWidget *playerAttitudeComboOptional;

  QComboBox *npcAttitudeCombo;
  OptionalWidget *npcAttitudeComboOptional;

  // todo: attitudeGroup
  // todo: itemAttitudeGroup

  QCheckBox *corpseStaysInFlock;
  OptionalWidget *corpseStaysInFlockOptional;

  // todo: instructions
  // todo: interactionInstruction
  // todo: deathInstruction

  VectorEditor *stateTransitionsEditor;
  OptionalWidget *stateTransitionsEditorOptional;

  QCheckBox *isMemory;
  OptionalWidget *isMemoryOptional;

  QLineEdit *memoriesCategory;
  OptionalWidget *memoriesCategoryOptional;

  QLineEdit *memoriesNameOverride;
  OptionalWidget *memoriesNameOverrideOptional;

  QDoubleSpinBox *spawnLockTime;
  OptionalWidget *spawnLockTimeOptional;
};