#pragma once
#include <string>
#include <vector>
#include <optional>

namespace General
{
  enum class AttitudeFlag
  {
    Hostile,
    Revered,
    Friendly,
    Ignore,
    Neutral
  };

  enum class DirectionFlag
  {
    Left,
    Backward,
    Right,
    Forward
  };

  enum class SearchTypeFlag
  {
    NpcOnly,
    PlayerFirst,
    PlayerOnly,
    NpcFirst
  };

  struct MotionController
  {
    std::string type;
    MotionController(const std::string &t) : type(t) {}
    virtual ~MotionController() = default;
  };

  struct DiveMotionController : MotionController
  {
    DiveMotionController() : MotionController("dive") {}
  };

  struct FlyMotionController : MotionController
  {
    FlyMotionController() : MotionController("fly") {}
  };

  struct WalkMotionController : MotionController
  {
    WalkMotionController() : MotionController("walk") {}
  };

  enum class ValueTypeFlag
  {
    String,
    Double,
    Int
  };
  struct ValueToParameterMapping
  {
    ValueTypeFlag valueType;
    std::string fromValue;
    std::string toParameter;
  };

  namespace ISensorEntityPrioritiser
  {
    struct ISensorEntityPrioritiser
    {
    };

    struct Attitude : ISensorEntityPrioritiser
    {
      std::vector<AttitudeFlag> attitudesByPriority;
    };
  };

  namespace ISensorEntityCollector
  {
    struct ISensorEntityCollector
    {
    };

    struct CombatTargets : ISensorEntityCollector // a collector which processes matched friendly and hostile targets and adds them to the NPC's short-term combat memory.
    {
    };
  };

  namespace IEntityFilter
  {
    enum class Type
    {
      Altitude,
      And,
      Attitude,
      Combat,
      Flock,
      HeightDifference,
      InsideBlock,
      Inventory,
      ItemInHand,
      LineOfSight,
      MovementState,
      NPCGroup,
      Not,
      Or,
      SpotsMe,
      StandingOnBlock,
      Stat,
      ViewSector
    };

    struct IEntityFilter
    {
      Type type;
      IEntityFilter(Type t) : type(t) {}
    };

    struct Altitude : IEntityFilter
    {
      std::optional<bool> enabled;
      std::vector<double> altitudeRange;
      Altitude() : IEntityFilter(Type::Altitude) {}
    };

    struct And : IEntityFilter
    {
      std::optional<bool> enabled;
      std::vector<IEntityFilter> filters;
      And() : IEntityFilter(Type::And) {}
    };

    struct Attitude : IEntityFilter
    {
      std::optional<bool> enabled;
      std::vector<AttitudeFlag> attitudes;
      Attitude() : IEntityFilter(Type::Attitude) {}
    };

    enum class CombatModeFlag
    {
      Ranged,
      Charging,
      Melee,
      Blocking,
      Sequence,
      Attacking,
      Any,
      None
    };

    struct Combat : IEntityFilter // if Mode is Sequence, the asset Sequence must be provided
    {
      std::optional<bool> enabled;
      std::optional<std::string> sequence; // asset
      std::optional<std::vector<double>> timeElapsedRange;
      std::optional<CombatModeFlag> mode;
      Combat() : IEntityFilter(Type::Combat) {}
    };

    enum class FlockStatusFlag
    {
      Leader,
      Follower,
      NotMember,
      Member,
      Any
    };

    enum class FlockPlayerStatusFlag
    {
      NotMember,
      Member,
      Any
    };

    struct Flock : IEntityFilter
    {
      std::optional<bool> enabled;
      std::optional<FlockStatusFlag> flockStatus;
      std::optional<FlockPlayerStatusFlag> flockPlayerStatus;
      std::optional<std::vector<int>> size;
      std::optional<bool> checkCanJoin;
      Flock() : IEntityFilter(Type::Flock) {}
    };

    struct HeightDifference : IEntityFilter
    {
      std::optional<bool> enabled;
      std::optional<std::vector<double>> heightDifference;
      std::optional<bool> useEyePosition;
      HeightDifference() : IEntityFilter(Type::HeightDifference) {}
    };

    struct InsideBlock : IEntityFilter
    {
      std::optional<bool> enabled;
      std::string blockSet; // asset
      InsideBlock() : IEntityFilter(Type::InsideBlock) {}
    };

    struct Inventory : IEntityFilter
    {
      std::optional<bool> enabled;
      std::optional<std::vector<std::string>> items; // asset array
      std::optional<std::vector<int>> countRange;
      std::optional<std::vector<int>> freeSlotRange;
      Inventory() : IEntityFilter(Type::Inventory) {}
    };

    enum class ItemInHandFlag
    {
      OffHand,
      Main,
      Both
    };

    struct ItemInHand : IEntityFilter
    {
      std::optional<bool> enabled;
      std::optional<std::vector<std::string>> items; // asset array
      std::optional<ItemInHandFlag> hand;
      ItemInHand() : IEntityFilter(Type::ItemInHand) {}
    };

    struct LineOfSight : IEntityFilter
    {
      std::optional<bool> enabled;
      LineOfSight() : IEntityFilter(Type::LineOfSight) {}
    };

    enum class MovementStateFlag
    {
      Walking,
      Flying,
      Running,
      Falling,
      Idle,
      Sprinting,
      Crouching,
      Climbing,
      Any,
      Jumping
    };

    struct MovementState : IEntityFilter
    {
      std::optional<bool> enabled;
      MovementStateFlag state;
      MovementState() : IEntityFilter(Type::MovementState) {}
    };

    struct NPCGroup : IEntityFilter
    {
      std::optional<bool> enabled;
      std::optional<std::vector<std::string>> includeGroups; // asset array
      std::optional<std::vector<std::string>> excludeGroups; // asset array
      NPCGroup() : IEntityFilter(Type::NPCGroup) {}
    };

    struct Not : IEntityFilter
    {
      std::optional<bool> enabled;
      IEntityFilter filter;
      Not() : IEntityFilter(Type::Not), filter(Type::Not) {} // placeholder inner type; caller should assign
    };

    struct Or : IEntityFilter
    {
      std::optional<bool> enabled;
      std::vector<IEntityFilter> filters;
      Or() : IEntityFilter(Type::Or) {}
    };

    enum class ViewTestFlag
    {
      View_Sector,
      None,
      View_Cone
    };

    struct SpotsMe : IEntityFilter
    {
      std::optional<bool> enabled;
      std::optional<double> viewAngle; //(0-360)
      std::optional<ViewTestFlag> viewTest;
      std::optional<bool> testLineOfSight;
      SpotsMe() : IEntityFilter(Type::SpotsMe) {}
    };

    struct StandingOnBlock : IEntityFilter
    {
      std::optional<bool> enabled;
      std::optional<std::string> blockSet; // asset
      StandingOnBlock() : IEntityFilter(Type::StandingOnBlock) {}
    };

    enum class StatFlag
    {
      Min,
      Max,
      Value
    };

    struct Stat : IEntityFilter
    {
      std::optional<bool> enabled;
      std::string stat; // asset
      StatFlag statTarget;
      std::string relativeTo; // asset
      StatFlag relativeToTarget;
      std::vector<double> valueRange;
      Stat() : IEntityFilter(Type::Stat) {}
    };

    struct ViewSector : IEntityFilter
    {
      std::optional<bool> enabled;
      std::optional<double> viewSector; //(0-360)
      ViewSector() : IEntityFilter(Type::ViewSector) {}
    };
  };

  namespace Sensor
  {
    enum class Type
    {
      AdjustPosition,
      Age,
      Alarm,
      And,
      Animation,
      Any,
      Beacon,
      BlockChange,
      BlockType,
      CanInteract,
      CanPlaceBlock,
      CombatActionEvaluator,
      Count,
      Damage,
      DroppedItem,
      EntityEvent,
      Flag,
      FlockCombatDamage,
      FlockLeader,
      HasHostileTargetMemory,
      HasInteracted,
      HasTask,
      InAir,
      InWater,
      InflictedDamage,
      InteractionContext,
      IsBackingAway,
      IsBusy,
      Kill,
      Leash,
      Light,
      Mob,
      Nav,
      Not,
      OnGround,
      Or,
      Path,
      Player,
      Random,
      ReadPosition,
      SearchRay,
      Self,
      State,
      Switch,
      Target,
      Time,
      Timer,
      ValueProviderWrapper,
      Weather
    };

    struct Sensor
    {
      Type type;
      Sensor(Type t) : type(t) {}
    };

    // Provides:
    // Vector Position
    struct AdjustPosition : Sensor
    {
      std::optional<bool> once;
      std::optional<bool> enabled;
      Sensor sensor;
      std::vector<double> offset;
      AdjustPosition() : Sensor(Type::AdjustPosition), sensor(Type::Any) {} // placeholder inner sensor
    };

    struct Age : Sensor
    {
      std::optional<bool> once;
      std::optional<bool> enabled;
      std::vector<double> ageRange; // Temporal Amount is the type in the wiki???
      Age() : Sensor(Type::Age) {}
    };

    struct Alarm : Sensor
    {
      enum class AlarmFlag
      {
        Set,
        Unset,
        Passed
      };
      std::optional<bool> once;
      std::optional<bool> enabled;
      std::string name;
      AlarmFlag state;
      std::optional<bool> clear;
      Alarm() : Sensor(Type::Alarm) {}
    };

    struct And : Sensor
    {
      std::optional<bool> once;
      std::optional<bool> enabled;
      std::vector<Sensor> sensors;
      std::optional<std::string> autoUnlockTargetSlot;
      And() : Sensor(Type::And) {}
    };

    struct Animation : Sensor
    {
      enum class AnimationFlag
      {
        Status,
        Action,
        Face
      };
      std::optional<bool> once;
      std::optional<bool> enabled;
      AnimationFlag slot;
      std::string animation;
      Animation() : Sensor(Type::Animation) {}
    };

    struct Any : Sensor
    {
      std::optional<bool> once;
      std::optional<bool> enabled;
      Any() : Sensor(Type::Any) {}
    };

    struct Beacon : Sensor
    {
      std::optional<bool> once;
      std::optional<bool> enabled;
      std::string message;
      std::optional<double> range; //(greater than 0)
      std::optional<std::string> targetSlot;
      std::optional<bool> consumeMessage;
      Beacon() : Sensor(Type::Beacon) {}
    };

    // Provides:
    // Player target
    // NPC target
    struct BlockChange : Sensor
    {
      enum class BlockChangeEventTypeFlag
      {
        Destruction,
        Interaction,
        Damage
      };
      std::optional<bool> once;
      std::optional<bool> enabled;
      double range;
      SearchTypeFlag searchType;
      std::optional<std::string> targetSlot;
      std::string blockSet; // asset
      std::optional<BlockChangeEventTypeFlag> eventType;
      BlockChange() : Sensor(Type::BlockChange) {}
    };

    struct BlockType : Sensor
    {
      std::optional<bool> once;
      std::optional<bool> enabled;
      Sensor sensor;
      std::string blockSet;                                       // asset
      BlockType() : Sensor(Type::BlockType), sensor(Type::Any) {} // placeholder inner sensor
    };

    struct CanInteract : Sensor
    {
      std::optional<bool> once;
      std::optional<bool> enabled;
      double viewSector; //(0-360)
      std::vector<AttitudeFlag> attitudes;
      CanInteract() : Sensor(Type::CanInteract) {}
    };

    struct CanPlaceBlock : Sensor
    {
      enum class CanPlaceBlockFlag
      {
        BodyPosition,
        FootPosition,
        HeadPosition
      };
      std::optional<bool> once;
      std::optional<bool> enabled;
      DirectionFlag direction;
      std::optional<CanPlaceBlockFlag> offset;
      std::optional<double> retryDelay;
      std::optional<bool> allowEmptyMaterials;
      CanPlaceBlock() : Sensor(Type::CanPlaceBlock) {}
    };

    // Experimental
    // Provides:
    // Player target
    // NPC target
    struct CombatActionEvaluator : Sensor
    {
      std::optional<bool> once;
      std::optional<bool> enabled;
      bool targetInRange;                       // whether to match on target being in or out of range.
      std::optional<double> allowableDeviation; // the allowable deviation from the desired attack range
      CombatActionEvaluator() : Sensor(Type::CombatActionEvaluator) {}
    };

    struct Count : Sensor // check if there is a certain number of NPCs or players within a specific range
    {
      std::optional<bool> once;
      std::optional<bool> enabled;
      std::vector<int> count;
      std::vector<double> range;
      std::optional<std::vector<std::string>> includeGroups; // asset array
      std::optional<std::vector<std::string>> excludeGroups; // asset array
      Count() : Sensor(Type::Count) {}
    };

    // Provides:
    // Player target
    // NPC target
    // Dropped item target
    struct Damage : Sensor // at least one of Combat, Drowning, Environment, Other must be true. If TargetSlot is true, Drowning, Environment, Other must be false
    {
      std::optional<bool> once;
      std::optional<bool> enabled;
      std::optional<bool> combat;
      std::optional<bool> friendly;
      std::optional<bool> drowning;
      std::optional<bool> environment;
      std::optional<bool> other;
      std::optional<std::string> targetSlot;
      Damage() : Sensor(Type::Damage) {}
    };

    // Provides:
    // Dropped item target
    struct DroppedItem : Sensor
    {
      enum class DroppedItemFlag
      {
        Neutral,
        Ignore,
        Like,
        Love,
        Dislike
      };
      std::optional<bool> once;
      std::optional<bool> enabled;
      double range;
      double viewSector; //(0-360)
      std::optional<bool> lineOfSight;
      std::optional<std::vector<std::string>> items; // asset array
      std::optional<std::vector<DroppedItemFlag>> attitudes;
      DroppedItem() : Sensor(Type::DroppedItem) {}
    };

    // Provides:
    // Player target
    // NPC target
    struct EntityEvent : Sensor
    {
      enum class EntityEventFlag
      {
        Death,
        Interaction,
        Damage
      };
      std::optional<bool> once;
      std::optional<bool> enabled;
      double range;
      std::optional<SearchTypeFlag> searchType;
      std::optional<std::string> targetSlot;
      std::string npcGroup;
      EntityEventFlag eventType;
      std::optional<bool> flockOnly;
      EntityEvent() : Sensor(Type::EntityEvent) {}
    };

    struct Flag : Sensor
    {
      std::optional<bool> once;
      std::optional<bool> enabled;
      std::string name;
      std::optional<bool> set;
      Flag() : Sensor(Type::Flag) {}
    };

    // Provides:
    // Player target
    // NPC target
    struct FlockCombatDamage : Sensor
    {
      std::optional<bool> once;
      std::optional<bool> enabled;
      std::optional<bool> leaderOnly;
      FlockCombatDamage() : Sensor(Type::FlockCombatDamage) {}
    };

    // Provides:
    // Player target
    // NPC target
    struct FlockLeader : Sensor
    {
      std::optional<bool> once;
      std::optional<bool> enabled;
      FlockLeader() : Sensor(Type::FlockLeader) {}
    };

    struct HasHostileTargetMemory : Sensor
    {
      std::optional<bool> once;
      std::optional<bool> enabled;
      HasHostileTargetMemory() : Sensor(Type::HasHostileTargetMemory) {}
    };

    struct HasInteracted : Sensor
    {
      std::optional<bool> once;
      std::optional<bool> enabled;
      HasInteracted() : Sensor(Type::HasInteracted) {}
    };

    struct HasTask : Sensor
    {
      std::optional<bool> once;
      std::optional<bool> enabled;
      std::vector<std::string> taskById;
      HasTask() : Sensor(Type::HasTask) {}
    };

    struct InAir : Sensor
    {
      std::optional<bool> once;
      std::optional<bool> enabled;
      InAir() : Sensor(Type::InAir) {}
    };

    struct InWater : Sensor
    {
      std::optional<bool> once;
      std::optional<bool> enabled;
      InWater() : Sensor(Type::InWater) {}
    };

    // Provides:
    // Player target
    // NPC target
    struct InflictedDamage : Sensor // return true if an individual or the flock it belongs to inflicted combat damage. Target position is entity which received most damage.
    {
      enum class InflictedDamageFlag
      {
        FlockLeader,
        Self,
        Flock
      };
      std::optional<bool> once;
      std::optional<bool> enabled;
      std::optional<InflictedDamageFlag> target;
      std::optional<bool> friendlyFire;
      InflictedDamage() : Sensor(Type::InflictedDamage) {}
    };

    struct InteractionContext : Sensor
    {
      std::optional<bool> once;
      std::optional<bool> enabled;
      std::string context;
      InteractionContext() : Sensor(Type::InteractionContext) {}
    };

    struct IsBackingAway : Sensor
    {
      std::optional<bool> once;
      std::optional<bool> enabled;
      IsBackingAway() : Sensor(Type::IsBackingAway) {}
    };

    struct IsBusy : Sensor
    {
      std::optional<bool> once;
      std::optional<bool> enabled;
      IsBusy() : Sensor(Type::IsBusy) {}
    };

    // Provides:
    // Vector position
    struct Kill : Sensor
    {
      std::optional<bool> once;
      std::optional<bool> enabled;
      std::optional<std::string> targetSlot;
      Kill() : Sensor(Type::Kill) {}
    };

    // Provides:
    // Vector position
    struct Leash : Sensor
    {
      std::optional<bool> once;
      std::optional<bool> enabled;
      double range;
      Leash() : Sensor(Type::Leash) {}
    };

    struct Light : Sensor
    {
      std::optional<bool> once;
      std::optional<bool> enabled;
      std::optional<std::vector<double>> lightRange;
      std::optional<std::vector<double>> skyLightRange;
      std::optional<std::vector<double>> sunlightRange;
      std::optional<std::vector<double>> redLightRange;
      std::optional<std::vector<double>> greenLightRange;
      std::optional<std::vector<double>> blueLightRange;
      std::optional<std::string> targetSlot;
      Light() : Sensor(Type::Light) {}
    };

    // Provides:
    // Player target
    // NPC target
    struct Mob : Sensor // range must be greater or equal than MinRange. At least one of GetPlayers, GetNPCs must be true
    {
      std::optional<bool> once;
      std::optional<bool> enabled;
      std::optional<double> minRange;
      double range; // functions at a max range if using min range, but the name is still just 'range' for some reason
      std::optional<bool> lockedOnTarget;
      std::optional<std::string> lockedTargetSlot;
      std::optional<bool> autoUnlockTarget;
      std::optional<bool> onlyLockedTarget;
      std::optional<std::string> ignoredTargetSlot;
      std::optional<bool> useProjectedDistance;
      std::optional<ISensorEntityPrioritiser::ISensorEntityPrioritiser> prioritizer;
      std::optional<ISensorEntityCollector::ISensorEntityCollector> collector;
      std::optional<std::vector<IEntityFilter::IEntityFilter>> filters;
      std::optional<bool> getPlayers;
      std::optional<bool> getNPCs;
      std::optional<bool> excludeOwnType;
      Mob() : Sensor(Type::Mob) {}
    };

    struct Nav : Sensor
    {
      enum class NavStatesFlag
      {
        Progressing,
        Init,
        At_Goal,
        Blocked,
        Aborted,
        Defer
      };
      std::optional<bool> once;
      std::optional<bool> enabled;
      std::optional<std::vector<NavStatesFlag>> navStates;
      std::optional<double> throttleDuration; // minimum time in seconds the path finder isn't able to reach target or 0 to ignore
      std::optional<double> targetDelta;      // minimum distance target has moved since path was computed or 0 to ignore
      Nav() : Sensor(Type::Nav) {}
    };

    struct Not : Sensor
    {
      std::optional<bool> once;
      std::optional<bool> enabled;
      Sensor sensor;
      std::optional<std::string> useTargetSlot;
      std::optional<std::string> autoUnlockTargetSlot;
      Not() : Sensor(Type::Not), sensor(Type::Any) {} // placeholder inner sensor
    };

    struct OnGround : Sensor
    {
      std::optional<bool> once;
      std::optional<bool> enabled;
      OnGround() : Sensor(Type::OnGround) {}
    };

    struct Or : Sensor
    {
      std::optional<bool> once;
      std::optional<bool> enabled;
      std::vector<Sensor> sensor;
      std::optional<std::string> autoUnlockTargetSlot;
      Or() : Sensor(Type::Or) {}
    };

    // Provides:
    // Vector position
    // Path
    struct Path : Sensor // if PathType is WorldPath, the following must apply to Path: String must be not empty
    {
      enum class PathTypeFlag
      {
        CurrentPrefabPath,
        TransientPath,
        AnyPrefabPath,
        WorldPath
      };
      std::optional<bool> once;
      std::optional<bool> enabled;
      std::optional<std::string> path;
      std::optional<double> range;
      std::optional<PathTypeFlag> pathType;
      Path() : Sensor(Type::Path) {}
    };

    // Provides:
    // Player target
    // NPC target
    struct Player : Sensor
    {
      std::optional<bool> once;
      std::optional<bool> enabled;
      std::optional<double> minRange;
      double range;
      std::optional<bool> lockedOnTarget;
      std::optional<std::string> lockedTargetSlot;
      std::optional<bool> autoUnlockTarget;
      std::optional<bool> onlyLockedTarget;
      std::optional<std::string> ignoredTargetSlot;
      std::optional<bool> useProjectedDistance;
      std::optional<ISensorEntityPrioritiser::ISensorEntityPrioritiser> prioritizer;
      std::optional<ISensorEntityCollector::ISensorEntityCollector> collector;
      std::optional<std::vector<IEntityFilter::IEntityFilter>> filters;
      Player() : Sensor(Type::Player) {}
    };

    struct Random : Sensor
    {
      std::optional<bool> once;
      std::optional<bool> enabled;
      std::vector<double> trueDurationRange;
      std::vector<double> falseDurationRange;
      Random() : Sensor(Type::Random) {}
    };

    // Provides:
    // Vector position
    struct ReadPosition : Sensor
    {
      std::optional<bool> once;
      std::optional<bool> enabled;
      std::string slot;
      std::optional<double> minRange;
      double range;
      std::optional<bool> useMarkedTarget;
      ReadPosition() : Sensor(Type::ReadPosition) {}
    };

    // Provides:
    // Vector position
    struct SearchRay : Sensor
    {
      std::optional<bool> once;
      std::optional<bool> enabled;
      std::string name;
      double angle;
      double range;
      std::string blocks; // asset
      std::optional<double> minRetestAngle;
      std::optional<double> minRetestMove;
      std::optional<double> throttleTime;
      SearchRay() : Sensor(Type::SearchRay) {}
    };

    // Provides:
    // Vector position
    struct Self : Sensor
    {
      std::optional<bool> once;
      std::optional<bool> enabled;
      std::optional<std::vector<IEntityFilter::IEntityFilter>> filters;
      Self() : Sensor(Type::Self) {}
    };

    struct State : Sensor
    {
      std::optional<bool> once;
      std::optional<bool> enabled;
      std::string state;
      std::optional<bool> ignoreMissingSetState;
      State() : Sensor(Type::State) {}
    };

    struct Switch : Sensor
    {
      std::optional<bool> once;
      std::optional<bool> enabled;
      bool switchCheck; // actual name is just switch, but I can't use that
      Switch() : Sensor(Type::Switch) {}
    };

    // Provides:
    // Player target
    // NPC target
    struct Target : Sensor
    {
      std::optional<bool> once;
      std::optional<bool> enabled;
      std::optional<std::string> targetSlot;
      double range;
      std::optional<bool> autoUnlockTarget;
      std::optional<std::vector<IEntityFilter::IEntityFilter>> filters;
      Target() : Sensor(Type::Target) {}
    };

    struct Time : Sensor
    {
      std::optional<bool> once;
      std::optional<bool> enabled;
      std::vector<double> period; //(0-24)
      std::optional<bool> checkDay;
      std::optional<bool> checkYear;
      std::optional<bool> scaleDayTimeRange;
      Time() : Sensor(Type::Time) {}
    };

    struct Timer : Sensor
    {
      enum class TimerStateFlag
      {
        Paused,
        Running,
        Stopped,
        Any
      };
      std::optional<bool> once;
      std::optional<bool> enabled;
      std::string name;
      std::optional<TimerStateFlag> state;
      std::optional<std::vector<double>> timeRemainingRange;
      Timer() : Sensor(Type::Timer) {}
    };

    struct ValueProviderWrapper : Sensor
    {
      std::optional<bool> once;
      std::optional<bool> enabled;
      std::optional<bool> passValues;
      Sensor sensor;
      std::vector<ValueToParameterMapping> valueToParameterMappings;
      ValueProviderWrapper() : Sensor(Type::ValueProviderWrapper), sensor(Type::Any) {} // placeholder inner sensor
    };

    struct Weather : Sensor
    {
      std::optional<bool> once;
      std::optional<bool> enabled;
      std::vector<std::string> weathers; // asset array
      Weather() : Sensor(Type::Weather) {}
    };
  };

  namespace Action
  {
    enum class Type
    {
      AddToHostileTargetMemory,
      Appearance,
      ApplyEntityEffect,
      CombatAbility,
      CompleteTask,
      Crouch,
      DelayDespawn,
      Despawn,
      Die,
      DisplayName,
      DropItem,
      FlockState,
      FlockTarget,
      IgnoreForAvoidance,
      Inventory,
      JoinFlock,
      LeaveFlock,
      LockOnInteractionTarget,
      Log,
      ModelAttachment,
      Mount,
      Nothing,
      Notify,
      OpenBarterShop,
      OpenShop,
      OverrideAltitude,
      OverrideAttitude,
      ParentState,
      PickUpItem,
      PlaceBlock,
      PlaySound,
      Random,
      RecomputePath,
      ReleaseTarget,
      Remove,
      ResetBlockSensors,
      ResetInstructions,
      ResetPath,
      ResetSearchRays,
      Role,
      Sequence,
      SetAlarm,
      SetBlockToPlace,
      SetFlag,
      SetInteractable,
      SetLeashPosition,
      SetMarkedTarget,
      SetStat,
      StartObjective,
      State,
      StorePosition,
      Timeout,
      TimerContinue,
      TimerModify,
      TimerPause,
      TimerRestart,
      TimerStart,
      TimerStop,
      ToggleStateEvaluator,
      TriggerSpawnBeacon,
      TriggerSpawners
    };

    struct Action
    {
      Type type;
      Action(Type t) : type(t) {}
    };

    struct WeightedAction
    {
      Action action;
      double weight;
      WeightedAction() : action(Type::Nothing) {} // placeholder
    };

    struct ActionList
    {
      std::vector<Action> actions;
    };

    struct AddToHostileTargetMemory : Action // must be attached to a sensor that provides one of player target, NPC target
    {
      std::optional<bool> once;
      AddToHostileTargetMemory() : Action(Type::AddToHostileTargetMemory) {}
    };

    struct Appearance : Action
    {
      std::optional<bool> once;
      std::string appearance;
      Appearance() : Action(Type::Appearance) {}
    };

    struct ApplyEntityEffect : Action // if UseTarget is true, must be attached to a sensor that provides one of player target, NPC target
    {
      std::optional<bool> once;
      std::string entityEffect;
      std::optional<bool> useTarget;
      ApplyEntityEffect() : Action(Type::ApplyEntityEffect) {}
    };

    struct CombatAbility : Action // starts the combat ability selected by the combat action evaluator.
    {
      std::optional<bool> once;
      CombatAbility() : Action(Type::CombatAbility) {}
    };

    struct CompleteTask : Action // complete a task. Tasks are picked based on those provided to SensorCanInteract.
    {
      enum class CompleteTaskFlag
      {
        Status,
        Action,
        Face
      };

      std::optional<bool> once;
      CompleteTaskFlag slot;
      std::optional<std::string> animation;
      std::optional<bool> playAnimation;
      CompleteTask() : Action(Type::CompleteTask) {}
    };

    struct Crouch : Action
    {
      std::optional<bool> once;
      std::optional<bool> crouch;
      Crouch() : Action(Type::Crouch) {}
    };

    struct DelayDespawn : Action
    {
      std::optional<bool> once;
      double time;                 // (greater than 0)
      std::optional<bool> shorten; // set the delay to either the current delay or the given time. Whatever is smaller.
      DelayDespawn() : Action(Type::DelayDespawn) {}
    };

    struct Despawn : Action // trigger the NPC to start the despawning cycle. If the script contains a despawn sensor it will run that action/motion before removing.
    {
      std::optional<bool> once;
      std::optional<bool> force;
      Despawn() : Action(Type::Despawn) {}
    };

    struct Die : Action
    {
      std::optional<bool> once;
      Die() : Action(Type::Die) {}
    };

    struct DisplayName : Action
    {
      std::optional<bool> once;
      std::string displayName;
      DisplayName() : Action(Type::DisplayName) {}
    };

    struct DropItem : Action
    {
      std::optional<bool> once;
      std::optional<std::vector<double>> delay;
      std::optional<std::string> item;
      std::optional<std::string> dropList;
      std::optional<double> throwSpeed;
      std::optional<std::vector<double>> distance;
      std::optional<std::vector<double>> dropSector;
      std::optional<bool> pitchHigh;
      DropItem() : Action(Type::DropItem) {}
    };

    struct FlockState : Action
    {
      std::optional<bool> once;
      std::string state; // string must be a valid state string. A main state must be included before the period (e.g. Main.Test). State strings consist of a main state and a sub state (e.g. Main.Test). If nested within a substate, the main state may be omitted (e.g. .Test) when referencing.
      FlockState() : Action(Type::FlockState) {}
    };

    struct FlockTarget : Action // must be attached to a sensor that provides one of player target, NPC target
    {
      std::optional<bool> once;
      std::optional<bool> clear;
      std::optional<std::string> targetSlot;
      FlockTarget() : Action(Type::FlockTarget) {}
    };

    struct IgnoreForAvoidance : Action
    {
      std::optional<bool> once;
      std::string targetSlot;
      IgnoreForAvoidance() : Action(Type::IgnoreForAvoidance) {}
    };

    struct Inventory : Action // if UseTarget is true, must be attached to a sensor that provides one of player target, NPC target
    {
      enum class OperationFlag
      {
        Add,
        RemoveHeldItem,
        SetHotbar,
        Equip,
        ClearHeldItem,
        EquipOffHand,
        Remove,
        EquipHotbar,
        SetOffHand
      };

      std::optional<bool> once;
      std::optional<OperationFlag> operation;
      std::optional<int> count;
      std::optional<std::string> item;
      std::optional<bool> useTarget;
      std::optional<int> slot;
      Inventory() : Action(Type::Inventory) {}
    };

    // Tries to build/join flock with target. Fails if both NPC and target are in a flock. If either NPC or target are in a flock, the one not in flock tries to join existing flock. If NPC and target are both not in a flock, a new flock with NPC is created and target is tried to be joined. Joining the flock can be rejected if the joining entity does have the correct type or the flock is full. This can be overridden by setting the ForceJoin flag to true.
    struct JoinFlock : Action // must be attached to a sensor that provides one of player target, NPC target
    {
      std::optional<bool> once;
      std::optional<bool> forceJoin;
      JoinFlock() : Action(Type::JoinFlock) {}
    };

    struct LeaveFlock : Action
    {
      std::optional<bool> once;
      LeaveFlock() : Action(Type::LeaveFlock) {}
    };

    struct LockOnInteractionTarget : Action
    {
      std::optional<bool> once;
      std::string targetSlot;
      LockOnInteractionTarget() : Action(Type::LockOnInteractionTarget) {}
    };

    struct Log : Action
    {
      std::optional<bool> once;
      std::string message;
      Log() : Action(Type::Log) {}
    };

    struct ModelAttachment : Action
    {
      std::optional<bool> once;
      std::string slot;
      std::string attachment;
      ModelAttachment() : Action(Type::ModelAttachment) {}
    };

    struct Mount : Action
    {
      std::optional<bool> once;
      double anchorX;
      double anchorY;
      double anchorZ;
      std::string movementConfig;
      Mount() : Action(Type::Mount) {}
    };

    struct Nothing : Action
    {
      Nothing() : Action(Type::Nothing) {}
    };

    struct Notify : Action // If slot is null, must be attached to a sensor that provides NPC target
    {
      std::optional<bool> once;
      std::string message;
      std::string slot;
      Notify() : Action(Type::Notify) {}
    };

    struct OpenBarterShop : Action
    {
      std::optional<bool> once;
      std::string shop; // asset
      OpenBarterShop() : Action(Type::OpenBarterShop) {}
    };

    struct OpenShop : Action
    {
      std::optional<bool> once;
      std::string shop; // asset
      OpenShop() : Action(Type::OpenShop) {}
    };

    struct OverrideAltitude : Action
    {
      std::optional<bool> once;
      std::vector<double> desiredAltitudeRange;
      OverrideAltitude() : Action(Type::OverrideAltitude) {}
    };

    struct OverrideAttitude : Action // must be attached to a sensor that provides one of player target, NPC target
    {
      std::optional<bool> once;
      AttitudeFlag attitude;
      double duration;
      OverrideAttitude() : Action(Type::OverrideAttitude) {}
    };

    struct ParentState : Action // may only be included within a component
    {
      std::optional<bool> once;
      std::string state;
      ParentState() : Action(Type::ParentState) {}
    };

    struct PickUpItem : Action // if Hoover is false, must be attached to a sensor that provides dropped item target
    {
      std::optional<bool> once;
      std::optional<std::vector<double>> delay; // 2 value range
      double range;                             // pickup range
      std::optional<bool> hoover;
      std::vector<std::string> items;
      PickUpItem() : Action(Type::PickUpItem) {}
    };

    struct PlaceBlock : Action // whether it should be possible to replace blocks that have empty material
    {
      std::optional<bool> once;
      double range;
      std::optional<bool> allowEmptyMaterials;
      PlaceBlock() : Action(Type::PlaceBlock) {}
    };

    struct PlaySound : Action
    {
      std::optional<bool> once;
      std::string soundEventId; // asset
      PlaySound() : Action(Type::PlaySound) {}
    };

    struct Random : Action
    {
      std::optional<bool> once;
      std::vector<WeightedAction> actions;
      Random() : Action(Type::Random) {}
    };

    struct RecomputePath : Action
    {
      std::optional<bool> once;
      RecomputePath() : Action(Type::RecomputePath) {}
    };

    struct ReleaseTarget : Action
    {
      std::optional<bool> once;
      std::string targetSlot;
      ReleaseTarget() : Action(Type::ReleaseTarget) {}
    };

    struct Remove : Action // if UseTarget is true, must be attached to a sensor that provides one of player target, NPC target
    {
      std::optional<bool> once;
      std::optional<bool> useTarget;
      Remove() : Action(Type::Remove) {}
    };

    struct ResetBlockSensors : Action
    {
      std::optional<bool> once;
      std::vector<std::string> blockSets; // asset array
      ResetBlockSensors() : Action(Type::ResetBlockSensors) {}
    };

    struct ResetInstructions : Action
    {
      std::optional<bool> once;
      std::optional<std::vector<std::string>> instructions; // the instructionList to reset. If left empty, will reset all instructionList
      ResetInstructions() : Action(Type::ResetInstructions) {}
    };

    struct ResetPath : Action
    {
      std::optional<bool> once;
      ResetPath() : Action(Type::ResetPath) {}
    };

    struct ResetSearchRays : Action
    {
      std::optional<bool> once;
      std::vector<std::string> names;
      ResetSearchRays() : Action(Type::ResetSearchRays) {}
    };

    struct Role : Action
    {
      std::optional<bool> once;
      std::string role; // asset
      std::optional<bool> changeAppearance;
      std::optional<std::string> state;
      Role() : Action(Type::Role) {}
    };

    struct Sequence : Action
    {
      std::optional<bool> once;
      std::optional<bool> blocking;
      std::optional<bool> atomic;
      ActionList actions;
      Sequence() : Action(Type::Sequence) {}
    };

    struct SetAlarm : Action
    {
      std::optional<bool> once;
      std::string name;
      std::vector<double> durationRange; // TemporalAmount is the type for this one??? The duration range from which to pick a duration to set the alarm for. [ "P0D", "P0D" ] will unset the alarm
      SetAlarm() : Action(Type::SetAlarm) {}
    };

    struct SetBlockToPlace : Action
    {
      std::optional<bool> once;
      std::string block; // asset
      SetBlockToPlace() : Action(Type::SetBlockToPlace) {}
    };

    struct SetFlag : Action
    {
      std::optional<bool> once;
      std::string name;
      std::optional<bool> setTo;
      SetFlag() : Action(Type::SetFlag) {}
    };

    struct SetInteractable : Action
    {
      std::optional<bool> once;
      std::optional<bool> interactable;
      std::optional<std::string> hint;
      std::optional<bool> showPrompt;
      SetInteractable() : Action(Type::SetInteractable) {}
    };

    struct SetLeashPosition : Action // At least one of ToCurrent, ToTarget must be true. If ToTarget is true, must be attached to a sensor that provides one of player target, NPC target, dropped item target
    {
      std::optional<bool> once;
      std::optional<bool> toCurrent;
      std::optional<bool> toTarget;
      SetLeashPosition() : Action(Type::SetLeashPosition) {}
    };

    struct SetMarkedTarget : Action // must be attached to a sensor that provides one of player target, NPC target
    {
      std::optional<bool> once;
      std::string targetSlot;
      SetMarkedTarget() : Action(Type::SetMarkedTarget) {}
    };

    struct SetStat : Action
    {
      std::optional<bool> once;
      std::string stat; // asset
      double value;
      std::optional<bool> add;
      SetStat() : Action(Type::SetStat) {}
    };

    struct StartObjective : Action
    {
      std::optional<bool> once;
      std::string objective; // asset
      StartObjective() : Action(Type::StartObjective) {}
    };

    struct State : Action
    {
      std::optional<bool> once;
      std::string state;
      std::optional<bool> clearState;
      State() : Action(Type::State) {}
    };

    struct StorePosition : Action
    {
      std::optional<bool> once;
      std::string slot;
      StorePosition() : Action(Type::StorePosition) {}
    };

    struct Timeout : Action
    {
      std::optional<bool> once;
      std::vector<double> delay;
      std::optional<bool> delayAfter;
      Action action;
      Timeout() : Action(Type::Timeout), action(Type::Nothing) {} // placeholder inner action
    };

    struct TimerContinue : Action
    {
      std::optional<bool> once;
      std::string name;
      TimerContinue() : Action(Type::TimerContinue) {}
    };

    struct TimerModify : Action
    {
      std::optional<bool> once;
      std::string name;
      std::optional<double> addValue;
      std::optional<std::vector<double>> maxValue;
      std::optional<double> rate;
      std::optional<double> setValue;
      std::optional<bool> repeating;
      TimerModify() : Action(Type::TimerModify) {}
    };

    struct TimerPause : Action
    {
      std::optional<bool> once;
      std::string name;
      TimerPause() : Action(Type::TimerPause) {}
    };

    struct TimerRestart : Action
    {
      std::optional<bool> once;
      std::string name;
      TimerRestart() : Action(Type::TimerRestart) {}
    };

    struct TimerStart : Action
    {
      std::optional<bool> once;
      std::string name;
      std::optional<std::vector<double>> startValueRange;
      std::optional<std::vector<double>> restartValueRange;
      std::optional<double> rate;
      std::optional<bool> repeating;
      TimerStart() : Action(Type::TimerStart) {}
    };

    struct TimerStop : Action
    {
      std::optional<bool> once;
      std::string name;
      TimerStop() : Action(Type::TimerStop) {}
    };

    struct ToggleStateEvaluator : Action
    {
      std::optional<bool> once;
      std::optional<bool> enabled;
      ToggleStateEvaluator() : Action(Type::ToggleStateEvaluator) {}
    };

    struct TriggerSpawnBeacon : Action
    {
      std::optional<bool> once;
      std::string beaconSpawn; // asset
      int range;
      std::optional<std::string> targetSlot;
      TriggerSpawnBeacon() : Action(Type::TriggerSpawnBeacon) {}
    };

    struct TriggerSpawners : Action
    {
      std::optional<bool> once;
      std::optional<std::string> spawnMarker;
      int range;
      std::optional<int> count;
      TriggerSpawners() : Action(Type::TriggerSpawners) {}
    };
  };

  struct Expression
  {
    enum class Kind
    {
      Literal,
      Range
    };

    Kind kind;

    std::variant<bool, int, double, std::string, std::vector<std::string>> literal;

    struct
    {
      double min;
      double max;
    } range;
  };

  struct ReferenceInstruction
  {
    std::string referenceId;
    std::unordered_map<std::string, Expression> overrides;
  };

  namespace BodyMotion
  {
    enum class Type
    {
      AimCharge,
      MaintainDistance,
      MatchLook,
      Nothing,
      Path,
      Sequence,
      Timer,
      Wander,
      WanderInCircle,
      WanderInRect
    };

    struct BodyMotion
    {
      Type type;
      BodyMotion(Type t) : type(t) {}
    };

    struct AimCharge : BodyMotion // must be attached to a sensor that provides one of player target, NPC target, dropped item target, vector position
    {
      std::optional<double> relativeTurnSpeed; // the relative turn speed modifier (0-2)
      AimCharge() : BodyMotion(Type::AimCharge) {}
    };

    struct MaintainDistance : BodyMotion // must be attached to a sensor that provides one of player target, NPC target, dropped item target, vector position
    {
      std::vector<double> desiredDistanceRange;
      std::optional<double> targetDistanceFactor;                // 0-1
      std::optional<double> moveThreshold;                       // greater than 0
      std::optional<double> relativeForwardsSpeed;               // greater than 0, less than or equal to 2
      std::optional<double> relativeBackwardsSpeed;              // greater than 0, less than or equal to 2
      std::optional<double> moveTowardsSlowdownThreshold;        // 0 or larger
      std::optional<std::vector<double>> strafingDurationRange;  // how long to strafe for (moving left or right around the target). If set to [ 0, 0 ], will not move horizontally at all. (0-inf, weakly ascending order)
      std::optional<std::vector<double>> strafingFrequencyRange; // how frequently to execute strafing (0-inf, weakly ascending order)
      MaintainDistance() : BodyMotion(Type::MaintainDistance) {}
    };

    struct MatchLook : BodyMotion
    {
      MatchLook() : BodyMotion(Type::MatchLook) {}
    };

    struct Nothing : BodyMotion
    {
      Nothing() : BodyMotion(Type::Nothing) {}
    };

    enum class MovementFlag
    {
      Backward,
      Random,
      Forward,
      Any
    };

    enum class PathShapeFlag
    {
      Chain,
      Line,
      Loop,
      Points
    };

    struct Path : BodyMotion // must be attached to a sensor that provides one of path
    {
      std::optional<bool> startAtNearestNode;
      std::optional<double> minRelSpeed; // 0-1
      std::optional<double> maxRelSpeed; // 0-1
      std::optional<MovementFlag> direction;
      std::optional<PathShapeFlag> shape;
      std::optional<double> minNodeDelay; // 0-inf
      std::optional<double> maxNodeDelay; // 0-inf
      std::optional<bool> useNodeViewDirection;
      std::optional<std::vector<double>> nodePauseScaleRange;        // (0-1, weakly ascending order)
      std::optional<std::vector<double>> nodePauseExtraPercentRange; // (0-1, weakly ascending order)
      std::optional<bool> pickRandomAngle;
      std::optional<unsigned int> viewSegments; // greater than 0
      Path() : BodyMotion(Type::Path) {}
    };

    struct Sequence : BodyMotion
    {
      std::optional<bool> looped;
      std::vector<BodyMotion> motions; // array must not be empty
      Sequence() : BodyMotion(Type::Sequence) {}
    };

    struct Timer : BodyMotion
    {
      std::optional<std::vector<double>> time; // range of time from which the random timer length can be chosen
      BodyMotion motion;
      Timer() : BodyMotion(Type::Timer), motion(Type::Nothing) {} // placeholder inner motion
    };

    struct Wander : BodyMotion
    {
      std::optional<double> minWalkTime;      // 0-inf
      std::optional<double> maxWalkTime;      // 0-inf
      std::optional<double> minHeadingChange; // 0-inf
      std::optional<double> maxHeadingChange; // 0-inf
      std::optional<bool> relaxHeadingChange;
      std::optional<double> relativeSpeed;   // 0-2
      std::optional<double> minMoveDistance; // 0-inf
      std::optional<double> stopDistance;    // 0-inf
      std::optional<int> testsPerTick;       // 1-inf
      std::optional<bool> avoidBlockDamage;
      std::optional<bool> relaxedMoveConstraints;
      std::optional<double> desiredAltitudeWeight; // how much this NPC prefers being within the desired height range. 0 means it doesn't care much, 1 means it will do its best to get there fast. Values below 0 mean the default in the motion controller will be used. (-1 to 1)
      Wander() : BodyMotion(Type::Wander) {}
    };

    struct WanderInCircle : BodyMotion
    {
      std::optional<double> minWalkTime;      // 0-inf
      std::optional<double> maxWalkTime;      // 0-inf
      std::optional<double> minHeadingChange; // 0-inf
      std::optional<double> maxHeadingChange; // 0-inf
      std::optional<bool> relaxHeadingChange;
      std::optional<double> relativeSpeed;   // 0-2
      std::optional<double> minMoveDistance; // 0-inf
      std::optional<double> stopDistance;    // 0-inf
      std::optional<int> testsPerTick;       // 1-inf
      std::optional<bool> avoidBlockDamage;
      std::optional<bool> relaxedMoveConstraints;
      std::optional<double> desiredAltitudeWeight; // how much this NPC prefers being within the desired height range. 0 means it doesn't care much, 1 means it will do its best to get there fast. Values below 0 mean the default in the motion controller will be used. (-1 to 1)
      std::optional<double> radius;                // greater than 0
      std::optional<bool> useSphere;               // use a sphere instead of circle cylinder
      WanderInCircle() : BodyMotion(Type::WanderInCircle) {}
    };

    struct WanderInRect : BodyMotion
    {
      std::optional<double> minWalkTime;      // 0-inf
      std::optional<double> maxWalkTime;      // 0-inf
      std::optional<double> minHeadingChange; // 0-inf
      std::optional<double> maxHeadingChange; // 0-inf
      std::optional<bool> relaxHeadingChange;
      std::optional<double> relativeSpeed;   // 0-2
      std::optional<double> minMoveDistance; // 0-inf
      std::optional<double> stopDistance;    // 0-inf
      std::optional<int> testsPerTick;       // 1-inf
      std::optional<bool> avoidBlockDamage;
      std::optional<bool> relaxedMoveConstraints;
      std::optional<double> desiredAltitudeWeight; // how much this NPC prefers being within the desired height range. 0 means it doesn't care much, 1 means it will do its best to get there fast. Values below 0 mean the default in the motion controller will be used. (-1 to 1)
      std::optional<double> width;                 // greater than 0
      std::optional<double> depth;                 // greater than 0
      WanderInRect() : BodyMotion(Type::WanderInRect) {}
    };
  };

  namespace HeadMotion
  {
    enum class Type
    {
      Aim,
      Nothing,
      Observe,
      Sequence,
      Timer,
      Watch
    };

    struct HeadMotion
    {
      Type type;
      HeadMotion(Type t) : type(t) {}
    };

    struct Aim : HeadMotion
    {
      std::optional<double> relativeTurnSpeed; // the relative turn speed modifier (0-2)
      Aim() : HeadMotion(Type::Aim) {}
    };

    struct Nothing : HeadMotion
    {
      Nothing() : HeadMotion(Type::Nothing) {}
    };

    struct Observe : HeadMotion
    {
      std::vector<double> angleRange;                    // the angle range to observe in degrees, offset from facing forwards (-180 to 180 and in weakly ascending order)
      std::optional<std::vector<double>> pauseTimeRange; // how long to continue looking in a given direction (greater than 0 and in weakly ascending order)
      std::optional<bool> pickRandomAngle;               // whether to pick random angles within the range. If false, will instead sweep across the range, pausing at either end.
      std::optional<unsigned int> viewSegments;          // the number of distinct segments to stop at when sweeping from left to right
      std::optional<double> relativeTurnSpeed;           // the relative turn speed modifier (0-2)
      Observe() : HeadMotion(Type::Observe) {}
    };

    struct Sequence : HeadMotion
    {
      std::optional<bool> looped;
      std::vector<HeadMotion> motions; // array must not be empty
      Sequence() : HeadMotion(Type::Sequence) {}
    };

    struct Timer : HeadMotion
    {
      std::optional<std::vector<double>> time; // range of time from which the random timer length can be chosen
      HeadMotion motion;
      Timer() : HeadMotion(Type::Timer), motion(Type::Nothing) {} // placeholder inner motion
    };

    struct Watch : HeadMotion
    {
      std::optional<double> relativeTurnSpeed; // the relative turn speed modifier (0-2)
      Watch() : HeadMotion(Type::Watch) {}
    };
  };

  struct Instruction
  {
    std::string name;
    std::optional<std::string> comment;
    std::optional<bool> enabled;

    Sensor::Sensor sensor;
    std::optional<BodyMotion::BodyMotion> bodyMotion;
    std::optional<HeadMotion::HeadMotion> headMotion;
    std::vector<Action::Action> actions;
    std::optional<bool> actionsBlocking;
    std::optional<bool> actionsAtomic;
    std::vector<Instruction> instructions;
    std::optional<bool> cont; // continue
    std::optional<unsigned int> weight;

    Instruction() : sensor(Sensor::Type::Any) {} // placeholder sensor
  };

  struct StateTransition
  {
    unsigned int priority;         // priority for the actions in this transition
    std::vector<std::string> from; // a set of from states
    std::vector<std::string> to;   // a set of from states
    std::optional<bool> enabled;   // Whether this sensor should be enabled on the NPC
  };

  struct RequiredAttributes
  {
    unsigned int maxHealth;                             // max health (greater than 0)
    std::string appearance;                             // Unique Asset ID of the model asset
    std::string nameTranslationKey;                     // Entity name
    std::vector<std::string> busyStates;                // states the entity cannot be interacted with
    std::vector<MotionController> motionControllerList; // list of motion controllers
  };

  struct Attributes
  {
    RequiredAttributes requiredAttributes;
    std::optional<std::string> initialMotionController;           // the initial motion controller to set. If omitted and there are multiple, one will be chosen at random.
    std::optional<std::vector<std::string>> displayNames;         // list of possible display names to choose from
    std::optional<std::string> opaqueBlockSet;                    // block set for blocks that interupt line of sight
    std::optional<unsigned int> knockbackScale;                   // scale factor for knockback. Values greater 1 increase knockback. Smaller values decrease it.
    std::optional<unsigned int> inventorySize;                    // number of available inventory slots (only numbers 0-36)
    std::optional<unsigned int> hotbarSize;                       // number of available hotbar slots (only numbers 3-8)
    std::optional<unsigned int> offhandSlots;                     // number of available offhand slots (only numbers 0-4)
    std::optional<std::vector<std::string>> hotbarItems;          // items in hotbar (array of asset ids)
    std::optional<std::vector<std::string>> offhandItems;         // items in offhand slots (array of asset ids)
    std::optional<std::string> possibleInventoryItems;            // possible inventory items (asset id of a droplist)
    std::optional<int> defaultOffhandSlot;                        // default offhand item slot (numbers between -1 and the amount of offhand slots, -1 is empty)
    std::optional<std::string> dropList;                          // possible item drops (asset id of a droplist)
    std::optional<std::string> startState;                        // starting state
    std::optional<std::string> defaultSubState;                   // the default sub state to reference when transitioning to a main state without a specified sub state
    std::optional<double> collisionDistance;                      // collision lookahead (greater than 0)
    std::optional<std::string> combatConfig;                      // the combat configuration providing optional combat action evaluator (asset id of combat config)
    std::optional<bool> invulnerable;                             // makes the entity immune to damage (true or false)
    std::optional<bool> pickupDropOnDeath;                        // drop last picked item on death (true or false)
    std::optional<std::string> deathInteraction;                  // interaction called on death (asset id of interaction)
    std::optional<AttitudeFlag> defaultPlayerAttitude;            // the default attitude of this NPC towards players
    std::optional<AttitudeFlag> defaultNPCAttitude;               // the default attitude of this NPC towards other NPCs
    std::optional<AttitudeFlag> attitudeGroup;                    // the attitude group towards other NPCs this NPC belongs to (often species related) (asset id to npc group)
    std::optional<AttitudeFlag> itemAttitudeGroup;                // this NPC's item attitudes (asset id to npc group)
    std::optional<bool> corpseStaysInFlock;                       // whether the NPC should stay in the flock until corpse removal or be removed at the moment of death (true or false)
    std::optional<std::vector<Instruction>> instructions;         // list of instructions
    std::optional<Instruction> interactionInstruction;            // an instruction designed to evaluate and set which players can interact with an NPC, along with setting correct states upon interaction
    std::optional<Instruction> deathInstruction;                  // an instruction which will run only when the NPC is dead until they are removed
    std::optional<std::vector<StateTransition>> stateTransitions; // a set of state transitions and the actions that will be executed during them
    std::optional<bool> isMemory;                                 // used to define if the NPC has a Memory to record.
    std::optional<std::string> memoriesCategory;                  // category to put the NPC in, as part of the Memories Plugin
    std::optional<std::string> memoriesNameOverride;              // overrides the Memory name when set
    std::optional<double> spawnLockTime;                          // how long the NPC should be locked and unable to perform behavior when first spawned (greater than or equal to 0)
  };
}