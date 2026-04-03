#include "nodes.hpp"
#include <QComboBox>
#include "styleGlobals.hpp"

RootNode::RootNode(NodeScene *scene)
    : NodeItem("Root")
{
  deletable = false;
  addOutputSocket("Instructions", scene, true);
}

InstructionNode::InstructionNode(NodeScene *scene)
    : NodeItem("Instruction", true, 240)
{
  fieldsHeight = 250;
  addInputSocket("In", scene);
  addOutputSocket("Sensor", scene);
  addOutputSocket("Actions", scene);
  addOutputSocket("Instructions", scene, true);
  addOutputSocket("Body Motion", scene, true);
  addOutputSocket("Head Motion", scene, true);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  nameEdit = new QLineEdit;
  form->addRow("Name:", nameEdit);
  QWidget *label = form->labelForField(nameEdit);
  QColor textColor = gStyleManager.getCurrentStyle().nodeText;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  continueBox = new QCheckBox;
  continueBox->setStyleSheet("color: gray;");
  form->addRow("Continue:", continueBox);
  label = form->labelForField(continueBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  blockingBox = new QCheckBox;
  blockingBox->setStyleSheet("color: gray;");
  form->addRow("Actions Blocking:", blockingBox);
  label = form->labelForField(blockingBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  atomicBox = new QCheckBox;
  atomicBox->setStyleSheet("color: gray;");
  form->addRow("Actions Atomic:", atomicBox);
  label = form->labelForField(atomicBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  weightSpin = new QSpinBox;
  weightSpin->setMinimum(0);
  weightSpin->setMaximum(100000);
  weightSpin->setStyleSheet("color: gray;");
  form->addRow("Weight:", weightSpin);
  label = form->labelForField(weightSpin);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}
General::Instruction InstructionNode::serialize()
{
  General::Instruction data;

  data.name = nameEdit->text().toStdString();

  if (enabledBox->isChecked())
    data.enabled = true;

  if (continueBox->isChecked())
    data.cont = true;

  if (blockingBox->isChecked())
    data.actionsBlocking = true;

  if (atomicBox->isChecked())
    data.actionsAtomic = true;

  if (weightSpin->value() != 0)
    data.weight = static_cast<unsigned int>(weightSpin->value());

  return data;
}

CommentNode::CommentNode(NodeScene *scene)
    : NodeItem("Comment", true)
{
  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  nameEdit = new QLineEdit;
  form->addRow("Comment:", nameEdit);
  QWidget *label = form->labelForField(nameEdit);
  QColor textColor = gStyleManager.getCurrentStyle().nodeText;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

SensorNodes::AdjustPositionNode::AdjustPositionNode(NodeScene *scene)
    : NodeItem("AdjustPosition", true)
{
  fieldsHeight = 180;
  addInputSocket("In", scene);
  addOutputSocket("Sensor", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  offsetX = new QDoubleSpinBox;
  offsetX->setRange(-1e6, 1e6);
  offsetY = new QDoubleSpinBox;
  offsetY->setRange(-1e6, 1e6);
  offsetZ = new QDoubleSpinBox;
  offsetZ->setRange(-1e6, 1e6);
  form->addRow("Offset X:", offsetX);
  form->addRow("Offset Y:", offsetY);
  form->addRow("Offset Z:", offsetZ);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Sensor::AdjustPosition SensorNodes::AdjustPositionNode::serialize()
{
  General::Sensor::AdjustPosition data;

  data.offset.push_back(offsetX->value());
  data.offset.push_back(offsetY->value());
  data.offset.push_back(offsetZ->value());

  if (onceBox->isChecked())
    data.once = true;

  if (enabledBox->isChecked())
    data.enabled = true;

  return data;
}

SensorNodes::AgeNode::AgeNode(NodeScene *scene)
    : NodeItem("Age", true, 220)
{
  fieldsHeight = 160;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  ageMin = new QDoubleSpinBox;
  ageMin->setRange(0, 1e9);
  ageMax = new QDoubleSpinBox;
  ageMax->setRange(0, 1e9);
  form->addRow("Age Min:", ageMin);
  form->addRow("Age Max:", ageMax);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Sensor::Age SensorNodes::AgeNode::serialize()
{
  General::Sensor::Age data;

  data.ageRange.push_back(ageMin->value());
  data.ageRange.push_back(ageMax->value());

  if (onceBox->isChecked())
    data.once = true;

  if (enabledBox->isChecked())
    data.enabled = true;

  return data;
}

SensorNodes::AlarmNode::AlarmNode(NodeScene *scene)
    : NodeItem("Alarm", true)
{
  fieldsHeight = 180;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  nameEdit = new QLineEdit;
  form->addRow("Name:", nameEdit);
  QWidget *label = form->labelForField(nameEdit);
  QColor textColor = gStyleManager.getCurrentStyle().nodeText;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  stateCombo = new QComboBox;
  stateCombo->addItems({"Set", "Unset", "Passed"});
  form->addRow("State:", stateCombo);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  label = form->labelForField(onceBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  clearBox = new QCheckBox;
  form->addRow("Clear:", clearBox);
  label = form->labelForField(clearBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Sensor::Alarm SensorNodes::AlarmNode::serialize()
{
  General::Sensor::Alarm data;

  data.name = nameEdit->text().toStdString();

  switch (stateCombo->currentIndex())
  {
  case 0:
    data.state = General::Sensor::Alarm::AlarmFlag::Set;
    break;
  case 1:
    data.state = General::Sensor::Alarm::AlarmFlag::Unset;
    break;
  case 2:
    data.state = General::Sensor::Alarm::AlarmFlag::Passed;
    break;
  }

  if (onceBox->isChecked())
    data.once = true;

  if (enabledBox->isChecked())
    data.enabled = true;

  if (clearBox->isChecked())
    data.clear = true;

  return data;
}

SensorNodes::AndNode::AndNode(NodeScene *scene)
    : NodeItem("And", true, 265)
{
  fieldsHeight = 120;
  addInputSocket("In", scene);
  addOutputSocket("Sensors", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  autoUnlockTargetSlotEdit = new QLineEdit;
  form->addRow("Auto Unlock Target Slot:", autoUnlockTargetSlotEdit);
  label = form->labelForField(autoUnlockTargetSlotEdit);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Sensor::And SensorNodes::AndNode::serialize()
{
  General::Sensor::And data;

  std::string marker = autoUnlockTargetSlotEdit->text().toStdString();
  if (!marker.empty())
    data.autoUnlockTargetSlot = marker;

  if (onceBox->isChecked())
    data.once = true;

  if (enabledBox->isChecked())
    data.enabled = true;

  return data;
}

SensorNodes::AnimationNode::AnimationNode(NodeScene *scene)
    : NodeItem("Animation", true)
{
  fieldsHeight = 160;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  slotCombo = new QComboBox;
  slotCombo->addItems({"Status", "Action", "Face"});
  form->addRow("Slot:", slotCombo);

  animationEdit = new QLineEdit;
  form->addRow("Animation:", animationEdit);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Sensor::Animation SensorNodes::AnimationNode::serialize()
{
  General::Sensor::Animation data;

  data.animation = animationEdit->text().toStdString();

  switch (slotCombo->currentIndex())
  {
  case 0:
    data.slot = General::Sensor::Animation::AnimationFlag::Status;
    break;
  case 1:
    data.slot = General::Sensor::Animation::AnimationFlag::Action;
    break;
  case 2:
    data.slot = General::Sensor::Animation::AnimationFlag::Face;
    break;
  }

  if (onceBox->isChecked())
    data.once = true;

  if (enabledBox->isChecked())
    data.enabled = true;

  return data;
}

SensorNodes::AnyNode::AnyNode(NodeScene *scene)
    : NodeItem("Any", true)
{
  fieldsHeight = 100;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Sensor::Any SensorNodes::AnyNode::serialize()
{
  General::Sensor::Any data;

  if (onceBox->isChecked())
    data.once = true;

  if (enabledBox->isChecked())
    data.enabled = true;

  return data;
}

SensorNodes::BeaconNode::BeaconNode(NodeScene *scene)
    : NodeItem("Beacon", true, 260)
{
  fieldsHeight = 200;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  messageEdit = new QLineEdit;
  form->addRow("Message:", messageEdit);
  auto *label = form->labelForField(messageEdit);
  QColor textColor = gStyleManager.getCurrentStyle().nodeText;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  label = form->labelForField(onceBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  rangeSpin = new QDoubleSpinBox;
  rangeSpin->setRange(0, 1e6);
  form->addRow("Range:", rangeSpin);
  label = form->labelForField(rangeSpin);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  targetSlotEdit = new QLineEdit;
  form->addRow("Target Slot:", targetSlotEdit);
  label = form->labelForField(targetSlotEdit);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  consumeMessageBox = new QCheckBox;
  form->addRow("Consume Message:", consumeMessageBox);
  label = form->labelForField(consumeMessageBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Sensor::Beacon SensorNodes::BeaconNode::serialize()
{
  General::Sensor::Beacon data;

  data.message = messageEdit->text().toStdString();

  if (rangeSpin->value() != 0)
    data.range = rangeSpin->value();

  std::string marker = targetSlotEdit->text().toStdString();
  if (!marker.empty())
    data.targetSlot = marker;

  if (onceBox->isChecked())
    data.once = true;

  if (enabledBox->isChecked())
    data.enabled = true;

  if (consumeMessageBox->isChecked())
    data.consumeMessage = true;

  return data;
}

SensorNodes::BlockNode::BlockNode(NodeScene *scene)
    : NodeItem("Block", true, 260)
{
  fieldsHeight = 260;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  blocksEdit = new QLineEdit;
  form->addRow("Blocks:", blocksEdit);
  auto *label = form->labelForField(blocksEdit);
  QColor textColor = gStyleManager.getCurrentStyle().nodeText;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  rangeSpin = new QDoubleSpinBox;
  rangeSpin->setRange(0, 1e6);
  form->addRow("Range:", rangeSpin);
  label = form->labelForField(rangeSpin);
  textColor = gStyleManager.getCurrentStyle().nodeText;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  label = form->labelForField(onceBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  maxHeightSpin = new QDoubleSpinBox;
  maxHeightSpin->setRange(0, 1e6);
  form->addRow("Max Height:", maxHeightSpin);
  label = form->labelForField(maxHeightSpin);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  randomBox = new QCheckBox;
  form->addRow("Random:", randomBox);
  label = form->labelForField(randomBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  reserveBox = new QCheckBox;
  form->addRow("Reserve:", reserveBox);
  label = form->labelForField(reserveBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Sensor::Block SensorNodes::BlockNode::serialize()
{
  General::Sensor::Block data;

  data.blocks = blocksEdit->text().toStdString();

  data.range = rangeSpin->value();

  if (maxHeightSpin->value() != 0)
    data.maxHeight = maxHeightSpin->value();

  if (onceBox->isChecked())
    data.once = true;

  if (enabledBox->isChecked())
    data.enabled = true;

  if (randomBox->isChecked())
    data.random = true;

  if (reserveBox->isChecked())
    data.reserve = true;

  return data;
}

SensorNodes::BlockChangeNode::BlockChangeNode(NodeScene *scene)
    : NodeItem("BlockChange", true, 240)
{
  fieldsHeight = 250;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  rangeSpin = new QDoubleSpinBox;
  rangeSpin->setRange(0, 1e6);
  form->addRow("Range:", rangeSpin);

  searchTypeCombo = new QComboBox;
  searchTypeCombo->addItems({"NpcOnly", "PlayerFirst", "PlayerOnly", "NpcFirst"});
  form->addRow("Search Type:", searchTypeCombo);

  blockSetEdit = new QLineEdit;
  form->addRow("Block Set (Asset):", blockSetEdit);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  targetSlotEdit = new QLineEdit;
  form->addRow("Target Slot:", targetSlotEdit);
  label = form->labelForField(targetSlotEdit);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  eventTypeCombo = new QComboBox;
  eventTypeCombo->addItems({"(None)", "Destruction", "Interaction", "Damage"});
  form->addRow("Event Type:", eventTypeCombo);
  label = form->labelForField(eventTypeCombo);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Sensor::BlockChange SensorNodes::BlockChangeNode::serialize()
{
  General::Sensor::BlockChange data;

  data.blockSet = blockSetEdit->text().toStdString();

  if (onceBox->isChecked())
    data.once = true;

  if (enabledBox->isChecked())
    data.enabled = true;

  data.range = rangeSpin->value();

  switch (searchTypeCombo->currentIndex())
  {
  case 0:
    data.searchType = General::SearchTypeFlag::NpcOnly;
    break;
  case 1:
    data.searchType = General::SearchTypeFlag::PlayerFirst;
    break;
  case 2:
    data.searchType = General::SearchTypeFlag::PlayerOnly;
    break;
  case 3:
    data.searchType = General::SearchTypeFlag::NpcFirst;
    break;
  }

  std::string marker = targetSlotEdit->text().toStdString();
  if (!marker.empty())
    data.targetSlot = marker;

  int eventIndex = eventTypeCombo->currentIndex();
  if (eventIndex > 0)
  {
    switch (eventIndex)
    {
    case 1:
      data.eventType = General::Sensor::BlockChange::BlockChangeEventTypeFlag::Destruction;
      break;
    case 2:
      data.eventType = General::Sensor::BlockChange::BlockChangeEventTypeFlag::Interaction;
      break;
    case 3:
      data.eventType = General::Sensor::BlockChange::BlockChangeEventTypeFlag::Damage;
      break;
    }
  }

  return data;
}

SensorNodes::BlockTypeNode::BlockTypeNode(NodeScene *scene)
    : NodeItem("BlockType", true)
{
  fieldsHeight = 120;
  addInputSocket("In", scene);
  addOutputSocket("Sensor", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  blockSetEdit = new QLineEdit;
  form->addRow("Block Set (Asset):", blockSetEdit);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Sensor::BlockType SensorNodes::BlockTypeNode::serialize()
{
  General::Sensor::BlockType data;

  std::string marker = blockSetEdit->text().toStdString();
  data.blockSet = marker;

  if (onceBox->isChecked())
    data.once = true;

  if (enabledBox->isChecked())
    data.enabled = true;

  return data;
}

SensorNodes::CanInteractNode::CanInteractNode(NodeScene *scene)
    : NodeItem("CanInteract", true)
{
  fieldsHeight = 200;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  viewSectorSpin = new QDoubleSpinBox;
  viewSectorSpin->setRange(0, 360);
  form->addRow("View Sector:", viewSectorSpin);

  attitudesList = new QListWidget;
  attitudesList->setSelectionMode(QAbstractItemView::MultiSelection);
  attitudesList->addItems({"Friendly", "Neutral", "Hostile", "Revered", "Ignore"});
  form->addRow("Attitudes:", attitudesList);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Sensor::CanInteract SensorNodes::CanInteractNode::serialize()
{
  General::Sensor::CanInteract data;

  for (int i = 0; i < attitudesList->count(); ++i)
  {
    QListWidgetItem *item = attitudesList->item(i);
    if (item)
    {
      std::string itemStr = item->text().toStdString();
      if (!itemStr.empty())
      {
        if (itemStr == "Friendly")
        {
          data.attitudes.push_back(General::AttitudeFlag::Friendly);
        }
        else if (itemStr == "Neutral")
        {
          data.attitudes.push_back(General::AttitudeFlag::Neutral);
        }
        else if (itemStr == "Hostile")
        {
          data.attitudes.push_back(General::AttitudeFlag::Hostile);
        }
        else if (itemStr == "Revered")
        {
          data.attitudes.push_back(General::AttitudeFlag::Revered);
        }
        else if (itemStr == "Ignore")
        {
          data.attitudes.push_back(General::AttitudeFlag::Ignore);
        }
      }
    }
  }

  data.viewSector = viewSectorSpin->value();

  if (onceBox->isChecked())
    data.once = true;

  if (enabledBox->isChecked())
    data.enabled = true;

  return data;
}

SensorNodes::CanPlaceBlockNode::CanPlaceBlockNode(NodeScene *scene)
    : NodeItem("CanPlaceBlock", true, 290)
{
  fieldsHeight = 220;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  directionCombo = new QComboBox;
  directionCombo->addItems({"Forward", "Backward", "Left", "Right"});
  form->addRow("Direction:", directionCombo);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  offsetCombo = new QComboBox;
  offsetCombo->addItems({"", "BodyPosition", "FootPosition", "HeadPosition"});
  form->addRow("Offset:", offsetCombo);
  label = form->labelForField(offsetCombo);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  retryDelaySpin = new QDoubleSpinBox;
  retryDelaySpin->setRange(0, 1e6);
  form->addRow("Retry Delay:", retryDelaySpin);
  label = form->labelForField(retryDelaySpin);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  allowEmptyMaterialsBox = new QCheckBox;
  form->addRow("Allow Empty Materials:", allowEmptyMaterialsBox);
  label = form->labelForField(allowEmptyMaterialsBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Sensor::CanPlaceBlock SensorNodes::CanPlaceBlockNode::serialize()
{
  General::Sensor::CanPlaceBlock data;

  std::string marker = directionCombo->currentText().toStdString();
  if (marker == "Forward")
  {
    data.direction = General::DirectionFlag::Forward;
  }
  else if (marker == "Backward")
  {
    data.direction = General::DirectionFlag::Backward;
  }
  else if (marker == "Left")
  {
    data.direction = General::DirectionFlag::Left;
  }
  else if (marker == "Right")
  {
    data.direction = General::DirectionFlag::Right;
  }

  marker = offsetCombo->currentText().toStdString();
  if (!marker.empty())
  {
    if (marker == "BodyPosition")
    {
      data.offset = General::Sensor::CanPlaceBlock::CanPlaceBlockFlag::BodyPosition;
    }
    else if (marker == "FootPosition")
    {
      data.offset = General::Sensor::CanPlaceBlock::CanPlaceBlockFlag::FootPosition;
    }
    else if (marker == "HeadPosition")
    {
      data.offset = General::Sensor::CanPlaceBlock::CanPlaceBlockFlag::HeadPosition;
    }
  }

  if (retryDelaySpin->value() != 0)
  {
    data.retryDelay = retryDelaySpin->value();
  }

  if (onceBox->isChecked())
    data.once = true;

  if (enabledBox->isChecked())
    data.enabled = true;

  if (allowEmptyMaterialsBox->isChecked())
    data.allowEmptyMaterials = true;

  return data;
}

SensorNodes::CombatActionEvaluatorNode::CombatActionEvaluatorNode(NodeScene *scene)
    : NodeItem("CombatActionEvaluator", true)
{
  fieldsHeight = 160;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  targetInRangeBox = new QCheckBox;
  form->addRow("Target In Range:", targetInRangeBox);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  allowableDeviationSpin = new QDoubleSpinBox;
  allowableDeviationSpin->setRange(0, 1e6);
  form->addRow("Allowable Deviation:", allowableDeviationSpin);
  label = form->labelForField(allowableDeviationSpin);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Sensor::CombatActionEvaluator SensorNodes::CombatActionEvaluatorNode::serialize()
{
  General::Sensor::CombatActionEvaluator data;

  if (allowableDeviationSpin->value() != 0)
  {
    data.allowableDeviation = allowableDeviationSpin->value();
  }

  data.targetInRange = targetInRangeBox->isChecked();

  if (onceBox->isChecked())
    data.once = true;

  if (enabledBox->isChecked())
    data.enabled = true;

  return data;
}

SensorNodes::CountNode::CountNode(NodeScene *scene)
    : NodeItem("Count", true, 250)
{
  fieldsHeight = 270;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  countMin = new QSpinBox;
  countMin->setRange(0, 100000);
  countMax = new QSpinBox;
  countMax->setRange(0, 100000);
  form->addRow("Count Min:", countMin);
  form->addRow("Count Max:", countMax);

  rangeMin = new QDoubleSpinBox;
  rangeMin->setRange(0, 1e6);
  rangeMax = new QDoubleSpinBox;
  rangeMax->setRange(0, 1e6);
  form->addRow("Range Min:", rangeMin);
  form->addRow("Range Max:", rangeMax);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  includeGroupsEdit = new QLineEdit;
  includeGroupsEdit->setPlaceholderText("comma-separated assets");
  form->addRow("Include Groups:", includeGroupsEdit);
  label = form->labelForField(includeGroupsEdit);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  excludeGroupsEdit = new QLineEdit;
  excludeGroupsEdit->setPlaceholderText("comma-separated assets");
  form->addRow("Exclude Groups:", excludeGroupsEdit);
  label = form->labelForField(excludeGroupsEdit);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Sensor::Count SensorNodes::CountNode::serialize()
{
  General::Sensor::Count data;

  data.count.push_back(countMin->value());
  data.count.push_back(countMax->value());

  data.range.push_back(rangeMin->value());
  data.range.push_back(rangeMax->value());

  std::string marker = includeGroupsEdit->text().toStdString();
  std::string item;
  std::stringstream ss(marker);

  if (!marker.empty())
  {
    data.includeGroups.emplace();
    while (std::getline(ss, item, ','))
    {
      data.includeGroups->push_back(item);
    }
  }

  marker = excludeGroupsEdit->text().toStdString();
  if (!marker.empty())
  {
    data.excludeGroups.emplace();
    std::stringstream ss2(marker);

    while (std::getline(ss2, item, ','))
    {
      data.excludeGroups->push_back(item);
    }
  }

  if (onceBox->isChecked())
    data.once = true;

  if (enabledBox->isChecked())
    data.enabled = true;

  return data;
}

SensorNodes::DamageNode::DamageNode(NodeScene *scene)
    : NodeItem("Damage", true)
{
  fieldsHeight = 280;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  combatBox = new QCheckBox;
  form->addRow("Combat:", combatBox);
  label = form->labelForField(combatBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  friendlyBox = new QCheckBox;
  form->addRow("Friendly:", friendlyBox);
  label = form->labelForField(friendlyBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  drowningBox = new QCheckBox;
  form->addRow("Drowning:", drowningBox);
  label = form->labelForField(drowningBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  environmentBox = new QCheckBox;
  form->addRow("Environment:", environmentBox);
  label = form->labelForField(environmentBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  otherBox = new QCheckBox;
  form->addRow("Other:", otherBox);
  label = form->labelForField(otherBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  targetSlotEdit = new QLineEdit;
  form->addRow("Target Slot:", targetSlotEdit);
  label = form->labelForField(targetSlotEdit);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Sensor::Damage SensorNodes::DamageNode::serialize()
{
  General::Sensor::Damage data;

  std::string marker = targetSlotEdit->text().toStdString();
  if (!marker.empty())
  {
    data.targetSlot = marker;
  }

  if (onceBox->isChecked())
    data.once = true;

  if (enabledBox->isChecked())
    data.enabled = true;

  if (combatBox->isChecked())
    data.combat = true;

  if (friendlyBox->isChecked())
    data.friendly = true;

  if (drowningBox->isChecked())
    data.drowning = true;

  if (environmentBox->isChecked())
    data.environment = true;

  if (otherBox->isChecked())
    data.other = true;

  return data;
}

SensorNodes::DroppedItemNode::DroppedItemNode(NodeScene *scene)
    : NodeItem("DroppedItem", true, 230)
{
  fieldsHeight = 270;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  rangeSpin = new QDoubleSpinBox;
  rangeSpin->setRange(0, 1e6);
  form->addRow("Range:", rangeSpin);

  viewSectorSpin = new QDoubleSpinBox;
  viewSectorSpin->setRange(0, 360);
  form->addRow("View Sector:", viewSectorSpin);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  lineOfSightBox = new QCheckBox;
  form->addRow("Line Of Sight:", lineOfSightBox);
  label = form->labelForField(lineOfSightBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  itemsEdit = new QLineEdit;
  itemsEdit->setPlaceholderText("comma-separated assets");
  form->addRow("Items:", itemsEdit);
  label = form->labelForField(itemsEdit);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  attitudesList = new QListWidget;
  attitudesList->setSelectionMode(QAbstractItemView::MultiSelection);
  attitudesList->addItems({"Neutral", "Ignore", "Like", "Love", "Dislike"});
  form->addRow("Attitudes:", attitudesList);
  label = form->labelForField(attitudesList);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Sensor::DroppedItem SensorNodes::DroppedItemNode::serialize()
{
  General::Sensor::DroppedItem data;

  data.range = rangeSpin->value();
  data.viewSector = viewSectorSpin->value();

  std::string marker = itemsEdit->text().toStdString();
  if (!marker.empty())
  {
    data.items.emplace();
    std::string item;
    std::stringstream ss(marker);

    while (std::getline(ss, item, ','))
    {
      data.items->push_back(item);
    }
  }

  for (int i = 0; i < attitudesList->count(); ++i)
  {
    QListWidgetItem *item = attitudesList->item(i);
    if (item)
    {
      std::string itemStr = item->text().toStdString();
      if (!itemStr.empty())
      {
        data.attitudes.emplace();
        if (itemStr == "Neutral")
        {
          data.attitudes->push_back(General::Sensor::DroppedItem::DroppedItemFlag::Neutral);
        }
        else if (itemStr == "Ignore")
        {
          data.attitudes->push_back(General::Sensor::DroppedItem::DroppedItemFlag::Ignore);
        }
        else if (itemStr == "Like")
        {
          data.attitudes->push_back(General::Sensor::DroppedItem::DroppedItemFlag::Like);
        }
        else if (itemStr == "Love")
        {
          data.attitudes->push_back(General::Sensor::DroppedItem::DroppedItemFlag::Love);
        }
        else if (itemStr == "Dislike")
        {
          data.attitudes->push_back(General::Sensor::DroppedItem::DroppedItemFlag::Dislike);
        }
      }
    }
  }

  if (onceBox->isChecked())
    data.once = true;

  if (enabledBox->isChecked())
    data.enabled = true;

  if (lineOfSightBox->isChecked())
    data.lineOfSight = true;

  return data;
}

SensorNodes::EntityEventNode::EntityEventNode(NodeScene *scene)
    : NodeItem("EntityEvent", true, 225)
{
  fieldsHeight = 300;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  rangeSpin = new QDoubleSpinBox;
  rangeSpin->setRange(0, 1e6);
  form->addRow("Range:", rangeSpin);

  npcGroupEdit = new QLineEdit;
  form->addRow("NPC Group:", npcGroupEdit);

  eventTypeCombo = new QComboBox;
  eventTypeCombo->addItems({"Death", "Interaction", "Damage"});
  form->addRow("Event Type:", eventTypeCombo);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  searchTypeCombo = new QComboBox;
  searchTypeCombo->addItems({"", "NpcOnly", "PlayerFirst", "PlayerOnly", "NpcFirst"});
  form->addRow("Search Type:", searchTypeCombo);
  label = form->labelForField(searchTypeCombo);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  targetSlotEdit = new QLineEdit;
  form->addRow("Target Slot:", targetSlotEdit);
  label = form->labelForField(targetSlotEdit);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  flockOnlyBox = new QCheckBox;
  form->addRow("Flock Only:", flockOnlyBox);
  label = form->labelForField(flockOnlyBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Sensor::EntityEvent SensorNodes::EntityEventNode::serialize()
{
  General::Sensor::EntityEvent data;

  data.range = rangeSpin->value();

  std::string marker = npcGroupEdit->text().toStdString();
  data.npcGroup = marker;

  marker = targetSlotEdit->text().toStdString();
  if (!marker.empty())
  {
    data.targetSlot = marker;
  }

  marker = eventTypeCombo->currentText().toStdString();
  if (marker == "Death")
  {
    data.eventType = General::Sensor::EntityEvent::EntityEventFlag::Death;
  }
  else if (marker == "Interaction")
  {
    data.eventType = General::Sensor::EntityEvent::EntityEventFlag::Interaction;
  }
  else if (marker == "Damage")
  {
    data.eventType = General::Sensor::EntityEvent::EntityEventFlag::Damage;
  }

  marker = searchTypeCombo->currentText().toStdString();
  if (!marker.empty())
  {
    if (marker == "NpcOnly")
    {
      data.searchType = General::SearchTypeFlag::NpcOnly;
    }
    else if (marker == "PlayerFirst")
    {
      data.searchType = General::SearchTypeFlag::PlayerFirst;
    }
    else if (marker == "PlayerOnly")
    {
      data.searchType = General::SearchTypeFlag::PlayerOnly;
    }
    else if (marker == "NpcFirst")
    {
      data.searchType = General::SearchTypeFlag::NpcFirst;
    }
  }

  if (onceBox->isChecked())
    data.once = true;

  if (enabledBox->isChecked())
    data.enabled = true;

  if (flockOnlyBox->isChecked())
    data.flockOnly = true;

  return data;
}

SensorNodes::FlagNode::FlagNode(NodeScene *scene)
    : NodeItem("Flag", true)
{
  fieldsHeight = 160;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  nameEdit = new QLineEdit;
  form->addRow("Name:", nameEdit);
  QWidget *label = form->labelForField(nameEdit);
  QColor textColor = gStyleManager.getCurrentStyle().nodeText;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  label = form->labelForField(onceBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  setBox = new QCheckBox;
  form->addRow("Set:", setBox);
  label = form->labelForField(setBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Sensor::Flag SensorNodes::FlagNode::serialize()
{
  General::Sensor::Flag data;

  std::string marker = nameEdit->text().toStdString();
  data.name = marker;

  if (onceBox->isChecked())
    data.once = true;

  if (enabledBox->isChecked())
    data.enabled = true;

  if (setBox->isChecked())
    data.set = true;

  return data;
}

SensorNodes::FlockCombatDamageNode::FlockCombatDamageNode(NodeScene *scene)
    : NodeItem("FlockCombatDamage", true)
{
  fieldsHeight = 130;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  leaderOnlyBox = new QCheckBox;
  form->addRow("Leader Only:", leaderOnlyBox);
  label = form->labelForField(leaderOnlyBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Sensor::FlockCombatDamage SensorNodes::FlockCombatDamageNode::serialize()
{
  General::Sensor::FlockCombatDamage data;

  if (onceBox->isChecked())
    data.once = true;

  if (enabledBox->isChecked())
    data.enabled = true;

  if (leaderOnlyBox->isChecked())
    data.leaderOnly = true;

  return data;
}

SensorNodes::FlockLeaderNode::FlockLeaderNode(NodeScene *scene)
    : NodeItem("FlockLeader", true)
{
  fieldsHeight = 100;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Sensor::FlockLeader SensorNodes::FlockLeaderNode::serialize()
{
  General::Sensor::FlockLeader data;

  if (onceBox->isChecked())
    data.once = true;

  if (enabledBox->isChecked())
    data.enabled = true;

  return data;
}

SensorNodes::HasHostileTargetMemoryNode::HasHostileTargetMemoryNode(NodeScene *scene)
    : NodeItem("HasHostileTargetMemory", true)
{
  fieldsHeight = 100;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Sensor::HasHostileTargetMemory SensorNodes::HasHostileTargetMemoryNode::serialize()
{
  General::Sensor::HasHostileTargetMemory data;

  if (onceBox->isChecked())
    data.once = true;

  if (enabledBox->isChecked())
    data.enabled = true;

  return data;
}

SensorNodes::HasInteractedNode::HasInteractedNode(NodeScene *scene)
    : NodeItem("HasInteracted", true)
{
  fieldsHeight = 100;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Sensor::HasInteracted SensorNodes::HasInteractedNode::serialize()
{
  General::Sensor::HasInteracted data;

  if (onceBox->isChecked())
    data.once = true;

  if (enabledBox->isChecked())
    data.enabled = true;

  return data;
}

SensorNodes::HasTaskNode::HasTaskNode(NodeScene *scene)
    : NodeItem("HasTask", true)
{
  fieldsHeight = 130;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  taskByIdEdit = new QLineEdit;
  taskByIdEdit->setPlaceholderText("comma-separated task IDs");
  form->addRow("Task By Id:", taskByIdEdit);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Sensor::HasTask SensorNodes::HasTaskNode::serialize()
{
  General::Sensor::HasTask data;

  std::string marker = taskByIdEdit->text().toStdString();
  std::string item;
  std::stringstream ss(marker);

  while (std::getline(ss, item, ','))
  {
    data.taskById.push_back(item);
  }

  if (onceBox->isChecked())
    data.once = true;

  if (enabledBox->isChecked())
    data.enabled = true;

  return data;
}

SensorNodes::InAirNode::InAirNode(NodeScene *scene)
    : NodeItem("InAir", true)
{
  fieldsHeight = 100;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Sensor::InAir SensorNodes::InAirNode::serialize()
{
  General::Sensor::InAir data;

  if (onceBox->isChecked())
    data.once = true;

  if (enabledBox->isChecked())
    data.enabled = true;

  return data;
}

SensorNodes::InWaterNode::InWaterNode(NodeScene *scene)
    : NodeItem("InWater", true)
{
  fieldsHeight = 100;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Sensor::InWater SensorNodes::InWaterNode::serialize()
{
  General::Sensor::InWater data;

  if (onceBox->isChecked())
    data.once = true;

  if (enabledBox->isChecked())
    data.enabled = true;

  return data;
}

SensorNodes::InflictedDamageNode::InflictedDamageNode(NodeScene *scene)
    : NodeItem("InflictedDamage", true, 215)
{
  fieldsHeight = 160;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  targetCombo = new QComboBox;
  targetCombo->addItems({"", "FlockLeader", "Self", "Flock"});
  form->addRow("Target:", targetCombo);
  label = form->labelForField(targetCombo);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  friendlyFireBox = new QCheckBox;
  form->addRow("Friendly Fire:", friendlyFireBox);
  label = form->labelForField(friendlyFireBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Sensor::InflictedDamage SensorNodes::InflictedDamageNode::serialize()
{
  General::Sensor::InflictedDamage data;

  std::string marker = targetCombo->currentText().toStdString();
  if (!marker.empty())
  {
    if (marker == "FlockLeader")
    {
      data.target = General::Sensor::InflictedDamage::InflictedDamageFlag::FlockLeader;
    }
    else if (marker == "Self")
    {
      data.target = General::Sensor::InflictedDamage::InflictedDamageFlag::Self;
    }
    else if (marker == "Flock")
    {
      data.target = General::Sensor::InflictedDamage::InflictedDamageFlag::Flock;
    }
  }

  if (onceBox->isChecked())
    data.once = true;

  if (enabledBox->isChecked())
    data.enabled = true;

  if (friendlyFireBox->isChecked())
    data.friendlyFire = true;

  return data;
}

SensorNodes::InteractionContextNode::InteractionContextNode(NodeScene *scene)
    : NodeItem("InteractionContext", true)
{
  fieldsHeight = 120;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  contextEdit = new QLineEdit;
  form->addRow("Context:", contextEdit);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Sensor::InteractionContext SensorNodes::InteractionContextNode::serialize()
{
  General::Sensor::InteractionContext data;

  std::string marker = contextEdit->text().toStdString();
  data.context = marker;

  if (onceBox->isChecked())
    data.once = true;

  if (enabledBox->isChecked())
    data.enabled = true;

  return data;
}

SensorNodes::IsBackingAwayNode::IsBackingAwayNode(NodeScene *scene)
    : NodeItem("IsBackingAway", true)
{
  fieldsHeight = 100;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Sensor::IsBackingAway SensorNodes::IsBackingAwayNode::serialize()
{
  General::Sensor::IsBackingAway data;

  if (onceBox->isChecked())
    data.once = true;

  if (enabledBox->isChecked())
    data.enabled = true;

  return data;
}

SensorNodes::IsBusyNode::IsBusyNode(NodeScene *scene)
    : NodeItem("IsBusy", true)
{
  fieldsHeight = 100;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Sensor::IsBusy SensorNodes::IsBusyNode::serialize()
{
  General::Sensor::IsBusy data;

  if (onceBox->isChecked())
    data.once = true;

  if (enabledBox->isChecked())
    data.enabled = true;

  return data;
}

SensorNodes::KillNode::KillNode(NodeScene *scene)
    : NodeItem("Kill", true)
{
  fieldsHeight = 130;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  targetSlotEdit = new QLineEdit;
  form->addRow("Target Slot:", targetSlotEdit);
  label = form->labelForField(targetSlotEdit);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Sensor::Kill SensorNodes::KillNode::serialize()
{
  General::Sensor::Kill data;

  std::string marker = targetSlotEdit->text().toStdString();
  if (!marker.empty())
  {
    data.targetSlot = marker;
  }

  if (onceBox->isChecked())
    data.once = true;

  if (enabledBox->isChecked())
    data.enabled = true;

  return data;
}

SensorNodes::LeashNode::LeashNode(NodeScene *scene)
    : NodeItem("Leash", true)
{
  fieldsHeight = 120;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  rangeSpin = new QDoubleSpinBox;
  rangeSpin->setRange(0, 1e6);
  form->addRow("Range:", rangeSpin);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Sensor::Leash SensorNodes::LeashNode::serialize()
{
  General::Sensor::Leash data;

  data.range = rangeSpin->value();

  if (onceBox->isChecked())
    data.once = true;

  if (enabledBox->isChecked())
    data.enabled = true;

  return data;
}

SensorNodes::LightNode::LightNode(NodeScene *scene)
    : NodeItem("Light", true, 280)
{
  fieldsHeight = 480;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  // Might change this because it doesn't line up with how the rest of the nodes handle ranges
  auto makeRangePair = [&](const QString &label, QDoubleSpinBox *&minS, QDoubleSpinBox *&maxS)
  {
    minS = new QDoubleSpinBox;
    minS->setRange(0, 15);
    maxS = new QDoubleSpinBox;
    maxS->setRange(0, 15);
    form->addRow(label + " Min:", minS);
    auto *labelWidget = form->labelForField(minS);
    labelWidget->setStyleSheet("color: gray;");

    form->addRow(label + " Max:", maxS);
    labelWidget = form->labelForField(maxS);
    labelWidget->setStyleSheet("color: gray;");
  };

  makeRangePair("Light Range", lightMin, lightMax);
  makeRangePair("Sky Light Range", skyLightMin, skyLightMax);
  makeRangePair("Sunlight Range", sunlightMin, sunlightMax);
  makeRangePair("Red Light Range", redMin, redMax);
  makeRangePair("Green Light Range", greenMin, greenMax);
  makeRangePair("Blue Light Range", blueMin, blueMax);

  targetSlotEdit = new QLineEdit;
  form->addRow("Target Slot:", targetSlotEdit);
  label = form->labelForField(targetSlotEdit);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Sensor::Light SensorNodes::LightNode::serialize()
{
  General::Sensor::Light data;

  std::string marker = targetSlotEdit->text().toStdString();
  if (!marker.empty())
    data.targetSlot = marker;

  if (lightMin->value() != 0 || lightMax->value() != 0)
  {
    data.lightRange.emplace(lightMin->value());
    data.lightRange.emplace(lightMax->value());
  }

  if (skyLightMin->value() != 0 || skyLightMax->value() != 0)
  {
    data.skyLightRange.emplace(skyLightMin->value());
    data.skyLightRange.emplace(skyLightMax->value());
  }

  if (sunlightMin->value() != 0 || sunlightMax->value() != 0)
  {
    data.sunlightRange.emplace(sunlightMin->value());
    data.sunlightRange.emplace(sunlightMax->value());
  }

  if (redMin->value() != 0 || redMax->value() != 0)
  {
    data.redLightRange.emplace(redMin->value());
    data.redLightRange.emplace(redMax->value());
  }

  if (greenMin->value() != 0 || greenMax->value() != 0)
  {
    data.greenLightRange.emplace(greenMin->value());
    data.greenLightRange.emplace(greenMax->value());
  }

  if (blueMin->value() != 0 || blueMax->value() != 0)
  {
    data.blueLightRange.emplace(blueMin->value());
    data.blueLightRange.emplace(blueMax->value());
  }

  if (onceBox->isChecked())
    data.once = true;

  if (enabledBox->isChecked())
    data.enabled = true;

  return data;
}

SensorNodes::MobNode::MobNode(NodeScene *scene)
    : NodeItem("Mob", true, 280)
{
  fieldsHeight = 420;
  addInputSocket("In", scene);
  addOutputSocket("Prioritizer (WIP)", scene, true); // TODO: Add nodes for prioritizers and collectors and filters
  addOutputSocket("Collector (WIP)", scene, true);
  addOutputSocket("Filters (WIP)", scene, true);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  rangeSpin = new QDoubleSpinBox;
  rangeSpin->setRange(0, 1e6);
  form->addRow("Range:", rangeSpin);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  minRangeSpin = new QDoubleSpinBox;
  minRangeSpin->setRange(0, 1e6);
  form->addRow("Min Range:", minRangeSpin);
  label = form->labelForField(minRangeSpin);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  lockedOnTargetBox = new QCheckBox;
  form->addRow("Locked On Target:", lockedOnTargetBox);
  label = form->labelForField(lockedOnTargetBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  lockedTargetSlotEdit = new QLineEdit;
  form->addRow("Locked Target Slot:", lockedTargetSlotEdit);
  label = form->labelForField(lockedTargetSlotEdit);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  autoUnlockTargetBox = new QCheckBox;
  form->addRow("Auto Unlock Target:", autoUnlockTargetBox);
  label = form->labelForField(autoUnlockTargetBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  onlyLockedTargetBox = new QCheckBox;
  form->addRow("Only Locked Target:", onlyLockedTargetBox);
  label = form->labelForField(onlyLockedTargetBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  ignoredTargetSlotEdit = new QLineEdit;
  form->addRow("Ignored Target Slot:", ignoredTargetSlotEdit);
  label = form->labelForField(ignoredTargetSlotEdit);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  useProjectedDistanceBox = new QCheckBox;
  form->addRow("Use Projected Distance:", useProjectedDistanceBox);
  label = form->labelForField(useProjectedDistanceBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  getPlayersBox = new QCheckBox;
  form->addRow("Get Players:", getPlayersBox);
  label = form->labelForField(getPlayersBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  getNPCsBox = new QCheckBox;
  form->addRow("Get NPCs:", getNPCsBox);
  label = form->labelForField(getNPCsBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  excludeOwnTypeBox = new QCheckBox;
  form->addRow("Exclude Own Type:", excludeOwnTypeBox);
  label = form->labelForField(excludeOwnTypeBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Sensor::Mob SensorNodes::MobNode::serialize()
{
  General::Sensor::Mob data;

  std::string marker = lockedTargetSlotEdit->text().toStdString();
  if (!marker.empty())
    data.lockedTargetSlot = marker;

  marker = ignoredTargetSlotEdit->text().toStdString();
  if (!marker.empty())
    data.ignoredTargetSlot = marker;

  data.range = rangeSpin->value();

  if (minRangeSpin->value() != 0)
  {
    data.minRange = minRangeSpin->value();
  }

  if (onceBox->isChecked())
    data.once = true;

  if (enabledBox->isChecked())
    data.enabled = true;

  if (lockedOnTargetBox->isChecked())
    data.lockedOnTarget = true;

  if (autoUnlockTargetBox->isChecked())
    data.autoUnlockTarget = true;

  if (onlyLockedTargetBox->isChecked())
    data.onlyLockedTarget = true;

  if (useProjectedDistanceBox->isChecked())
    data.useProjectedDistance = true;

  if (getPlayersBox->isChecked())
    data.getPlayers = true;

  if (getNPCsBox->isChecked())
    data.getNPCs = true;

  if (excludeOwnTypeBox->isChecked())
    data.excludeOwnType = true;

  return data;
}

SensorNodes::NavNode::NavNode(NodeScene *scene)
    : NodeItem("Nav", true, 260)
{
  fieldsHeight = 220;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  navStatesList = new QListWidget;
  navStatesList->setSelectionMode(QAbstractItemView::MultiSelection);
  navStatesList->addItems({"Progressing", "Init", "At_Goal", "Blocked", "Aborted", "Defer"});
  form->addRow("Nav States:", navStatesList);
  label = form->labelForField(navStatesList);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  throttleDurationSpin = new QDoubleSpinBox;
  throttleDurationSpin->setRange(0, 1e6);
  form->addRow("Throttle Duration:", throttleDurationSpin);
  label = form->labelForField(throttleDurationSpin);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  targetDeltaSpin = new QDoubleSpinBox;
  targetDeltaSpin->setRange(0, 1e6);
  form->addRow("Target Delta:", targetDeltaSpin);
  label = form->labelForField(targetDeltaSpin);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Sensor::Nav SensorNodes::NavNode::serialize()
{
  General::Sensor::Nav data;

  for (int i = 0; i < navStatesList->count(); ++i)
  {
    QListWidgetItem *item = navStatesList->item(i);
    if (item)
    {
      std::string itemStr = item->text().toStdString();
      if (!itemStr.empty())
      {
        data.navStates.emplace();
        if (itemStr == "Progressing")
        {
          data.navStates->push_back(General::Sensor::Nav::NavStatesFlag::Progressing);
        }
        else if (itemStr == "Init")
        {
          data.navStates->push_back(General::Sensor::Nav::NavStatesFlag::Init);
        }
        else if (itemStr == "At_Goal")
        {
          data.navStates->push_back(General::Sensor::Nav::NavStatesFlag::At_Goal);
        }
        else if (itemStr == "Blocked")
        {
          data.navStates->push_back(General::Sensor::Nav::NavStatesFlag::Blocked);
        }
        else if (itemStr == "Aborted")
        {
          data.navStates->push_back(General::Sensor::Nav::NavStatesFlag::Aborted);
        }
        else if (itemStr == "Defer")
        {
          data.navStates->push_back(General::Sensor::Nav::NavStatesFlag::Defer);
        }
      }
    }
  }

  if (throttleDurationSpin->value() != 0)
  {
    data.throttleDuration = throttleDurationSpin->value();
  }

  if (targetDeltaSpin->value() != 0)
  {
    data.targetDelta = targetDeltaSpin->value();
  }

  if (onceBox->isChecked())
    data.once = true;

  if (enabledBox->isChecked())
    data.enabled = true;

  return data;
}

SensorNodes::NotNode::NotNode(NodeScene *scene)
    : NodeItem("Not", true, 260)
{
  fieldsHeight = 150;
  addInputSocket("In", scene);
  addOutputSocket("Sensor", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  useTargetSlotEdit = new QLineEdit;
  form->addRow("Use Target Slot:", useTargetSlotEdit);
  label = form->labelForField(useTargetSlotEdit);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  autoUnlockTargetSlotEdit = new QLineEdit;
  form->addRow("Auto Unlock Target Slot:", autoUnlockTargetSlotEdit);
  label = form->labelForField(autoUnlockTargetSlotEdit);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Sensor::Not SensorNodes::NotNode::serialize()
{
  General::Sensor::Not data;

  std::string marker = useTargetSlotEdit->text().toStdString();
  if (!marker.empty())
    data.useTargetSlot = marker;

  marker = autoUnlockTargetSlotEdit->text().toStdString();
  if (!marker.empty())
    data.autoUnlockTargetSlot = marker;

  if (onceBox->isChecked())
    data.once = true;

  if (enabledBox->isChecked())
    data.enabled = true;

  return data;
}

SensorNodes::OnGroundNode::OnGroundNode(NodeScene *scene)
    : NodeItem("OnGround", true)
{
  fieldsHeight = 100;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Sensor::OnGround SensorNodes::OnGroundNode::serialize()
{
  General::Sensor::OnGround data;

  if (onceBox->isChecked())
    data.once = true;

  if (enabledBox->isChecked())
    data.enabled = true;

  return data;
}

SensorNodes::OrNode::OrNode(NodeScene *scene)
    : NodeItem("Or", true, 260)
{
  fieldsHeight = 120;
  addInputSocket("In", scene);
  addInputSocket("Sensors", scene); // TODO: add serialization for this

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  autoUnlockTargetSlotEdit = new QLineEdit;
  form->addRow("Auto Unlock Target Slot:", autoUnlockTargetSlotEdit);
  label = form->labelForField(autoUnlockTargetSlotEdit);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Sensor::Or SensorNodes::OrNode::serialize()
{
  General::Sensor::Or data;

  std::string marker = autoUnlockTargetSlotEdit->text().toStdString();
  if (!marker.empty())
    data.autoUnlockTargetSlot = marker;

  if (onceBox->isChecked())
    data.once = true;

  if (enabledBox->isChecked())
    data.enabled = true;

  return data;
}

SensorNodes::PathNode::PathNode(NodeScene *scene)
    : NodeItem("Path", true, 230)
{
  fieldsHeight = 180;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  pathEdit = new QLineEdit;
  form->addRow("Path:", pathEdit);
  label = form->labelForField(pathEdit);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  rangeSpin = new QDoubleSpinBox;
  rangeSpin->setRange(0, 1e6);
  form->addRow("Range:", rangeSpin);
  label = form->labelForField(rangeSpin);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  pathTypeCombo = new QComboBox;
  pathTypeCombo->addItems({"", "CurrentPrefabPath", "TransientPath", "AnyPrefabPath", "WorldPath"});
  form->addRow("Path Type:", pathTypeCombo);
  label = form->labelForField(pathTypeCombo);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Sensor::Path SensorNodes::PathNode::serialize()
{
  General::Sensor::Path data;

  std::string marker = pathEdit->text().toStdString();
  if (!marker.empty())
    data.path = marker;

  marker = pathTypeCombo->currentText().toStdString();
  if (!marker.empty())
  {
    if (marker == "CurrentPrefabPath")
    {
      data.pathType = General::Sensor::Path::PathTypeFlag::CurrentPrefabPath;
    }
    else if (marker == "TransientPath")
    {
      data.pathType = General::Sensor::Path::PathTypeFlag::TransientPath;
    }
    else if (marker == "AnyPrefabPath")
    {
      data.pathType = General::Sensor::Path::PathTypeFlag::AnyPrefabPath;
    }
    else if (marker == "WorldPath")
    {
      data.pathType = General::Sensor::Path::PathTypeFlag::WorldPath;
    }
  }

  if (rangeSpin->value() != 0)
  {
    data.range = rangeSpin->value();
  }

  if (onceBox->isChecked())
    data.once = true;

  if (enabledBox->isChecked())
    data.enabled = true;

  return data;
}

SensorNodes::PlayerNode::PlayerNode(NodeScene *scene)
    : NodeItem("Player", true, 270)
{
  fieldsHeight = 330;
  addInputSocket("In", scene);
  addOutputSocket("Prioritizer (WIP)", scene, true); // TODO: Add nodes for prioritizers and collectors and filters
  addOutputSocket("Collector (WIP)", scene, true);
  addOutputSocket("Filters (WIP)", scene, true);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  rangeSpin = new QDoubleSpinBox;
  rangeSpin->setRange(0, 1e6);
  form->addRow("Range:", rangeSpin);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  minRangeSpin = new QDoubleSpinBox;
  minRangeSpin->setRange(0, 1e6);
  form->addRow("Min Range:", minRangeSpin);
  label = form->labelForField(minRangeSpin);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  lockedOnTargetBox = new QCheckBox;
  form->addRow("Locked On Target:", lockedOnTargetBox);
  label = form->labelForField(lockedOnTargetBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  lockedTargetSlotEdit = new QLineEdit;
  form->addRow("Locked Target Slot:", lockedTargetSlotEdit);
  label = form->labelForField(lockedTargetSlotEdit);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  autoUnlockTargetBox = new QCheckBox;
  form->addRow("Auto Unlock Target:", autoUnlockTargetBox);
  label = form->labelForField(autoUnlockTargetBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  onlyLockedTargetBox = new QCheckBox;
  form->addRow("Only Locked Target:", onlyLockedTargetBox);
  label = form->labelForField(onlyLockedTargetBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  ignoredTargetSlotEdit = new QLineEdit;
  form->addRow("Ignored Target Slot:", ignoredTargetSlotEdit);
  label = form->labelForField(ignoredTargetSlotEdit);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  useProjectedDistanceBox = new QCheckBox;
  form->addRow("Use Projected Distance:", useProjectedDistanceBox);
  label = form->labelForField(useProjectedDistanceBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Sensor::Player SensorNodes::PlayerNode::serialize()
{
  General::Sensor::Player data;

  std::string marker = lockedTargetSlotEdit->text().toStdString();
  if (!marker.empty())
    data.lockedTargetSlot = marker;

  marker = ignoredTargetSlotEdit->text().toStdString();
  if (!marker.empty())
    data.ignoredTargetSlot = marker;

  data.range = rangeSpin->value();

  if (minRangeSpin->value() != 0)
  {
    data.minRange = minRangeSpin->value();
  }

  if (onceBox->isChecked())
    data.once = true;

  if (enabledBox->isChecked())
    data.enabled = true;

  if (lockedOnTargetBox->isChecked())
    data.lockedOnTarget = true;

  if (autoUnlockTargetBox->isChecked())
    data.autoUnlockTarget = true;

  if (onlyLockedTargetBox->isChecked())
    data.onlyLockedTarget = true;

  if (useProjectedDistanceBox->isChecked())
    data.useProjectedDistance = true;

  return data;
}

SensorNodes::RandomNode::RandomNode(NodeScene *scene)
    : NodeItem("Random", true, 250)
{
  fieldsHeight = 200;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  trueDurMin = new QDoubleSpinBox;
  trueDurMin->setRange(0, 1e6);
  trueDurMax = new QDoubleSpinBox;
  trueDurMax->setRange(0, 1e6);
  form->addRow("True Duration Min:", trueDurMin);
  form->addRow("True Duration Max:", trueDurMax);

  falseDurMin = new QDoubleSpinBox;
  falseDurMin->setRange(0, 1e6);
  falseDurMax = new QDoubleSpinBox;
  falseDurMax->setRange(0, 1e6);
  form->addRow("False Duration Min:", falseDurMin);
  form->addRow("False Duration Max:", falseDurMax);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Sensor::Random SensorNodes::RandomNode::serialize()
{
  General::Sensor::Random data;

  data.trueDurationRange.push_back(trueDurMin->value());
  data.trueDurationRange.push_back(trueDurMax->value());

  data.falseDurationRange.push_back(falseDurMin->value());
  data.falseDurationRange.push_back(falseDurMax->value());

  if (onceBox->isChecked())
    data.once = true;

  if (enabledBox->isChecked())
    data.enabled = true;

  return data;
}

SensorNodes::ReadPositionNode::ReadPositionNode(NodeScene *scene)
    : NodeItem("ReadPosition", true, 250)
{
  fieldsHeight = 200;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  slotEdit = new QLineEdit;
  form->addRow("Slot:", slotEdit);

  rangeSpin = new QDoubleSpinBox;
  rangeSpin->setRange(0, 1e6);
  form->addRow("Range:", rangeSpin);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  minRangeSpin = new QDoubleSpinBox;
  minRangeSpin->setRange(0, 1e6);
  form->addRow("Min Range:", minRangeSpin);
  label = form->labelForField(minRangeSpin);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  useMarkedTargetBox = new QCheckBox;
  form->addRow("Use Marked Target:", useMarkedTargetBox);
  label = form->labelForField(useMarkedTargetBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Sensor::ReadPosition SensorNodes::ReadPositionNode::serialize()
{
  General::Sensor::ReadPosition data;

  std::string marker = slotEdit->text().toStdString();
  data.slot = marker;

  data.range = rangeSpin->value();

  if (minRangeSpin->value() != 0)
  {
    data.minRange = minRangeSpin->value();
  }

  if (onceBox->isChecked())
    data.once = true;

  if (enabledBox->isChecked())
    data.enabled = true;

  if (useMarkedTargetBox->isChecked())
    data.useMarkedTarget = true;

  return data;
}

SensorNodes::SearchRayNode::SearchRayNode(NodeScene *scene)
    : NodeItem("SearchRay", true, 240)
{
  fieldsHeight = 280;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  nameEdit = new QLineEdit;
  form->addRow("Name:", nameEdit);
  QWidget *label = form->labelForField(nameEdit);
  QColor textColor = gStyleManager.getCurrentStyle().nodeText;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  angleSpin = new QDoubleSpinBox;
  angleSpin->setRange(-360, 360);
  form->addRow("Angle:", angleSpin);

  rangeSpin = new QDoubleSpinBox;
  rangeSpin->setRange(0, 1e6);
  form->addRow("Range:", rangeSpin);

  blocksEdit = new QLineEdit;
  form->addRow("Blocks:", blocksEdit);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  label = form->labelForField(onceBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  minRetestAngleSpin = new QDoubleSpinBox;
  minRetestAngleSpin->setRange(0, 360);
  form->addRow("Min Retest Angle:", minRetestAngleSpin);
  label = form->labelForField(minRetestAngleSpin);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  minRetestMoveSpin = new QDoubleSpinBox;
  minRetestMoveSpin->setRange(0, 1e6);
  form->addRow("Min Retest Move:", minRetestMoveSpin);
  label = form->labelForField(minRetestMoveSpin);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  throttleTimeSpin = new QDoubleSpinBox;
  throttleTimeSpin->setRange(0, 1e6);
  form->addRow("Throttle Time:", throttleTimeSpin);
  label = form->labelForField(throttleTimeSpin);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Sensor::SearchRay SensorNodes::SearchRayNode::serialize()
{
  General::Sensor::SearchRay data;

  std::string marker = nameEdit->text().toStdString();
  data.name = marker;

  marker = blocksEdit->text().toStdString();
  data.blocks = marker;

  data.angle = angleSpin->value();
  data.range = rangeSpin->value();

  if (minRetestAngleSpin->value() != 0)
  {
    data.minRetestAngle = minRetestAngleSpin->value();
  }

  if (minRetestMoveSpin->value() != 0)
  {
    data.minRetestMove = minRetestMoveSpin->value();
  }

  if (throttleTimeSpin->value() != 0)
  {
    data.throttleTime = throttleTimeSpin->value();
  }

  if (onceBox->isChecked())
    data.once = true;

  if (enabledBox->isChecked())
    data.enabled = true;

  return data;
}

SensorNodes::SelfNode::SelfNode(NodeScene *scene)
    : NodeItem("Self", true)
{
  fieldsHeight = 100;
  addInputSocket("In", scene);
  addOutputSocket("Filters (WIP)", scene, true); // TODO: add serialization for filters

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Sensor::Self SensorNodes::SelfNode::serialize()
{
  General::Sensor::Self data;

  if (onceBox->isChecked())
    data.once = true;

  if (enabledBox->isChecked())
    data.enabled = true;

  return data;
}

SensorNodes::StateNode::StateNode(NodeScene *scene)
    : NodeItem("State", true, 250)
{
  fieldsHeight = 150;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  stateEdit = new QLineEdit;
  form->addRow("State:", stateEdit);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  ignoreMissingSetStateBox = new QCheckBox;
  form->addRow("Ignore Missing Set State:", ignoreMissingSetStateBox);
  label = form->labelForField(ignoreMissingSetStateBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Sensor::State SensorNodes::StateNode::serialize()
{
  General::Sensor::State data;

  std::string marker = stateEdit->text().toStdString();
  data.state = marker;

  if (onceBox->isChecked())
    data.once = true;

  if (enabledBox->isChecked())
    data.enabled = true;

  if (ignoreMissingSetStateBox->isChecked())
    data.ignoreMissingSetState = true;

  return data;
}

SensorNodes::SwitchNode::SwitchNode(NodeScene *scene)
    : NodeItem("Switch", true)
{
  fieldsHeight = 130;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  switchCheckBox = new QCheckBox;
  form->addRow("Switch:", switchCheckBox);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Sensor::Switch SensorNodes::SwitchNode::serialize()
{
  General::Sensor::Switch data;

  data.switchCheck = switchCheckBox->isChecked();

  if (onceBox->isChecked())
    data.once = true;

  if (enabledBox->isChecked())
    data.enabled = true;

  return data;
}

SensorNodes::TargetNode::TargetNode(NodeScene *scene)
    : NodeItem("Target", true, 250)
{
  fieldsHeight = 190;
  addInputSocket("In", scene);
  addOutputSocket("Filters (WIP)", scene, true); // TODO: add serialization for filters

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  rangeSpin = new QDoubleSpinBox;
  rangeSpin->setRange(0, 1e6);
  form->addRow("Range:", rangeSpin);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  targetSlotEdit = new QLineEdit;
  form->addRow("Target Slot:", targetSlotEdit);
  label = form->labelForField(targetSlotEdit);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  autoUnlockTargetBox = new QCheckBox;
  form->addRow("Auto Unlock Target:", autoUnlockTargetBox);
  label = form->labelForField(autoUnlockTargetBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Sensor::Target SensorNodes::TargetNode::serialize()
{
  General::Sensor::Target data;

  data.range = rangeSpin->value();

  std::string marker = targetSlotEdit->text().toStdString();
  if (!marker.empty())
    data.targetSlot = marker;

  if (onceBox->isChecked())
    data.once = true;

  if (enabledBox->isChecked())
    data.enabled = true;

  if (autoUnlockTargetBox->isChecked())
    data.autoUnlockTarget = true;

  return data;
}

SensorNodes::TimeNode::TimeNode(NodeScene *scene)
    : NodeItem("Time", true, 235)
{
  fieldsHeight = 240;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  periodMin = new QDoubleSpinBox;
  periodMin->setRange(0, 24);
  periodMax = new QDoubleSpinBox;
  periodMax->setRange(0, 24);
  form->addRow("Period Min:", periodMin);
  form->addRow("Period Max:", periodMax);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  checkDayBox = new QCheckBox;
  form->addRow("Check Day:", checkDayBox);
  label = form->labelForField(checkDayBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  checkYearBox = new QCheckBox;
  form->addRow("Check Year:", checkYearBox);
  label = form->labelForField(checkYearBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  scaleDayTimeRangeBox = new QCheckBox;
  form->addRow("Scale Day Time Range:", scaleDayTimeRangeBox);
  label = form->labelForField(scaleDayTimeRangeBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Sensor::Time SensorNodes::TimeNode::serialize()
{
  General::Sensor::Time data;

  data.period.push_back(periodMin->value());
  data.period.push_back(periodMax->value());

  if (onceBox->isChecked())
    data.once = true;

  if (enabledBox->isChecked())
    data.enabled = true;

  if (checkDayBox->isChecked())
    data.checkDay = true;

  if (checkYearBox->isChecked())
    data.checkYear = true;

  if (scaleDayTimeRangeBox->isChecked())
    data.scaleDayTimeRange = true;

  return data;
}

SensorNodes::TimerNode::TimerNode(NodeScene *scene)
    : NodeItem("Timer", true, 280)
{
  fieldsHeight = 210;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  nameEdit = new QLineEdit;
  form->addRow("Name:", nameEdit);
  QWidget *label = form->labelForField(nameEdit);
  QColor textColor = gStyleManager.getCurrentStyle().nodeText;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  label = form->labelForField(onceBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  stateCombo = new QComboBox;
  stateCombo->addItems({"", "Paused", "Running", "Stopped", "Any"});
  form->addRow("State:", stateCombo);
  label = form->labelForField(stateCombo);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  timeRemainingMin = new QDoubleSpinBox;
  timeRemainingMin->setRange(0, 1e9);
  timeRemainingMax = new QDoubleSpinBox;
  timeRemainingMax->setRange(0, 1e9);
  form->addRow("Time Remaining Min:", timeRemainingMin);
  label = form->labelForField(timeRemainingMin);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
  form->addRow("Time Remaining Max:", timeRemainingMax);
  label = form->labelForField(timeRemainingMax);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Sensor::Timer SensorNodes::TimerNode::serialize()
{
  General::Sensor::Timer data;

  std::string marker = nameEdit->text().toStdString();
  data.name = marker;

  marker = stateCombo->currentText().toStdString();
  if (!marker.empty())
  {
    if (marker == "Paused")
    {
      data.state = General::Sensor::Timer::TimerStateFlag::Paused;
    }
    else if (marker == "Running")
    {
      data.state = General::Sensor::Timer::TimerStateFlag::Running;
    }
    else if (marker == "Stopped")
    {
      data.state = General::Sensor::Timer::TimerStateFlag::Stopped;
    }
    else if (marker == "Any")
    {
      data.state = General::Sensor::Timer::TimerStateFlag::Any;
    }
  }

  if (timeRemainingMin->value() != 0 || timeRemainingMax->value() != 0)
  {
    data.timeRemainingRange.emplace(timeRemainingMin->value());
    data.timeRemainingRange.emplace(timeRemainingMax->value());
  }

  if (onceBox->isChecked())
    data.once = true;

  if (enabledBox->isChecked())
    data.enabled = true;

  return data;
}

SensorNodes::ValueProviderWrapperNode::ValueProviderWrapperNode(NodeScene *scene)
    : NodeItem("ValueProviderWrapper", true)
{
  fieldsHeight = 130;
  addInputSocket("In", scene);
  addOutputSocket("Sensor", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  passValuesBox = new QCheckBox;
  form->addRow("Pass Values:", passValuesBox);
  label = form->labelForField(passValuesBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Sensor::ValueProviderWrapper SensorNodes::ValueProviderWrapperNode::serialize()
{
  General::Sensor::ValueProviderWrapper data;

  if (onceBox->isChecked())
    data.once = true;

  if (enabledBox->isChecked())
    data.enabled = true;

  if (passValuesBox->isChecked())
    data.passValues = true;

  return data;
}

SensorNodes::WeatherNode::WeatherNode(NodeScene *scene)
    : NodeItem("Weather", true)
{
  fieldsHeight = 130;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  weathersEdit = new QLineEdit;
  weathersEdit->setPlaceholderText("comma-separated assets");
  form->addRow("Weathers:", weathersEdit);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Sensor::Weather SensorNodes::WeatherNode::serialize()
{
  General::Sensor::Weather data;

  std::string marker = weathersEdit->text().toStdString();
  std::string item;
  std::stringstream ss(marker);

  while (std::getline(ss, item, ','))
  {
    data.weathers.push_back(item);
  }

  if (onceBox->isChecked())
    data.once = true;

  if (enabledBox->isChecked())
    data.enabled = true;

  return data;
}

ActionNodes::WeightedActionNode::WeightedActionNode(NodeScene *scene) // TODO: Add serialization for weighted actions
    : NodeItem("WeightedAction", true)
{
  fieldsHeight = 60;
  addInputSocket("In", scene);
  addOutputSocket("Action", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  weightSpin = new QDoubleSpinBox;
  weightSpin->setMinimum(0);
  weightSpin->setMaximum(999999);
  weightSpin->setValue(20.0);
  form->addRow("Weight:", weightSpin);
}

ActionNodes::AddToHostileTargetMemoryNode::AddToHostileTargetMemoryNode(NodeScene *scene)
    : NodeItem("AddToHostileTargetMemory", true)
{
  fieldsHeight = 60;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::AddToHostileTargetMemory ActionNodes::AddToHostileTargetMemoryNode::serialize()
{
  General::Action::AddToHostileTargetMemory data;

  if (onceBox->isChecked())
    data.once = true;

  return data;
}

ActionNodes::AppearanceNode::AppearanceNode(NodeScene *scene)
    : NodeItem("Appearance", true)
{
  fieldsHeight = 100;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  appearanceEdit = new QLineEdit;
  form->addRow("Appearance:", appearanceEdit);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::Appearance ActionNodes::AppearanceNode::serialize()
{
  General::Action::Appearance data;

  std::string marker = appearanceEdit->text().toStdString();
  data.appearance = marker;

  if (onceBox->isChecked())
    data.once = true;

  return data;
}

ActionNodes::ApplyEntityEffectNode::ApplyEntityEffectNode(NodeScene *scene)
    : NodeItem("ApplyEntityEffect", true)
{
  fieldsHeight = 130;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  entityEffectEdit = new QLineEdit;
  form->addRow("Entity Effect:", entityEffectEdit);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  useTargetBox = new QCheckBox;
  form->addRow("Use Target:", useTargetBox);
  label = form->labelForField(useTargetBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::ApplyEntityEffect ActionNodes::ApplyEntityEffectNode::serialize()
{
  General::Action::ApplyEntityEffect data;

  std::string marker = entityEffectEdit->text().toStdString();
  data.entityEffect = marker;

  if (onceBox->isChecked())
    data.once = true;

  if (useTargetBox->isChecked())
    data.useTarget = true;

  return data;
}

ActionNodes::CombatAbilityNode::CombatAbilityNode(NodeScene *scene)
    : NodeItem("CombatAbility", true)
{
  fieldsHeight = 60;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::CombatAbility ActionNodes::CombatAbilityNode::serialize()
{
  General::Action::CombatAbility data;

  if (onceBox->isChecked())
    data.once = true;

  return data;
}

ActionNodes::CompleteTaskNode::CompleteTaskNode(NodeScene *scene)
    : NodeItem("CompleteTask", true, 230)
{
  fieldsHeight = 160;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  slotCombo = new QComboBox;
  slotCombo->addItems({"Status", "Action", "Face"});
  form->addRow("Slot:", slotCombo);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  animationEdit = new QLineEdit;
  form->addRow("Animation:", animationEdit);
  label = form->labelForField(animationEdit);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  playAnimationBox = new QCheckBox;
  form->addRow("Play Animation:", playAnimationBox);
  label = form->labelForField(playAnimationBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::CompleteTask ActionNodes::CompleteTaskNode::serialize()
{
  General::Action::CompleteTask data;

  std::string marker = slotCombo->currentText().toStdString();
  if (marker == "Status")
  {
    data.slot = General::Action::CompleteTask::CompleteTaskFlag::Status;
  }
  else if (marker == "Action")
  {
    data.slot = General::Action::CompleteTask::CompleteTaskFlag::Action;
  }
  else if (marker == "Face")
  {
    data.slot = General::Action::CompleteTask::CompleteTaskFlag::Face;
  }

  if (onceBox->isChecked())
    data.once = true;

  if (playAnimationBox->isChecked())
    data.playAnimation = true;

  marker = animationEdit->text().toStdString();
  if (data.playAnimation && !marker.empty())
    data.animation = marker;

  return data;
}

ActionNodes::CrouchNode::CrouchNode(NodeScene *scene)
    : NodeItem("Crouch", true)
{
  fieldsHeight = 100;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  crouchBox = new QCheckBox;
  form->addRow("Crouch:", crouchBox);
  label = form->labelForField(crouchBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::Crouch ActionNodes::CrouchNode::serialize()
{
  General::Action::Crouch data;

  if (onceBox->isChecked())
    data.once = true;

  if (crouchBox->isChecked())
    data.crouch = true;

  return data;
}

ActionNodes::DelayDespawnNode::DelayDespawnNode(NodeScene *scene)
    : NodeItem("DelayDespawn", true)
{
  fieldsHeight = 130;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  timeSpin = new QDoubleSpinBox;
  timeSpin->setMinimum(0.001);
  timeSpin->setMaximum(999999);
  timeSpin->setValue(1.0);
  form->addRow("Time:", timeSpin);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  shortenBox = new QCheckBox;
  form->addRow("Shorten:", shortenBox);
  label = form->labelForField(shortenBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::DelayDespawn ActionNodes::DelayDespawnNode::serialize()
{
  General::Action::DelayDespawn data;

  data.time = timeSpin->value();

  if (onceBox->isChecked())
    data.once = true;

  if (shortenBox->isChecked())
    data.shorten = true;

  return data;
}

ActionNodes::DespawnNode::DespawnNode(NodeScene *scene)
    : NodeItem("Despawn", true)
{
  fieldsHeight = 100;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  forceBox = new QCheckBox;
  form->addRow("Force:", forceBox);
  label = form->labelForField(forceBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::Despawn ActionNodes::DespawnNode::serialize()
{
  General::Action::Despawn data;

  if (onceBox->isChecked())
    data.once = true;

  if (forceBox->isChecked())
    data.force = true;

  return data;
}

ActionNodes::DieNode::DieNode(NodeScene *scene)
    : NodeItem("Die", true)
{
  fieldsHeight = 60;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::Die ActionNodes::DieNode::serialize()
{
  General::Action::Die data;

  if (onceBox->isChecked())
    data.once = true;

  return data;
}

ActionNodes::DisplayNameNode::DisplayNameNode(NodeScene *scene)
    : NodeItem("DisplayName", true)
{
  fieldsHeight = 100;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  displayNameEdit = new QLineEdit;
  form->addRow("Display Name:", displayNameEdit);
  QWidget *label = form->labelForField(displayNameEdit);
  QColor textColor = gStyleManager.getCurrentStyle().nodeText;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  label = form->labelForField(onceBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::DisplayName ActionNodes::DisplayNameNode::serialize()
{
  General::Action::DisplayName data;

  std::string marker = displayNameEdit->text().toStdString();
  data.displayName = marker;

  if (onceBox->isChecked())
    data.once = true;

  return data;
}

ActionNodes::DropItemNode::DropItemNode(NodeScene *scene)
    : NodeItem("DropItem", true, 295)
{
  fieldsHeight = 280;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  auto *delayWidget = new QWidget;
  auto *delayLayout = new QHBoxLayout(delayWidget);
  delayLayout->setContentsMargins(0, 0, 0, 0);
  delayMinSpin = new QDoubleSpinBox;
  delayMaxSpin = new QDoubleSpinBox;
  delayLayout->addWidget(delayMinSpin);
  delayLayout->addWidget(delayMaxSpin);
  form->addRow("Delay:", delayWidget);
  label = form->labelForField(delayWidget);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  itemEdit = new QLineEdit;
  form->addRow("Item:", itemEdit);
  label = form->labelForField(itemEdit);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  dropListEdit = new QLineEdit;
  form->addRow("Drop List:", dropListEdit);
  label = form->labelForField(dropListEdit);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  throwSpeedSpin = new QDoubleSpinBox;
  throwSpeedSpin->setMaximum(999999);
  form->addRow("Throw Speed:", throwSpeedSpin);
  label = form->labelForField(throwSpeedSpin);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  auto *distanceWidget = new QWidget;
  auto *distanceLayout = new QHBoxLayout(distanceWidget);
  distanceLayout->setContentsMargins(0, 0, 0, 0);
  distanceMinSpin = new QDoubleSpinBox;
  distanceMaxSpin = new QDoubleSpinBox;
  distanceLayout->addWidget(distanceMinSpin);
  distanceLayout->addWidget(distanceMaxSpin);
  form->addRow("Distance:", distanceWidget);
  label = form->labelForField(distanceWidget);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  auto *dropSectorWidget = new QWidget;
  auto *dropSectorLayout = new QHBoxLayout(dropSectorWidget);
  dropSectorLayout->setContentsMargins(0, 0, 0, 0);
  dropSectorMinSpin = new QDoubleSpinBox;
  dropSectorMaxSpin = new QDoubleSpinBox;
  dropSectorLayout->addWidget(dropSectorMinSpin);
  dropSectorLayout->addWidget(dropSectorMaxSpin);
  form->addRow("Drop Sector:", dropSectorWidget);
  label = form->labelForField(dropSectorWidget);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  pitchHighBox = new QCheckBox;
  form->addRow("Pitch High:", pitchHighBox);
  label = form->labelForField(pitchHighBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::DropItem ActionNodes::DropItemNode::serialize()
{
  General::Action::DropItem data;

  if (delayMinSpin->value() != 0 || delayMaxSpin->value() != 0)
  {
    data.delay.emplace(delayMinSpin->value());
    data.delay.emplace(delayMaxSpin->value());
  }

  if (distanceMinSpin->value() != 0 || distanceMaxSpin->value() != 0)
  {
    data.distance.emplace(distanceMinSpin->value());
    data.distance.emplace(distanceMaxSpin->value());
  }

  if (dropSectorMinSpin->value() != 0 || dropSectorMaxSpin->value() != 0)
  {
    data.dropSector.emplace(dropSectorMinSpin->value());
    data.dropSector.emplace(dropSectorMaxSpin->value());
  }

  std::string marker = itemEdit->text().toStdString();
  if (!marker.empty())
  {
    data.item = marker;
  }

  marker = dropListEdit->text().toStdString();
  if (!marker.empty())
  {
    data.dropList = marker;
  }

  if (throwSpeedSpin->value() != 0)
    data.throwSpeed = throwSpeedSpin->value();

  if (onceBox->isChecked())
    data.once = true;

  if (pitchHighBox->isChecked())
    data.pitchHigh = true;

  return data;
}

ActionNodes::FlockStateNode::FlockStateNode(NodeScene *scene)
    : NodeItem("FlockState", true)
{
  fieldsHeight = 100;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  stateEdit = new QLineEdit;
  form->addRow("State:", stateEdit);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::FlockState ActionNodes::FlockStateNode::serialize()
{
  General::Action::FlockState data;

  std::string marker = stateEdit->text().toStdString();
  data.state = marker;

  if (onceBox->isChecked())
    data.once = true;

  return data;
}

ActionNodes::FlockTargetNode::FlockTargetNode(NodeScene *scene)
    : NodeItem("FlockTarget", true)
{
  fieldsHeight = 130;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  clearBox = new QCheckBox;
  form->addRow("Clear:", clearBox);
  label = form->labelForField(clearBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  targetSlotEdit = new QLineEdit;
  form->addRow("Target Slot:", targetSlotEdit);
  label = form->labelForField(targetSlotEdit);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::FlockTarget ActionNodes::FlockTargetNode::serialize()
{
  General::Action::FlockTarget data;

  std::string marker = targetSlotEdit->text().toStdString();
  if (!marker.empty())
    data.targetSlot = marker;

  if (onceBox->isChecked())
    data.once = true;
  if (clearBox->isChecked())
    data.clear = true;

  return data;
}

ActionNodes::IgnoreForAvoidanceNode::IgnoreForAvoidanceNode(NodeScene *scene)
    : NodeItem("IgnoreForAvoidance", true)
{
  fieldsHeight = 100;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  targetSlotEdit = new QLineEdit;
  form->addRow("Target Slot:", targetSlotEdit);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::IgnoreForAvoidance ActionNodes::IgnoreForAvoidanceNode::serialize()
{
  General::Action::IgnoreForAvoidance data;

  std::string marker = targetSlotEdit->text().toStdString();
  data.targetSlot = marker;

  if (onceBox->isChecked())
    data.once = true;

  return data;
}

ActionNodes::InventoryNode::InventoryNode(NodeScene *scene)
    : NodeItem("Inventory", true, 230)
{
  fieldsHeight = 250;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  operationCombo = new QComboBox;
  operationCombo->addItems({"", "Add", "RemoveHeldItem", "SetHotbar", "Equip", "ClearHeldItem", "EquipOffHand", "Remove", "EquipHotbar", "SetOffHand"});
  form->addRow("Operation:", operationCombo);
  label = form->labelForField(operationCombo);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  countSpin = new QSpinBox;
  countSpin->setMinimum(0);
  countSpin->setMaximum(999999);
  form->addRow("Count:", countSpin);
  label = form->labelForField(countSpin);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  itemEdit = new QLineEdit;
  form->addRow("Item:", itemEdit);
  label = form->labelForField(itemEdit);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  useTargetBox = new QCheckBox;
  form->addRow("Use Target:", useTargetBox);
  label = form->labelForField(useTargetBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  slotSpin = new QSpinBox;
  slotSpin->setMinimum(0);
  slotSpin->setMaximum(999);
  form->addRow("Slot:", slotSpin);
  label = form->labelForField(slotSpin);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::Inventory ActionNodes::InventoryNode::serialize()
{
  General::Action::Inventory data;

  std::string marker = operationCombo->currentText().toStdString();
  if (!marker.empty())
  {
    if (marker == "Add")
    {
      data.operation = General::Action::Inventory::OperationFlag::Add;
    }
    else if (marker == "RemoveHeldItem")
    {
      data.operation = General::Action::Inventory::OperationFlag::RemoveHeldItem;
    }
    else if (marker == "SetHotbar")
    {
      data.operation = General::Action::Inventory::OperationFlag::SetHotbar;
    }
    else if (marker == "Equip")
    {
      data.operation = General::Action::Inventory::OperationFlag::Equip;
    }
    else if (marker == "ClearHeldItem")
    {
      data.operation = General::Action::Inventory::OperationFlag::ClearHeldItem;
    }
    else if (marker == "EquipOffHand")
    {
      data.operation = General::Action::Inventory::OperationFlag::EquipOffHand;
    }
    else if (marker == "Remove")
    {
      data.operation = General::Action::Inventory::OperationFlag::Remove;
    }
    else if (marker == "EquipHotbar")
    {
      data.operation = General::Action::Inventory::OperationFlag::EquipHotbar;
    }
    else if (marker == "SetOffHand")
    {
      data.operation = General::Action::Inventory::OperationFlag::SetOffHand;
    }
  }

  marker = itemEdit->text().toStdString();
  if (!marker.empty())
  {
    data.item = marker;
  }

  if (countSpin->value() != 0)
    data.count = countSpin->value();
  if (slotSpin->value() != 0)
    data.slot = slotSpin->value();

  if (onceBox->isChecked())
    data.once = true;

  if (useTargetBox->isChecked())
    data.useTarget = true;

  return data;
}

ActionNodes::JoinFlockNode::JoinFlockNode(NodeScene *scene)
    : NodeItem("JoinFlock", true)
{
  fieldsHeight = 100;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  forceJoinBox = new QCheckBox;
  form->addRow("Force Join:", forceJoinBox);
  label = form->labelForField(forceJoinBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::JoinFlock ActionNodes::JoinFlockNode::serialize()
{
  General::Action::JoinFlock data;

  if (onceBox->isChecked())
    data.once = true;

  if (forceJoinBox->isChecked())
    data.forceJoin = true;

  return data;
}

ActionNodes::LeaveFlockNode::LeaveFlockNode(NodeScene *scene)
    : NodeItem("LeaveFlock", true)
{
  fieldsHeight = 60;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::LeaveFlock ActionNodes::LeaveFlockNode::serialize()
{
  General::Action::LeaveFlock data;

  if (onceBox->isChecked())
    data.once = true;

  return data;
}

ActionNodes::LockOnInteractionTargetNode::LockOnInteractionTargetNode(NodeScene *scene)
    : NodeItem("LockOnInteractionTarget", true)
{
  fieldsHeight = 100;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  targetSlotEdit = new QLineEdit;
  form->addRow("Target Slot:", targetSlotEdit);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::LockOnInteractionTarget ActionNodes::LockOnInteractionTargetNode::serialize()
{
  General::Action::LockOnInteractionTarget data;

  std::string marker = targetSlotEdit->text().toStdString();
  data.targetSlot = marker;

  if (onceBox->isChecked())
    data.once = true;

  return data;
}

ActionNodes::LogNode::LogNode(NodeScene *scene)
    : NodeItem("Log", true)
{
  fieldsHeight = 100;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  messageEdit = new QLineEdit;
  form->addRow("Message:", messageEdit);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::Log ActionNodes::LogNode::serialize()
{
  General::Action::Log data;

  std::string marker = messageEdit->text().toStdString();
  data.message = marker;

  if (onceBox->isChecked())
    data.once = true;

  return data;
}

ActionNodes::ModelAttachmentNode::ModelAttachmentNode(NodeScene *scene)
    : NodeItem("ModelAttachment", true)
{
  fieldsHeight = 130;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  slotEdit = new QLineEdit;
  form->addRow("Slot:", slotEdit);

  attachmentEdit = new QLineEdit;
  form->addRow("Attachment:", attachmentEdit);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::ModelAttachment ActionNodes::ModelAttachmentNode::serialize()
{
  General::Action::ModelAttachment data;

  std::string marker = attachmentEdit->text().toStdString();
  data.attachment = marker;

  marker = slotEdit->text().toStdString();
  data.slot = marker;

  if (onceBox->isChecked())
    data.once = true;

  return data;
}

ActionNodes::MountNode::MountNode(NodeScene *scene)
    : NodeItem("Mount", true, 260)
{
  fieldsHeight = 180;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  anchorXSpin = new QDoubleSpinBox;
  anchorXSpin->setRange(-999999, 999999);
  form->addRow("Anchor X:", anchorXSpin);

  anchorYSpin = new QDoubleSpinBox;
  anchorYSpin->setRange(-999999, 999999);
  form->addRow("Anchor Y:", anchorYSpin);

  anchorZSpin = new QDoubleSpinBox;
  anchorZSpin->setRange(-999999, 999999);
  form->addRow("Anchor Z:", anchorZSpin);

  movementConfigEdit = new QLineEdit;
  form->addRow("Movement Config:", movementConfigEdit);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::Mount ActionNodes::MountNode::serialize()
{
  General::Action::Mount data;

  std::string marker = movementConfigEdit->text().toStdString();
  data.movementConfig = marker;

  data.anchorX = anchorXSpin->value();
  data.anchorY = anchorYSpin->value();
  data.anchorZ = anchorZSpin->value();

  if (onceBox->isChecked())
    data.once = true;

  return data;
}

ActionNodes::NothingNode::NothingNode(NodeScene *scene)
    : NodeItem("Nothing", false)
{
  addInputSocket("In", scene);
}

General::Action::Nothing ActionNodes::NothingNode::serialize()
{
  General::Action::Nothing data;
  return data;
}

ActionNodes::NotifyNode::NotifyNode(NodeScene *scene)
    : NodeItem("Notify", true)
{
  fieldsHeight = 140;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  messageEdit = new QLineEdit;
  form->addRow("Message:", messageEdit);

  slotEdit = new QLineEdit;
  form->addRow("Slot:", slotEdit);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::Notify ActionNodes::NotifyNode::serialize()
{
  General::Action::Notify data;

  std::string marker = messageEdit->text().toStdString();
  data.message = marker;

  marker = slotEdit->text().toStdString();
  data.slot = marker;

  if (onceBox->isChecked())
    data.once = true;

  return data;
}

ActionNodes::OpenBarterShopNode::OpenBarterShopNode(NodeScene *scene)
    : NodeItem("OpenBarterShop", true)
{
  fieldsHeight = 100;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  shopEdit = new QLineEdit;
  form->addRow("Shop:", shopEdit);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::OpenBarterShop ActionNodes::OpenBarterShopNode::serialize()
{
  General::Action::OpenBarterShop data;

  std::string marker = shopEdit->text().toStdString();
  data.shop = marker;

  if (onceBox->isChecked())
    data.once = true;

  return data;
}

ActionNodes::OpenShopNode::OpenShopNode(NodeScene *scene)
    : NodeItem("OpenShop", true)
{
  fieldsHeight = 100;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  shopEdit = new QLineEdit;
  form->addRow("Shop:", shopEdit);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::OpenShop ActionNodes::OpenShopNode::serialize()
{
  General::Action::OpenShop data;

  std::string marker = shopEdit->text().toStdString();
  data.shop = marker;

  if (onceBox->isChecked())
    data.once = true;

  return data;
}

ActionNodes::OverrideAltitudeNode::OverrideAltitudeNode(NodeScene *scene)
    : NodeItem("OverrideAltitude", true, 220)
{
  fieldsHeight = 100;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  auto *altWidget = new QWidget;
  auto *altLayout = new QHBoxLayout(altWidget);
  altLayout->setContentsMargins(0, 0, 0, 0);
  altitudeMinSpin = new QDoubleSpinBox;
  altitudeMinSpin->setRange(-999999, 999999);
  altitudeMaxSpin = new QDoubleSpinBox;
  altitudeMaxSpin->setRange(-999999, 999999);
  altLayout->addWidget(altitudeMinSpin);
  altLayout->addWidget(altitudeMaxSpin);
  form->addRow("Altitude Range:", altWidget);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::OverrideAltitude ActionNodes::OverrideAltitudeNode::serialize()
{
  General::Action::OverrideAltitude data;

  data.desiredAltitudeRange.push_back(altitudeMinSpin->value());
  data.desiredAltitudeRange.push_back(altitudeMaxSpin->value());

  if (onceBox->isChecked())
    data.once = true;

  return data;
}

ActionNodes::OverrideAttitudeNode::OverrideAttitudeNode(NodeScene *scene)
    : NodeItem("OverrideAttitude", true)
{
  fieldsHeight = 140;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  attitudeCombo = new QComboBox;
  attitudeCombo->addItems({"Friendly", "Neutral", "Hostile"});
  form->addRow("Attitude:", attitudeCombo);

  durationSpin = new QDoubleSpinBox;
  durationSpin->setRange(0, 999999);
  form->addRow("Duration:", durationSpin);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::OverrideAttitude ActionNodes::OverrideAttitudeNode::serialize()
{
  General::Action::OverrideAttitude data;

  data.duration = durationSpin->value();

  std::string marker = attitudeCombo->currentText().toStdString();
  if (marker == "Friendly")
  {
    data.attitude = General::AttitudeFlag::Friendly;
  }
  else if (marker == "Neutral")
  {
    data.attitude = General::AttitudeFlag::Neutral;
  }
  else if (marker == "Hostile")
  {
    data.attitude = General::AttitudeFlag::Hostile;
  }

  if (onceBox->isChecked())
    data.once = true;

  return data;
}

ActionNodes::ParentStateNode::ParentStateNode(NodeScene *scene)
    : NodeItem("ParentState", true)
{
  fieldsHeight = 100;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  stateEdit = new QLineEdit;
  form->addRow("State:", stateEdit);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::ParentState ActionNodes::ParentStateNode::serialize()
{
  General::Action::ParentState data;

  std::string marker = stateEdit->text().toStdString();
  data.state = marker;

  if (onceBox->isChecked())
    data.once = true;

  return data;
}

ActionNodes::PickUpItemNode::PickUpItemNode(NodeScene *scene)
    : NodeItem("PickUpItem", true, 245)
{
  fieldsHeight = 180;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  rangeSpin = new QDoubleSpinBox;
  rangeSpin->setRange(0, 999999);
  form->addRow("Range:", rangeSpin);

  itemsEdit = new QLineEdit;
  itemsEdit->setPlaceholderText("Comma-separated items");
  form->addRow("Items:", itemsEdit);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  auto *delayWidget = new QWidget;
  auto *delayLayout = new QHBoxLayout(delayWidget);
  delayLayout->setContentsMargins(0, 0, 0, 0);
  delayMinSpin = new QDoubleSpinBox;
  delayMaxSpin = new QDoubleSpinBox;
  delayLayout->addWidget(delayMinSpin);
  delayLayout->addWidget(delayMaxSpin);
  form->addRow("Delay:", delayWidget);
  label = form->labelForField(delayWidget);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  hooverBox = new QCheckBox;
  form->addRow("Hoover:", hooverBox);
  label = form->labelForField(hooverBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::PickUpItem ActionNodes::PickUpItemNode::serialize()
{
  General::Action::PickUpItem data;

  data.range = rangeSpin->value();

  std::string marker = itemsEdit->text().toStdString();
  std::string item;
  std::stringstream ss(marker);

  while (std::getline(ss, item, ','))
  {
    data.items.push_back(item);
  }

  if (delayMinSpin->value() != 0 || delayMaxSpin->value() != 0)
  {
    data.delay.emplace(delayMinSpin->value());
    data.delay.emplace(delayMaxSpin->value());
  }

  if (onceBox->isChecked())
    data.once = true;

  if (hooverBox->isChecked())
    data.hoover = true;

  return data;
}

ActionNodes::PlaceBlockNode::PlaceBlockNode(NodeScene *scene)
    : NodeItem("PlaceBlock", true, 250)
{
  fieldsHeight = 130;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  rangeSpin = new QDoubleSpinBox;
  rangeSpin->setRange(0, 999999);
  form->addRow("Range:", rangeSpin);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  allowEmptyMaterialsBox = new QCheckBox;
  form->addRow("Allow Empty Materials:", allowEmptyMaterialsBox);
  label = form->labelForField(allowEmptyMaterialsBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::PlaceBlock ActionNodes::PlaceBlockNode::serialize()
{
  General::Action::PlaceBlock data;

  data.range = rangeSpin->value();

  if (onceBox->isChecked())
    data.once = true;

  if (allowEmptyMaterialsBox->isChecked())
    data.allowEmptyMaterials = true;

  return data;
}

ActionNodes::PlaySoundNode::PlaySoundNode(NodeScene *scene)
    : NodeItem("PlaySound", true)
{
  fieldsHeight = 100;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  soundEventIdEdit = new QLineEdit;
  form->addRow("Sound Event ID:", soundEventIdEdit);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::PlaySound ActionNodes::PlaySoundNode::serialize()
{
  General::Action::PlaySound data;

  std::string marker = soundEventIdEdit->text().toStdString();
  data.soundEventId = marker;

  if (onceBox->isChecked())
    data.once = true;

  return data;
}

ActionNodes::RandomNode::RandomNode(NodeScene *scene) // TODO: Add serialization for weighted actions
    : NodeItem("Random", true, 210)
{
  fieldsHeight = 60;
  addInputSocket("In", scene);
  addOutputSocket("Weighted Actions", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

ActionNodes::RecomputePathNode::RecomputePathNode(NodeScene *scene)
    : NodeItem("RecomputePath", true)
{
  fieldsHeight = 60;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::RecomputePath ActionNodes::RecomputePathNode::serialize()
{
  General::Action::RecomputePath data;

  if (onceBox->isChecked())
    data.once = true;

  return data;
}

ActionNodes::ReleaseTargetNode::ReleaseTargetNode(NodeScene *scene)
    : NodeItem("ReleaseTarget", true)
{
  fieldsHeight = 100;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  targetSlotEdit = new QLineEdit;
  form->addRow("Target Slot:", targetSlotEdit);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::ReleaseTarget ActionNodes::ReleaseTargetNode::serialize()
{
  General::Action::ReleaseTarget data;

  std::string marker = targetSlotEdit->text().toStdString();
  data.targetSlot = marker;

  if (onceBox->isChecked())
    data.once = true;

  return data;
}

ActionNodes::RemoveNode::RemoveNode(NodeScene *scene)
    : NodeItem("Remove", true)
{
  fieldsHeight = 100;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  useTargetBox = new QCheckBox;
  form->addRow("Use Target:", useTargetBox);
  label = form->labelForField(useTargetBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::Remove ActionNodes::RemoveNode::serialize()
{
  General::Action::Remove data;

  if (onceBox->isChecked())
    data.once = true;

  if (useTargetBox->isChecked())
    data.useTarget = true;

  return data;
}

ActionNodes::ResetBlockSensorsNode::ResetBlockSensorsNode(NodeScene *scene)
    : NodeItem("ResetBlockSensors", true)
{
  fieldsHeight = 100;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  blockSetsEdit = new QLineEdit;
  blockSetsEdit->setPlaceholderText("Comma-separated block sets");
  form->addRow("Block Sets:", blockSetsEdit);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::ResetBlockSensors ActionNodes::ResetBlockSensorsNode::serialize()
{
  General::Action::ResetBlockSensors data;

  std::string marker = blockSetsEdit->text().toStdString();
  std::string blockSet;
  std::stringstream ss(marker);

  while (std::getline(ss, blockSet, ','))
  {
    data.blockSets.push_back(blockSet);
  }

  if (onceBox->isChecked())
    data.once = true;

  return data;
}

ActionNodes::ResetInstructionsNode::ResetInstructionsNode(NodeScene *scene)
    : NodeItem("ResetInstructions", true)
{
  fieldsHeight = 100;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  instructionsEdit = new QLineEdit;
  instructionsEdit->setPlaceholderText("Comma-separated names");
  form->addRow("Instructions:", instructionsEdit);
  label = form->labelForField(instructionsEdit);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::ResetInstructions ActionNodes::ResetInstructionsNode::serialize()
{
  General::Action::ResetInstructions data;

  std::string marker = instructionsEdit->text().toStdString();
  if (!marker.empty())
  {
    std::string instruction;
    std::stringstream ss(marker);

    while (std::getline(ss, instruction, ','))
    {
      data.instructions->push_back(instruction);
    }
  }

  if (onceBox->isChecked())
    data.once = true;

  return data;
}

ActionNodes::ResetPathNode::ResetPathNode(NodeScene *scene)
    : NodeItem("ResetPath", true)
{
  fieldsHeight = 60;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::ResetPath ActionNodes::ResetPathNode::serialize()
{
  General::Action::ResetPath data;

  if (onceBox->isChecked())
    data.once = true;

  return data;
}

ActionNodes::ResetSearchRaysNode::ResetSearchRaysNode(NodeScene *scene)
    : NodeItem("ResetSearchRays", true)
{
  fieldsHeight = 100;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  namesEdit = new QLineEdit;
  namesEdit->setPlaceholderText("Comma-separated names");
  form->addRow("Names:", namesEdit);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::ResetSearchRays ActionNodes::ResetSearchRaysNode::serialize()
{
  General::Action::ResetSearchRays data;

  std::string marker = namesEdit->text().toStdString();

  std::string name;
  std::stringstream ss(marker);
  while (std::getline(ss, name, ','))
  {
    data.names.push_back(name);
  }

  if (onceBox->isChecked())
    data.once = true;

  return data;
}

ActionNodes::RoleNode::RoleNode(NodeScene *scene)
    : NodeItem("Role", true)
{
  fieldsHeight = 150;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  roleEdit = new QLineEdit;
  form->addRow("Role:", roleEdit);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  changeAppearanceBox = new QCheckBox;
  form->addRow("Change Appearance:", changeAppearanceBox);
  label = form->labelForField(changeAppearanceBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  stateEdit = new QLineEdit;
  form->addRow("State:", stateEdit);
  label = form->labelForField(stateEdit);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::Role ActionNodes::RoleNode::serialize()
{
  General::Action::Role data;

  std::string marker = roleEdit->text().toStdString();
  data.role = marker;

  marker = stateEdit->text().toStdString();
  if (!marker.empty())
    data.state = marker;

  if (onceBox->isChecked())
    data.once = true;

  if (changeAppearanceBox->isChecked())
    data.changeAppearance = true;

  return data;
}

ActionNodes::SequenceNode::SequenceNode(NodeScene *scene)
    : NodeItem("Sequence", true)
{
  fieldsHeight = 120;
  addInputSocket("In", scene);
  addOutputSocket("Actions", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  blockingBox = new QCheckBox;
  form->addRow("Blocking:", blockingBox);
  label = form->labelForField(blockingBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  atomicBox = new QCheckBox;
  form->addRow("Atomic:", atomicBox);
  label = form->labelForField(atomicBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

ActionNodes::SetAlarmNode::SetAlarmNode(NodeScene *scene)
    : NodeItem("SetAlarm", true, 285)
{
  fieldsHeight = 120;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  nameEdit = new QLineEdit;
  form->addRow("Name:", nameEdit);
  QWidget *label = form->labelForField(nameEdit);
  QColor textColor = gStyleManager.getCurrentStyle().nodeText;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  auto *durationWidget = new QWidget;
  auto *durationLayout = new QHBoxLayout(durationWidget);
  durationLayout->setContentsMargins(0, 0, 0, 0);
  durationMinEdit = new QDoubleSpinBox();
  durationMaxEdit = new QDoubleSpinBox();
  durationLayout->addWidget(durationMinEdit);
  durationLayout->addWidget(durationMaxEdit);
  form->addRow("Duration Range:", durationWidget);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  label = form->labelForField(onceBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::SetAlarm ActionNodes::SetAlarmNode::serialize()
{
  General::Action::SetAlarm data;

  std::string marker = nameEdit->text().toStdString();
  data.name = marker;

  data.durationRange.push_back(durationMinEdit->value());
  data.durationRange.push_back(durationMaxEdit->value());

  if (onceBox->isChecked())
    data.once = true;

  return data;
}

ActionNodes::SetBlockToPlaceNode::SetBlockToPlaceNode(NodeScene *scene)
    : NodeItem("SetBlockToPlace", true)
{
  fieldsHeight = 100;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  blockEdit = new QLineEdit;
  form->addRow("Block:", blockEdit);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::SetBlockToPlace ActionNodes::SetBlockToPlaceNode::serialize()
{
  General::Action::SetBlockToPlace data;

  std::string marker = blockEdit->text().toStdString();
  data.block = marker;

  if (onceBox->isChecked())
    data.once = true;

  return data;
}

ActionNodes::SetFlagNode::SetFlagNode(NodeScene *scene)
    : NodeItem("SetFlag", true)
{
  fieldsHeight = 120;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  nameEdit = new QLineEdit;
  form->addRow("Name:", nameEdit);
  QWidget *label = form->labelForField(nameEdit);
  QColor textColor = gStyleManager.getCurrentStyle().nodeText;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  label = form->labelForField(onceBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  setToBox = new QCheckBox;
  form->addRow("Set To:", setToBox);
  label = form->labelForField(setToBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::SetFlag ActionNodes::SetFlagNode::serialize()
{
  General::Action::SetFlag data;

  std::string marker = nameEdit->text().toStdString();
  data.name = marker;

  if (onceBox->isChecked())
    data.once = true;

  if (setToBox->isChecked())
    data.setTo = true;

  return data;
}

ActionNodes::SetInteractableNode::SetInteractableNode(NodeScene *scene)
    : NodeItem("SetInteractable", true)
{
  fieldsHeight = 150;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  interactableBox = new QCheckBox;
  form->addRow("Interactable:", interactableBox);
  label = form->labelForField(interactableBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  hintEdit = new QLineEdit;
  form->addRow("Hint:", hintEdit);
  label = form->labelForField(hintEdit);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  showPromptBox = new QCheckBox;
  form->addRow("Show Prompt:", showPromptBox);
  label = form->labelForField(showPromptBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::SetInteractable ActionNodes::SetInteractableNode::serialize()
{
  General::Action::SetInteractable data;

  std::string marker = hintEdit->text().toStdString();
  if (!marker.empty())
    data.hint = marker;

  if (onceBox->isChecked())
    data.once = true;

  if (interactableBox->isChecked())
    data.interactable = true;

  if (showPromptBox->isChecked())
    data.showPrompt = true;

  return data;
}

ActionNodes::SetLeashPositionNode::SetLeashPositionNode(NodeScene *scene)
    : NodeItem("SetLeashPosition", true)
{
  fieldsHeight = 130;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  toCurrentBox = new QCheckBox;
  form->addRow("To Current:", toCurrentBox);
  label = form->labelForField(toCurrentBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  toTargetBox = new QCheckBox;
  form->addRow("To Target:", toTargetBox);
  label = form->labelForField(toTargetBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::SetLeashPosition ActionNodes::SetLeashPositionNode::serialize()
{
  General::Action::SetLeashPosition data;

  if (onceBox->isChecked())
    data.once = true;

  if (toCurrentBox->isChecked())
    data.toCurrent = true;

  if (toTargetBox->isChecked())
    data.toTarget = true;

  return data;
}

ActionNodes::SetMarkedTargetNode::SetMarkedTargetNode(NodeScene *scene)
    : NodeItem("SetMarkedTarget", true)
{
  fieldsHeight = 100;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  targetSlotEdit = new QLineEdit;
  form->addRow("Target Slot:", targetSlotEdit);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::SetMarkedTarget ActionNodes::SetMarkedTargetNode::serialize()
{
  General::Action::SetMarkedTarget data;

  std::string marker = targetSlotEdit->text().toStdString();
  data.targetSlot = marker;

  if (onceBox->isChecked())
    data.once = true;

  return data;
}

ActionNodes::SetStatNode::SetStatNode(NodeScene *scene)
    : NodeItem("SetStat", true)
{
  fieldsHeight = 160;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  statEdit = new QLineEdit;
  form->addRow("Stat:", statEdit);

  valueSpin = new QDoubleSpinBox;
  valueSpin->setRange(-999999, 999999);
  form->addRow("Value:", valueSpin);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  addBox = new QCheckBox;
  form->addRow("Add:", addBox);
  label = form->labelForField(addBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::SetStat ActionNodes::SetStatNode::serialize()
{
  General::Action::SetStat data;

  std::string marker = statEdit->text().toStdString();
  data.stat = marker;

  data.value = valueSpin->value();

  if (onceBox->isChecked())
    data.once = true;

  if (addBox->isChecked())
    data.add = true;

  return data;
}

ActionNodes::StartObjectiveNode::StartObjectiveNode(NodeScene *scene)
    : NodeItem("StartObjective", true)
{
  fieldsHeight = 100;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  objectiveEdit = new QLineEdit;
  form->addRow("Objective:", objectiveEdit);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::StartObjective ActionNodes::StartObjectiveNode::serialize()
{
  General::Action::StartObjective data;

  std::string marker = objectiveEdit->text().toStdString();
  data.objective = marker;

  if (onceBox->isChecked())
    data.once = true;

  return data;
}

ActionNodes::StateNode::StateNode(NodeScene *scene)
    : NodeItem("State", true)
{
  fieldsHeight = 120;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  stateEdit = new QLineEdit;
  form->addRow("State:", stateEdit);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  clearStateBox = new QCheckBox;
  form->addRow("Clear State:", clearStateBox);
  label = form->labelForField(clearStateBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::State ActionNodes::StateNode::serialize()
{
  General::Action::State data;

  std::string marker = stateEdit->text().toStdString();
  data.state = marker;

  if (onceBox->isChecked())
    data.once = true;

  if (clearStateBox->isChecked())
    data.clearState = true;

  return data;
}

ActionNodes::StorePositionNode::StorePositionNode(NodeScene *scene)
    : NodeItem("StorePosition", true)
{
  fieldsHeight = 100;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  slotEdit = new QLineEdit;
  form->addRow("Slot:", slotEdit);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::StorePosition ActionNodes::StorePositionNode::serialize()
{
  General::Action::StorePosition data;

  std::string marker = slotEdit->text().toStdString();
  data.slot = marker;

  if (onceBox->isChecked())
    data.once = true;

  return data;
}

ActionNodes::TimeoutNode::TimeoutNode(NodeScene *scene)
    : NodeItem("Timeout", true, 285)
{
  fieldsHeight = 120;
  addInputSocket("In", scene);
  addOutputSocket("Action", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  auto *delayWidget = new QWidget;
  auto *delayLayout = new QHBoxLayout(delayWidget);
  delayLayout->setContentsMargins(0, 0, 0, 0);
  delayMinSpin = new QDoubleSpinBox;
  delayMaxSpin = new QDoubleSpinBox;
  delayLayout->addWidget(delayMinSpin);
  delayLayout->addWidget(delayMaxSpin);
  form->addRow("Delay:", delayWidget);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  delayAfterBox = new QCheckBox;
  delayAfterBox->setStyleSheet("color: gray;");
  form->addRow("Delay After:", delayAfterBox);
  label = form->labelForField(delayAfterBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

ActionNodes::TimerContinueNode::TimerContinueNode(NodeScene *scene)
    : NodeItem("TimerContinue", true)
{
  fieldsHeight = 100;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  nameEdit = new QLineEdit;
  form->addRow("Name:", nameEdit);
  auto *label = form->labelForField(nameEdit);
  QColor textColor = gStyleManager.getCurrentStyle().nodeText;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  label = form->labelForField(onceBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::TimerContinue ActionNodes::TimerContinueNode::serialize()
{
  General::Action::TimerContinue data;

  std::string marker = nameEdit->text().toStdString();
  data.name = marker;

  if (onceBox->isChecked())
    data.once = true;

  return data;
}

ActionNodes::TimerModifyNode::TimerModifyNode(NodeScene *scene)
    : NodeItem("TimerModify", true, 285)
{
  fieldsHeight = 230;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  nameEdit = new QLineEdit;
  form->addRow("Name:", nameEdit);
  auto *label = form->labelForField(nameEdit);
  QColor textColor = gStyleManager.getCurrentStyle().nodeText;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  label = form->labelForField(onceBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  addValueSpin = new QDoubleSpinBox;
  addValueSpin->setRange(-999999, 999999);
  addValueSpin->setStyleSheet("color: gray;");
  form->addRow("Add Value:", addValueSpin);
  label = form->labelForField(addValueSpin);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  auto *maxValueWidget = new QWidget;
  auto *maxValueLayout = new QHBoxLayout(maxValueWidget);
  maxValueLayout->setContentsMargins(0, 0, 0, 0);
  maxValueMinSpin = new QDoubleSpinBox;
  maxValueMinSpin->setStyleSheet("color: gray;");
  maxValueMaxSpin = new QDoubleSpinBox;
  maxValueMaxSpin->setStyleSheet("color: gray;");
  maxValueLayout->addWidget(maxValueMinSpin);
  maxValueLayout->addWidget(maxValueMaxSpin);
  form->addRow("Max Value:", maxValueWidget);
  label = form->labelForField(maxValueWidget);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  rateSpin = new QDoubleSpinBox;
  rateSpin->setRange(-999999, 999999);
  rateSpin->setStyleSheet("color: gray;");
  form->addRow("Rate:", rateSpin);
  label = form->labelForField(rateSpin);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  setValueSpin = new QDoubleSpinBox;
  setValueSpin->setRange(-999999, 999999);
  setValueSpin->setStyleSheet("color: gray;");
  form->addRow("Set Value:", setValueSpin);
  label = form->labelForField(setValueSpin);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  repeatingBox = new QCheckBox;
  repeatingBox->setStyleSheet("color: gray;");
  form->addRow("Repeating:", repeatingBox);
  label = form->labelForField(repeatingBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::TimerModify ActionNodes::TimerModifyNode::serialize()
{
  General::Action::TimerModify data;

  std::string marker = nameEdit->text().toStdString();
  data.name = marker;

  if (onceBox->isChecked())
    data.once = true;

  if (addValueSpin->value() != 0)
    data.addValue = addValueSpin->value();

  if (maxValueMinSpin->value() != 0 && maxValueMaxSpin != 0)
  {
    data.maxValue.emplace(maxValueMinSpin->value());
    data.maxValue.emplace(maxValueMaxSpin->value());
  }

  if (rateSpin->value() != 0)
    data.rate = rateSpin->value();

  if (setValueSpin->value() != 0)
    data.setValue = setValueSpin->value();

  if (repeatingBox->isChecked())
    data.repeating = true;

  return data;
}

ActionNodes::TimerPauseNode::TimerPauseNode(NodeScene *scene)
    : NodeItem("TimerPause", true)
{
  fieldsHeight = 100;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  nameEdit = new QLineEdit;
  form->addRow("Name:", nameEdit);
  auto *label = form->labelForField(nameEdit);
  QColor textColor = gStyleManager.getCurrentStyle().nodeText;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  label = form->labelForField(onceBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::TimerPause ActionNodes::TimerPauseNode::serialize()
{
  General::Action::TimerPause data;

  std::string marker = nameEdit->text().toStdString();
  data.name = marker;

  if (onceBox->isChecked())
    data.once = true;

  return data;
}

ActionNodes::TimerRestartNode::TimerRestartNode(NodeScene *scene)
    : NodeItem("TimerRestart", true)
{
  fieldsHeight = 100;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  nameEdit = new QLineEdit;
  form->addRow("Name:", nameEdit);
  auto *label = form->labelForField(nameEdit);
  QColor textColor = gStyleManager.getCurrentStyle().nodeText;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  label = form->labelForField(onceBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::TimerRestart ActionNodes::TimerRestartNode::serialize()
{
  General::Action::TimerRestart data;

  std::string marker = nameEdit->text().toStdString();
  data.name = marker;

  if (onceBox->isChecked())
    data.once = true;

  return data;
}

ActionNodes::TimerStartNode::TimerStartNode(NodeScene *scene)
    : NodeItem("TimerStart", true, 285)
{
  fieldsHeight = 200;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  nameEdit = new QLineEdit;
  form->addRow("Name:", nameEdit);
  auto *label = form->labelForField(nameEdit);
  QColor textColor = gStyleManager.getCurrentStyle().nodeText;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  label = form->labelForField(onceBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  auto *startWidget = new QWidget;
  auto *startLayout = new QHBoxLayout(startWidget);
  startLayout->setContentsMargins(0, 0, 0, 0);
  startValueMinSpin = new QDoubleSpinBox;
  startValueMaxSpin = new QDoubleSpinBox;
  startValueMinSpin->setStyleSheet("color: gray;");
  startValueMaxSpin->setStyleSheet("color: gray;");
  startLayout->addWidget(startValueMinSpin);
  startLayout->addWidget(startValueMaxSpin);
  form->addRow("Start Value:", startWidget);
  label = form->labelForField(startWidget);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  auto *restartWidget = new QWidget;
  auto *restartLayout = new QHBoxLayout(restartWidget);
  restartLayout->setContentsMargins(0, 0, 0, 0);
  restartValueMinSpin = new QDoubleSpinBox;
  restartValueMaxSpin = new QDoubleSpinBox;
  restartValueMinSpin->setStyleSheet("color: gray;");
  restartValueMaxSpin->setStyleSheet("color: gray;");
  restartLayout->addWidget(restartValueMinSpin);
  restartLayout->addWidget(restartValueMaxSpin);
  form->addRow("Restart Value:", restartWidget);
  label = form->labelForField(restartWidget);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  rateSpin = new QDoubleSpinBox;
  rateSpin->setRange(-999999, 999999);
  rateSpin->setStyleSheet("color: gray;");
  form->addRow("Rate:", rateSpin);
  label = form->labelForField(rateSpin);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  repeatingBox = new QCheckBox;
  repeatingBox->setStyleSheet("color: gray;");
  form->addRow("Repeating:", repeatingBox);
  label = form->labelForField(repeatingBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::TimerStart ActionNodes::TimerStartNode::serialize()
{
  General::Action::TimerStart data;

  std::string marker = nameEdit->text().toStdString();
  data.name = marker;

  if (onceBox->isChecked())
    data.once = true;

  if (startValueMinSpin->value() != 0 && startValueMaxSpin != 0)
  {
    data.startValueRange.emplace(startValueMinSpin->value());
    data.startValueRange.emplace(startValueMaxSpin->value());
  }

  if (restartValueMinSpin->value() != 0 && restartValueMaxSpin != 0)
  {
    data.restartValueRange.emplace(restartValueMinSpin->value());
    data.restartValueRange.emplace(restartValueMaxSpin->value());
  }

  if (rateSpin->value() != 0)
    data.rate = rateSpin->value();

  if (repeatingBox->isChecked())
    data.repeating = true;

  return data;
}

ActionNodes::TimerStopNode::TimerStopNode(NodeScene *scene)
    : NodeItem("TimerStop", true)
{
  fieldsHeight = 100;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  nameEdit = new QLineEdit;
  form->addRow("Name:", nameEdit);
  auto *label = form->labelForField(nameEdit);
  QColor textColor = gStyleManager.getCurrentStyle().nodeText;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  label = form->labelForField(onceBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::TimerStop ActionNodes::TimerStopNode::serialize()
{
  General::Action::TimerStop data;

  std::string marker = nameEdit->text().toStdString();
  data.name = marker;

  if (onceBox->isChecked())
    data.once = true;

  return data;
}

ActionNodes::ToggleStateEvaluatorNode::ToggleStateEvaluatorNode(NodeScene *scene)
    : NodeItem("ToggleStateEvaluator", true)
{
  fieldsHeight = 100;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::ToggleStateEvaluator ActionNodes::ToggleStateEvaluatorNode::serialize()
{
  General::Action::ToggleStateEvaluator data;

  if (onceBox->isChecked())
    data.once = true;

  if (enabledBox->isChecked())
    data.enabled = true;

  return data;
}

ActionNodes::TriggerSpawnBeaconNode::TriggerSpawnBeaconNode(NodeScene *scene)
    : NodeItem("TriggerSpawnBeacon", true)
{
  fieldsHeight = 150;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  beaconSpawnEdit = new QLineEdit;
  form->addRow("Beacon Spawn:", beaconSpawnEdit);

  rangeSpin = new QSpinBox;
  rangeSpin->setRange(0, 999999);
  form->addRow("Range:", rangeSpin);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  targetSlotEdit = new QLineEdit;
  targetSlotEdit->setStyleSheet("color: gray;");
  form->addRow("Target Slot:", targetSlotEdit);
  label = form->labelForField(targetSlotEdit);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::TriggerSpawnBeacon ActionNodes::TriggerSpawnBeaconNode::serialize()
{
  General::Action::TriggerSpawnBeacon data;

  data.range = rangeSpin->value();

  std::string marker = beaconSpawnEdit->text().toStdString();
  data.beaconSpawn = marker;

  if (onceBox->isChecked())
    data.once = true;

  marker = targetSlotEdit->text().toStdString();
  if (!marker.empty())
    data.targetSlot = marker;

  return data;
}

ActionNodes::TriggerSpawnersNode::TriggerSpawnersNode(NodeScene *scene)
    : NodeItem("TriggerSpawners", true)
{
  fieldsHeight = 150;
  addInputSocket("In", scene);

  auto layout = static_cast<QVBoxLayout *>(propertiesWidget()->layout());
  auto *formContainer = new QWidget;
  auto *form = new QFormLayout(formContainer);
  layout->addWidget(formContainer);

  rangeSpin = new QSpinBox;
  rangeSpin->setRange(0, 999999);
  form->addRow("Range:", rangeSpin);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  QColor textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  spawnMarkerEdit = new QLineEdit;
  spawnMarkerEdit->setStyleSheet("color: gray;");
  form->addRow("Spawn Marker:", spawnMarkerEdit);
  label = form->labelForField(spawnMarkerEdit);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));

  countSpin = new QSpinBox;
  countSpin->setRange(0, 999999);
  countSpin->setStyleSheet("color: gray;");
  form->addRow("Count:", countSpin);
  label = form->labelForField(countSpin);
  textColor = gStyleManager.getCurrentStyle().nodeTextOptional;
  label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
}

General::Action::TriggerSpawners ActionNodes::TriggerSpawnersNode::serialize()
{
  General::Action::TriggerSpawners data;

  data.range = rangeSpin->value();

  if (onceBox->isChecked())
    data.once = true;

  std::string marker = spawnMarkerEdit->text().toStdString();
  if (!marker.empty())
    data.spawnMarker = marker;

  if (countSpin->value() != 0)
    data.count = countSpin->value();
  return data;
}

nlohmann::json InstructionNode::serializeNode() const
{
  nlohmann::json j;
  j["name"] = nameEdit->text().toStdString();
  j["enabled"] = enabledBox->isChecked();
  j["continue"] = continueBox->isChecked();
  j["blocking"] = blockingBox->isChecked();
  j["atomic"] = atomicBox->isChecked();
  j["weight"] = weightSpin->value();

  return j;
}

void InstructionNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("name"))
    nameEdit->setText(QString::fromStdString(j["name"]));

  if (j.contains("enabled"))
    enabledBox->setChecked(j["enabled"]);

  if (j.contains("continue"))
    continueBox->setChecked(j["continue"]);

  if (j.contains("blocking"))
    blockingBox->setChecked(j["blocking"]);

  if (j.contains("atomic"))
    atomicBox->setChecked(j["atomic"]);

  if (j.contains("weight"))
    weightSpin->setValue(j["weight"]);
}

nlohmann::json CommentNode::serializeNode() const
{
  nlohmann::json j;
  j["comment"] = nameEdit->text().toStdString();
  return j;
}

void CommentNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("comment"))
    nameEdit->setText(QString::fromStdString(j["comment"].get<std::string>()));
}

nlohmann::json SensorNodes::AdjustPositionNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["enabled"] = enabledBox->isChecked();
  j["offsetX"] = offsetX->value();
  j["offsetY"] = offsetY->value();
  j["offsetZ"] = offsetZ->value();
  return j;
}

void SensorNodes::AdjustPositionNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("enabled"))
    enabledBox->setChecked(j["enabled"]);
  if (j.contains("offsetX"))
    offsetX->setValue(j["offsetX"].get<double>());
  if (j.contains("offsetY"))
    offsetY->setValue(j["offsetY"].get<double>());
  if (j.contains("offsetZ"))
    offsetZ->setValue(j["offsetZ"].get<double>());
}

nlohmann::json SensorNodes::AgeNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["enabled"] = enabledBox->isChecked();
  j["ageMin"] = ageMin->value();
  j["ageMax"] = ageMax->value();
  return j;
}

void SensorNodes::AgeNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("enabled"))
    enabledBox->setChecked(j["enabled"]);
  if (j.contains("ageMin"))
    ageMin->setValue(j["ageMin"].get<double>());
  if (j.contains("ageMax"))
    ageMax->setValue(j["ageMax"].get<double>());
}

nlohmann::json SensorNodes::AlarmNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["enabled"] = enabledBox->isChecked();
  j["name"] = nameEdit->text().toStdString();
  j["state"] = stateCombo->currentIndex();
  j["clear"] = clearBox->isChecked();
  return j;
}

void SensorNodes::AlarmNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("enabled"))
    enabledBox->setChecked(j["enabled"]);
  if (j.contains("name"))
    nameEdit->setText(QString::fromStdString(j["name"].get<std::string>()));
  if (j.contains("state"))
    stateCombo->setCurrentIndex(j["state"].get<int>());
  if (j.contains("clear"))
    clearBox->setChecked(j["clear"]);
}

nlohmann::json SensorNodes::AndNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["enabled"] = enabledBox->isChecked();
  j["autoUnlockTargetSlot"] = autoUnlockTargetSlotEdit->text().toStdString();
  return j;
}

void SensorNodes::AndNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("enabled"))
    enabledBox->setChecked(j["enabled"]);
  if (j.contains("autoUnlockTargetSlot"))
    autoUnlockTargetSlotEdit->setText(QString::fromStdString(j["autoUnlockTargetSlot"].get<std::string>()));
}

nlohmann::json SensorNodes::AnimationNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["enabled"] = enabledBox->isChecked();
  j["slot"] = slotCombo->currentIndex();
  j["animation"] = animationEdit->text().toStdString();
  return j;
}

void SensorNodes::AnimationNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("enabled"))
    enabledBox->setChecked(j["enabled"]);
  if (j.contains("slot"))
    slotCombo->setCurrentIndex(j["slot"].get<int>());
  if (j.contains("animation"))
    animationEdit->setText(QString::fromStdString(j["animation"].get<std::string>()));
}

nlohmann::json SensorNodes::AnyNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["enabled"] = enabledBox->isChecked();
  return j;
}

void SensorNodes::AnyNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("enabled"))
    enabledBox->setChecked(j["enabled"]);
}

nlohmann::json SensorNodes::BeaconNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["enabled"] = enabledBox->isChecked();
  j["message"] = messageEdit->text().toStdString();
  j["range"] = rangeSpin->value();
  j["targetSlot"] = targetSlotEdit->text().toStdString();
  j["consumeMessage"] = consumeMessageBox->isChecked();
  return j;
}

void SensorNodes::BeaconNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("enabled"))
    enabledBox->setChecked(j["enabled"]);
  if (j.contains("message"))
    messageEdit->setText(QString::fromStdString(j["message"].get<std::string>()));
  if (j.contains("range"))
    rangeSpin->setValue(j["range"].get<double>());
  if (j.contains("targetSlot"))
    targetSlotEdit->setText(QString::fromStdString(j["targetSlot"].get<std::string>()));
  if (j.contains("consumeMessage"))
    consumeMessageBox->setChecked(j["consumeMessage"]);
}

nlohmann::json SensorNodes::BlockNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["enabled"] = enabledBox->isChecked();
  j["blocks"] = blocksEdit->text().toStdString();
  j["range"] = rangeSpin->value();
  j["maxHeight"] = maxHeightSpin->value();
  j["random"] = randomBox->isChecked();
  j["reserve"] = reserveBox->isChecked();
  return j;
}

void SensorNodes::BlockNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("enabled"))
    enabledBox->setChecked(j["enabled"]);
  if (j.contains("blocks"))
    blocksEdit->setText(QString::fromStdString(j["blocks"].get<std::string>()));
  if (j.contains("range"))
    rangeSpin->setValue(j["range"].get<double>());
  if (j.contains("maxHeight"))
    maxHeightSpin->setValue(j["maxHeight"].get<double>());
  if (j.contains("random"))
    randomBox->setChecked(j["random"]);
  if (j.contains("reserve"))
    reserveBox->setChecked(j["reserve"]);
}

nlohmann::json SensorNodes::BlockChangeNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["enabled"] = enabledBox->isChecked();
  j["range"] = rangeSpin->value();
  j["searchType"] = searchTypeCombo->currentIndex();
  j["targetSlot"] = targetSlotEdit->text().toStdString();
  j["blockSet"] = blockSetEdit->text().toStdString();
  j["eventType"] = eventTypeCombo->currentIndex();
  return j;
}

void SensorNodes::BlockChangeNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("enabled"))
    enabledBox->setChecked(j["enabled"]);
  if (j.contains("range"))
    rangeSpin->setValue(j["range"].get<double>());
  if (j.contains("searchType"))
    searchTypeCombo->setCurrentIndex(j["searchType"].get<int>());
  if (j.contains("targetSlot"))
    targetSlotEdit->setText(QString::fromStdString(j["targetSlot"].get<std::string>()));
  if (j.contains("blockSet"))
    blockSetEdit->setText(QString::fromStdString(j["blockSet"].get<std::string>()));
  if (j.contains("eventType"))
    eventTypeCombo->setCurrentIndex(j["eventType"].get<int>());
}

nlohmann::json SensorNodes::BlockTypeNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["enabled"] = enabledBox->isChecked();
  j["blockSet"] = blockSetEdit->text().toStdString();
  return j;
}

void SensorNodes::BlockTypeNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("enabled"))
    enabledBox->setChecked(j["enabled"]);
  if (j.contains("blockSet"))
    blockSetEdit->setText(QString::fromStdString(j["blockSet"].get<std::string>()));
}

nlohmann::json SensorNodes::CanInteractNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["enabled"] = enabledBox->isChecked();
  j["viewSector"] = viewSectorSpin->value();
  {
    nlohmann::json arr = nlohmann::json::array();
    for (int i = 0; i < attitudesList->count(); ++i)
    {
      auto *item = attitudesList->item(i);
      if (item && item->isSelected())
        arr.push_back(item->text().toStdString());
    }
    j["attitudes"] = arr;
  }
  return j;
}

void SensorNodes::CanInteractNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("enabled"))
    enabledBox->setChecked(j["enabled"]);
  if (j.contains("viewSector"))
    viewSectorSpin->setValue(j["viewSector"].get<double>());
  if (j.contains("attitudes"))
  {
    attitudesList->clearSelection();
    for (const auto &val : j["attitudes"])
    {
      QString qval = QString::fromStdString(val.get<std::string>());
      for (int i = 0; i < attitudesList->count(); ++i)
      {
        if (attitudesList->item(i)->text() == qval)
          attitudesList->item(i)->setSelected(true);
      }
    }
  }
}

nlohmann::json SensorNodes::CanPlaceBlockNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["enabled"] = enabledBox->isChecked();
  j["direction"] = directionCombo->currentIndex();
  j["offset"] = offsetCombo->currentIndex();
  j["retryDelay"] = retryDelaySpin->value();
  j["allowEmptyMaterials"] = allowEmptyMaterialsBox->isChecked();
  return j;
}

void SensorNodes::CanPlaceBlockNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("enabled"))
    enabledBox->setChecked(j["enabled"]);
  if (j.contains("direction"))
    directionCombo->setCurrentIndex(j["direction"].get<int>());
  if (j.contains("offset"))
    offsetCombo->setCurrentIndex(j["offset"].get<int>());
  if (j.contains("retryDelay"))
    retryDelaySpin->setValue(j["retryDelay"].get<double>());
  if (j.contains("allowEmptyMaterials"))
    allowEmptyMaterialsBox->setChecked(j["allowEmptyMaterials"]);
}

nlohmann::json SensorNodes::CombatActionEvaluatorNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["enabled"] = enabledBox->isChecked();
  j["targetInRange"] = targetInRangeBox->isChecked();
  j["allowableDeviation"] = allowableDeviationSpin->value();
  return j;
}

void SensorNodes::CombatActionEvaluatorNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("enabled"))
    enabledBox->setChecked(j["enabled"]);
  if (j.contains("targetInRange"))
    targetInRangeBox->setChecked(j["targetInRange"]);
  if (j.contains("allowableDeviation"))
    allowableDeviationSpin->setValue(j["allowableDeviation"].get<double>());
}

nlohmann::json SensorNodes::CountNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["enabled"] = enabledBox->isChecked();
  j["countMin"] = countMin->value();
  j["countMax"] = countMax->value();
  j["rangeMin"] = rangeMin->value();
  j["rangeMax"] = rangeMax->value();
  j["includeGroups"] = includeGroupsEdit->text().toStdString();
  j["excludeGroups"] = excludeGroupsEdit->text().toStdString();
  return j;
}

void SensorNodes::CountNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("enabled"))
    enabledBox->setChecked(j["enabled"]);
  if (j.contains("countMin"))
    countMin->setValue(j["countMin"].get<int>());
  if (j.contains("countMax"))
    countMax->setValue(j["countMax"].get<int>());
  if (j.contains("rangeMin"))
    rangeMin->setValue(j["rangeMin"].get<double>());
  if (j.contains("rangeMax"))
    rangeMax->setValue(j["rangeMax"].get<double>());
  if (j.contains("includeGroups"))
    includeGroupsEdit->setText(QString::fromStdString(j["includeGroups"].get<std::string>()));
  if (j.contains("excludeGroups"))
    excludeGroupsEdit->setText(QString::fromStdString(j["excludeGroups"].get<std::string>()));
}

nlohmann::json SensorNodes::DamageNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["enabled"] = enabledBox->isChecked();
  j["combat"] = combatBox->isChecked();
  j["friendly"] = friendlyBox->isChecked();
  j["drowning"] = drowningBox->isChecked();
  j["environment"] = environmentBox->isChecked();
  j["other"] = otherBox->isChecked();
  j["targetSlot"] = targetSlotEdit->text().toStdString();
  return j;
}

void SensorNodes::DamageNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("enabled"))
    enabledBox->setChecked(j["enabled"]);
  if (j.contains("combat"))
    combatBox->setChecked(j["combat"]);
  if (j.contains("friendly"))
    friendlyBox->setChecked(j["friendly"]);
  if (j.contains("drowning"))
    drowningBox->setChecked(j["drowning"]);
  if (j.contains("environment"))
    environmentBox->setChecked(j["environment"]);
  if (j.contains("other"))
    otherBox->setChecked(j["other"]);
  if (j.contains("targetSlot"))
    targetSlotEdit->setText(QString::fromStdString(j["targetSlot"].get<std::string>()));
}

nlohmann::json SensorNodes::DroppedItemNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["enabled"] = enabledBox->isChecked();
  j["range"] = rangeSpin->value();
  j["viewSector"] = viewSectorSpin->value();
  j["lineOfSight"] = lineOfSightBox->isChecked();
  j["items"] = itemsEdit->text().toStdString();
  {
    nlohmann::json arr = nlohmann::json::array();
    for (int i = 0; i < attitudesList->count(); ++i)
    {
      auto *item = attitudesList->item(i);
      if (item && item->isSelected())
        arr.push_back(item->text().toStdString());
    }
    j["attitudes"] = arr;
  }
  return j;
}

void SensorNodes::DroppedItemNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("enabled"))
    enabledBox->setChecked(j["enabled"]);
  if (j.contains("range"))
    rangeSpin->setValue(j["range"].get<double>());
  if (j.contains("viewSector"))
    viewSectorSpin->setValue(j["viewSector"].get<double>());
  if (j.contains("lineOfSight"))
    lineOfSightBox->setChecked(j["lineOfSight"]);
  if (j.contains("items"))
    itemsEdit->setText(QString::fromStdString(j["items"].get<std::string>()));
  if (j.contains("attitudes"))
  {
    attitudesList->clearSelection();
    for (const auto &val : j["attitudes"])
    {
      QString qval = QString::fromStdString(val.get<std::string>());
      for (int i = 0; i < attitudesList->count(); ++i)
      {
        if (attitudesList->item(i)->text() == qval)
          attitudesList->item(i)->setSelected(true);
      }
    }
  }
}

nlohmann::json SensorNodes::EntityEventNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["enabled"] = enabledBox->isChecked();
  j["range"] = rangeSpin->value();
  j["searchType"] = searchTypeCombo->currentIndex();
  j["targetSlot"] = targetSlotEdit->text().toStdString();
  j["npcGroup"] = npcGroupEdit->text().toStdString();
  j["eventType"] = eventTypeCombo->currentIndex();
  j["flockOnly"] = flockOnlyBox->isChecked();
  return j;
}

void SensorNodes::EntityEventNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("enabled"))
    enabledBox->setChecked(j["enabled"]);
  if (j.contains("range"))
    rangeSpin->setValue(j["range"].get<double>());
  if (j.contains("searchType"))
    searchTypeCombo->setCurrentIndex(j["searchType"].get<int>());
  if (j.contains("targetSlot"))
    targetSlotEdit->setText(QString::fromStdString(j["targetSlot"].get<std::string>()));
  if (j.contains("npcGroup"))
    npcGroupEdit->setText(QString::fromStdString(j["npcGroup"].get<std::string>()));
  if (j.contains("eventType"))
    eventTypeCombo->setCurrentIndex(j["eventType"].get<int>());
  if (j.contains("flockOnly"))
    flockOnlyBox->setChecked(j["flockOnly"]);
}

nlohmann::json SensorNodes::FlagNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["enabled"] = enabledBox->isChecked();
  j["name"] = nameEdit->text().toStdString();
  j["set"] = setBox->isChecked();
  return j;
}

void SensorNodes::FlagNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("enabled"))
    enabledBox->setChecked(j["enabled"]);
  if (j.contains("name"))
    nameEdit->setText(QString::fromStdString(j["name"].get<std::string>()));
  if (j.contains("set"))
    setBox->setChecked(j["set"]);
}

nlohmann::json SensorNodes::FlockCombatDamageNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["enabled"] = enabledBox->isChecked();
  j["leaderOnly"] = leaderOnlyBox->isChecked();
  return j;
}

void SensorNodes::FlockCombatDamageNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("enabled"))
    enabledBox->setChecked(j["enabled"]);
  if (j.contains("leaderOnly"))
    leaderOnlyBox->setChecked(j["leaderOnly"]);
}

nlohmann::json SensorNodes::FlockLeaderNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["enabled"] = enabledBox->isChecked();
  return j;
}

void SensorNodes::FlockLeaderNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("enabled"))
    enabledBox->setChecked(j["enabled"]);
}

nlohmann::json SensorNodes::HasHostileTargetMemoryNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["enabled"] = enabledBox->isChecked();
  return j;
}

void SensorNodes::HasHostileTargetMemoryNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("enabled"))
    enabledBox->setChecked(j["enabled"]);
}

nlohmann::json SensorNodes::HasInteractedNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["enabled"] = enabledBox->isChecked();
  return j;
}

void SensorNodes::HasInteractedNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("enabled"))
    enabledBox->setChecked(j["enabled"]);
}

nlohmann::json SensorNodes::HasTaskNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["enabled"] = enabledBox->isChecked();
  j["taskById"] = taskByIdEdit->text().toStdString();
  return j;
}

void SensorNodes::HasTaskNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("enabled"))
    enabledBox->setChecked(j["enabled"]);
  if (j.contains("taskById"))
    taskByIdEdit->setText(QString::fromStdString(j["taskById"].get<std::string>()));
}

nlohmann::json SensorNodes::InAirNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["enabled"] = enabledBox->isChecked();
  return j;
}

void SensorNodes::InAirNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("enabled"))
    enabledBox->setChecked(j["enabled"]);
}

nlohmann::json SensorNodes::InWaterNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["enabled"] = enabledBox->isChecked();
  return j;
}

void SensorNodes::InWaterNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("enabled"))
    enabledBox->setChecked(j["enabled"]);
}

nlohmann::json SensorNodes::InflictedDamageNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["enabled"] = enabledBox->isChecked();
  j["target"] = targetCombo->currentIndex();
  j["friendlyFire"] = friendlyFireBox->isChecked();
  return j;
}

void SensorNodes::InflictedDamageNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("enabled"))
    enabledBox->setChecked(j["enabled"]);
  if (j.contains("target"))
    targetCombo->setCurrentIndex(j["target"].get<int>());
  if (j.contains("friendlyFire"))
    friendlyFireBox->setChecked(j["friendlyFire"]);
}

nlohmann::json SensorNodes::InteractionContextNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["enabled"] = enabledBox->isChecked();
  j["context"] = contextEdit->text().toStdString();
  return j;
}

void SensorNodes::InteractionContextNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("enabled"))
    enabledBox->setChecked(j["enabled"]);
  if (j.contains("context"))
    contextEdit->setText(QString::fromStdString(j["context"].get<std::string>()));
}

nlohmann::json SensorNodes::IsBackingAwayNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["enabled"] = enabledBox->isChecked();
  return j;
}

void SensorNodes::IsBackingAwayNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("enabled"))
    enabledBox->setChecked(j["enabled"]);
}

nlohmann::json SensorNodes::IsBusyNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["enabled"] = enabledBox->isChecked();
  return j;
}

void SensorNodes::IsBusyNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("enabled"))
    enabledBox->setChecked(j["enabled"]);
}

nlohmann::json SensorNodes::KillNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["enabled"] = enabledBox->isChecked();
  j["targetSlot"] = targetSlotEdit->text().toStdString();
  return j;
}

void SensorNodes::KillNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("enabled"))
    enabledBox->setChecked(j["enabled"]);
  if (j.contains("targetSlot"))
    targetSlotEdit->setText(QString::fromStdString(j["targetSlot"].get<std::string>()));
}

nlohmann::json SensorNodes::LeashNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["enabled"] = enabledBox->isChecked();
  j["range"] = rangeSpin->value();
  return j;
}

void SensorNodes::LeashNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("enabled"))
    enabledBox->setChecked(j["enabled"]);
  if (j.contains("range"))
    rangeSpin->setValue(j["range"].get<double>());
}

nlohmann::json SensorNodes::LightNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["enabled"] = enabledBox->isChecked();
  j["lightMin"] = lightMin->value();
  j["lightMax"] = lightMax->value();
  j["skyLightMin"] = skyLightMin->value();
  j["skyLightMax"] = skyLightMax->value();
  j["sunlightMin"] = sunlightMin->value();
  j["sunlightMax"] = sunlightMax->value();
  j["redMin"] = redMin->value();
  j["redMax"] = redMax->value();
  j["greenMin"] = greenMin->value();
  j["greenMax"] = greenMax->value();
  j["blueMin"] = blueMin->value();
  j["blueMax"] = blueMax->value();
  j["targetSlot"] = targetSlotEdit->text().toStdString();
  return j;
}

void SensorNodes::LightNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("enabled"))
    enabledBox->setChecked(j["enabled"]);
  if (j.contains("lightMin"))
    lightMin->setValue(j["lightMin"].get<double>());
  if (j.contains("lightMax"))
    lightMax->setValue(j["lightMax"].get<double>());
  if (j.contains("skyLightMin"))
    skyLightMin->setValue(j["skyLightMin"].get<double>());
  if (j.contains("skyLightMax"))
    skyLightMax->setValue(j["skyLightMax"].get<double>());
  if (j.contains("sunlightMin"))
    sunlightMin->setValue(j["sunlightMin"].get<double>());
  if (j.contains("sunlightMax"))
    sunlightMax->setValue(j["sunlightMax"].get<double>());
  if (j.contains("redMin"))
    redMin->setValue(j["redMin"].get<double>());
  if (j.contains("redMax"))
    redMax->setValue(j["redMax"].get<double>());
  if (j.contains("greenMin"))
    greenMin->setValue(j["greenMin"].get<double>());
  if (j.contains("greenMax"))
    greenMax->setValue(j["greenMax"].get<double>());
  if (j.contains("blueMin"))
    blueMin->setValue(j["blueMin"].get<double>());
  if (j.contains("blueMax"))
    blueMax->setValue(j["blueMax"].get<double>());
  if (j.contains("targetSlot"))
    targetSlotEdit->setText(QString::fromStdString(j["targetSlot"].get<std::string>()));
}

nlohmann::json SensorNodes::MobNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["enabled"] = enabledBox->isChecked();
  j["minRange"] = minRangeSpin->value();
  j["range"] = rangeSpin->value();
  j["lockedOnTarget"] = lockedOnTargetBox->isChecked();
  j["lockedTargetSlot"] = lockedTargetSlotEdit->text().toStdString();
  j["autoUnlockTarget"] = autoUnlockTargetBox->isChecked();
  j["onlyLockedTarget"] = onlyLockedTargetBox->isChecked();
  j["ignoredTargetSlot"] = ignoredTargetSlotEdit->text().toStdString();
  j["useProjectedDistance"] = useProjectedDistanceBox->isChecked();
  j["getPlayers"] = getPlayersBox->isChecked();
  j["getNPCs"] = getNPCsBox->isChecked();
  j["excludeOwnType"] = excludeOwnTypeBox->isChecked();
  return j;
}

void SensorNodes::MobNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("enabled"))
    enabledBox->setChecked(j["enabled"]);
  if (j.contains("minRange"))
    minRangeSpin->setValue(j["minRange"].get<double>());
  if (j.contains("range"))
    rangeSpin->setValue(j["range"].get<double>());
  if (j.contains("lockedOnTarget"))
    lockedOnTargetBox->setChecked(j["lockedOnTarget"]);
  if (j.contains("lockedTargetSlot"))
    lockedTargetSlotEdit->setText(QString::fromStdString(j["lockedTargetSlot"].get<std::string>()));
  if (j.contains("autoUnlockTarget"))
    autoUnlockTargetBox->setChecked(j["autoUnlockTarget"]);
  if (j.contains("onlyLockedTarget"))
    onlyLockedTargetBox->setChecked(j["onlyLockedTarget"]);
  if (j.contains("ignoredTargetSlot"))
    ignoredTargetSlotEdit->setText(QString::fromStdString(j["ignoredTargetSlot"].get<std::string>()));
  if (j.contains("useProjectedDistance"))
    useProjectedDistanceBox->setChecked(j["useProjectedDistance"]);
  if (j.contains("getPlayers"))
    getPlayersBox->setChecked(j["getPlayers"]);
  if (j.contains("getNPCs"))
    getNPCsBox->setChecked(j["getNPCs"]);
  if (j.contains("excludeOwnType"))
    excludeOwnTypeBox->setChecked(j["excludeOwnType"]);
}

nlohmann::json SensorNodes::NavNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["enabled"] = enabledBox->isChecked();
  {
    nlohmann::json arr = nlohmann::json::array();
    for (int i = 0; i < navStatesList->count(); ++i)
    {
      auto *item = navStatesList->item(i);
      if (item && item->isSelected())
        arr.push_back(item->text().toStdString());
    }
    j["navStates"] = arr;
  }
  j["throttleDuration"] = throttleDurationSpin->value();
  j["targetDelta"] = targetDeltaSpin->value();
  return j;
}

void SensorNodes::NavNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("enabled"))
    enabledBox->setChecked(j["enabled"]);
  if (j.contains("navStates"))
  {
    navStatesList->clearSelection();
    for (const auto &val : j["navStates"])
    {
      QString qval = QString::fromStdString(val.get<std::string>());
      for (int i = 0; i < navStatesList->count(); ++i)
      {
        if (navStatesList->item(i)->text() == qval)
          navStatesList->item(i)->setSelected(true);
      }
    }
  }
  if (j.contains("throttleDuration"))
    throttleDurationSpin->setValue(j["throttleDuration"].get<double>());
  if (j.contains("targetDelta"))
    targetDeltaSpin->setValue(j["targetDelta"].get<double>());
}

nlohmann::json SensorNodes::NotNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["enabled"] = enabledBox->isChecked();
  j["useTargetSlot"] = useTargetSlotEdit->text().toStdString();
  j["autoUnlockTargetSlot"] = autoUnlockTargetSlotEdit->text().toStdString();
  return j;
}

void SensorNodes::NotNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("enabled"))
    enabledBox->setChecked(j["enabled"]);
  if (j.contains("useTargetSlot"))
    useTargetSlotEdit->setText(QString::fromStdString(j["useTargetSlot"].get<std::string>()));
  if (j.contains("autoUnlockTargetSlot"))
    autoUnlockTargetSlotEdit->setText(QString::fromStdString(j["autoUnlockTargetSlot"].get<std::string>()));
}

nlohmann::json SensorNodes::OnGroundNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["enabled"] = enabledBox->isChecked();
  return j;
}

void SensorNodes::OnGroundNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("enabled"))
    enabledBox->setChecked(j["enabled"]);
}

nlohmann::json SensorNodes::OrNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["enabled"] = enabledBox->isChecked();
  j["autoUnlockTargetSlot"] = autoUnlockTargetSlotEdit->text().toStdString();
  return j;
}

void SensorNodes::OrNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("enabled"))
    enabledBox->setChecked(j["enabled"]);
  if (j.contains("autoUnlockTargetSlot"))
    autoUnlockTargetSlotEdit->setText(QString::fromStdString(j["autoUnlockTargetSlot"].get<std::string>()));
}

nlohmann::json SensorNodes::PathNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["enabled"] = enabledBox->isChecked();
  j["path"] = pathEdit->text().toStdString();
  j["range"] = rangeSpin->value();
  j["pathType"] = pathTypeCombo->currentIndex();
  return j;
}

void SensorNodes::PathNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("enabled"))
    enabledBox->setChecked(j["enabled"]);
  if (j.contains("path"))
    pathEdit->setText(QString::fromStdString(j["path"].get<std::string>()));
  if (j.contains("range"))
    rangeSpin->setValue(j["range"].get<double>());
  if (j.contains("pathType"))
    pathTypeCombo->setCurrentIndex(j["pathType"].get<int>());
}

nlohmann::json SensorNodes::PlayerNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["enabled"] = enabledBox->isChecked();
  j["minRange"] = minRangeSpin->value();
  j["range"] = rangeSpin->value();
  j["lockedOnTarget"] = lockedOnTargetBox->isChecked();
  j["lockedTargetSlot"] = lockedTargetSlotEdit->text().toStdString();
  j["autoUnlockTarget"] = autoUnlockTargetBox->isChecked();
  j["onlyLockedTarget"] = onlyLockedTargetBox->isChecked();
  j["ignoredTargetSlot"] = ignoredTargetSlotEdit->text().toStdString();
  j["useProjectedDistance"] = useProjectedDistanceBox->isChecked();
  return j;
}

void SensorNodes::PlayerNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("enabled"))
    enabledBox->setChecked(j["enabled"]);
  if (j.contains("minRange"))
    minRangeSpin->setValue(j["minRange"].get<double>());
  if (j.contains("range"))
    rangeSpin->setValue(j["range"].get<double>());
  if (j.contains("lockedOnTarget"))
    lockedOnTargetBox->setChecked(j["lockedOnTarget"]);
  if (j.contains("lockedTargetSlot"))
    lockedTargetSlotEdit->setText(QString::fromStdString(j["lockedTargetSlot"].get<std::string>()));
  if (j.contains("autoUnlockTarget"))
    autoUnlockTargetBox->setChecked(j["autoUnlockTarget"]);
  if (j.contains("onlyLockedTarget"))
    onlyLockedTargetBox->setChecked(j["onlyLockedTarget"]);
  if (j.contains("ignoredTargetSlot"))
    ignoredTargetSlotEdit->setText(QString::fromStdString(j["ignoredTargetSlot"].get<std::string>()));
  if (j.contains("useProjectedDistance"))
    useProjectedDistanceBox->setChecked(j["useProjectedDistance"]);
}

nlohmann::json SensorNodes::RandomNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["enabled"] = enabledBox->isChecked();
  j["trueDurMin"] = trueDurMin->value();
  j["trueDurMax"] = trueDurMax->value();
  j["falseDurMin"] = falseDurMin->value();
  j["falseDurMax"] = falseDurMax->value();
  return j;
}

void SensorNodes::RandomNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("enabled"))
    enabledBox->setChecked(j["enabled"]);
  if (j.contains("trueDurMin"))
    trueDurMin->setValue(j["trueDurMin"].get<double>());
  if (j.contains("trueDurMax"))
    trueDurMax->setValue(j["trueDurMax"].get<double>());
  if (j.contains("falseDurMin"))
    falseDurMin->setValue(j["falseDurMin"].get<double>());
  if (j.contains("falseDurMax"))
    falseDurMax->setValue(j["falseDurMax"].get<double>());
}

nlohmann::json SensorNodes::ReadPositionNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["enabled"] = enabledBox->isChecked();
  j["slot"] = slotEdit->text().toStdString();
  j["minRange"] = minRangeSpin->value();
  j["range"] = rangeSpin->value();
  j["useMarkedTarget"] = useMarkedTargetBox->isChecked();
  return j;
}

void SensorNodes::ReadPositionNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("enabled"))
    enabledBox->setChecked(j["enabled"]);
  if (j.contains("slot"))
    slotEdit->setText(QString::fromStdString(j["slot"].get<std::string>()));
  if (j.contains("minRange"))
    minRangeSpin->setValue(j["minRange"].get<double>());
  if (j.contains("range"))
    rangeSpin->setValue(j["range"].get<double>());
  if (j.contains("useMarkedTarget"))
    useMarkedTargetBox->setChecked(j["useMarkedTarget"]);
}

nlohmann::json SensorNodes::SearchRayNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["enabled"] = enabledBox->isChecked();
  j["name"] = nameEdit->text().toStdString();
  j["angle"] = angleSpin->value();
  j["range"] = rangeSpin->value();
  j["blocks"] = blocksEdit->text().toStdString();
  j["minRetestAngle"] = minRetestAngleSpin->value();
  j["minRetestMove"] = minRetestMoveSpin->value();
  j["throttleTime"] = throttleTimeSpin->value();
  return j;
}

void SensorNodes::SearchRayNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("enabled"))
    enabledBox->setChecked(j["enabled"]);
  if (j.contains("name"))
    nameEdit->setText(QString::fromStdString(j["name"].get<std::string>()));
  if (j.contains("angle"))
    angleSpin->setValue(j["angle"].get<double>());
  if (j.contains("range"))
    rangeSpin->setValue(j["range"].get<double>());
  if (j.contains("blocks"))
    blocksEdit->setText(QString::fromStdString(j["blocks"].get<std::string>()));
  if (j.contains("minRetestAngle"))
    minRetestAngleSpin->setValue(j["minRetestAngle"].get<double>());
  if (j.contains("minRetestMove"))
    minRetestMoveSpin->setValue(j["minRetestMove"].get<double>());
  if (j.contains("throttleTime"))
    throttleTimeSpin->setValue(j["throttleTime"].get<double>());
}

nlohmann::json SensorNodes::SelfNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["enabled"] = enabledBox->isChecked();
  return j;
}

void SensorNodes::SelfNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("enabled"))
    enabledBox->setChecked(j["enabled"]);
}

nlohmann::json SensorNodes::StateNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["enabled"] = enabledBox->isChecked();
  j["state"] = stateEdit->text().toStdString();
  j["ignoreMissingSetState"] = ignoreMissingSetStateBox->isChecked();
  return j;
}

void SensorNodes::StateNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("enabled"))
    enabledBox->setChecked(j["enabled"]);
  if (j.contains("state"))
    stateEdit->setText(QString::fromStdString(j["state"].get<std::string>()));
  if (j.contains("ignoreMissingSetState"))
    ignoreMissingSetStateBox->setChecked(j["ignoreMissingSetState"]);
}

nlohmann::json SensorNodes::SwitchNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["enabled"] = enabledBox->isChecked();
  j["switch"] = switchCheckBox->isChecked();
  return j;
}

void SensorNodes::SwitchNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("enabled"))
    enabledBox->setChecked(j["enabled"]);
  if (j.contains("switch"))
    switchCheckBox->setChecked(j["switch"]);
}

nlohmann::json SensorNodes::TargetNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["enabled"] = enabledBox->isChecked();
  j["targetSlot"] = targetSlotEdit->text().toStdString();
  j["range"] = rangeSpin->value();
  j["autoUnlockTarget"] = autoUnlockTargetBox->isChecked();
  return j;
}

void SensorNodes::TargetNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("enabled"))
    enabledBox->setChecked(j["enabled"]);
  if (j.contains("targetSlot"))
    targetSlotEdit->setText(QString::fromStdString(j["targetSlot"].get<std::string>()));
  if (j.contains("range"))
    rangeSpin->setValue(j["range"].get<double>());
  if (j.contains("autoUnlockTarget"))
    autoUnlockTargetBox->setChecked(j["autoUnlockTarget"]);
}

nlohmann::json SensorNodes::TimeNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["enabled"] = enabledBox->isChecked();
  j["periodMin"] = periodMin->value();
  j["periodMax"] = periodMax->value();
  j["checkDay"] = checkDayBox->isChecked();
  j["checkYear"] = checkYearBox->isChecked();
  j["scaleDayTimeRange"] = scaleDayTimeRangeBox->isChecked();
  return j;
}

void SensorNodes::TimeNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("enabled"))
    enabledBox->setChecked(j["enabled"]);
  if (j.contains("periodMin"))
    periodMin->setValue(j["periodMin"].get<double>());
  if (j.contains("periodMax"))
    periodMax->setValue(j["periodMax"].get<double>());
  if (j.contains("checkDay"))
    checkDayBox->setChecked(j["checkDay"]);
  if (j.contains("checkYear"))
    checkYearBox->setChecked(j["checkYear"]);
  if (j.contains("scaleDayTimeRange"))
    scaleDayTimeRangeBox->setChecked(j["scaleDayTimeRange"]);
}

nlohmann::json SensorNodes::TimerNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["enabled"] = enabledBox->isChecked();
  j["name"] = nameEdit->text().toStdString();
  j["state"] = stateCombo->currentIndex();
  j["timeRemainingMin"] = timeRemainingMin->value();
  j["timeRemainingMax"] = timeRemainingMax->value();
  return j;
}

void SensorNodes::TimerNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("enabled"))
    enabledBox->setChecked(j["enabled"]);
  if (j.contains("name"))
    nameEdit->setText(QString::fromStdString(j["name"].get<std::string>()));
  if (j.contains("state"))
    stateCombo->setCurrentIndex(j["state"].get<int>());
  if (j.contains("timeRemainingMin"))
    timeRemainingMin->setValue(j["timeRemainingMin"].get<double>());
  if (j.contains("timeRemainingMax"))
    timeRemainingMax->setValue(j["timeRemainingMax"].get<double>());
}

nlohmann::json SensorNodes::ValueProviderWrapperNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["enabled"] = enabledBox->isChecked();
  j["passValues"] = passValuesBox->isChecked();
  return j;
}

void SensorNodes::ValueProviderWrapperNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("enabled"))
    enabledBox->setChecked(j["enabled"]);
  if (j.contains("passValues"))
    passValuesBox->setChecked(j["passValues"]);
}

nlohmann::json SensorNodes::WeatherNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["enabled"] = enabledBox->isChecked();
  j["weathers"] = weathersEdit->text().toStdString();
  return j;
}

void SensorNodes::WeatherNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("enabled"))
    enabledBox->setChecked(j["enabled"]);
  if (j.contains("weathers"))
    weathersEdit->setText(QString::fromStdString(j["weathers"].get<std::string>()));
}

nlohmann::json ActionNodes::WeightedActionNode::serializeNode() const
{
  nlohmann::json j;
  j["weight"] = weightSpin->value();
  return j;
}

void ActionNodes::WeightedActionNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("weight"))
    weightSpin->setValue(j["weight"].get<double>());
}

nlohmann::json ActionNodes::AddToHostileTargetMemoryNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  return j;
}

void ActionNodes::AddToHostileTargetMemoryNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
}

nlohmann::json ActionNodes::AppearanceNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["appearance"] = appearanceEdit->text().toStdString();
  return j;
}

void ActionNodes::AppearanceNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("appearance"))
    appearanceEdit->setText(QString::fromStdString(j["appearance"].get<std::string>()));
}

nlohmann::json ActionNodes::ApplyEntityEffectNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["entityEffect"] = entityEffectEdit->text().toStdString();
  j["useTarget"] = useTargetBox->isChecked();
  return j;
}

void ActionNodes::ApplyEntityEffectNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("entityEffect"))
    entityEffectEdit->setText(QString::fromStdString(j["entityEffect"].get<std::string>()));
  if (j.contains("useTarget"))
    useTargetBox->setChecked(j["useTarget"]);
}

nlohmann::json ActionNodes::CombatAbilityNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  return j;
}

void ActionNodes::CombatAbilityNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
}

nlohmann::json ActionNodes::CompleteTaskNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["slot"] = slotCombo->currentIndex();
  j["animation"] = animationEdit->text().toStdString();
  j["playAnimation"] = playAnimationBox->isChecked();
  return j;
}

void ActionNodes::CompleteTaskNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("slot"))
    slotCombo->setCurrentIndex(j["slot"].get<int>());
  if (j.contains("animation"))
    animationEdit->setText(QString::fromStdString(j["animation"].get<std::string>()));
  if (j.contains("playAnimation"))
    playAnimationBox->setChecked(j["playAnimation"]);
}

nlohmann::json ActionNodes::CrouchNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["crouch"] = crouchBox->isChecked();
  return j;
}

void ActionNodes::CrouchNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("crouch"))
    crouchBox->setChecked(j["crouch"]);
}

nlohmann::json ActionNodes::DelayDespawnNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["time"] = timeSpin->value();
  j["shorten"] = shortenBox->isChecked();
  return j;
}

void ActionNodes::DelayDespawnNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("time"))
    timeSpin->setValue(j["time"].get<double>());
  if (j.contains("shorten"))
    shortenBox->setChecked(j["shorten"]);
}

nlohmann::json ActionNodes::DespawnNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["force"] = forceBox->isChecked();
  return j;
}

void ActionNodes::DespawnNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("force"))
    forceBox->setChecked(j["force"]);
}

nlohmann::json ActionNodes::DieNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  return j;
}

void ActionNodes::DieNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
}

nlohmann::json ActionNodes::DisplayNameNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["displayName"] = displayNameEdit->text().toStdString();
  return j;
}

void ActionNodes::DisplayNameNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("displayName"))
    displayNameEdit->setText(QString::fromStdString(j["displayName"].get<std::string>()));
}

nlohmann::json ActionNodes::DropItemNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["delayMin"] = delayMinSpin->value();
  j["delayMax"] = delayMaxSpin->value();
  j["item"] = itemEdit->text().toStdString();
  j["dropList"] = dropListEdit->text().toStdString();
  j["throwSpeed"] = throwSpeedSpin->value();
  j["distanceMin"] = distanceMinSpin->value();
  j["distanceMax"] = distanceMaxSpin->value();
  j["dropSectorMin"] = dropSectorMinSpin->value();
  j["dropSectorMax"] = dropSectorMaxSpin->value();
  j["pitchHigh"] = pitchHighBox->isChecked();
  return j;
}

void ActionNodes::DropItemNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("delayMin"))
    delayMinSpin->setValue(j["delayMin"].get<double>());
  if (j.contains("delayMax"))
    delayMaxSpin->setValue(j["delayMax"].get<double>());
  if (j.contains("item"))
    itemEdit->setText(QString::fromStdString(j["item"].get<std::string>()));
  if (j.contains("dropList"))
    dropListEdit->setText(QString::fromStdString(j["dropList"].get<std::string>()));
  if (j.contains("throwSpeed"))
    throwSpeedSpin->setValue(j["throwSpeed"].get<double>());
  if (j.contains("distanceMin"))
    distanceMinSpin->setValue(j["distanceMin"].get<double>());
  if (j.contains("distanceMax"))
    distanceMaxSpin->setValue(j["distanceMax"].get<double>());
  if (j.contains("dropSectorMin"))
    dropSectorMinSpin->setValue(j["dropSectorMin"].get<double>());
  if (j.contains("dropSectorMax"))
    dropSectorMaxSpin->setValue(j["dropSectorMax"].get<double>());
  if (j.contains("pitchHigh"))
    pitchHighBox->setChecked(j["pitchHigh"]);
}

nlohmann::json ActionNodes::FlockStateNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["state"] = stateEdit->text().toStdString();
  return j;
}

void ActionNodes::FlockStateNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("state"))
    stateEdit->setText(QString::fromStdString(j["state"].get<std::string>()));
}

nlohmann::json ActionNodes::FlockTargetNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["clear"] = clearBox->isChecked();
  j["targetSlot"] = targetSlotEdit->text().toStdString();
  return j;
}

void ActionNodes::FlockTargetNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("clear"))
    clearBox->setChecked(j["clear"]);
  if (j.contains("targetSlot"))
    targetSlotEdit->setText(QString::fromStdString(j["targetSlot"].get<std::string>()));
}

nlohmann::json ActionNodes::IgnoreForAvoidanceNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["targetSlot"] = targetSlotEdit->text().toStdString();
  return j;
}

void ActionNodes::IgnoreForAvoidanceNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("targetSlot"))
    targetSlotEdit->setText(QString::fromStdString(j["targetSlot"].get<std::string>()));
}

nlohmann::json ActionNodes::InventoryNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["operation"] = operationCombo->currentIndex();
  j["count"] = countSpin->value();
  j["item"] = itemEdit->text().toStdString();
  j["useTarget"] = useTargetBox->isChecked();
  j["slot"] = slotSpin->value();
  return j;
}

void ActionNodes::InventoryNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("operation"))
    operationCombo->setCurrentIndex(j["operation"].get<int>());
  if (j.contains("count"))
    countSpin->setValue(j["count"].get<int>());
  if (j.contains("item"))
    itemEdit->setText(QString::fromStdString(j["item"].get<std::string>()));
  if (j.contains("useTarget"))
    useTargetBox->setChecked(j["useTarget"]);
  if (j.contains("slot"))
    slotSpin->setValue(j["slot"].get<int>());
}

nlohmann::json ActionNodes::JoinFlockNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["forceJoin"] = forceJoinBox->isChecked();
  return j;
}

void ActionNodes::JoinFlockNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("forceJoin"))
    forceJoinBox->setChecked(j["forceJoin"]);
}

nlohmann::json ActionNodes::LeaveFlockNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  return j;
}

void ActionNodes::LeaveFlockNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
}

nlohmann::json ActionNodes::LockOnInteractionTargetNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["targetSlot"] = targetSlotEdit->text().toStdString();
  return j;
}

void ActionNodes::LockOnInteractionTargetNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("targetSlot"))
    targetSlotEdit->setText(QString::fromStdString(j["targetSlot"].get<std::string>()));
}

nlohmann::json ActionNodes::LogNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["message"] = messageEdit->text().toStdString();
  return j;
}

void ActionNodes::LogNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("message"))
    messageEdit->setText(QString::fromStdString(j["message"].get<std::string>()));
}

nlohmann::json ActionNodes::ModelAttachmentNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["slot"] = slotEdit->text().toStdString();
  j["attachment"] = attachmentEdit->text().toStdString();
  return j;
}

void ActionNodes::ModelAttachmentNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("slot"))
    slotEdit->setText(QString::fromStdString(j["slot"].get<std::string>()));
  if (j.contains("attachment"))
    attachmentEdit->setText(QString::fromStdString(j["attachment"].get<std::string>()));
}

nlohmann::json ActionNodes::MountNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["anchorX"] = anchorXSpin->value();
  j["anchorY"] = anchorYSpin->value();
  j["anchorZ"] = anchorZSpin->value();
  j["movementConfig"] = movementConfigEdit->text().toStdString();
  return j;
}

void ActionNodes::MountNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("anchorX"))
    anchorXSpin->setValue(j["anchorX"].get<double>());
  if (j.contains("anchorY"))
    anchorYSpin->setValue(j["anchorY"].get<double>());
  if (j.contains("anchorZ"))
    anchorZSpin->setValue(j["anchorZ"].get<double>());
  if (j.contains("movementConfig"))
    movementConfigEdit->setText(QString::fromStdString(j["movementConfig"].get<std::string>()));
}

nlohmann::json ActionNodes::NothingNode::serializeNode() const
{
  nlohmann::json j;
  return j;
}

void ActionNodes::NothingNode::deserializeNode(const nlohmann::json &j)
{
}

nlohmann::json ActionNodes::NotifyNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["message"] = messageEdit->text().toStdString();
  j["slot"] = slotEdit->text().toStdString();
  return j;
}

void ActionNodes::NotifyNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("message"))
    messageEdit->setText(QString::fromStdString(j["message"].get<std::string>()));
  if (j.contains("slot"))
    slotEdit->setText(QString::fromStdString(j["slot"].get<std::string>()));
}

nlohmann::json ActionNodes::OpenBarterShopNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["shop"] = shopEdit->text().toStdString();
  return j;
}

void ActionNodes::OpenBarterShopNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("shop"))
    shopEdit->setText(QString::fromStdString(j["shop"].get<std::string>()));
}

nlohmann::json ActionNodes::OpenShopNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["shop"] = shopEdit->text().toStdString();
  return j;
}

void ActionNodes::OpenShopNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("shop"))
    shopEdit->setText(QString::fromStdString(j["shop"].get<std::string>()));
}

nlohmann::json ActionNodes::OverrideAltitudeNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["altitudeMin"] = altitudeMinSpin->value();
  j["altitudeMax"] = altitudeMaxSpin->value();
  return j;
}

void ActionNodes::OverrideAltitudeNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("altitudeMin"))
    altitudeMinSpin->setValue(j["altitudeMin"].get<double>());
  if (j.contains("altitudeMax"))
    altitudeMaxSpin->setValue(j["altitudeMax"].get<double>());
}

nlohmann::json ActionNodes::OverrideAttitudeNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["attitude"] = attitudeCombo->currentIndex();
  j["duration"] = durationSpin->value();
  return j;
}

void ActionNodes::OverrideAttitudeNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("attitude"))
    attitudeCombo->setCurrentIndex(j["attitude"].get<int>());
  if (j.contains("duration"))
    durationSpin->setValue(j["duration"].get<double>());
}

nlohmann::json ActionNodes::ParentStateNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["state"] = stateEdit->text().toStdString();
  return j;
}

void ActionNodes::ParentStateNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("state"))
    stateEdit->setText(QString::fromStdString(j["state"].get<std::string>()));
}

nlohmann::json ActionNodes::PickUpItemNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["delayMin"] = delayMinSpin->value();
  j["delayMax"] = delayMaxSpin->value();
  j["range"] = rangeSpin->value();
  j["hoover"] = hooverBox->isChecked();
  j["items"] = itemsEdit->text().toStdString();
  return j;
}

void ActionNodes::PickUpItemNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("delayMin"))
    delayMinSpin->setValue(j["delayMin"].get<double>());
  if (j.contains("delayMax"))
    delayMaxSpin->setValue(j["delayMax"].get<double>());
  if (j.contains("range"))
    rangeSpin->setValue(j["range"].get<double>());
  if (j.contains("hoover"))
    hooverBox->setChecked(j["hoover"]);
  if (j.contains("items"))
    itemsEdit->setText(QString::fromStdString(j["items"].get<std::string>()));
}

nlohmann::json ActionNodes::PlaceBlockNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["range"] = rangeSpin->value();
  j["allowEmptyMaterials"] = allowEmptyMaterialsBox->isChecked();
  return j;
}

void ActionNodes::PlaceBlockNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("range"))
    rangeSpin->setValue(j["range"].get<double>());
  if (j.contains("allowEmptyMaterials"))
    allowEmptyMaterialsBox->setChecked(j["allowEmptyMaterials"]);
}

nlohmann::json ActionNodes::PlaySoundNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["soundEventId"] = soundEventIdEdit->text().toStdString();
  return j;
}

void ActionNodes::PlaySoundNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("soundEventId"))
    soundEventIdEdit->setText(QString::fromStdString(j["soundEventId"].get<std::string>()));
}

nlohmann::json ActionNodes::RandomNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  return j;
}

void ActionNodes::RandomNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
}

nlohmann::json ActionNodes::RecomputePathNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  return j;
}

void ActionNodes::RecomputePathNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
}

nlohmann::json ActionNodes::ReleaseTargetNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["targetSlot"] = targetSlotEdit->text().toStdString();
  return j;
}

void ActionNodes::ReleaseTargetNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("targetSlot"))
    targetSlotEdit->setText(QString::fromStdString(j["targetSlot"].get<std::string>()));
}

nlohmann::json ActionNodes::RemoveNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["useTarget"] = useTargetBox->isChecked();
  return j;
}

void ActionNodes::RemoveNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("useTarget"))
    useTargetBox->setChecked(j["useTarget"]);
}

nlohmann::json ActionNodes::ResetBlockSensorsNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["blockSets"] = blockSetsEdit->text().toStdString();
  return j;
}

void ActionNodes::ResetBlockSensorsNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("blockSets"))
    blockSetsEdit->setText(QString::fromStdString(j["blockSets"].get<std::string>()));
}

nlohmann::json ActionNodes::ResetInstructionsNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["instructions"] = instructionsEdit->text().toStdString();
  return j;
}

void ActionNodes::ResetInstructionsNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("instructions"))
    instructionsEdit->setText(QString::fromStdString(j["instructions"].get<std::string>()));
}

nlohmann::json ActionNodes::ResetPathNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  return j;
}

void ActionNodes::ResetPathNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
}

nlohmann::json ActionNodes::ResetSearchRaysNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["names"] = namesEdit->text().toStdString();
  return j;
}

void ActionNodes::ResetSearchRaysNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("names"))
    namesEdit->setText(QString::fromStdString(j["names"].get<std::string>()));
}

nlohmann::json ActionNodes::RoleNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["role"] = roleEdit->text().toStdString();
  j["changeAppearance"] = changeAppearanceBox->isChecked();
  j["state"] = stateEdit->text().toStdString();
  return j;
}

void ActionNodes::RoleNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("role"))
    roleEdit->setText(QString::fromStdString(j["role"].get<std::string>()));
  if (j.contains("changeAppearance"))
    changeAppearanceBox->setChecked(j["changeAppearance"]);
  if (j.contains("state"))
    stateEdit->setText(QString::fromStdString(j["state"].get<std::string>()));
}

nlohmann::json ActionNodes::SequenceNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["blocking"] = blockingBox->isChecked();
  j["atomic"] = atomicBox->isChecked();
  return j;
}

void ActionNodes::SequenceNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("blocking"))
    blockingBox->setChecked(j["blocking"]);
  if (j.contains("atomic"))
    atomicBox->setChecked(j["atomic"]);
}

nlohmann::json ActionNodes::SetAlarmNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["name"] = nameEdit->text().toStdString();
  j["durationMin"] = durationMinEdit->value();
  j["durationMax"] = durationMaxEdit->value();
  return j;
}

void ActionNodes::SetAlarmNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("name"))
    nameEdit->setText(QString::fromStdString(j["name"].get<std::string>()));
  if (j.contains("durationMin"))
    durationMinEdit->setValue(j["durationMin"].get<double>());
  if (j.contains("durationMax"))
    durationMaxEdit->setValue(j["durationMax"].get<double>());
}

nlohmann::json ActionNodes::SetBlockToPlaceNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["block"] = blockEdit->text().toStdString();
  return j;
}

void ActionNodes::SetBlockToPlaceNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("block"))
    blockEdit->setText(QString::fromStdString(j["block"].get<std::string>()));
}

nlohmann::json ActionNodes::SetFlagNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["name"] = nameEdit->text().toStdString();
  j["setTo"] = setToBox->isChecked();
  return j;
}

void ActionNodes::SetFlagNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("name"))
    nameEdit->setText(QString::fromStdString(j["name"].get<std::string>()));
  if (j.contains("setTo"))
    setToBox->setChecked(j["setTo"]);
}

nlohmann::json ActionNodes::SetInteractableNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["interactable"] = interactableBox->isChecked();
  j["hint"] = hintEdit->text().toStdString();
  j["showPrompt"] = showPromptBox->isChecked();
  return j;
}

void ActionNodes::SetInteractableNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("interactable"))
    interactableBox->setChecked(j["interactable"]);
  if (j.contains("hint"))
    hintEdit->setText(QString::fromStdString(j["hint"].get<std::string>()));
  if (j.contains("showPrompt"))
    showPromptBox->setChecked(j["showPrompt"]);
}

nlohmann::json ActionNodes::SetLeashPositionNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["toCurrent"] = toCurrentBox->isChecked();
  j["toTarget"] = toTargetBox->isChecked();
  return j;
}

void ActionNodes::SetLeashPositionNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("toCurrent"))
    toCurrentBox->setChecked(j["toCurrent"]);
  if (j.contains("toTarget"))
    toTargetBox->setChecked(j["toTarget"]);
}

nlohmann::json ActionNodes::SetMarkedTargetNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["targetSlot"] = targetSlotEdit->text().toStdString();
  return j;
}

void ActionNodes::SetMarkedTargetNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("targetSlot"))
    targetSlotEdit->setText(QString::fromStdString(j["targetSlot"].get<std::string>()));
}

nlohmann::json ActionNodes::SetStatNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["stat"] = statEdit->text().toStdString();
  j["value"] = valueSpin->value();
  j["add"] = addBox->isChecked();
  return j;
}

void ActionNodes::SetStatNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("stat"))
    statEdit->setText(QString::fromStdString(j["stat"].get<std::string>()));
  if (j.contains("value"))
    valueSpin->setValue(j["value"].get<double>());
  if (j.contains("add"))
    addBox->setChecked(j["add"]);
}

nlohmann::json ActionNodes::StartObjectiveNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["objective"] = objectiveEdit->text().toStdString();
  return j;
}

void ActionNodes::StartObjectiveNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("objective"))
    objectiveEdit->setText(QString::fromStdString(j["objective"].get<std::string>()));
}

nlohmann::json ActionNodes::StateNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["state"] = stateEdit->text().toStdString();
  j["clearState"] = clearStateBox->isChecked();
  return j;
}

void ActionNodes::StateNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("state"))
    stateEdit->setText(QString::fromStdString(j["state"].get<std::string>()));
  if (j.contains("clearState"))
    clearStateBox->setChecked(j["clearState"]);
}

nlohmann::json ActionNodes::StorePositionNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["slot"] = slotEdit->text().toStdString();
  return j;
}

void ActionNodes::StorePositionNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("slot"))
    slotEdit->setText(QString::fromStdString(j["slot"].get<std::string>()));
}

nlohmann::json ActionNodes::TimeoutNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["delayMin"] = delayMinSpin->value();
  j["delayMax"] = delayMaxSpin->value();
  j["delayAfter"] = delayAfterBox->isChecked();
  return j;
}

void ActionNodes::TimeoutNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("delayMin"))
    delayMinSpin->setValue(j["delayMin"].get<double>());
  if (j.contains("delayMax"))
    delayMaxSpin->setValue(j["delayMax"].get<double>());
  if (j.contains("delayAfter"))
    delayAfterBox->setChecked(j["delayAfter"]);
}

nlohmann::json ActionNodes::TimerContinueNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["name"] = nameEdit->text().toStdString();
  return j;
}

void ActionNodes::TimerContinueNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("name"))
    nameEdit->setText(QString::fromStdString(j["name"].get<std::string>()));
}

nlohmann::json ActionNodes::TimerModifyNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["name"] = nameEdit->text().toStdString();
  j["addValue"] = addValueSpin->value();
  j["maxValueMin"] = maxValueMinSpin->value();
  j["maxValueMax"] = maxValueMaxSpin->value();
  j["rate"] = rateSpin->value();
  j["setValue"] = setValueSpin->value();
  j["repeating"] = repeatingBox->isChecked();
  return j;
}

void ActionNodes::TimerModifyNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("name"))
    nameEdit->setText(QString::fromStdString(j["name"].get<std::string>()));
  if (j.contains("addValue"))
    addValueSpin->setValue(j["addValue"].get<double>());
  if (j.contains("maxValueMin"))
    maxValueMinSpin->setValue(j["maxValueMin"].get<double>());
  if (j.contains("maxValueMax"))
    maxValueMaxSpin->setValue(j["maxValueMax"].get<double>());
  if (j.contains("rate"))
    rateSpin->setValue(j["rate"].get<double>());
  if (j.contains("setValue"))
    setValueSpin->setValue(j["setValue"].get<double>());
  if (j.contains("repeating"))
    repeatingBox->setChecked(j["repeating"]);
}

nlohmann::json ActionNodes::TimerPauseNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["name"] = nameEdit->text().toStdString();
  return j;
}

void ActionNodes::TimerPauseNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("name"))
    nameEdit->setText(QString::fromStdString(j["name"].get<std::string>()));
}

nlohmann::json ActionNodes::TimerRestartNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["name"] = nameEdit->text().toStdString();
  return j;
}

void ActionNodes::TimerRestartNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("name"))
    nameEdit->setText(QString::fromStdString(j["name"].get<std::string>()));
}

nlohmann::json ActionNodes::TimerStartNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["name"] = nameEdit->text().toStdString();
  j["startValueMin"] = startValueMinSpin->value();
  j["startValueMax"] = startValueMaxSpin->value();
  j["restartValueMin"] = restartValueMinSpin->value();
  j["restartValueMax"] = restartValueMaxSpin->value();
  j["rate"] = rateSpin->value();
  j["repeating"] = repeatingBox->isChecked();
  return j;
}

void ActionNodes::TimerStartNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("name"))
    nameEdit->setText(QString::fromStdString(j["name"].get<std::string>()));
  if (j.contains("startValueMin"))
    startValueMinSpin->setValue(j["startValueMin"].get<double>());
  if (j.contains("startValueMax"))
    startValueMaxSpin->setValue(j["startValueMax"].get<double>());
  if (j.contains("restartValueMin"))
    restartValueMinSpin->setValue(j["restartValueMin"].get<double>());
  if (j.contains("restartValueMax"))
    restartValueMaxSpin->setValue(j["restartValueMax"].get<double>());
  if (j.contains("rate"))
    rateSpin->setValue(j["rate"].get<double>());
  if (j.contains("repeating"))
    repeatingBox->setChecked(j["repeating"]);
}

nlohmann::json ActionNodes::TimerStopNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["name"] = nameEdit->text().toStdString();
  return j;
}

void ActionNodes::TimerStopNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("name"))
    nameEdit->setText(QString::fromStdString(j["name"].get<std::string>()));
}

nlohmann::json ActionNodes::ToggleStateEvaluatorNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["enabled"] = enabledBox->isChecked();
  return j;
}

void ActionNodes::ToggleStateEvaluatorNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("enabled"))
    enabledBox->setChecked(j["enabled"]);
}

nlohmann::json ActionNodes::TriggerSpawnBeaconNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["beaconSpawn"] = beaconSpawnEdit->text().toStdString();
  j["range"] = rangeSpin->value();
  j["targetSlot"] = targetSlotEdit->text().toStdString();
  return j;
}

void ActionNodes::TriggerSpawnBeaconNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("beaconSpawn"))
    beaconSpawnEdit->setText(QString::fromStdString(j["beaconSpawn"].get<std::string>()));
  if (j.contains("range"))
    rangeSpin->setValue(j["range"].get<int>());
  if (j.contains("targetSlot"))
    targetSlotEdit->setText(QString::fromStdString(j["targetSlot"].get<std::string>()));
}

nlohmann::json ActionNodes::TriggerSpawnersNode::serializeNode() const
{
  nlohmann::json j;
  j["once"] = onceBox->isChecked();
  j["spawnMarker"] = spawnMarkerEdit->text().toStdString();
  j["range"] = rangeSpin->value();
  j["count"] = countSpin->value();
  return j;
}

void ActionNodes::TriggerSpawnersNode::deserializeNode(const nlohmann::json &j)
{
  if (j.contains("once"))
    onceBox->setChecked(j["once"]);
  if (j.contains("spawnMarker"))
    spawnMarkerEdit->setText(QString::fromStdString(j["spawnMarker"].get<std::string>()));
  if (j.contains("range"))
    rangeSpin->setValue(j["range"].get<int>());
  if (j.contains("count"))
    countSpin->setValue(j["count"].get<int>());
}