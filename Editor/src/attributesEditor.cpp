#include "attributesEditor.hpp"
#include "jsonConverter.hpp"
#include "styleGlobals.hpp"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsPathItem>
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QMenu>
#include <QFileDialog>
#include <QLabel>
#include <fstream>

AttributesEditor::AttributesEditor(QString projectPath, QWidget *parent) : projectPath(projectPath), QWidget(parent)
{
  topBar = new QWidget;
  topBar->setFixedHeight(30);

  QColor windowColor = palette().color(QPalette::Window);
  QColor darkColor = windowColor.darker(110);
  QColor borderColor = windowColor.darker(130);

  QHBoxLayout *rowLayout = new QHBoxLayout(topBar);
  rowLayout->setContentsMargins(5, 0, 5, 0);
  rowLayout->setSpacing(5);

  settingsButton = new QPushButton("Settings");
  exportButton = new QPushButton("Export");
  settingsButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
  exportButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

  rowLayout->addWidget(settingsButton);
  rowLayout->addWidget(exportButton);
  rowLayout->addStretch();

  updateSpecialStyles();

  auto *layout = new QFormLayout(this);
  layout->setContentsMargins(0, 0, 10, 0);
  layout->setSpacing(0);

  layout->addRow(topBar);

  QWidget *spacer = new QWidget;
  spacer->setFixedHeight(17);
  spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  layout->addWidget(spacer);

  tabs = new QTabWidget;
  layout->addRow(tabs);

  initRequiredTab();
  initOptionalsTab();
  initStatesTab();
  initBehaviorsTab();

  connect(settingsButton, &QPushButton::clicked, this, [this]()
          {
    QDialog *popup = new QDialog(this);
    popup->setWindowTitle("Settings");
    popup->setModal(true);
    popup->setMinimumSize(300, 200);

    QVBoxLayout *layout = new QVBoxLayout(popup);
    layout->setContentsMargins(10, 10, 10, 10);
    layout->setSpacing(10);

    QLabel *themeLabel = new QLabel("Theme:", popup);
    QComboBox *themeSelector = new QComboBox(popup);
    themeSelector->addItem("Dark");
    themeSelector->addItem("Light");

    connect(themeSelector, &QComboBox::currentTextChanged, this, [this](const QString &text) {
        if (text == "Dark")
            gStyleManager.setDarkStyle();
        else
            gStyleManager.setLightStyle();

      updateSpecialStyles();
      qApp->processEvents();
    });
    
  connect(exportButton, &QPushButton::clicked, this, &AttributesEditor::printValues);

    layout->addWidget(themeLabel);
    layout->addWidget(themeSelector);
    layout->addStretch();

    popup->show(); });
}

void AttributesEditor::updateSpecialStyles()
{
  QPalette appPal = qApp->palette();

  QColor bg = appPal.color(QPalette::Window).darker(110);
  QColor border = appPal.color(QPalette::Window).darker(130);
  topBar->setStyleSheet(QString("background-color: %1; border-bottom: 1px solid %2;")
                            .arg(bg.name())
                            .arg(border.name()));

  QColor textColor = appPal.color(QPalette::ButtonText);
  QColor hoverColor = appPal.color(QPalette::Highlight);
  QColor pressedColor = hoverColor.darker(120);

  QString buttonStyle = QString(
                            "QPushButton {"
                            "  padding: 0px 10px;"
                            "  border: none;"
                            "  background-color: transparent;"
                            "  color: %1;"
                            "} "
                            "QPushButton:hover {"
                            "  background-color: %2;"
                            "} "
                            "QPushButton:pressed {"
                            "  background-color: %3;"
                            "}")
                            .arg(textColor.name())
                            .arg(hoverColor.name())
                            .arg(pressedColor.name());

  settingsButton->setStyleSheet(buttonStyle);
  exportButton->setStyleSheet(buttonStyle);
}

void AttributesEditor::initRequiredTab()
{
  auto *requiredTab = new QWidget;
  auto *requiredTabLayout = new QVBoxLayout(requiredTab);
  requiredTabLayout->setContentsMargins(0, 0, 0, 0);

  auto *requiredFormContainer = new QWidget;
  auto *requiredForm = new QFormLayout(requiredFormContainer);

  auto *requiredScroll = new QScrollArea;
  requiredScroll->setWidgetResizable(true);
  requiredScroll->setFrameShape(QFrame::NoFrame);
  requiredScroll->setWidget(requiredFormContainer);

  requiredTabLayout->addWidget(requiredScroll);

  tabs->addTab(requiredTab, "Required Attributes");

  maxHealthSpin = new QSpinBox;
  maxHealthSpin->setRange(1, 10000);
  requiredForm->addRow("Max Health:", maxHealthSpin);

  appearanceEdit = new QLineEdit;
  requiredForm->addRow("Appearance:", appearanceEdit);

  nameKeyEdit = new QLineEdit;
  requiredForm->addRow("Name Translation Key:", nameKeyEdit);

  busyStatesEditor = new VectorEditor(
      []() -> QWidget *
      {
        return new QLineEdit();
      });
  requiredForm->addRow("Busy States:", busyStatesEditor);

  motionControllerEditor = new VectorEditor(
      []() -> QWidget *
      {
        QComboBox *selector = new QComboBox;
        selector->addItems({"walk", "fly", "dive"});
        return selector;
      });
  requiredForm->addRow("Motion Controllers:", motionControllerEditor);
}

void AttributesEditor::initOptionalsTab()
{
  auto *optionalTab = new QWidget;
  auto *optionalTabLayout = new QVBoxLayout(optionalTab);
  optionalTabLayout->setContentsMargins(0, 0, 0, 0);

  auto *formContainer = new QWidget;
  auto *optionalForm = new QFormLayout(formContainer);

  auto *scroll = new QScrollArea;
  scroll->setWidgetResizable(true);
  scroll->setFrameShape(QFrame::NoFrame);
  scroll->setWidget(formContainer);

  optionalTabLayout->addWidget(scroll);

  tabs->addTab(optionalTab, "Optional Attributes");

  motionCombo = new QComboBox;
  motionCombo->addItems({"walk", "fly", "dive"});
  motionComboOptional = new OptionalWidget(motionCombo);
  optionalForm->addRow("Initial Motion Controller:", motionComboOptional);

  displayNamesEditor = new VectorEditor(
      []() -> QWidget *
      {
        return new QLineEdit();
      });
  displayNamesOptional = new OptionalWidget(displayNamesEditor);
  optionalForm->addRow("Display Names:", displayNamesOptional);

  opaqueBlockSet = new QLineEdit;
  opaqueBlockSetOptional = new OptionalWidget(opaqueBlockSet);
  optionalForm->addRow("Opaque Block Set:", opaqueBlockSetOptional);

  knockbackScale = new QSpinBox;
  knockbackScale->setRange(0, 1000);
  knockbackScaleOptional = new OptionalWidget(knockbackScale);
  optionalForm->addRow("Knockback Scale:", knockbackScaleOptional);

  inventorySpin = new QSpinBox;
  inventorySpin->setRange(0, 36);
  inventorySpinOptional = new OptionalWidget(inventorySpin);
  optionalForm->addRow("Inventory Size:", inventorySpinOptional);

  hotbarSize = new QSpinBox;
  hotbarSize->setRange(0, 9);
  hotbarSizeOptional = new OptionalWidget(hotbarSize);
  optionalForm->addRow("Hotbar Size:", hotbarSizeOptional);

  offhandSlots = new QSpinBox;
  offhandSlots->setRange(0, 4);
  offhandSlotsOptional = new OptionalWidget(offhandSlots);
  optionalForm->addRow("Offhand Slots:", offhandSlotsOptional);

  offhandItems = new VectorEditor(
      []() -> QWidget *
      {
        return new QLineEdit;
      });
  offhandItemsOptional = new OptionalWidget(offhandItems);
  optionalForm->addRow("Offhand Items:", offhandItemsOptional);

  possibleInventoryItems = new QLineEdit;
  possibleInventoryItemsOptional = new OptionalWidget(possibleInventoryItems);
  optionalForm->addRow("Possible Inventory Items:", possibleInventoryItemsOptional);

  defaultOffhandSlot = new QSpinBox;
  defaultOffhandSlot->setRange(0, 4);
  defaultOffhandSlotOptional = new OptionalWidget(defaultOffhandSlot);
  optionalForm->addRow("Default Offhand Slot:", defaultOffhandSlotOptional);

  dropList = new QLineEdit;
  dropListOptional = new OptionalWidget(dropList);
  optionalForm->addRow("Drop List:", dropListOptional);

  collisionDistance = new QDoubleSpinBox;
  collisionDistance->setRange(0.0, 1000.0);
  collisionDistance->setDecimals(3);
  collisionDistanceOptional = new OptionalWidget(collisionDistance);
  optionalForm->addRow("Collision Distance:", collisionDistanceOptional);

  combatConfig = new QLineEdit;
  combatConfigOptional = new OptionalWidget(combatConfig);
  optionalForm->addRow("Combat Config:", combatConfigOptional);

  invulnerableCheck = new QCheckBox;
  invulnerableCheckOptional = new OptionalWidget(invulnerableCheck);
  optionalForm->addRow("Invulnerable:", invulnerableCheckOptional);

  pickupDropOnDeath = new QCheckBox;
  pickupDropOnDeathOptional = new OptionalWidget(pickupDropOnDeath);
  optionalForm->addRow("Pickup Drop On Death:", pickupDropOnDeathOptional);

  deathInteraction = new QLineEdit;
  deathInteractionOptional = new OptionalWidget(deathInteraction);
  optionalForm->addRow("Death Interaction:", deathInteractionOptional);

  playerAttitudeCombo = new QComboBox;
  playerAttitudeCombo->addItems({"Hostile", "Revered", "Friendly", "Ignore", "Neutral"});
  playerAttitudeComboOptional = new OptionalWidget(playerAttitudeCombo);
  optionalForm->addRow("Default Player Attitude:", playerAttitudeComboOptional);

  npcAttitudeCombo = new QComboBox;
  npcAttitudeCombo->addItems({"Hostile", "Revered", "Friendly", "Ignore", "Neutral"});
  npcAttitudeComboOptional = new OptionalWidget(npcAttitudeCombo);
  optionalForm->addRow("Default NPC Attitude:", npcAttitudeComboOptional);

  corpseStaysInFlock = new QCheckBox;
  corpseStaysInFlockOptional = new OptionalWidget(corpseStaysInFlock);
  optionalForm->addRow("Corpse Stays In Flock:", corpseStaysInFlockOptional);

  isMemory = new QCheckBox;
  isMemoryOptional = new OptionalWidget(isMemory);
  optionalForm->addRow("Is Memory:", isMemoryOptional);

  memoriesCategory = new QLineEdit;
  memoriesCategoryOptional = new OptionalWidget(memoriesCategory);
  optionalForm->addRow("Memories Category:", memoriesCategoryOptional);

  memoriesNameOverride = new QLineEdit;
  memoriesNameOverrideOptional = new OptionalWidget(memoriesNameOverride);
  optionalForm->addRow("Memories Name Override:", memoriesNameOverrideOptional);

  spawnLockTime = new QDoubleSpinBox;
  spawnLockTime->setRange(0.0, 10000.0);
  spawnLockTime->setDecimals(3);
  spawnLockTimeOptional = new OptionalWidget(spawnLockTime);
  optionalForm->addRow("Spawn Lock Time:", spawnLockTimeOptional);
}

void AttributesEditor::initStatesTab()
{
  auto *statesTab = new QWidget;
  auto *statesTabLayout = new QVBoxLayout(statesTab);
  statesTabLayout->setContentsMargins(0, 0, 0, 0);

  auto *statesFormContainer = new QWidget;
  auto *statesForm = new QFormLayout(statesFormContainer);

  auto *statesScroll = new QScrollArea;
  statesScroll->setWidgetResizable(true);
  statesScroll->setFrameShape(QFrame::NoFrame);
  statesScroll->setWidget(statesFormContainer);

  statesTabLayout->addWidget(statesScroll);

  tabs->addTab(statesTab, "Entity States");

  startState = new QLineEdit;
  startStateOptional = new OptionalWidget(startState);
  statesForm->addRow("Start State:", startStateOptional);

  defaultSubState = new QLineEdit;
  defaultSubStateOptional = new OptionalWidget(defaultSubState);
  statesForm->addRow("Default Sub State:", defaultSubStateOptional);

  stateTransitionsEditor = new VectorEditor(
      []() -> QWidget *
      {
        return new StateTransitionEditor();
      });
  stateTransitionsEditorOptional = new OptionalWidget(stateTransitionsEditor);
  statesForm->addRow("State Transitions:", stateTransitionsEditorOptional);
}

void AttributesEditor::initBehaviorsTab()
{
  auto *instructionsTab = new QWidget;
  auto *instructionsTabLayout = new QVBoxLayout(instructionsTab);
  instructionsTabLayout->setContentsMargins(0, 0, 0, 0);

  tabs->addTab(instructionsTab, "Behavior Editor");

  scene = new NodeScene(this);
  scene->setSceneRect(-500, -500, 1000, 1000);
  scene->initNodeFactory();

  auto *topBar = new QWidget;
  auto *topBarLayout = new QHBoxLayout(topBar);
  topBarLayout->setContentsMargins(4, 4, 4, 4);

  auto *addButton = new QToolButton;
  addButton->setText("Add Node   ");
  addButton->setPopupMode(QToolButton::InstantPopup);

  QMenu *addMenu = buildAddMenu(scene, addButton);
  addButton->setMenu(addMenu);

  topBarLayout->addWidget(addButton);
  topBarLayout->addStretch();

  instructionsTabLayout->addWidget(topBar);

  auto *view = new NodeView();
  view->setScene(scene);
  view->setRenderHint(QPainter::Antialiasing);
  view->setDragMode(QGraphicsView::RubberBandDrag);
  view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  view->setMinimumSize(400, 300);
  view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  instructionsTabLayout->addWidget(view);
}

void AttributesEditor::setupScene()
{
  bool res = deserializeEditorFromDisk();
  if (!res)
  {
    General::Attributes attr;
    attr.requiredAttributes.maxHealth = 100;
    attr.requiredAttributes.appearance = "Deer_Stag";
    attr.requiredAttributes.nameTranslationKey = "server.npcRoles.Template.name";
    attr.initialMotionController = "walk";
    attr.defaultPlayerAttitude = General::AttitudeFlag::Neutral;
    attr.defaultNPCAttitude = General::AttitudeFlag::Neutral;
    attr.invulnerable = false;
    attr.inventorySize = 5;

    loadAttributes(attr);

    rootNode = new RootNode(scene);
    rootNode->id = scene->generateId();
    rootNode->setPos(0, 0);
    scene->addItem(rootNode);
    scene->nodes.emplace_back(rootNode);
  }
}

void AttributesEditor::spawnNodesDebug()
{
  int x = 50;
  int y = 50;
  int w = 325;
  int h = 700;
  int nW = 14;
  int indexX = 1;
  int indexY = 0;
  for (auto it = scene->nodeFactory.begin(); it != scene->nodeFactory.end(); ++it)
  {
    const QString &key = it.key();
    auto &factory = it.value();

    // if (!key.contains("Sensors"))
    //   continue;

    auto node = factory(scene);
    node->setPos(x + indexX * w, y + indexY * h);
    scene->addItem(node.get());
    scene->nodes.emplace_back(node);

    indexX++;

    if (indexX > nW)
    {
      indexY++;
      indexX = 0;
    }
  }
}

QMenu *AttributesEditor::buildAddMenu(NodeScene *scene, QWidget *parent)
{
  QMenu *rootMenu = new QMenu(parent);

  QMap<QString, QMenu *> subMenus;

  for (auto it = scene->nodeFactory.begin(); it != scene->nodeFactory.end(); ++it)
  {
    QString fullPath = it.key();
    QStringList parts = fullPath.split("/");

    QMenu *currentMenu = rootMenu;
    QString accumulated;

    for (int i = 0; i < parts.size() - 1; ++i)
    {
      accumulated += parts[i];

      if (!subMenus.contains(accumulated))
      {
        subMenus[accumulated] = currentMenu->addMenu(parts[i]);
      }

      currentMenu = subMenus[accumulated];
      accumulated += "/";
    }

    QAction *action = currentMenu->addAction(parts.last());

    QObject::connect(action, &QAction::triggered, parent, [scene, fullPath]()
                     { scene->spawnNode(fullPath, {0, 0}); });
  }

  return rootMenu;
}

void AttributesEditor::loadAttributes(const General::Attributes &attr)
{
  maxHealthSpin->setValue(attr.requiredAttributes.maxHealth);
  appearanceEdit->setText(QString::fromStdString(attr.requiredAttributes.appearance));
  nameKeyEdit->setText(QString::fromStdString(attr.requiredAttributes.nameTranslationKey));
  if (attr.initialMotionController)
    motionCombo->setCurrentText(QString::fromStdString(*attr.initialMotionController));
  if (attr.defaultPlayerAttitude)
    playerAttitudeCombo->setCurrentText(attitudeFlagToString(*attr.defaultPlayerAttitude));
  if (attr.defaultNPCAttitude)
    npcAttitudeCombo->setCurrentText(attitudeFlagToString(*attr.defaultNPCAttitude));
  if (attr.invulnerable)
    invulnerableCheck->setChecked(*attr.invulnerable);
  if (attr.inventorySize)
    inventorySpin->setValue(*attr.inventorySize);
}

void AttributesEditor::serializeEditorToDisk()
{
  nlohmann::json j;

  j["serializationVersion"] = "1";

  j["scene"] = scene->serializeScene();

  j["maxHealth"] = maxHealthSpin->value();
  j["appearance"] = appearanceEdit->text().toStdString();
  j["nameKey"] = nameKeyEdit->text().toStdString();

  j["busyStates"] = serializeVectorEditor(busyStatesEditor);
  j["motionController"] = serializeVectorEditor(motionControllerEditor);

  j["motion"] = motionCombo->currentText().toStdString();
  j["motionOptional"] = motionComboOptional->isEnabled();

  j["displayNames"] = serializeVectorEditor(displayNamesEditor);
  j["displayNamesOptional"] = displayNamesOptional->isEnabled();

  j["opaqueBlockSet"] = opaqueBlockSet->text().toStdString();
  j["opaqueBlockSetOptional"] = opaqueBlockSetOptional->isEnabled();

  j["knockbackScale"] = knockbackScale->value();
  j["knockbackScaleOptional"] = knockbackScaleOptional->isEnabled();

  j["inventory"] = inventorySpin->value();
  j["inventoryOptional"] = inventorySpinOptional->isEnabled();

  j["hotbarSize"] = hotbarSize->value();
  j["hotbarSizeOptional"] = hotbarSizeOptional->isEnabled();

  j["offhandSlots"] = offhandSlots->value();
  j["offhandSlotsOptional"] = offhandSlotsOptional->isEnabled();

  j["offhandItems"] = serializeVectorEditor(offhandItems);
  j["offhandItemsOptional"] = offhandItemsOptional->isEnabled();

  j["possibleInventoryItems"] = possibleInventoryItems->text().toStdString();
  j["possibleInventoryItemsOptional"] = possibleInventoryItemsOptional->isEnabled();

  j["defaultOffhandSlot"] = defaultOffhandSlot->value();
  j["defaultOffhandSlotOptional"] = defaultOffhandSlotOptional->isEnabled();

  j["dropList"] = dropList->text().toStdString();
  j["dropListOptional"] = dropListOptional->isEnabled();

  j["startState"] = startState->text().toStdString();
  j["startStateOptional"] = startStateOptional->isEnabled();

  j["defaultSubState"] = defaultSubState->text().toStdString();
  j["defaultSubStateOptional"] = defaultSubStateOptional->isEnabled();

  j["collisionDistance"] = collisionDistance->value();
  j["collisionDistanceOptional"] = collisionDistanceOptional->isEnabled();

  j["combatConfig"] = combatConfig->text().toStdString();
  j["combatConfigOptional"] = combatConfigOptional->isEnabled();

  j["invulnerable"] = invulnerableCheck->isChecked();
  j["invulnerableOptional"] = invulnerableCheckOptional->isEnabled();

  j["pickupDropOnDeath"] = pickupDropOnDeath->isChecked();
  j["pickupDropOnDeathOptional"] = pickupDropOnDeathOptional->isEnabled();

  j["deathInteraction"] = deathInteraction->text().toStdString();
  j["deathInteractionOptional"] = deathInteractionOptional->isEnabled();

  j["playerAttitude"] = playerAttitudeCombo->currentText().toStdString();
  j["playerAttitudeOptional"] = playerAttitudeComboOptional->isEnabled();

  j["npcAttitude"] = npcAttitudeCombo->currentText().toStdString();
  j["npcAttitudeOptional"] = npcAttitudeComboOptional->isEnabled();

  j["corpseStaysInFlock"] = corpseStaysInFlock->isChecked();
  j["corpseStaysInFlockOptional"] = corpseStaysInFlockOptional->isEnabled();

  // j["stateTransitions"] = stateTransitionsEditor->toJson();
  j["stateTransitionsOptional"] = stateTransitionsEditorOptional->isEnabled();

  j["isMemory"] = isMemory->isChecked();
  j["isMemoryOptional"] = isMemoryOptional->isEnabled();

  j["memoriesCategory"] = memoriesCategory->text().toStdString();
  j["memoriesCategoryOptional"] = memoriesCategoryOptional->isEnabled();

  j["memoriesNameOverride"] = memoriesNameOverride->text().toStdString();
  j["memoriesNameOverrideOptional"] = memoriesNameOverrideOptional->isEnabled();

  j["spawnLockTime"] = spawnLockTime->value();
  j["spawnLockTimeOptional"] = spawnLockTimeOptional->isEnabled();

  QString sceneFilePath = QDir(projectPath).filePath("scene.json");
  std::ofstream file(sceneFilePath.toStdString());
  file << j.dump(4);
}

// returns true if successfully deserialized, returns false if failed to find scene.json file
bool AttributesEditor::deserializeEditorFromDisk()
{
  nlohmann::json j;

  QString sceneFilePath = QDir(projectPath).filePath("scene.json");
  std::ifstream file(sceneFilePath.toStdString());
  if (!file.is_open())
  {
    return false;
  }

  file >> j;
  file.close();

  if (j.contains("scene"))
    rootNode = scene->deserializeScene(j["scene"]);

  if (j.contains("maxHealth"))
    maxHealthSpin->setValue(j["maxHealth"]);

  if (j.contains("appearance"))
    appearanceEdit->setText(QString::fromStdString(j["appearance"]));

  if (j.contains("nameKey"))
    nameKeyEdit->setText(QString::fromStdString(j["nameKey"]));

  if (j.contains("busyStates"))
    deserializeVectorEditor(busyStatesEditor, j["busyStates"]);

  if (j.contains("motionController"))
    deserializeVectorEditor(motionControllerEditor, j["motionController"]);

  if (j.contains("motion"))
    motionCombo->setCurrentText(QString::fromStdString(j["motion"]));

  if (j.contains("motionOptional"))
    motionComboOptional->setEnabledValue(j["motionOptional"]);

  if (j.contains("displayNames"))
    deserializeVectorEditor(displayNamesEditor, j["displayNames"]);

  if (j.contains("displayNamesOptional"))
    displayNamesOptional->setEnabledValue(j["displayNamesOptional"]);

  if (j.contains("opaqueBlockSet"))
    opaqueBlockSet->setText(QString::fromStdString(j["opaqueBlockSet"]));

  if (j.contains("opaqueBlockSetOptional"))
    opaqueBlockSetOptional->setEnabledValue(j["opaqueBlockSetOptional"]);

  if (j.contains("knockbackScale"))
    knockbackScale->setValue(j["knockbackScale"]);

  if (j.contains("knockbackScaleOptional"))
    knockbackScaleOptional->setEnabledValue(j["knockbackScaleOptional"]);

  if (j.contains("inventory"))
    inventorySpin->setValue(j["inventory"]);

  if (j.contains("inventoryOptional"))
    inventorySpinOptional->setEnabledValue(j["inventoryOptional"]);

  if (j.contains("hotbarSize"))
    hotbarSize->setValue(j["hotbarSize"]);

  if (j.contains("hotbarSizeOptional"))
    hotbarSizeOptional->setEnabledValue(j["hotbarSizeOptional"]);

  if (j.contains("offhandSlots"))
    offhandSlots->setValue(j["offhandSlots"]);

  if (j.contains("offhandSlotsOptional"))
    offhandSlotsOptional->setEnabledValue(j["offhandSlotsOptional"]);

  if (j.contains("offhandItems"))
    deserializeVectorEditor(offhandItems, j["offhandItems"]);

  if (j.contains("offhandItemsOptional"))
    offhandItemsOptional->setEnabledValue(j["offhandItemsOptional"]);

  if (j.contains("possibleInventoryItems"))
    possibleInventoryItems->setText(QString::fromStdString(j["possibleInventoryItems"]));

  if (j.contains("possibleInventoryItemsOptional"))
    possibleInventoryItemsOptional->setEnabledValue(j["possibleInventoryItemsOptional"]);

  if (j.contains("defaultOffhandSlot"))
    defaultOffhandSlot->setValue(j["defaultOffhandSlot"]);

  if (j.contains("defaultOffhandSlotOptional"))
    defaultOffhandSlotOptional->setEnabledValue(j["defaultOffhandSlotOptional"]);

  if (j.contains("dropList"))
    dropList->setText(QString::fromStdString(j["dropList"]));

  if (j.contains("dropListOptional"))
    dropListOptional->setEnabledValue(j["dropListOptional"]);

  if (j.contains("startState"))
    startState->setText(QString::fromStdString(j["startState"]));

  if (j.contains("startStateOptional"))
    startStateOptional->setEnabledValue(j["startStateOptional"]);

  if (j.contains("defaultSubState"))
    defaultSubState->setText(QString::fromStdString(j["defaultSubState"]));

  if (j.contains("defaultSubStateOptional"))
    defaultSubStateOptional->setEnabledValue(j["defaultSubStateOptional"]);

  if (j.contains("collisionDistance"))
    collisionDistance->setValue(j["collisionDistance"]);

  if (j.contains("collisionDistanceOptional"))
    collisionDistanceOptional->setEnabledValue(j["collisionDistanceOptional"]);

  if (j.contains("combatConfig"))
    combatConfig->setText(QString::fromStdString(j["combatConfig"]));

  if (j.contains("combatConfigOptional"))
    combatConfigOptional->setEnabledValue(j["combatConfigOptional"]);

  if (j.contains("invulnerable"))
    invulnerableCheck->setChecked(j["invulnerable"]);

  if (j.contains("invulnerableOptional"))
    invulnerableCheckOptional->setEnabledValue(j["invulnerableOptional"]);

  if (j.contains("pickupDropOnDeath"))
    pickupDropOnDeath->setChecked(j["pickupDropOnDeath"]);

  if (j.contains("pickupDropOnDeathOptional"))
    pickupDropOnDeathOptional->setEnabledValue(j["pickupDropOnDeathOptional"]);

  if (j.contains("deathInteraction"))
    deathInteraction->setText(QString::fromStdString(j["deathInteraction"]));

  if (j.contains("deathInteractionOptional"))
    deathInteractionOptional->setEnabledValue(j["deathInteractionOptional"]);

  if (j.contains("playerAttitude"))
    playerAttitudeCombo->setCurrentText(QString::fromStdString(j["playerAttitude"]));

  if (j.contains("playerAttitudeOptional"))
    playerAttitudeComboOptional->setEnabledValue(j["playerAttitudeOptional"]);

  if (j.contains("npcAttitude"))
    npcAttitudeCombo->setCurrentText(QString::fromStdString(j["npcAttitude"]));

  if (j.contains("npcAttitudeOptional"))
    npcAttitudeComboOptional->setEnabledValue(j["npcAttitudeOptional"]);

  if (j.contains("corpseStaysInFlock"))
    corpseStaysInFlock->setChecked(j["corpseStaysInFlock"]);

  if (j.contains("corpseStaysInFlockOptional"))
    corpseStaysInFlockOptional->setEnabledValue(j["corpseStaysInFlockOptional"]);

  // if (j.contains("stateTransitions"))
  //   stateTransitionsEditor->fromJson(j["stateTransitions"]);

  if (j.contains("stateTransitionsOptional"))
    stateTransitionsEditorOptional->setEnabledValue(j["stateTransitionsOptional"]);

  if (j.contains("isMemory"))
    isMemory->setChecked(j["isMemory"]);

  if (j.contains("isMemoryOptional"))
    isMemoryOptional->setEnabledValue(j["isMemoryOptional"]);

  if (j.contains("memoriesCategory"))
    memoriesCategory->setText(QString::fromStdString(j["memoriesCategory"]));

  if (j.contains("memoriesCategoryOptional"))
    memoriesCategoryOptional->setEnabledValue(j["memoriesCategoryOptional"]);

  if (j.contains("memoriesNameOverride"))
    memoriesNameOverride->setText(QString::fromStdString(j["memoriesNameOverride"]));

  if (j.contains("memoriesNameOverrideOptional"))
    memoriesNameOverrideOptional->setEnabledValue(j["memoriesNameOverrideOptional"]);

  if (j.contains("spawnLockTime"))
    spawnLockTime->setValue(j["spawnLockTime"]);

  if (j.contains("spawnLockTimeOptional"))
    spawnLockTimeOptional->setEnabledValue(j["spawnLockTimeOptional"]);

  return true;
}

General::Attributes AttributesEditor::getAttributes()
{
  General::Attributes attr;
  attr.requiredAttributes.maxHealth = maxHealthSpin->value();
  attr.requiredAttributes.appearance = appearanceEdit->text().toStdString();
  attr.requiredAttributes.nameTranslationKey = nameKeyEdit->text().toStdString();

  // serialize attr.requiredAttributes.motionControllerList
  for (int i = 0; i < motionControllerEditor->count(); i++)
  {
    QWidget *frame = motionControllerEditor->itemAt(i);

    QComboBox *combo = frame->findChild<QComboBox *>();
    if (!combo)
      continue;

    std::string type = combo->currentText().toStdString();

    if (type == "walk")
      attr.requiredAttributes.motionControllerList.push_back(std::make_unique<General::WalkMotionController>());
    else if (type == "fly")
      attr.requiredAttributes.motionControllerList.push_back(std::make_unique<General::FlyMotionController>());
    else if (type == "dive")
      attr.requiredAttributes.motionControllerList.push_back(std::make_unique<General::DiveMotionController>());
  }
  //

  // serialize attr.requiredAttributes.busyStates
  for (int i = 0; i < busyStatesEditor->count(); i++)
  {
    QWidget *frame = busyStatesEditor->itemAt(i);

    QLineEdit *line = frame->findChild<QLineEdit *>();
    if (!line)
      continue;

    attr.requiredAttributes.busyStates.push_back(line->text().toStdString());
  }
  //

  attr.instructions = serializeInstructions(&serializer, scene, rootNode);
  if (motionComboOptional->isEnabled())
  {
    attr.initialMotionController = motionCombo->currentText().toStdString();
  }

  if (displayNamesOptional->isEnabled())
  {
    std::vector<std::string> names;

    auto *editor = static_cast<VectorEditor *>(displayNamesOptional->editor);
    for (int i = 0; i < editor->count(); i++)
    {
      QWidget *frame = editor->itemAt(i);
      QLineEdit *line = frame->findChild<QLineEdit *>();
      if (line)
        names.push_back(line->text().toStdString());
    }

    attr.displayNames = names;
  }

  if (opaqueBlockSetOptional->isEnabled())
  {
    attr.opaqueBlockSet = opaqueBlockSet->text().toStdString();
  }

  if (knockbackScaleOptional->isEnabled())
  {
    attr.knockbackScale = knockbackScale->value();
  }

  if (inventorySpinOptional->isEnabled())
  {
    attr.inventorySize = inventorySpin->value();
  }

  if (hotbarSizeOptional->isEnabled())
  {
    attr.hotbarSize = hotbarSize->value();
  }

  if (offhandSlotsOptional->isEnabled())
  {
    attr.offhandSlots = offhandSlots->value();
  }

  if (offhandItemsOptional->isEnabled())
  {
    std::vector<std::string> items;

    auto *editor = static_cast<VectorEditor *>(offhandItemsOptional->editor);
    for (int i = 0; i < editor->count(); i++)
    {
      QWidget *frame = editor->itemAt(i);
      QLineEdit *line = frame->findChild<QLineEdit *>();
      if (line)
        items.push_back(line->text().toStdString());
    }

    attr.offhandItems = items;
  }

  if (possibleInventoryItemsOptional->isEnabled())
  {
    attr.possibleInventoryItems = possibleInventoryItems->text().toStdString();
  }

  if (defaultOffhandSlotOptional->isEnabled())
  {
    attr.defaultOffhandSlot = defaultOffhandSlot->value();
  }

  if (dropListOptional->isEnabled())
  {
    attr.dropList = dropList->text().toStdString();
  }

  if (collisionDistanceOptional->isEnabled())
  {
    attr.collisionDistance = collisionDistance->value();
  }

  if (combatConfigOptional->isEnabled())
  {
    attr.combatConfig = combatConfig->text().toStdString();
  }

  if (invulnerableCheckOptional->isEnabled())
  {
    attr.invulnerable = invulnerableCheck->isChecked();
  }

  if (pickupDropOnDeathOptional->isEnabled())
  {
    attr.pickupDropOnDeath = pickupDropOnDeath->isChecked();
  }

  if (deathInteractionOptional->isEnabled())
  {
    attr.deathInteraction = deathInteraction->text().toStdString();
  }

  if (playerAttitudeComboOptional->isEnabled())
  {
    attr.defaultPlayerAttitude = stringToAttitudeFlag(playerAttitudeCombo->currentText());
  }

  if (npcAttitudeComboOptional->isEnabled())
  {
    attr.defaultNPCAttitude = stringToAttitudeFlag(npcAttitudeCombo->currentText());
  }

  if (corpseStaysInFlockOptional->isEnabled())
  {
    attr.corpseStaysInFlock = corpseStaysInFlock->isChecked();
  }

  if (isMemoryOptional->isEnabled())
  {
    attr.isMemory = isMemory->isChecked();
  }

  if (memoriesCategoryOptional->isEnabled())
  {
    attr.memoriesCategory = memoriesCategory->text().toStdString();
  }

  if (memoriesNameOverrideOptional->isEnabled())
  {
    attr.memoriesNameOverride = memoriesNameOverride->text().toStdString();
  }

  if (spawnLockTimeOptional->isEnabled())
  {
    attr.spawnLockTime = spawnLockTime->value();
  }

  return attr;
}

void AttributesEditor::printValues()
{
  General::Attributes attr = getAttributes();

  // print(attr); //debug printer

  QString path = QFileDialog::getSaveFileName(
      nullptr,
      "Save JSON",
      "",
      "JSON Files (*.json)");

  if (path.isEmpty())
    return;

  nlohmann::json j;
  General::to_json(j, attr);

  std::ofstream file(path.toStdString());
  if (!file.is_open())
    return;

  file << j.dump(4);
}