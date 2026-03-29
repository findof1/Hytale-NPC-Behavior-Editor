#pragma once
#include "nodeWidgets.hpp"
#include "types.hpp"
#include <QLineEdit>
#include <QFormLayout>
#include <QCheckBox>
#include <QComboBox>
#include <QSpinBox>
#include <QVariantMap>
#include <QListWidget>

class RootNode : public NodeItem
{
public:
  QString nodeType() const override { return "Root"; }
  nlohmann::json serializeNode() const override
  {
    return {};
  }
  void deserializeNode(const nlohmann::json &j) override {}

  RootNode(NodeScene *scene);
};

class InstructionNode : public NodeItem
{
public:
  QString nodeType() const override { return "Instruction"; }
  nlohmann::json serializeNode() const override;
  void deserializeNode(const nlohmann::json &j) override;

  QLineEdit *nameEdit;
  QCheckBox *enabledBox;
  QCheckBox *continueBox;
  QCheckBox *blockingBox;
  QCheckBox *atomicBox;
  QSpinBox *weightSpin;

  InstructionNode(NodeScene *scene);

  General::Instruction serialize();
};

class CommentNode : public NodeItem
{
public:
  QString nodeType() const override { return "Comment"; }
  nlohmann::json serializeNode() const override;
  void deserializeNode(const nlohmann::json &j) override;
  QLineEdit *nameEdit;

  CommentNode(NodeScene *scene);
};

namespace SensorNodes
{
  class AdjustPositionNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "AdjustPosition"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *enabledBox;

    QDoubleSpinBox *offsetX;
    QDoubleSpinBox *offsetY;
    QDoubleSpinBox *offsetZ;

    AdjustPositionNode(NodeScene *scene);

    General::Sensor::AdjustPosition serialize();
  };

  class AgeNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "Age"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *enabledBox;
    QDoubleSpinBox *ageMin;
    QDoubleSpinBox *ageMax;

    AgeNode(NodeScene *scene);

    General::Sensor::Age serialize();
  };

  class AlarmNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "Alarm"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *enabledBox;
    QLineEdit *nameEdit;
    QComboBox *stateCombo;
    QCheckBox *clearBox;

    AlarmNode(NodeScene *scene);

    General::Sensor::Alarm serialize();
  };

  class AndNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "And"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *enabledBox;
    QLineEdit *autoUnlockTargetSlotEdit;

    AndNode(NodeScene *scene);

    General::Sensor::And serialize();
  };

  class AnimationNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "Animation"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *enabledBox;
    QComboBox *slotCombo;
    QLineEdit *animationEdit;

    AnimationNode(NodeScene *scene);

    General::Sensor::Animation serialize();
  };

  class AnyNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "Any"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *enabledBox;

    AnyNode(NodeScene *scene);

    General::Sensor::Any serialize();
  };

  class BeaconNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "Beacon"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *enabledBox;
    QLineEdit *messageEdit;
    QDoubleSpinBox *rangeSpin;
    QLineEdit *targetSlotEdit;
    QCheckBox *consumeMessageBox;

    BeaconNode(NodeScene *scene);

    General::Sensor::Beacon serialize();
  };

  class BlockChangeNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "BlockChange"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *enabledBox;
    QDoubleSpinBox *rangeSpin;
    QComboBox *searchTypeCombo;
    QLineEdit *targetSlotEdit;
    QLineEdit *blockSetEdit;
    QComboBox *eventTypeCombo;

    BlockChangeNode(NodeScene *scene);

    General::Sensor::BlockChange serialize();
  };

  class BlockTypeNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "BlockType"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *enabledBox;
    QLineEdit *blockSetEdit;

    BlockTypeNode(NodeScene *scene);

    General::Sensor::BlockType serialize();
  };

  class CanInteractNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "CanInteract"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *enabledBox;
    QDoubleSpinBox *viewSectorSpin;
    QListWidget *attitudesList;

    CanInteractNode(NodeScene *scene);

    General::Sensor::CanInteract serialize();
  };

  class CanPlaceBlockNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "CanPlaceBlock"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *enabledBox;
    QComboBox *directionCombo;
    QComboBox *offsetCombo;
    QDoubleSpinBox *retryDelaySpin;
    QCheckBox *allowEmptyMaterialsBox;

    CanPlaceBlockNode(NodeScene *scene);

    General::Sensor::CanPlaceBlock serialize();
  };

  class CombatActionEvaluatorNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "CombatActionEvaluator"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *enabledBox;
    QCheckBox *targetInRangeBox;
    QDoubleSpinBox *allowableDeviationSpin;

    CombatActionEvaluatorNode(NodeScene *scene);

    General::Sensor::CombatActionEvaluator serialize();
  };

  class CountNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "Count"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *enabledBox;
    QSpinBox *countMin;
    QSpinBox *countMax;
    QDoubleSpinBox *rangeMin;
    QDoubleSpinBox *rangeMax;
    QLineEdit *includeGroupsEdit;
    QLineEdit *excludeGroupsEdit;

    CountNode(NodeScene *scene);

    General::Sensor::Count serialize();
  };

  class DamageNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "Damage"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *enabledBox;
    QCheckBox *combatBox;
    QCheckBox *friendlyBox;
    QCheckBox *drowningBox;
    QCheckBox *environmentBox;
    QCheckBox *otherBox;
    QLineEdit *targetSlotEdit;

    DamageNode(NodeScene *scene);

    General::Sensor::Damage serialize();
  };

  class DroppedItemNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "DroppedItem"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *enabledBox;
    QDoubleSpinBox *rangeSpin;
    QDoubleSpinBox *viewSectorSpin;
    QCheckBox *lineOfSightBox;
    QLineEdit *itemsEdit;
    QListWidget *attitudesList;

    DroppedItemNode(NodeScene *scene);

    General::Sensor::DroppedItem serialize();
  };

  class EntityEventNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "EntityEvent"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *enabledBox;
    QDoubleSpinBox *rangeSpin;
    QComboBox *searchTypeCombo;
    QLineEdit *targetSlotEdit;
    QLineEdit *npcGroupEdit;
    QComboBox *eventTypeCombo;
    QCheckBox *flockOnlyBox;

    EntityEventNode(NodeScene *scene);

    General::Sensor::EntityEvent serialize();
  };

  class FlagNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "Flag"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *enabledBox;
    QLineEdit *nameEdit;
    QCheckBox *setBox;

    FlagNode(NodeScene *scene);

    General::Sensor::Flag serialize();
  };

  class FlockCombatDamageNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "FlockCombatDamage"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *enabledBox;
    QCheckBox *leaderOnlyBox;

    FlockCombatDamageNode(NodeScene *scene);

    General::Sensor::FlockCombatDamage serialize();
  };

  class FlockLeaderNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "FlockLeader"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *enabledBox;

    FlockLeaderNode(NodeScene *scene);

    General::Sensor::FlockLeader serialize();
  };

  class HasHostileTargetMemoryNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "HasHostileTargetMemory"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *enabledBox;

    HasHostileTargetMemoryNode(NodeScene *scene);

    General::Sensor::HasHostileTargetMemory serialize();
  };

  class HasInteractedNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "HasInteracted"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *enabledBox;

    HasInteractedNode(NodeScene *scene);

    General::Sensor::HasInteracted serialize();
  };

  class HasTaskNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "HasTask"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *enabledBox;
    QLineEdit *taskByIdEdit;

    HasTaskNode(NodeScene *scene);

    General::Sensor::HasTask serialize();
  };

  class InAirNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "InAir"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *enabledBox;

    InAirNode(NodeScene *scene);

    General::Sensor::InAir serialize();
  };

  class InWaterNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "InWater"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *enabledBox;

    InWaterNode(NodeScene *scene);

    General::Sensor::InWater serialize();
  };

  class InflictedDamageNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "InflictedDamage"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *enabledBox;
    QComboBox *targetCombo;
    QCheckBox *friendlyFireBox;

    InflictedDamageNode(NodeScene *scene);

    General::Sensor::InflictedDamage serialize();
  };

  class InteractionContextNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "InteractionContext"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *enabledBox;
    QLineEdit *contextEdit;

    InteractionContextNode(NodeScene *scene);

    General::Sensor::InteractionContext serialize();
  };

  class IsBackingAwayNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "IsBackingAway"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *enabledBox;

    IsBackingAwayNode(NodeScene *scene);

    General::Sensor::IsBackingAway serialize();
  };

  class IsBusyNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "IsBusy"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *enabledBox;

    IsBusyNode(NodeScene *scene);

    General::Sensor::IsBusy serialize();
  };

  class KillNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "Kill"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *enabledBox;
    QLineEdit *targetSlotEdit;

    KillNode(NodeScene *scene);

    General::Sensor::Kill serialize();
  };

  class LeashNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "Leash"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *enabledBox;
    QDoubleSpinBox *rangeSpin;

    LeashNode(NodeScene *scene);

    General::Sensor::Leash serialize();
  };

  class LightNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "Light"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *enabledBox;
    QDoubleSpinBox *lightMin, *lightMax;
    QDoubleSpinBox *skyLightMin, *skyLightMax;
    QDoubleSpinBox *sunlightMin, *sunlightMax;
    QDoubleSpinBox *redMin, *redMax;
    QDoubleSpinBox *greenMin, *greenMax;
    QDoubleSpinBox *blueMin, *blueMax;
    QLineEdit *targetSlotEdit;

    LightNode(NodeScene *scene);

    General::Sensor::Light serialize();
  };

  class MobNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "Mob"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *enabledBox;
    QDoubleSpinBox *minRangeSpin;
    QDoubleSpinBox *rangeSpin;
    QCheckBox *lockedOnTargetBox;
    QLineEdit *lockedTargetSlotEdit;
    QCheckBox *autoUnlockTargetBox;
    QCheckBox *onlyLockedTargetBox;
    QLineEdit *ignoredTargetSlotEdit;
    QCheckBox *useProjectedDistanceBox;
    QCheckBox *getPlayersBox;
    QCheckBox *getNPCsBox;
    QCheckBox *excludeOwnTypeBox;

    MobNode(NodeScene *scene);

    General::Sensor::Mob serialize();
  };

  class NavNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "Nav"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *enabledBox;
    QListWidget *navStatesList;
    QDoubleSpinBox *throttleDurationSpin;
    QDoubleSpinBox *targetDeltaSpin;

    NavNode(NodeScene *scene);

    General::Sensor::Nav serialize();
  };

  class NotNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "Not"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *enabledBox;
    QLineEdit *useTargetSlotEdit;
    QLineEdit *autoUnlockTargetSlotEdit;

    NotNode(NodeScene *scene);

    General::Sensor::Not serialize();
  };

  class OnGroundNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "OnGround"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *enabledBox;

    OnGroundNode(NodeScene *scene);

    General::Sensor::OnGround serialize();
  };

  class OrNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "Or"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *enabledBox;
    QLineEdit *autoUnlockTargetSlotEdit;

    OrNode(NodeScene *scene);

    General::Sensor::Or serialize();
  };

  class PathNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "Path"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *enabledBox;
    QLineEdit *pathEdit;
    QDoubleSpinBox *rangeSpin;
    QComboBox *pathTypeCombo;

    PathNode(NodeScene *scene);

    General::Sensor::Path serialize();
  };

  class PlayerNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "Player"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *enabledBox;
    QDoubleSpinBox *minRangeSpin;
    QDoubleSpinBox *rangeSpin;
    QCheckBox *lockedOnTargetBox;
    QLineEdit *lockedTargetSlotEdit;
    QCheckBox *autoUnlockTargetBox;
    QCheckBox *onlyLockedTargetBox;
    QLineEdit *ignoredTargetSlotEdit;
    QCheckBox *useProjectedDistanceBox;

    PlayerNode(NodeScene *scene);

    General::Sensor::Player serialize();
  };

  class RandomNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "Random"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *enabledBox;
    QDoubleSpinBox *trueDurMin;
    QDoubleSpinBox *trueDurMax;
    QDoubleSpinBox *falseDurMin;
    QDoubleSpinBox *falseDurMax;

    RandomNode(NodeScene *scene);

    General::Sensor::Random serialize();
  };

  class ReadPositionNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "ReadPosition"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *enabledBox;
    QLineEdit *slotEdit;
    QDoubleSpinBox *minRangeSpin;
    QDoubleSpinBox *rangeSpin;
    QCheckBox *useMarkedTargetBox;

    ReadPositionNode(NodeScene *scene);

    General::Sensor::ReadPosition serialize();
  };

  class SearchRayNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "SearchRay"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *enabledBox;
    QLineEdit *nameEdit;
    QDoubleSpinBox *angleSpin;
    QDoubleSpinBox *rangeSpin;
    QLineEdit *blocksEdit;
    QDoubleSpinBox *minRetestAngleSpin;
    QDoubleSpinBox *minRetestMoveSpin;
    QDoubleSpinBox *throttleTimeSpin;

    SearchRayNode(NodeScene *scene);

    General::Sensor::SearchRay serialize();
  };

  class SelfNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "Self"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *enabledBox;

    SelfNode(NodeScene *scene);

    General::Sensor::Self serialize();
  };

  class StateNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "State"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *enabledBox;
    QLineEdit *stateEdit;
    QCheckBox *ignoreMissingSetStateBox;

    StateNode(NodeScene *scene);

    General::Sensor::State serialize();
  };

  class SwitchNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "Switch"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *enabledBox;
    QCheckBox *switchCheckBox;

    SwitchNode(NodeScene *scene);

    General::Sensor::Switch serialize();
  };

  class TargetNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "Target"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *enabledBox;
    QLineEdit *targetSlotEdit;
    QDoubleSpinBox *rangeSpin;
    QCheckBox *autoUnlockTargetBox;

    TargetNode(NodeScene *scene);

    General::Sensor::Target serialize();
  };

  class TimeNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "Time"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *enabledBox;
    QDoubleSpinBox *periodMin;
    QDoubleSpinBox *periodMax;
    QCheckBox *checkDayBox;
    QCheckBox *checkYearBox;
    QCheckBox *scaleDayTimeRangeBox;

    TimeNode(NodeScene *scene);

    General::Sensor::Time serialize();
  };

  class TimerNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "Timer"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *enabledBox;
    QLineEdit *nameEdit;
    QComboBox *stateCombo;
    QDoubleSpinBox *timeRemainingMin;
    QDoubleSpinBox *timeRemainingMax;

    TimerNode(NodeScene *scene);

    General::Sensor::Timer serialize();
  };

  class ValueProviderWrapperNode : public NodeItem // TODO: Figure out how to edit values to pass in
  {
  public:
    QString nodeType() const override { return "ValueProviderWrapper"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *enabledBox;
    QCheckBox *passValuesBox;

    ValueProviderWrapperNode(NodeScene *scene);

    General::Sensor::ValueProviderWrapper serialize();
  };

  class WeatherNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "Weather"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *enabledBox;
    QLineEdit *weathersEdit;

    WeatherNode(NodeScene *scene);

    General::Sensor::Weather serialize();
  };
};

namespace ActionNodes
{

  class WeightedActionNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "WeightedAction"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QDoubleSpinBox *weightSpin;

    WeightedActionNode(NodeScene *scene);

    General::Action::WeightedAction serialize() // TODO: Add serialization for actions
    {
      General::Action::WeightedAction data;

      data.weight = weightSpin->value();

      return data;
    }
  };

  class AddToHostileTargetMemoryNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "AddToHostileTargetMemory"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;

    AddToHostileTargetMemoryNode(NodeScene *scene);

    General::Action::AddToHostileTargetMemory serialize();
  };

  class AppearanceNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "Appearance"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QLineEdit *appearanceEdit;

    AppearanceNode(NodeScene *scene);

    General::Action::Appearance serialize();
  };

  class ApplyEntityEffectNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "ApplyEntityEffect"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QLineEdit *entityEffectEdit;
    QCheckBox *useTargetBox;

    ApplyEntityEffectNode(NodeScene *scene);

    General::Action::ApplyEntityEffect serialize();
  };

  class CombatAbilityNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "CombatAbility"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;

    CombatAbilityNode(NodeScene *scene);

    General::Action::CombatAbility serialize();
  };

  class CompleteTaskNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "CompleteTask"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QComboBox *slotCombo;
    QLineEdit *animationEdit;
    QCheckBox *playAnimationBox;

    CompleteTaskNode(NodeScene *scene);

    General::Action::CompleteTask serialize();
  };

  class CrouchNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "Crouch"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *crouchBox;

    CrouchNode(NodeScene *scene);

    General::Action::Crouch serialize();
  };

  class DelayDespawnNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "DelayDespawn"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QDoubleSpinBox *timeSpin;
    QCheckBox *shortenBox;

    DelayDespawnNode(NodeScene *scene);

    General::Action::DelayDespawn serialize();
  };

  class DespawnNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "Despawn"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *forceBox;

    DespawnNode(NodeScene *scene);

    General::Action::Despawn serialize();
  };

  class DieNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "Die"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;

    DieNode(NodeScene *scene);

    General::Action::Die serialize();
  };

  class DisplayNameNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "DisplayName"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QLineEdit *displayNameEdit;

    DisplayNameNode(NodeScene *scene);

    General::Action::DisplayName serialize();
  };

  class DropItemNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "DropItem"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QDoubleSpinBox *delayMinSpin;
    QDoubleSpinBox *delayMaxSpin;
    QLineEdit *itemEdit;
    QLineEdit *dropListEdit;
    QDoubleSpinBox *throwSpeedSpin;
    QDoubleSpinBox *distanceMinSpin;
    QDoubleSpinBox *distanceMaxSpin;
    QDoubleSpinBox *dropSectorMinSpin;
    QDoubleSpinBox *dropSectorMaxSpin;
    QCheckBox *pitchHighBox;

    DropItemNode(NodeScene *scene);

    General::Action::DropItem serialize();
  };

  class FlockStateNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "FlockState"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QLineEdit *stateEdit;

    FlockStateNode(NodeScene *scene);

    General::Action::FlockState serialize();
  };

  class FlockTargetNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "FlockTarget"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *clearBox;
    QLineEdit *targetSlotEdit;

    FlockTargetNode(NodeScene *scene);

    General::Action::FlockTarget serialize();
  };

  class IgnoreForAvoidanceNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "IgnoreForAvoidance"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QLineEdit *targetSlotEdit;

    IgnoreForAvoidanceNode(NodeScene *scene);

    General::Action::IgnoreForAvoidance serialize();
  };

  class InventoryNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "Inventory"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QComboBox *operationCombo;
    QSpinBox *countSpin;
    QLineEdit *itemEdit;
    QCheckBox *useTargetBox;
    QSpinBox *slotSpin;

    InventoryNode(NodeScene *scene);

    General::Action::Inventory serialize();
  };

  class JoinFlockNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "JoinFlock"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *forceJoinBox;

    JoinFlockNode(NodeScene *scene);

    General::Action::JoinFlock serialize();
  };

  class LeaveFlockNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "LeaveFlock"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;

    LeaveFlockNode(NodeScene *scene);

    General::Action::LeaveFlock serialize();
  };

  class LockOnInteractionTargetNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "LockOnInteractionTarget"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QLineEdit *targetSlotEdit;

    LockOnInteractionTargetNode(NodeScene *scene);

    General::Action::LockOnInteractionTarget serialize();
  };

  class LogNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "Log"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QLineEdit *messageEdit;

    LogNode(NodeScene *scene);

    General::Action::Log serialize();
  };

  class ModelAttachmentNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "ModelAttachment"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QLineEdit *slotEdit;
    QLineEdit *attachmentEdit;

    ModelAttachmentNode(NodeScene *scene);

    General::Action::ModelAttachment serialize();
  };

  class MountNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "Mount"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QDoubleSpinBox *anchorXSpin;
    QDoubleSpinBox *anchorYSpin;
    QDoubleSpinBox *anchorZSpin;
    QLineEdit *movementConfigEdit;

    MountNode(NodeScene *scene);

    General::Action::Mount serialize();
  };

  class NothingNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "Nothing"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    NothingNode(NodeScene *scene);

    General::Action::Nothing serialize();
  };

  class NotifyNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "Notify"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QLineEdit *messageEdit;
    QLineEdit *slotEdit;

    NotifyNode(NodeScene *scene);

    General::Action::Notify serialize();
  };

  class OpenBarterShopNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "OpenBarterShop"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QLineEdit *shopEdit;

    OpenBarterShopNode(NodeScene *scene);

    General::Action::OpenBarterShop serialize();
  };

  class OpenShopNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "OpenShop"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QLineEdit *shopEdit;

    OpenShopNode(NodeScene *scene);

    General::Action::OpenShop serialize();
  };

  class OverrideAltitudeNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "OverrideAltitude"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QDoubleSpinBox *altitudeMinSpin;
    QDoubleSpinBox *altitudeMaxSpin;

    OverrideAltitudeNode(NodeScene *scene);

    General::Action::OverrideAltitude serialize();
  };

  class OverrideAttitudeNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "OverrideAttitude"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QComboBox *attitudeCombo;
    QDoubleSpinBox *durationSpin;

    OverrideAttitudeNode(NodeScene *scene);

    General::Action::OverrideAttitude serialize();
  };

  class ParentStateNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "ParentState"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QLineEdit *stateEdit;

    ParentStateNode(NodeScene *scene);

    General::Action::ParentState serialize();
  };

  class PickUpItemNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "PickUpItem"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QDoubleSpinBox *delayMinSpin;
    QDoubleSpinBox *delayMaxSpin;
    QDoubleSpinBox *rangeSpin;
    QCheckBox *hooverBox;
    QLineEdit *itemsEdit;

    PickUpItemNode(NodeScene *scene);

    General::Action::PickUpItem serialize();
  };

  class PlaceBlockNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "PlaceBlock"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QDoubleSpinBox *rangeSpin;
    QCheckBox *allowEmptyMaterialsBox;

    PlaceBlockNode(NodeScene *scene);

    General::Action::PlaceBlock serialize();
  };

  class PlaySoundNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "PlaySound"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QLineEdit *soundEventIdEdit;

    PlaySoundNode(NodeScene *scene);

    General::Action::PlaySound serialize();
  };

  class RandomNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "Random"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;

    RandomNode(NodeScene *scene);

    General::Action::Random serialize() // TODO: Add serialization for weighted actions output
    {
      General::Action::Random data;

      if (onceBox->isChecked())
        data.once = true;

      return data;
    }
  };

  class RecomputePathNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "RecomputePath"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;

    RecomputePathNode(NodeScene *scene);

    General::Action::RecomputePath serialize();
  };

  class ReleaseTargetNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "ReleaseTarget"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QLineEdit *targetSlotEdit;

    ReleaseTargetNode(NodeScene *scene);

    General::Action::ReleaseTarget serialize();
  };

  class RemoveNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "Remove"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *useTargetBox;

    RemoveNode(NodeScene *scene);

    General::Action::Remove serialize();
  };

  class ResetBlockSensorsNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "ResetBlockSensors"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QLineEdit *blockSetsEdit;

    ResetBlockSensorsNode(NodeScene *scene);

    General::Action::ResetBlockSensors serialize();
  };

  class ResetInstructionsNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "ResetInstructions"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QLineEdit *instructionsEdit;

    ResetInstructionsNode(NodeScene *scene);

    General::Action::ResetInstructions serialize();
  };

  class ResetPathNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "ResetPath"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;

    ResetPathNode(NodeScene *scene);

    General::Action::ResetPath serialize();
  };

  class ResetSearchRaysNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "ResetSearchRays"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QLineEdit *namesEdit;

    ResetSearchRaysNode(NodeScene *scene);

    General::Action::ResetSearchRays serialize();
  };

  class RoleNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "Role"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QLineEdit *roleEdit;
    QCheckBox *changeAppearanceBox;
    QLineEdit *stateEdit;

    RoleNode(NodeScene *scene);

    General::Action::Role serialize();
  };

  class SequenceNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "Sequence"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *blockingBox;
    QCheckBox *atomicBox;

    SequenceNode(NodeScene *scene);

    General::Action::Sequence serialize() // TODO: serialize actions output node
    {
      General::Action::Sequence data;

      if (onceBox->isChecked())
        data.once = true;

      if (blockingBox->isChecked())
        data.blocking = true;

      if (atomicBox->isChecked())
        data.atomic = true;

      return data;
    }
  };

  class SetAlarmNode : public NodeItem // TODO: Fix duration so it alligns with the temporal type in-game
  {
  public:
    QString nodeType() const override { return "SetAlarm"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QLineEdit *nameEdit;
    QDoubleSpinBox *durationMinEdit;
    QDoubleSpinBox *durationMaxEdit;

    SetAlarmNode(NodeScene *scene);

    General::Action::SetAlarm serialize();
  };

  class SetBlockToPlaceNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "SetBlockToPlace"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QLineEdit *blockEdit;

    SetBlockToPlaceNode(NodeScene *scene);

    General::Action::SetBlockToPlace serialize();
  };

  class SetFlagNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "SetFlag"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QLineEdit *nameEdit;
    QCheckBox *setToBox;

    SetFlagNode(NodeScene *scene);

    General::Action::SetFlag serialize();
  };

  class SetInteractableNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "SetInteractable"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *interactableBox;
    QLineEdit *hintEdit;
    QCheckBox *showPromptBox;

    SetInteractableNode(NodeScene *scene);

    General::Action::SetInteractable serialize();
  };

  // At least one of ToCurrent, ToTarget must be true. If ToTarget is true, must be attached to a sensor that provides one of player target, NPC target, dropped item target
  class SetLeashPositionNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "SetLeashPosition"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *toCurrentBox;
    QCheckBox *toTargetBox;

    SetLeashPositionNode(NodeScene *scene);

    General::Action::SetLeashPosition serialize();
  };

  // must be attached to a sensor that provides one of player target, NPC target
  class SetMarkedTargetNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "SetMarkedTarget"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QLineEdit *targetSlotEdit;

    SetMarkedTargetNode(NodeScene *scene);

    General::Action::SetMarkedTarget serialize();
  };

  class SetStatNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "SetStat"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QLineEdit *statEdit;
    QDoubleSpinBox *valueSpin;
    QCheckBox *addBox;

    SetStatNode(NodeScene *scene);

    General::Action::SetStat serialize();
  };

  class StartObjectiveNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "StartObjective"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QLineEdit *objectiveEdit;

    StartObjectiveNode(NodeScene *scene);

    General::Action::StartObjective serialize();
  };

  class StateNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "State"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QLineEdit *stateEdit;
    QCheckBox *clearStateBox;

    StateNode(NodeScene *scene);

    General::Action::State serialize();
  };

  class StorePositionNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "StorePosition"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QLineEdit *slotEdit;

    StorePositionNode(NodeScene *scene);

    General::Action::StorePosition serialize();
  };

  class TimeoutNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "Timeout"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QDoubleSpinBox *delayMinSpin;
    QDoubleSpinBox *delayMaxSpin;
    QCheckBox *delayAfterBox;

    TimeoutNode(NodeScene *scene);

    General::Action::Timeout serialize() // TODO: Connect Serialization for data.action
    {
      General::Action::Timeout data;

      data.delay.push_back(delayMinSpin->value());
      data.delay.push_back(delayMaxSpin->value());

      if (onceBox->isChecked())
        data.once = true;

      if (delayAfterBox->isChecked())
        data.delayAfter = true;

      return data;
    }
  };

  class TimerContinueNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "TimerContinue"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QLineEdit *nameEdit;

    TimerContinueNode(NodeScene *scene);

    General::Action::TimerContinue serialize();
  };

  class TimerModifyNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "TimerModify"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QLineEdit *nameEdit;
    QDoubleSpinBox *addValueSpin;
    QDoubleSpinBox *maxValueMinSpin;
    QDoubleSpinBox *maxValueMaxSpin;
    QDoubleSpinBox *rateSpin;
    QDoubleSpinBox *setValueSpin;
    QCheckBox *repeatingBox;

    TimerModifyNode(NodeScene *scene);

    General::Action::TimerModify serialize();
  };

  class TimerPauseNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "TimerPause"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QLineEdit *nameEdit;

    TimerPauseNode(NodeScene *scene);

    General::Action::TimerPause serialize();
  };

  class TimerRestartNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "TimerRestart"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QLineEdit *nameEdit;

    TimerRestartNode(NodeScene *scene);

    General::Action::TimerRestart serialize();
  };

  class TimerStartNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "TimerStart"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QLineEdit *nameEdit;
    QDoubleSpinBox *startValueMinSpin;
    QDoubleSpinBox *startValueMaxSpin;
    QDoubleSpinBox *restartValueMinSpin;
    QDoubleSpinBox *restartValueMaxSpin;
    QDoubleSpinBox *rateSpin;
    QCheckBox *repeatingBox;

    TimerStartNode(NodeScene *scene);

    General::Action::TimerStart serialize();
  };

  class TimerStopNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "TimerStop"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QLineEdit *nameEdit;

    TimerStopNode(NodeScene *scene);

    General::Action::TimerStop serialize();
  };

  class ToggleStateEvaluatorNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "ToggleStateEvaluator"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QCheckBox *enabledBox;

    ToggleStateEvaluatorNode(NodeScene *scene);

    General::Action::ToggleStateEvaluator serialize();
  };

  class TriggerSpawnBeaconNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "TriggerSpawnBeacon"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QLineEdit *beaconSpawnEdit;
    QSpinBox *rangeSpin;
    QLineEdit *targetSlotEdit;

    TriggerSpawnBeaconNode(NodeScene *scene);

    General::Action::TriggerSpawnBeacon serialize();
  };

  class TriggerSpawnersNode : public NodeItem
  {
  public:
    QString nodeType() const override { return "TriggerSpawners"; }
    nlohmann::json serializeNode() const override;
    void deserializeNode(const nlohmann::json &j) override;
    QCheckBox *onceBox;
    QLineEdit *spawnMarkerEdit;
    QSpinBox *rangeSpin;
    QSpinBox *countSpin;

    TriggerSpawnersNode(NodeScene *scene);

    General::Action::TriggerSpawners serialize();
  };
};