#include "attributesEditor.hpp"
#include "jsonConverter.hpp"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsPathItem>
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QMenu>
#include <QFileDialog>
#include <fstream>

AttributesEditor::AttributesEditor(QWidget *parent) : QWidget(parent)
{
  auto *layout = new QFormLayout(this);
  auto *tabs = new QTabWidget;
  layout->addRow(tabs);

  // required fields
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

    /*
    auto *requiredFieldsSection = new CollapsibleSection("Required Attributes");
    layout->addRow(requiredFieldsSection);
    auto *requiredFieldsLayout = requiredFieldsSection->contentLayout();
    auto *requiredForm = new QFormLayout;
    requiredFieldsLayout->addLayout(requiredForm);*/

    // Max Health
    maxHealthSpin = new QSpinBox;
    maxHealthSpin->setRange(1, 10000);
    requiredForm->addRow("Max Health:", maxHealthSpin);

    // Appearance
    appearanceEdit = new QLineEdit;
    requiredForm->addRow("Appearance:", appearanceEdit);

    // Name Translation Key
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

  // optional fields
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

    /*
    auto *optionalFieldsSection = new CollapsibleSection("Optional Attributes");
    layout->addRow(optionalFieldsSection);
    auto *optionalFieldsLayout = optionalFieldsSection->contentLayout();
    auto *formContainer = new QWidget;
    auto *optionalForm = new QFormLayout(formContainer);
    optionalFieldsLayout->addLayout(optionalForm);
    auto *scroll = new QScrollArea;
    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);
    scroll->setWidget(formContainer);

    optionalFieldsLayout->addWidget(scroll);*/

    // Initial Motion Controller
    motionCombo = new QComboBox;
    motionCombo->addItems({"walk", "fly", "dive"});
    motionComboOptional = new OptionalWidget(motionCombo);
    optionalForm->addRow("Initial Motion Controller:", motionComboOptional);

    // Different display names
    VectorEditor *displayNamesEditor = new VectorEditor(
        []() -> QWidget *
        {
          return new QLineEdit();
        });
    displayNamesOptional = new OptionalWidget(displayNamesEditor);
    optionalForm->addRow("Display Names:", displayNamesOptional);

    // Block set for blocks the entity cannot see through
    opaqueBlockSet = new QLineEdit;
    opaqueBlockSetOptional = new OptionalWidget(opaqueBlockSet);
    optionalForm->addRow("Opaque Block Set:", opaqueBlockSetOptional);

    // Knockback Scale
    knockbackScale = new QSpinBox;
    knockbackScale->setRange(0, 1000);
    knockbackScaleOptional = new OptionalWidget(knockbackScale);
    optionalForm->addRow("Knockback Scale:", knockbackScaleOptional);

    // Inventory Size
    inventorySpin = new QSpinBox;
    inventorySpin->setRange(0, 36);
    inventorySpinOptional = new OptionalWidget(inventorySpin);
    optionalForm->addRow("Inventory Size:", inventorySpinOptional);

    // Hotbar Size
    hotbarSize = new QSpinBox;
    hotbarSize->setRange(0, 9);
    hotbarSizeOptional = new OptionalWidget(hotbarSize);
    optionalForm->addRow("Hotbar Size:", hotbarSizeOptional);

    // Offhand Slots
    offhandSlots = new QSpinBox;
    offhandSlots->setRange(0, 4);
    offhandSlotsOptional = new OptionalWidget(offhandSlots);
    optionalForm->addRow("Offhand Slots:", offhandSlotsOptional);

    // Offhand Items
    offhandItems = new VectorEditor(
        []() -> QWidget *
        {
          return new QLineEdit;
        });
    offhandItemsOptional = new OptionalWidget(offhandItems);
    optionalForm->addRow("Offhand Items:", offhandItemsOptional);

    // Possible Inventory Items
    possibleInventoryItems = new QLineEdit;
    possibleInventoryItemsOptional = new OptionalWidget(possibleInventoryItems);
    optionalForm->addRow("Possible Inventory Items:", possibleInventoryItemsOptional);

    // Default Offhand Slot
    defaultOffhandSlot = new QSpinBox;
    defaultOffhandSlot->setRange(0, 4);
    defaultOffhandSlotOptional = new OptionalWidget(defaultOffhandSlot);
    optionalForm->addRow("Default Offhand Slot:", defaultOffhandSlotOptional);

    // Drop List
    dropList = new QLineEdit;
    dropListOptional = new OptionalWidget(dropList);
    optionalForm->addRow("Drop List:", dropListOptional);

    // Collision Distance
    collisionDistance = new QDoubleSpinBox;
    collisionDistance->setRange(0.0, 1000.0);
    collisionDistance->setDecimals(3);
    collisionDistanceOptional = new OptionalWidget(collisionDistance);
    optionalForm->addRow("Collision Distance:", collisionDistanceOptional);

    // Combat Config
    combatConfig = new QLineEdit;
    combatConfigOptional = new OptionalWidget(combatConfig);
    optionalForm->addRow("Combat Config:", combatConfigOptional);

    // Invulnerable
    invulnerableCheck = new QCheckBox;
    invulnerableCheckOptional = new OptionalWidget(invulnerableCheck);
    optionalForm->addRow("Invulnerable:", invulnerableCheckOptional);

    // Pickup Drop On Death
    pickupDropOnDeath = new QCheckBox;
    pickupDropOnDeathOptional = new OptionalWidget(pickupDropOnDeath);
    optionalForm->addRow("Pickup Drop On Death:", pickupDropOnDeathOptional);

    // Death Interaction
    deathInteraction = new QLineEdit;
    deathInteractionOptional = new OptionalWidget(deathInteraction);
    optionalForm->addRow("Death Interaction:", deathInteractionOptional);

    // Default Player Attitude
    playerAttitudeCombo = new QComboBox;
    playerAttitudeCombo->addItems({"Hostile", "Revered", "Friendly", "Ignore", "Neutral"});
    playerAttitudeComboOptional = new OptionalWidget(playerAttitudeCombo);
    optionalForm->addRow("Default Player Attitude:", playerAttitudeComboOptional);

    // Default NPC Attitude
    npcAttitudeCombo = new QComboBox;
    npcAttitudeCombo->addItems({"Hostile", "Revered", "Friendly", "Ignore", "Neutral"});
    npcAttitudeComboOptional = new OptionalWidget(npcAttitudeCombo);
    optionalForm->addRow("Default NPC Attitude:", npcAttitudeComboOptional);

    // Corpse Stays In Flock
    corpseStaysInFlock = new QCheckBox;
    corpseStaysInFlockOptional = new OptionalWidget(corpseStaysInFlock);
    optionalForm->addRow("Corpse Stays In Flock:", corpseStaysInFlockOptional);

    // Is Memory
    isMemory = new QCheckBox;
    isMemoryOptional = new OptionalWidget(isMemory);
    optionalForm->addRow("Is Memory:", isMemoryOptional);

    // Memories Category
    memoriesCategory = new QLineEdit;
    memoriesCategoryOptional = new OptionalWidget(memoriesCategory);
    optionalForm->addRow("Memories Category:", memoriesCategoryOptional);

    // Memories Name Override
    memoriesNameOverride = new QLineEdit;
    memoriesNameOverrideOptional = new OptionalWidget(memoriesNameOverride);
    optionalForm->addRow("Memories Name Override:", memoriesNameOverrideOptional);

    // Spawn Lock Time
    spawnLockTime = new QDoubleSpinBox;
    spawnLockTime->setRange(0.0, 10000.0);
    spawnLockTime->setDecimals(3);
    spawnLockTimeOptional = new OptionalWidget(spawnLockTime);
    optionalForm->addRow("Spawn Lock Time:", spawnLockTimeOptional);
  }

  // state transitions
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
    /*
    auto *statesFieldsSection = new CollapsibleSection("Entity States");
    layout->addRow(statesFieldsSection);
    auto *statesFieldsLayout = statesFieldsSection->contentLayout();
    auto *statesForm = new QFormLayout;
    statesFieldsLayout->addLayout(statesForm);*/

    // Start State
    startState = new QLineEdit;
    startStateOptional = new OptionalWidget(startState);
    statesForm->addRow("Start State:", startStateOptional);

    // Default Sub State
    defaultSubState = new QLineEdit;
    defaultSubStateOptional = new OptionalWidget(defaultSubState);
    statesForm->addRow("Default Sub State:", defaultSubStateOptional);

    // State Transitions Editor
    stateTransitionsEditor = new VectorEditor(
        []() -> QWidget *
        {
          return new StateTransitionEditor();
        });
    stateTransitionsEditorOptional = new OptionalWidget(stateTransitionsEditor);
    statesForm->addRow("State Transitions:", stateTransitionsEditorOptional);
  }

  {
    auto *instructionsTab = new QWidget;
    auto *instructionsTabLayout = new QVBoxLayout(instructionsTab);
    instructionsTabLayout->setContentsMargins(0, 0, 0, 0);

    tabs->addTab(instructionsTab, "Behavior Editor");

    scene = new NodeScene(this);
    scene->setSceneRect(-500, -500, 1000, 1000);

    // add node types for UI builder:
    scene->nodeFactory["Instruction"] = [](NodeScene *s)
    {
      return std::make_shared<InstructionNode>(s);
    };

    scene->nodeFactory["Comment"] = [](NodeScene *s)
    {
      return std::make_shared<CommentNode>(s);
    };

    scene->nodeFactory["Sensors/Adjust Position"] = [](NodeScene *s)
    {
      return std::make_shared<SensorNodes::AdjustPositionNode>(s);
    };

    scene->nodeFactory["Sensors/Age"] = [](NodeScene *s)
    {
      return std::make_shared<SensorNodes::AgeNode>(s);
    };

    scene->nodeFactory["Sensors/Alarm"] = [](NodeScene *s)
    {
      return std::make_shared<SensorNodes::AlarmNode>(s);
    };

    scene->nodeFactory["Sensors/And"] = [](NodeScene *s)
    {
      return std::make_shared<SensorNodes::AndNode>(s);
    };

    scene->nodeFactory["Sensors/Animation"] = [](NodeScene *s)
    {
      return std::make_shared<SensorNodes::AnimationNode>(s);
    };

    scene->nodeFactory["Sensors/Any"] = [](NodeScene *s)
    {
      return std::make_shared<SensorNodes::AnyNode>(s);
    };

    scene->nodeFactory["Sensors/Beacon"] = [](NodeScene *s)
    {
      return std::make_shared<SensorNodes::BeaconNode>(s);
    };

    scene->nodeFactory["Sensors/Block Change"] = [](NodeScene *s)
    {
      return std::make_shared<SensorNodes::BlockChangeNode>(s);
    };

    scene->nodeFactory["Sensors/Block Type"] = [](NodeScene *s)
    {
      return std::make_shared<SensorNodes::BlockTypeNode>(s);
    };

    scene->nodeFactory["Sensors/Can Interact"] = [](NodeScene *s)
    {
      return std::make_shared<SensorNodes::CanInteractNode>(s);
    };

    scene->nodeFactory["Sensors/Can Place Block"] = [](NodeScene *s)
    {
      return std::make_shared<SensorNodes::CanPlaceBlockNode>(s);
    };

    scene->nodeFactory["Sensors/Combat Action Evaluator"] = [](NodeScene *s)
    {
      return std::make_shared<SensorNodes::CombatActionEvaluatorNode>(s);
    };

    scene->nodeFactory["Sensors/Count"] = [](NodeScene *s)
    {
      return std::make_shared<SensorNodes::CountNode>(s);
    };

    scene->nodeFactory["Sensors/Damage"] = [](NodeScene *s)
    {
      return std::make_shared<SensorNodes::DamageNode>(s);
    };

    scene->nodeFactory["Sensors/Dropped Item"] = [](NodeScene *s)
    {
      return std::make_shared<SensorNodes::DroppedItemNode>(s);
    };

    scene->nodeFactory["Sensors/Entity Event"] = [](NodeScene *s)
    {
      return std::make_shared<SensorNodes::EntityEventNode>(s);
    };

    scene->nodeFactory["Sensors/Flag"] = [](NodeScene *s)
    {
      return std::make_shared<SensorNodes::FlagNode>(s);
    };

    scene->nodeFactory["Sensors/Flock Combat Damage"] = [](NodeScene *s)
    {
      return std::make_shared<SensorNodes::FlockCombatDamageNode>(s);
    };

    scene->nodeFactory["Sensors/Flock Leader"] = [](NodeScene *s)
    {
      return std::make_shared<SensorNodes::FlockLeaderNode>(s);
    };

    scene->nodeFactory["Sensors/Has Hostile Target Memory"] = [](NodeScene *s)
    {
      return std::make_shared<SensorNodes::HasHostileTargetMemoryNode>(s);
    };

    scene->nodeFactory["Sensors/Has Interacted"] = [](NodeScene *s)
    {
      return std::make_shared<SensorNodes::HasInteractedNode>(s);
    };

    scene->nodeFactory["Sensors/Has Task"] = [](NodeScene *s)
    {
      return std::make_shared<SensorNodes::HasTaskNode>(s);
    };

    scene->nodeFactory["Sensors/In Air"] = [](NodeScene *s)
    {
      return std::make_shared<SensorNodes::InAirNode>(s);
    };

    scene->nodeFactory["Sensors/In Water"] = [](NodeScene *s)
    {
      return std::make_shared<SensorNodes::InWaterNode>(s);
    };

    scene->nodeFactory["Sensors/Inflicted Damage"] = [](NodeScene *s)
    {
      return std::make_shared<SensorNodes::InflictedDamageNode>(s);
    };

    scene->nodeFactory["Sensors/Interaction Context"] = [](NodeScene *s)
    {
      return std::make_shared<SensorNodes::InteractionContextNode>(s);
    };

    scene->nodeFactory["Sensors/Is Backing Away"] = [](NodeScene *s)
    {
      return std::make_shared<SensorNodes::IsBackingAwayNode>(s);
    };

    scene->nodeFactory["Sensors/Is Busy"] = [](NodeScene *s)
    {
      return std::make_shared<SensorNodes::IsBusyNode>(s);
    };

    scene->nodeFactory["Sensors/Kill"] = [](NodeScene *s)
    {
      return std::make_shared<SensorNodes::KillNode>(s);
    };

    scene->nodeFactory["Sensors/Leash"] = [](NodeScene *s)
    {
      return std::make_shared<SensorNodes::LeashNode>(s);
    };

    scene->nodeFactory["Sensors/Light"] = [](NodeScene *s)
    {
      return std::make_shared<SensorNodes::LightNode>(s);
    };

    scene->nodeFactory["Sensors/Mob"] = [](NodeScene *s)
    {
      return std::make_shared<SensorNodes::MobNode>(s);
    };

    scene->nodeFactory["Sensors/Nav"] = [](NodeScene *s)
    {
      return std::make_shared<SensorNodes::NavNode>(s);
    };

    scene->nodeFactory["Sensors/Not"] = [](NodeScene *s)
    {
      return std::make_shared<SensorNodes::NotNode>(s);
    };

    scene->nodeFactory["Sensors/On Ground"] = [](NodeScene *s)
    {
      return std::make_shared<SensorNodes::OnGroundNode>(s);
    };

    scene->nodeFactory["Sensors/Or"] = [](NodeScene *s)
    {
      return std::make_shared<SensorNodes::OrNode>(s);
    };

    scene->nodeFactory["Sensors/Path"] = [](NodeScene *s)
    {
      return std::make_shared<SensorNodes::PathNode>(s);
    };

    scene->nodeFactory["Sensors/Player"] = [](NodeScene *s)
    {
      return std::make_shared<SensorNodes::PlayerNode>(s);
    };

    scene->nodeFactory["Sensors/Random"] = [](NodeScene *s)
    {
      return std::make_shared<SensorNodes::RandomNode>(s);
    };

    scene->nodeFactory["Sensors/Read Position"] = [](NodeScene *s)
    {
      return std::make_shared<SensorNodes::ReadPositionNode>(s);
    };

    scene->nodeFactory["Sensors/Search Ray"] = [](NodeScene *s)
    {
      return std::make_shared<SensorNodes::SearchRayNode>(s);
    };

    scene->nodeFactory["Sensors/Self"] = [](NodeScene *s)
    {
      return std::make_shared<SensorNodes::SelfNode>(s);
    };

    scene->nodeFactory["Sensors/State"] = [](NodeScene *s)
    {
      return std::make_shared<SensorNodes::StateNode>(s);
    };

    scene->nodeFactory["Sensors/Switch"] = [](NodeScene *s)
    {
      return std::make_shared<SensorNodes::SwitchNode>(s);
    };

    scene->nodeFactory["Sensors/Target"] = [](NodeScene *s)
    {
      return std::make_shared<SensorNodes::TargetNode>(s);
    };

    scene->nodeFactory["Sensors/Time"] = [](NodeScene *s)
    {
      return std::make_shared<SensorNodes::TimeNode>(s);
    };

    scene->nodeFactory["Sensors/Timer"] = [](NodeScene *s)
    {
      return std::make_shared<SensorNodes::TimerNode>(s);
    };

    scene->nodeFactory["Sensors/Value Provider Wrapper"] = [](NodeScene *s)
    {
      return std::make_shared<SensorNodes::ValueProviderWrapperNode>(s);
    };

    scene->nodeFactory["Sensors/Weather"] = [](NodeScene *s)
    {
      return std::make_shared<SensorNodes::WeatherNode>(s);
    };

    scene->nodeFactory["Actions/Add To Hostile Target Memory"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::AddToHostileTargetMemoryNode>(s);
    };

    scene->nodeFactory["Actions/Appearance"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::AppearanceNode>(s);
    };

    scene->nodeFactory["Actions/Apply Entity Effect"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::ApplyEntityEffectNode>(s);
    };

    scene->nodeFactory["Actions/Combat Ability"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::CombatAbilityNode>(s);
    };

    scene->nodeFactory["Actions/Complete Task"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::CompleteTaskNode>(s);
    };

    scene->nodeFactory["Actions/Crouch"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::CrouchNode>(s);
    };

    scene->nodeFactory["Actions/Delay Despawn"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::DelayDespawnNode>(s);
    };

    scene->nodeFactory["Actions/Despawn"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::DespawnNode>(s);
    };

    scene->nodeFactory["Actions/Die"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::DieNode>(s);
    };

    scene->nodeFactory["Actions/Display Name"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::DisplayNameNode>(s);
    };

    scene->nodeFactory["Actions/Drop Item"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::DropItemNode>(s);
    };

    scene->nodeFactory["Actions/Flock State"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::FlockStateNode>(s);
    };

    scene->nodeFactory["Actions/Flock Target"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::FlockTargetNode>(s);
    };

    scene->nodeFactory["Actions/Ignore For Avoidance"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::IgnoreForAvoidanceNode>(s);
    };

    scene->nodeFactory["Actions/Inventory"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::InventoryNode>(s);
    };

    scene->nodeFactory["Actions/Join Flock"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::JoinFlockNode>(s);
    };

    scene->nodeFactory["Actions/Leave Flock"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::LeaveFlockNode>(s);
    };

    scene->nodeFactory["Actions/Lock On Interaction Target"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::LockOnInteractionTargetNode>(s);
    };

    scene->nodeFactory["Actions/Log"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::LogNode>(s);
    };

    scene->nodeFactory["Actions/Model Attachment"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::ModelAttachmentNode>(s);
    };

    scene->nodeFactory["Actions/Mount"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::MountNode>(s);
    };

    scene->nodeFactory["Actions/Nothing"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::NothingNode>(s);
    };

    scene->nodeFactory["Actions/Notify"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::NotifyNode>(s);
    };

    scene->nodeFactory["Actions/Open Barter Shop"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::OpenBarterShopNode>(s);
    };

    scene->nodeFactory["Actions/Open Shop"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::OpenShopNode>(s);
    };

    scene->nodeFactory["Actions/Override Altitude"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::OverrideAltitudeNode>(s);
    };

    scene->nodeFactory["Actions/Override Attitude"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::OverrideAttitudeNode>(s);
    };

    scene->nodeFactory["Actions/Parent State"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::ParentStateNode>(s);
    };

    scene->nodeFactory["Actions/Pick Up Item"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::PickUpItemNode>(s);
    };

    scene->nodeFactory["Actions/Place Block"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::PlaceBlockNode>(s);
    };

    scene->nodeFactory["Actions/Play Sound"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::PlaySoundNode>(s);
    };

    scene->nodeFactory["Actions/Random"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::RandomNode>(s);
    };

    scene->nodeFactory["Actions/Recompute Path"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::RecomputePathNode>(s);
    };

    scene->nodeFactory["Actions/Release Target"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::ReleaseTargetNode>(s);
    };

    scene->nodeFactory["Actions/Remove"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::RemoveNode>(s);
    };

    scene->nodeFactory["Actions/Reset Block Sensors"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::ResetBlockSensorsNode>(s);
    };

    scene->nodeFactory["Actions/Reset Instructions"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::ResetInstructionsNode>(s);
    };

    scene->nodeFactory["Actions/Reset Path"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::ResetPathNode>(s);
    };

    scene->nodeFactory["Actions/Reset Search Rays"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::ResetSearchRaysNode>(s);
    };

    scene->nodeFactory["Actions/Role"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::RoleNode>(s);
    };

    scene->nodeFactory["Actions/Sequence"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::SequenceNode>(s);
    };

    scene->nodeFactory["Actions/Set Alarm"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::SetAlarmNode>(s);
    };

    scene->nodeFactory["Actions/Set Block To Place"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::SetBlockToPlaceNode>(s);
    };

    scene->nodeFactory["Actions/Set Flag"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::SetFlagNode>(s);
    };

    scene->nodeFactory["Actions/Set Interactable"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::SetInteractableNode>(s);
    };

    scene->nodeFactory["Actions/Set Leash Position"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::SetLeashPositionNode>(s);
    };

    scene->nodeFactory["Actions/Set Marked Target"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::SetMarkedTargetNode>(s);
    };

    scene->nodeFactory["Actions/Set Stat"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::SetStatNode>(s);
    };

    scene->nodeFactory["Actions/Start Objective"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::StartObjectiveNode>(s);
    };

    scene->nodeFactory["Actions/State"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::StateNode>(s);
    };

    scene->nodeFactory["Actions/Store Position"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::StorePositionNode>(s);
    };

    scene->nodeFactory["Actions/Timeout"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::TimeoutNode>(s);
    };

    scene->nodeFactory["Actions/Timer Continue"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::TimerContinueNode>(s);
    };

    scene->nodeFactory["Actions/Timer Modify"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::TimerModifyNode>(s);
    };

    scene->nodeFactory["Actions/Timer Pause"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::TimerPauseNode>(s);
    };

    scene->nodeFactory["Actions/Timer Restart"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::TimerRestartNode>(s);
    };

    scene->nodeFactory["Actions/Timer Start"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::TimerStartNode>(s);
    };

    scene->nodeFactory["Actions/Timer Stop"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::TimerStopNode>(s);
    };

    scene->nodeFactory["Actions/Toggle State Evaluator"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::ToggleStateEvaluatorNode>(s);
    };

    scene->nodeFactory["Actions/Trigger Spawn Beacon"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::TriggerSpawnBeaconNode>(s);
    };

    scene->nodeFactory["Actions/Trigger Spawners"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::TriggerSpawnersNode>(s);
    };

    scene->nodeFactory["Actions/Weighted Action"] = [](NodeScene *s)
    {
      return std::make_shared<ActionNodes::WeightedActionNode>(s);
    };
    //

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

    rootNode = new RootNode(scene);
    rootNode->setPos(0, 0);
    scene->addItem(rootNode);
    scene->nodes.emplace_back(rootNode);

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

  auto *exportBtn = new QPushButton("Export NPC Role");
  layout->addRow(exportBtn);
  connect(exportBtn, &QPushButton::clicked, this, &AttributesEditor::printValues);
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
                     {
            auto node = scene->nodeFactory[fullPath](scene);
            node->setPos(0, 0);
            scene->addItem(node.get());
            scene->nodes.emplace_back(node); });
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