#include "nodes.hpp"
#include <QComboBox>

RootNode::RootNode(NodeScene *scene)
    : NodeItem("Root")
{
  deletable = false;
  addOutputSocket("Instructions", scene);
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

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  QWidget *label = form->labelForField(enabledBox);
  label->setStyleSheet("color: gray;");

  continueBox = new QCheckBox;
  continueBox->setStyleSheet("color: gray;");
  form->addRow("Continue:", continueBox);
  label = form->labelForField(continueBox);
  label->setStyleSheet("color: gray;");

  blockingBox = new QCheckBox;
  blockingBox->setStyleSheet("color: gray;");
  form->addRow("Actions Blocking:", blockingBox);
  label = form->labelForField(blockingBox);
  label->setStyleSheet("color: gray;");

  atomicBox = new QCheckBox;
  atomicBox->setStyleSheet("color: gray;");
  form->addRow("Actions Atomic:", atomicBox);
  label = form->labelForField(atomicBox);
  label->setStyleSheet("color: gray;");

  weightSpin = new QSpinBox;
  weightSpin->setMinimum(0);
  weightSpin->setMaximum(100000);
  weightSpin->setStyleSheet("color: gray;");
  form->addRow("Weight:", weightSpin);
  label = form->labelForField(weightSpin);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  label->setStyleSheet("color: gray;");
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

  stateCombo = new QComboBox;
  stateCombo->addItems({"Set", "Unset", "Passed"});
  form->addRow("State:", stateCombo);

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  label->setStyleSheet("color: gray;");

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  label->setStyleSheet("color: gray;");

  clearBox = new QCheckBox;
  form->addRow("Clear:", clearBox);
  label = form->labelForField(clearBox);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  label->setStyleSheet("color: gray;");

  autoUnlockTargetSlotEdit = new QLineEdit;
  form->addRow("Auto Unlock Target Slot:", autoUnlockTargetSlotEdit);
  label = form->labelForField(autoUnlockTargetSlotEdit);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  label->setStyleSheet("color: gray;");
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

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  label->setStyleSheet("color: gray;");

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  label->setStyleSheet("color: gray;");

  rangeSpin = new QDoubleSpinBox;
  rangeSpin->setRange(0, 1e6);
  form->addRow("Range:", rangeSpin);
  label = form->labelForField(rangeSpin);
  label->setStyleSheet("color: gray;");

  targetSlotEdit = new QLineEdit;
  form->addRow("Target Slot:", targetSlotEdit);
  label = form->labelForField(targetSlotEdit);
  label->setStyleSheet("color: gray;");

  consumeMessageBox = new QCheckBox;
  form->addRow("Consume Message:", consumeMessageBox);
  label = form->labelForField(consumeMessageBox);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  label->setStyleSheet("color: gray;");

  targetSlotEdit = new QLineEdit;
  form->addRow("Target Slot:", targetSlotEdit);
  label = form->labelForField(targetSlotEdit);
  label->setStyleSheet("color: gray;");

  eventTypeCombo = new QComboBox;
  eventTypeCombo->addItems({"(None)", "Destruction", "Interaction", "Damage"});
  form->addRow("Event Type:", eventTypeCombo);
  label = form->labelForField(eventTypeCombo);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  label->setStyleSheet("color: gray;");

  offsetCombo = new QComboBox;
  offsetCombo->addItems({"", "BodyPosition", "FootPosition", "HeadPosition"});
  form->addRow("Offset:", offsetCombo);
  label = form->labelForField(offsetCombo);
  label->setStyleSheet("color: gray;");

  retryDelaySpin = new QDoubleSpinBox;
  retryDelaySpin->setRange(0, 1e6);
  form->addRow("Retry Delay:", retryDelaySpin);
  label = form->labelForField(retryDelaySpin);
  label->setStyleSheet("color: gray;");

  allowEmptyMaterialsBox = new QCheckBox;
  form->addRow("Allow Empty Materials:", allowEmptyMaterialsBox);
  label = form->labelForField(allowEmptyMaterialsBox);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  label->setStyleSheet("color: gray;");

  allowableDeviationSpin = new QDoubleSpinBox;
  allowableDeviationSpin->setRange(0, 1e6);
  form->addRow("Allowable Deviation:", allowableDeviationSpin);
  label = form->labelForField(allowableDeviationSpin);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  label->setStyleSheet("color: gray;");

  includeGroupsEdit = new QLineEdit;
  includeGroupsEdit->setPlaceholderText("comma-separated assets");
  form->addRow("Include Groups:", includeGroupsEdit);
  label = form->labelForField(includeGroupsEdit);
  label->setStyleSheet("color: gray;");

  excludeGroupsEdit = new QLineEdit;
  excludeGroupsEdit->setPlaceholderText("comma-separated assets");
  form->addRow("Exclude Groups:", excludeGroupsEdit);
  label = form->labelForField(excludeGroupsEdit);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  label->setStyleSheet("color: gray;");

  combatBox = new QCheckBox;
  form->addRow("Combat:", combatBox);
  label = form->labelForField(combatBox);
  label->setStyleSheet("color: gray;");

  friendlyBox = new QCheckBox;
  form->addRow("Friendly:", friendlyBox);
  label = form->labelForField(friendlyBox);
  label->setStyleSheet("color: gray;");

  drowningBox = new QCheckBox;
  form->addRow("Drowning:", drowningBox);
  label = form->labelForField(drowningBox);
  label->setStyleSheet("color: gray;");

  environmentBox = new QCheckBox;
  form->addRow("Environment:", environmentBox);
  label = form->labelForField(environmentBox);
  label->setStyleSheet("color: gray;");

  otherBox = new QCheckBox;
  form->addRow("Other:", otherBox);
  label = form->labelForField(otherBox);
  label->setStyleSheet("color: gray;");

  targetSlotEdit = new QLineEdit;
  form->addRow("Target Slot:", targetSlotEdit);
  label = form->labelForField(targetSlotEdit);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  label->setStyleSheet("color: gray;");

  lineOfSightBox = new QCheckBox;
  form->addRow("Line Of Sight:", lineOfSightBox);
  label = form->labelForField(lineOfSightBox);
  label->setStyleSheet("color: gray;");

  itemsEdit = new QLineEdit;
  itemsEdit->setPlaceholderText("comma-separated assets");
  form->addRow("Items:", itemsEdit);
  label = form->labelForField(itemsEdit);
  label->setStyleSheet("color: gray;");

  attitudesList = new QListWidget;
  attitudesList->setSelectionMode(QAbstractItemView::MultiSelection);
  attitudesList->addItems({"Neutral", "Ignore", "Like", "Love", "Dislike"});
  form->addRow("Attitudes:", attitudesList);
  label = form->labelForField(attitudesList);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  label->setStyleSheet("color: gray;");

  searchTypeCombo = new QComboBox;
  searchTypeCombo->addItems({"", "NpcOnly", "PlayerFirst", "PlayerOnly", "NpcFirst"});
  form->addRow("Search Type:", searchTypeCombo);
  label = form->labelForField(searchTypeCombo);
  label->setStyleSheet("color: gray;");

  targetSlotEdit = new QLineEdit;
  form->addRow("Target Slot:", targetSlotEdit);
  label = form->labelForField(targetSlotEdit);
  label->setStyleSheet("color: gray;");

  flockOnlyBox = new QCheckBox;
  form->addRow("Flock Only:", flockOnlyBox);
  label = form->labelForField(flockOnlyBox);
  label->setStyleSheet("color: gray;");
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

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  label->setStyleSheet("color: gray;");

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  label->setStyleSheet("color: gray;");

  setBox = new QCheckBox;
  form->addRow("Set:", setBox);
  label = form->labelForField(setBox);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  label->setStyleSheet("color: gray;");

  leaderOnlyBox = new QCheckBox;
  form->addRow("Leader Only:", leaderOnlyBox);
  label = form->labelForField(leaderOnlyBox);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  label->setStyleSheet("color: gray;");

  targetCombo = new QComboBox;
  targetCombo->addItems({"", "FlockLeader", "Self", "Flock"});
  form->addRow("Target:", targetCombo);
  label = form->labelForField(targetCombo);
  label->setStyleSheet("color: gray;");

  friendlyFireBox = new QCheckBox;
  form->addRow("Friendly Fire:", friendlyFireBox);
  label = form->labelForField(friendlyFireBox);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  label->setStyleSheet("color: gray;");

  targetSlotEdit = new QLineEdit;
  form->addRow("Target Slot:", targetSlotEdit);
  label = form->labelForField(targetSlotEdit);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  label->setStyleSheet("color: gray;");

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
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  label->setStyleSheet("color: gray;");

  minRangeSpin = new QDoubleSpinBox;
  minRangeSpin->setRange(0, 1e6);
  form->addRow("Min Range:", minRangeSpin);
  label = form->labelForField(minRangeSpin);
  label->setStyleSheet("color: gray;");

  lockedOnTargetBox = new QCheckBox;
  form->addRow("Locked On Target:", lockedOnTargetBox);
  label = form->labelForField(lockedOnTargetBox);
  label->setStyleSheet("color: gray;");

  lockedTargetSlotEdit = new QLineEdit;
  form->addRow("Locked Target Slot:", lockedTargetSlotEdit);
  label = form->labelForField(lockedTargetSlotEdit);
  label->setStyleSheet("color: gray;");

  autoUnlockTargetBox = new QCheckBox;
  form->addRow("Auto Unlock Target:", autoUnlockTargetBox);
  label = form->labelForField(autoUnlockTargetBox);
  label->setStyleSheet("color: gray;");

  onlyLockedTargetBox = new QCheckBox;
  form->addRow("Only Locked Target:", onlyLockedTargetBox);
  label = form->labelForField(onlyLockedTargetBox);
  label->setStyleSheet("color: gray;");

  ignoredTargetSlotEdit = new QLineEdit;
  form->addRow("Ignored Target Slot:", ignoredTargetSlotEdit);
  label = form->labelForField(ignoredTargetSlotEdit);
  label->setStyleSheet("color: gray;");

  useProjectedDistanceBox = new QCheckBox;
  form->addRow("Use Projected Distance:", useProjectedDistanceBox);
  label = form->labelForField(useProjectedDistanceBox);
  label->setStyleSheet("color: gray;");

  getPlayersBox = new QCheckBox;
  form->addRow("Get Players:", getPlayersBox);
  label = form->labelForField(getPlayersBox);
  label->setStyleSheet("color: gray;");

  getNPCsBox = new QCheckBox;
  form->addRow("Get NPCs:", getNPCsBox);
  label = form->labelForField(getNPCsBox);
  label->setStyleSheet("color: gray;");

  excludeOwnTypeBox = new QCheckBox;
  form->addRow("Exclude Own Type:", excludeOwnTypeBox);
  label = form->labelForField(excludeOwnTypeBox);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  label->setStyleSheet("color: gray;");

  navStatesList = new QListWidget;
  navStatesList->setSelectionMode(QAbstractItemView::MultiSelection);
  navStatesList->addItems({"Progressing", "Init", "At_Goal", "Blocked", "Aborted", "Defer"});
  form->addRow("Nav States:", navStatesList);
  label = form->labelForField(navStatesList);
  label->setStyleSheet("color: gray;");

  throttleDurationSpin = new QDoubleSpinBox;
  throttleDurationSpin->setRange(0, 1e6);
  form->addRow("Throttle Duration:", throttleDurationSpin);
  label = form->labelForField(throttleDurationSpin);
  label->setStyleSheet("color: gray;");

  targetDeltaSpin = new QDoubleSpinBox;
  targetDeltaSpin->setRange(0, 1e6);
  form->addRow("Target Delta:", targetDeltaSpin);
  label = form->labelForField(targetDeltaSpin);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  label->setStyleSheet("color: gray;");

  useTargetSlotEdit = new QLineEdit;
  form->addRow("Use Target Slot:", useTargetSlotEdit);
  label = form->labelForField(useTargetSlotEdit);
  label->setStyleSheet("color: gray;");

  autoUnlockTargetSlotEdit = new QLineEdit;
  form->addRow("Auto Unlock Target Slot:", autoUnlockTargetSlotEdit);
  label = form->labelForField(autoUnlockTargetSlotEdit);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  label->setStyleSheet("color: gray;");

  autoUnlockTargetSlotEdit = new QLineEdit;
  form->addRow("Auto Unlock Target Slot:", autoUnlockTargetSlotEdit);
  label = form->labelForField(autoUnlockTargetSlotEdit);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  label->setStyleSheet("color: gray;");

  pathEdit = new QLineEdit;
  form->addRow("Path:", pathEdit);
  label = form->labelForField(pathEdit);
  label->setStyleSheet("color: gray;");

  rangeSpin = new QDoubleSpinBox;
  rangeSpin->setRange(0, 1e6);
  form->addRow("Range:", rangeSpin);
  label = form->labelForField(rangeSpin);
  label->setStyleSheet("color: gray;");

  pathTypeCombo = new QComboBox;
  pathTypeCombo->addItems({"", "CurrentPrefabPath", "TransientPath", "AnyPrefabPath", "WorldPath"});
  form->addRow("Path Type:", pathTypeCombo);
  label = form->labelForField(pathTypeCombo);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  label->setStyleSheet("color: gray;");

  minRangeSpin = new QDoubleSpinBox;
  minRangeSpin->setRange(0, 1e6);
  form->addRow("Min Range:", minRangeSpin);
  label = form->labelForField(minRangeSpin);
  label->setStyleSheet("color: gray;");

  lockedOnTargetBox = new QCheckBox;
  form->addRow("Locked On Target:", lockedOnTargetBox);
  label = form->labelForField(lockedOnTargetBox);
  label->setStyleSheet("color: gray;");

  lockedTargetSlotEdit = new QLineEdit;
  form->addRow("Locked Target Slot:", lockedTargetSlotEdit);
  label = form->labelForField(lockedTargetSlotEdit);
  label->setStyleSheet("color: gray;");

  autoUnlockTargetBox = new QCheckBox;
  form->addRow("Auto Unlock Target:", autoUnlockTargetBox);
  label = form->labelForField(autoUnlockTargetBox);
  label->setStyleSheet("color: gray;");

  onlyLockedTargetBox = new QCheckBox;
  form->addRow("Only Locked Target:", onlyLockedTargetBox);
  label = form->labelForField(onlyLockedTargetBox);
  label->setStyleSheet("color: gray;");

  ignoredTargetSlotEdit = new QLineEdit;
  form->addRow("Ignored Target Slot:", ignoredTargetSlotEdit);
  label = form->labelForField(ignoredTargetSlotEdit);
  label->setStyleSheet("color: gray;");

  useProjectedDistanceBox = new QCheckBox;
  form->addRow("Use Projected Distance:", useProjectedDistanceBox);
  label = form->labelForField(useProjectedDistanceBox);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  label->setStyleSheet("color: gray;");

  minRangeSpin = new QDoubleSpinBox;
  minRangeSpin->setRange(0, 1e6);
  form->addRow("Min Range:", minRangeSpin);
  label = form->labelForField(minRangeSpin);
  label->setStyleSheet("color: gray;");

  useMarkedTargetBox = new QCheckBox;
  form->addRow("Use Marked Target:", useMarkedTargetBox);
  label = form->labelForField(useMarkedTargetBox);
  label->setStyleSheet("color: gray;");
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
  auto *label = form->labelForField(onceBox);
  label->setStyleSheet("color: gray;");

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  label->setStyleSheet("color: gray;");

  minRetestAngleSpin = new QDoubleSpinBox;
  minRetestAngleSpin->setRange(0, 360);
  form->addRow("Min Retest Angle:", minRetestAngleSpin);
  label = form->labelForField(minRetestAngleSpin);
  label->setStyleSheet("color: gray;");

  minRetestMoveSpin = new QDoubleSpinBox;
  minRetestMoveSpin->setRange(0, 1e6);
  form->addRow("Min Retest Move:", minRetestMoveSpin);
  label = form->labelForField(minRetestMoveSpin);
  label->setStyleSheet("color: gray;");

  throttleTimeSpin = new QDoubleSpinBox;
  throttleTimeSpin->setRange(0, 1e6);
  form->addRow("Throttle Time:", throttleTimeSpin);
  label = form->labelForField(throttleTimeSpin);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  label->setStyleSheet("color: gray;");

  ignoreMissingSetStateBox = new QCheckBox;
  form->addRow("Ignore Missing Set State:", ignoreMissingSetStateBox);
  label = form->labelForField(ignoreMissingSetStateBox);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  label->setStyleSheet("color: gray;");

  targetSlotEdit = new QLineEdit;
  form->addRow("Target Slot:", targetSlotEdit);
  label = form->labelForField(targetSlotEdit);
  label->setStyleSheet("color: gray;");

  autoUnlockTargetBox = new QCheckBox;
  form->addRow("Auto Unlock Target:", autoUnlockTargetBox);
  label = form->labelForField(autoUnlockTargetBox);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  label->setStyleSheet("color: gray;");

  checkDayBox = new QCheckBox;
  form->addRow("Check Day:", checkDayBox);
  label = form->labelForField(checkDayBox);
  label->setStyleSheet("color: gray;");

  checkYearBox = new QCheckBox;
  form->addRow("Check Year:", checkYearBox);
  label = form->labelForField(checkYearBox);
  label->setStyleSheet("color: gray;");

  scaleDayTimeRangeBox = new QCheckBox;
  form->addRow("Scale Day Time Range:", scaleDayTimeRangeBox);
  label = form->labelForField(scaleDayTimeRangeBox);
  label->setStyleSheet("color: gray;");
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

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  label->setStyleSheet("color: gray;");

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  label->setStyleSheet("color: gray;");

  stateCombo = new QComboBox;
  stateCombo->addItems({"", "Paused", "Running", "Stopped", "Any"});
  form->addRow("State:", stateCombo);
  label = form->labelForField(stateCombo);
  label->setStyleSheet("color: gray;");

  timeRemainingMin = new QDoubleSpinBox;
  timeRemainingMin->setRange(0, 1e9);
  timeRemainingMax = new QDoubleSpinBox;
  timeRemainingMax->setRange(0, 1e9);
  form->addRow("Time Remaining Min:", timeRemainingMin);
  label = form->labelForField(timeRemainingMin);
  label->setStyleSheet("color: gray;");
  form->addRow("Time Remaining Max:", timeRemainingMax);
  label = form->labelForField(timeRemainingMax);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  label->setStyleSheet("color: gray;");

  passValuesBox = new QCheckBox;
  form->addRow("Pass Values:", passValuesBox);
  label = form->labelForField(passValuesBox);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  useTargetBox = new QCheckBox;
  form->addRow("Use Target:", useTargetBox);
  label = form->labelForField(useTargetBox);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  animationEdit = new QLineEdit;
  form->addRow("Animation:", animationEdit);
  label = form->labelForField(animationEdit);
  label->setStyleSheet("color: gray;");

  playAnimationBox = new QCheckBox;
  form->addRow("Play Animation:", playAnimationBox);
  label = form->labelForField(playAnimationBox);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  crouchBox = new QCheckBox;
  form->addRow("Crouch:", crouchBox);
  label = form->labelForField(crouchBox);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  shortenBox = new QCheckBox;
  form->addRow("Shorten:", shortenBox);
  label = form->labelForField(shortenBox);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  forceBox = new QCheckBox;
  form->addRow("Force:", forceBox);
  label = form->labelForField(forceBox);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");
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

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  auto *delayWidget = new QWidget;
  auto *delayLayout = new QHBoxLayout(delayWidget);
  delayLayout->setContentsMargins(0, 0, 0, 0);
  delayMinSpin = new QDoubleSpinBox;
  delayMaxSpin = new QDoubleSpinBox;
  delayLayout->addWidget(delayMinSpin);
  delayLayout->addWidget(delayMaxSpin);
  form->addRow("Delay:", delayWidget);
  label = form->labelForField(delayWidget);
  label->setStyleSheet("color: gray;");

  itemEdit = new QLineEdit;
  form->addRow("Item:", itemEdit);
  label = form->labelForField(itemEdit);
  label->setStyleSheet("color: gray;");

  dropListEdit = new QLineEdit;
  form->addRow("Drop List:", dropListEdit);
  label = form->labelForField(dropListEdit);
  label->setStyleSheet("color: gray;");

  throwSpeedSpin = new QDoubleSpinBox;
  throwSpeedSpin->setMaximum(999999);
  form->addRow("Throw Speed:", throwSpeedSpin);
  label = form->labelForField(throwSpeedSpin);
  label->setStyleSheet("color: gray;");

  auto *distanceWidget = new QWidget;
  auto *distanceLayout = new QHBoxLayout(distanceWidget);
  distanceLayout->setContentsMargins(0, 0, 0, 0);
  distanceMinSpin = new QDoubleSpinBox;
  distanceMaxSpin = new QDoubleSpinBox;
  distanceLayout->addWidget(distanceMinSpin);
  distanceLayout->addWidget(distanceMaxSpin);
  form->addRow("Distance:", distanceWidget);
  label = form->labelForField(distanceWidget);
  label->setStyleSheet("color: gray;");

  auto *dropSectorWidget = new QWidget;
  auto *dropSectorLayout = new QHBoxLayout(dropSectorWidget);
  dropSectorLayout->setContentsMargins(0, 0, 0, 0);
  dropSectorMinSpin = new QDoubleSpinBox;
  dropSectorMaxSpin = new QDoubleSpinBox;
  dropSectorLayout->addWidget(dropSectorMinSpin);
  dropSectorLayout->addWidget(dropSectorMaxSpin);
  form->addRow("Drop Sector:", dropSectorWidget);
  label = form->labelForField(dropSectorWidget);
  label->setStyleSheet("color: gray;");

  pitchHighBox = new QCheckBox;
  form->addRow("Pitch High:", pitchHighBox);
  label = form->labelForField(pitchHighBox);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  clearBox = new QCheckBox;
  form->addRow("Clear:", clearBox);
  label = form->labelForField(clearBox);
  label->setStyleSheet("color: gray;");

  targetSlotEdit = new QLineEdit;
  form->addRow("Target Slot:", targetSlotEdit);
  label = form->labelForField(targetSlotEdit);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  operationCombo = new QComboBox;
  operationCombo->addItems({"", "Add", "RemoveHeldItem", "SetHotbar", "Equip", "ClearHeldItem", "EquipOffHand", "Remove", "EquipHotbar", "SetOffHand"});
  form->addRow("Operation:", operationCombo);
  label = form->labelForField(operationCombo);
  label->setStyleSheet("color: gray;");

  countSpin = new QSpinBox;
  countSpin->setMinimum(0);
  countSpin->setMaximum(999999);
  form->addRow("Count:", countSpin);
  label = form->labelForField(countSpin);
  label->setStyleSheet("color: gray;");

  itemEdit = new QLineEdit;
  form->addRow("Item:", itemEdit);
  label = form->labelForField(itemEdit);
  label->setStyleSheet("color: gray;");

  useTargetBox = new QCheckBox;
  form->addRow("Use Target:", useTargetBox);
  label = form->labelForField(useTargetBox);
  label->setStyleSheet("color: gray;");

  slotSpin = new QSpinBox;
  slotSpin->setMinimum(0);
  slotSpin->setMaximum(999);
  form->addRow("Slot:", slotSpin);
  label = form->labelForField(slotSpin);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  forceJoinBox = new QCheckBox;
  form->addRow("Force Join:", forceJoinBox);
  label = form->labelForField(forceJoinBox);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  auto *delayWidget = new QWidget;
  auto *delayLayout = new QHBoxLayout(delayWidget);
  delayLayout->setContentsMargins(0, 0, 0, 0);
  delayMinSpin = new QDoubleSpinBox;
  delayMaxSpin = new QDoubleSpinBox;
  delayLayout->addWidget(delayMinSpin);
  delayLayout->addWidget(delayMaxSpin);
  form->addRow("Delay:", delayWidget);
  label = form->labelForField(delayWidget);
  label->setStyleSheet("color: gray;");

  hooverBox = new QCheckBox;
  form->addRow("Hoover:", hooverBox);
  label = form->labelForField(hooverBox);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  allowEmptyMaterialsBox = new QCheckBox;
  form->addRow("Allow Empty Materials:", allowEmptyMaterialsBox);
  label = form->labelForField(allowEmptyMaterialsBox);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  useTargetBox = new QCheckBox;
  form->addRow("Use Target:", useTargetBox);
  label = form->labelForField(useTargetBox);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  instructionsEdit = new QLineEdit;
  instructionsEdit->setPlaceholderText("Comma-separated names");
  form->addRow("Instructions:", instructionsEdit);
  label = form->labelForField(instructionsEdit);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  changeAppearanceBox = new QCheckBox;
  form->addRow("Change Appearance:", changeAppearanceBox);
  label = form->labelForField(changeAppearanceBox);
  label->setStyleSheet("color: gray;");

  stateEdit = new QLineEdit;
  form->addRow("State:", stateEdit);
  label = form->labelForField(stateEdit);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  blockingBox = new QCheckBox;
  form->addRow("Blocking:", blockingBox);
  label = form->labelForField(blockingBox);
  label->setStyleSheet("color: gray;");

  atomicBox = new QCheckBox;
  form->addRow("Atomic:", atomicBox);
  label = form->labelForField(atomicBox);
  label->setStyleSheet("color: gray;");
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
  auto *label = form->labelForField(onceBox);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");
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

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  label->setStyleSheet("color: gray;");

  setToBox = new QCheckBox;
  form->addRow("Set To:", setToBox);
  label = form->labelForField(setToBox);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  interactableBox = new QCheckBox;
  form->addRow("Interactable:", interactableBox);
  label = form->labelForField(interactableBox);
  label->setStyleSheet("color: gray;");

  hintEdit = new QLineEdit;
  form->addRow("Hint:", hintEdit);
  label = form->labelForField(hintEdit);
  label->setStyleSheet("color: gray;");

  showPromptBox = new QCheckBox;
  form->addRow("Show Prompt:", showPromptBox);
  label = form->labelForField(showPromptBox);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  toCurrentBox = new QCheckBox;
  form->addRow("To Current:", toCurrentBox);
  label = form->labelForField(toCurrentBox);
  label->setStyleSheet("color: gray;");

  toTargetBox = new QCheckBox;
  form->addRow("To Target:", toTargetBox);
  label = form->labelForField(toTargetBox);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  addBox = new QCheckBox;
  form->addRow("Add:", addBox);
  label = form->labelForField(addBox);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  clearStateBox = new QCheckBox;
  form->addRow("Clear State:", clearStateBox);
  label = form->labelForField(clearStateBox);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  delayAfterBox = new QCheckBox;
  delayAfterBox->setStyleSheet("color: gray;");
  form->addRow("Delay After:", delayAfterBox);
  label = form->labelForField(delayAfterBox);
  label->setStyleSheet("color: gray;");
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

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  label->setStyleSheet("color: gray;");
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

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  label->setStyleSheet("color: gray;");

  addValueSpin = new QDoubleSpinBox;
  addValueSpin->setRange(-999999, 999999);
  addValueSpin->setStyleSheet("color: gray;");
  form->addRow("Add Value:", addValueSpin);
  label = form->labelForField(addValueSpin);
  label->setStyleSheet("color: gray;");

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
  label->setStyleSheet("color: gray;");

  rateSpin = new QDoubleSpinBox;
  rateSpin->setRange(-999999, 999999);
  rateSpin->setStyleSheet("color: gray;");
  form->addRow("Rate:", rateSpin);
  label = form->labelForField(rateSpin);
  label->setStyleSheet("color: gray;");

  setValueSpin = new QDoubleSpinBox;
  setValueSpin->setRange(-999999, 999999);
  setValueSpin->setStyleSheet("color: gray;");
  form->addRow("Set Value:", setValueSpin);
  label = form->labelForField(setValueSpin);
  label->setStyleSheet("color: gray;");

  repeatingBox = new QCheckBox;
  repeatingBox->setStyleSheet("color: gray;");
  form->addRow("Repeating:", repeatingBox);
  label = form->labelForField(repeatingBox);
  label->setStyleSheet("color: gray;");
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

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  label->setStyleSheet("color: gray;");
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

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  label->setStyleSheet("color: gray;");
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

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  label->setStyleSheet("color: gray;");

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
  label->setStyleSheet("color: gray;");

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
  label->setStyleSheet("color: gray;");

  rateSpin = new QDoubleSpinBox;
  rateSpin->setRange(-999999, 999999);
  rateSpin->setStyleSheet("color: gray;");
  form->addRow("Rate:", rateSpin);
  label = form->labelForField(rateSpin);
  label->setStyleSheet("color: gray;");

  repeatingBox = new QCheckBox;
  repeatingBox->setStyleSheet("color: gray;");
  form->addRow("Repeating:", repeatingBox);
  label = form->labelForField(repeatingBox);
  label->setStyleSheet("color: gray;");
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

  onceBox = new QCheckBox;
  form->addRow("Once:", onceBox);
  auto *label = form->labelForField(onceBox);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  enabledBox = new QCheckBox;
  form->addRow("Enabled:", enabledBox);
  label = form->labelForField(enabledBox);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  targetSlotEdit = new QLineEdit;
  targetSlotEdit->setStyleSheet("color: gray;");
  form->addRow("Target Slot:", targetSlotEdit);
  label = form->labelForField(targetSlotEdit);
  label->setStyleSheet("color: gray;");
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
  label->setStyleSheet("color: gray;");

  spawnMarkerEdit = new QLineEdit;
  spawnMarkerEdit->setStyleSheet("color: gray;");
  form->addRow("Spawn Marker:", spawnMarkerEdit);
  label = form->labelForField(spawnMarkerEdit);
  label->setStyleSheet("color: gray;");

  countSpin = new QSpinBox;
  countSpin->setRange(0, 999999);
  countSpin->setStyleSheet("color: gray;");
  form->addRow("Count:", countSpin);
  label = form->labelForField(countSpin);
  label->setStyleSheet("color: gray;");
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