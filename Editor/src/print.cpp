#include "print.hpp"
#include <variant>

using namespace General;
void printOpt(const char *label, const std::optional<bool> &v, std::ostream &os)
{
  if (v.has_value())
    os << "  " << label << ": " << (v.value() ? "true" : "false") << "\n";
}
void printOpt(const char *label, const std::optional<std::string> &v, std::ostream &os)
{
  if (v.has_value())
    os << "  " << label << ": " << v.value() << "\n";
}
void printOpt(const char *label, const std::optional<double> &v, std::ostream &os)
{
  if (v.has_value())
    os << "  " << label << ": " << v.value() << "\n";
}
void printOpt(const char *label, const std::optional<int> &v, std::ostream &os)
{
  if (v.has_value())
    os << "  " << label << ": " << v.value() << "\n";
}
void printOpt(const char *label, const std::optional<unsigned int> &v, std::ostream &os)
{
  if (v.has_value())
    os << "  " << label << ": " << v.value() << "\n";
}
void printVec(const char *label, const std::vector<double> &v, std::ostream &os)
{
  if (v.empty())
    return;
  os << "  " << label << ": [";
  for (size_t i = 0; i < v.size(); ++i)
  {
    if (i)
      os << ", ";
    os << v[i];
  }
  os << "]\n";
}
void printVec(const char *label, const std::vector<int> &v, std::ostream &os)
{
  if (v.empty())
    return;
  os << "  " << label << ": [";
  for (size_t i = 0; i < v.size(); ++i)
  {
    if (i)
      os << ", ";
    os << v[i];
  }
  os << "]\n";
}
void printVec(const char *label, const std::vector<std::string> &v, std::ostream &os)
{
  if (v.empty())
    return;
  os << "  " << label << ": [";
  for (size_t i = 0; i < v.size(); ++i)
  {
    if (i)
      os << ", ";
    os << v[i];
  }
  os << "]\n";
}
void printOpt(const char *label, const std::optional<std::vector<double>> &v, std::ostream &os)
{
  if (v.has_value())
    printVec(label, v.value(), os);
}
void printOpt(const char *label, const std::optional<std::vector<int>> &v, std::ostream &os)
{
  if (v.has_value())
    printVec(label, v.value(), os);
}
void printOpt(const char *label, const std::optional<std::vector<std::string>> &v, std::ostream &os)
{
  if (v.has_value())
    printVec(label, v.value(), os);
}

void print(AttitudeFlag v, std::ostream &os)
{
  switch (v)
  {
  case AttitudeFlag::Hostile:
    os << "Hostile";
    break;
  case AttitudeFlag::Revered:
    os << "Revered";
    break;
  case AttitudeFlag::Friendly:
    os << "Friendly";
    break;
  case AttitudeFlag::Ignore:
    os << "Ignore";
    break;
  case AttitudeFlag::Neutral:
    os << "Neutral";
    break;
  }
}

void print(DirectionFlag v, std::ostream &os)
{
  switch (v)
  {
  case DirectionFlag::Left:
    os << "Left";
    break;
  case DirectionFlag::Backward:
    os << "Backward";
    break;
  case DirectionFlag::Right:
    os << "Right";
    break;
  case DirectionFlag::Forward:
    os << "Forward";
    break;
  }
}

void print(SearchTypeFlag v, std::ostream &os)
{
  switch (v)
  {
  case SearchTypeFlag::NpcOnly:
    os << "NpcOnly";
    break;
  case SearchTypeFlag::PlayerFirst:
    os << "PlayerFirst";
    break;
  case SearchTypeFlag::PlayerOnly:
    os << "PlayerOnly";
    break;
  case SearchTypeFlag::NpcFirst:
    os << "NpcFirst";
    break;
  }
}

void print(ValueTypeFlag v, std::ostream &os)
{
  switch (v)
  {
  case ValueTypeFlag::String:
    os << "String";
    break;
  case ValueTypeFlag::Double:
    os << "Double";
    break;
  case ValueTypeFlag::Int:
    os << "Int";
    break;
  }
}

void print(const MotionController &v, std::ostream &os)
{
  os << "MotionController { type: " << v.type << " }\n";
}

void print(const ValueToParameterMapping &v, std::ostream &os)
{
  os << "ValueToParameterMapping {\n";
  os << "  valueType: ";
  print(v.valueType, os);
  os << "\n";
  os << "  fromValue: " << v.fromValue << "\n";
  os << "  toParameter: " << v.toParameter << "\n";
  os << "}\n";
}

void print(const ISensorEntityPrioritiser::ISensorEntityPrioritiser &, std::ostream &os)
{
  os << "ISensorEntityPrioritiser {}\n";
}

void print(const ISensorEntityPrioritiser::Attitude &v, std::ostream &os)
{
  os << "ISensorEntityPrioritiser::Attitude {\n";
  os << "  attitudesByPriority: [";
  for (size_t i = 0; i < v.attitudesByPriority.size(); ++i)
  {
    if (i)
      os << ", ";
    print(v.attitudesByPriority[i], os);
  }
  os << "]\n}\n";
}

void print(const ISensorEntityCollector::ISensorEntityCollector &, std::ostream &os)
{
  os << "ISensorEntityCollector {}\n";
}

void print(const ISensorEntityCollector::CombatTargets &, std::ostream &os)
{
  os << "ISensorEntityCollector::CombatTargets {}\n";
}

void print(IEntityFilter::Type v, std::ostream &os)
{
  switch (v)
  {
  case IEntityFilter::Type::Altitude:
    os << "Altitude";
    break;
  case IEntityFilter::Type::And:
    os << "And";
    break;
  case IEntityFilter::Type::Attitude:
    os << "Attitude";
    break;
  case IEntityFilter::Type::Combat:
    os << "Combat";
    break;
  case IEntityFilter::Type::Flock:
    os << "Flock";
    break;
  case IEntityFilter::Type::HeightDifference:
    os << "HeightDifference";
    break;
  case IEntityFilter::Type::InsideBlock:
    os << "InsideBlock";
    break;
  case IEntityFilter::Type::Inventory:
    os << "Inventory";
    break;
  case IEntityFilter::Type::ItemInHand:
    os << "ItemInHand";
    break;
  case IEntityFilter::Type::LineOfSight:
    os << "LineOfSight";
    break;
  case IEntityFilter::Type::MovementState:
    os << "MovementState";
    break;
  case IEntityFilter::Type::NPCGroup:
    os << "NPCGroup";
    break;
  case IEntityFilter::Type::Not:
    os << "Not";
    break;
  case IEntityFilter::Type::Or:
    os << "Or";
    break;
  case IEntityFilter::Type::SpotsMe:
    os << "SpotsMe";
    break;
  case IEntityFilter::Type::StandingOnBlock:
    os << "StandingOnBlock";
    break;
  case IEntityFilter::Type::Stat:
    os << "Stat";
    break;
  case IEntityFilter::Type::ViewSector:
    os << "ViewSector";
    break;
  }
}

void print(IEntityFilter::CombatModeFlag v, std::ostream &os)
{
  switch (v)
  {
  case IEntityFilter::CombatModeFlag::Ranged:
    os << "Ranged";
    break;
  case IEntityFilter::CombatModeFlag::Charging:
    os << "Charging";
    break;
  case IEntityFilter::CombatModeFlag::Melee:
    os << "Melee";
    break;
  case IEntityFilter::CombatModeFlag::Blocking:
    os << "Blocking";
    break;
  case IEntityFilter::CombatModeFlag::Sequence:
    os << "Sequence";
    break;
  case IEntityFilter::CombatModeFlag::Attacking:
    os << "Attacking";
    break;
  case IEntityFilter::CombatModeFlag::Any:
    os << "Any";
    break;
  case IEntityFilter::CombatModeFlag::None:
    os << "None";
    break;
  }
}

void print(IEntityFilter::FlockStatusFlag v, std::ostream &os)
{
  switch (v)
  {
  case IEntityFilter::FlockStatusFlag::Leader:
    os << "Leader";
    break;
  case IEntityFilter::FlockStatusFlag::Follower:
    os << "Follower";
    break;
  case IEntityFilter::FlockStatusFlag::NotMember:
    os << "NotMember";
    break;
  case IEntityFilter::FlockStatusFlag::Member:
    os << "Member";
    break;
  case IEntityFilter::FlockStatusFlag::Any:
    os << "Any";
    break;
  }
}

void print(IEntityFilter::FlockPlayerStatusFlag v, std::ostream &os)
{
  switch (v)
  {
  case IEntityFilter::FlockPlayerStatusFlag::NotMember:
    os << "NotMember";
    break;
  case IEntityFilter::FlockPlayerStatusFlag::Member:
    os << "Member";
    break;
  case IEntityFilter::FlockPlayerStatusFlag::Any:
    os << "Any";
    break;
  }
}

void print(IEntityFilter::ItemInHandFlag v, std::ostream &os)
{
  switch (v)
  {
  case IEntityFilter::ItemInHandFlag::OffHand:
    os << "OffHand";
    break;
  case IEntityFilter::ItemInHandFlag::Main:
    os << "Main";
    break;
  case IEntityFilter::ItemInHandFlag::Both:
    os << "Both";
    break;
  }
}

void print(IEntityFilter::MovementStateFlag v, std::ostream &os)
{
  switch (v)
  {
  case IEntityFilter::MovementStateFlag::Walking:
    os << "Walking";
    break;
  case IEntityFilter::MovementStateFlag::Flying:
    os << "Flying";
    break;
  case IEntityFilter::MovementStateFlag::Running:
    os << "Running";
    break;
  case IEntityFilter::MovementStateFlag::Falling:
    os << "Falling";
    break;
  case IEntityFilter::MovementStateFlag::Idle:
    os << "Idle";
    break;
  case IEntityFilter::MovementStateFlag::Sprinting:
    os << "Sprinting";
    break;
  case IEntityFilter::MovementStateFlag::Crouching:
    os << "Crouching";
    break;
  case IEntityFilter::MovementStateFlag::Climbing:
    os << "Climbing";
    break;
  case IEntityFilter::MovementStateFlag::Any:
    os << "Any";
    break;
  case IEntityFilter::MovementStateFlag::Jumping:
    os << "Jumping";
    break;
  }
}

void print(IEntityFilter::ViewTestFlag v, std::ostream &os)
{
  switch (v)
  {
  case IEntityFilter::ViewTestFlag::View_Sector:
    os << "View_Sector";
    break;
  case IEntityFilter::ViewTestFlag::None:
    os << "None";
    break;
  case IEntityFilter::ViewTestFlag::View_Cone:
    os << "View_Cone";
    break;
  }
}

void print(IEntityFilter::StatFlag v, std::ostream &os)
{
  switch (v)
  {
  case IEntityFilter::StatFlag::Min:
    os << "Min";
    break;
  case IEntityFilter::StatFlag::Max:
    os << "Max";
    break;
  case IEntityFilter::StatFlag::Value:
    os << "Value";
    break;
  }
}

void print(const IEntityFilter::IEntityFilter &v, std::ostream &os)
{
  os << "IEntityFilter { type: ";
  print(v.type, os);
  os << " }\n";
}

void print(const IEntityFilter::Altitude &v, std::ostream &os)
{
  os << "IEntityFilter::Altitude {\n";
  printOpt("enabled", v.enabled, os);
  printVec("altitudeRange", v.altitudeRange, os);
  os << "}\n";
}

void print(const IEntityFilter::And &v, std::ostream &os)
{
  os << "IEntityFilter::And {\n";
  printOpt("enabled", v.enabled, os);
  os << "  filters: [" << v.filters.size() << " entries]\n";
  os << "}\n";
}

void print(const IEntityFilter::Attitude &v, std::ostream &os)
{
  os << "IEntityFilter::Attitude {\n";
  printOpt("enabled", v.enabled, os);
  os << "  attitudes: [";
  for (size_t i = 0; i < v.attitudes.size(); ++i)
  {
    if (i)
      os << ", ";
    print(v.attitudes[i], os);
  }
  os << "]\n}\n";
}

void print(const IEntityFilter::Combat &v, std::ostream &os)
{
  os << "IEntityFilter::Combat {\n";
  printOpt("enabled", v.enabled, os);
  printOpt("sequence", v.sequence, os);
  printOpt("timeElapsedRange", v.timeElapsedRange, os);
  if (v.mode)
  {
    os << "  mode: ";
    print(*v.mode, os);
    os << "\n";
  }
  os << "}\n";
}

void print(const IEntityFilter::Flock &v, std::ostream &os)
{
  os << "IEntityFilter::Flock {\n";
  printOpt("enabled", v.enabled, os);
  if (v.flockStatus)
  {
    os << "  flockStatus: ";
    print(*v.flockStatus, os);
    os << "\n";
  }
  if (v.flockPlayerStatus)
  {
    os << "  flockPlayerStatus: ";
    print(*v.flockPlayerStatus, os);
    os << "\n";
  }
  printOpt("size", v.size, os);
  printOpt("checkCanJoin", v.checkCanJoin, os);
  os << "}\n";
}

void print(const IEntityFilter::HeightDifference &v, std::ostream &os)
{
  os << "IEntityFilter::HeightDifference {\n";
  printOpt("enabled", v.enabled, os);
  printOpt("heightDifference", v.heightDifference, os);
  printOpt("useEyePosition", v.useEyePosition, os);
  os << "}\n";
}

void print(const IEntityFilter::InsideBlock &v, std::ostream &os)
{
  os << "IEntityFilter::InsideBlock {\n";
  printOpt("enabled", v.enabled, os);
  os << "  blockSet: " << v.blockSet << "\n";
  os << "}\n";
}

void print(const IEntityFilter::Inventory &v, std::ostream &os)
{
  os << "IEntityFilter::Inventory {\n";
  printOpt("enabled", v.enabled, os);
  printOpt("items", v.items, os);
  printOpt("countRange", v.countRange, os);
  printOpt("freeSlotRange", v.freeSlotRange, os);
  os << "}\n";
}

void print(const IEntityFilter::ItemInHand &v, std::ostream &os)
{
  os << "IEntityFilter::ItemInHand {\n";
  printOpt("enabled", v.enabled, os);
  printOpt("items", v.items, os);
  if (v.hand)
  {
    os << "  hand: ";
    print(*v.hand, os);
    os << "\n";
  }
  os << "}\n";
}

void print(const IEntityFilter::LineOfSight &v, std::ostream &os)
{
  os << "IEntityFilter::LineOfSight {\n";
  printOpt("enabled", v.enabled, os);
  os << "}\n";
}

void print(const IEntityFilter::MovementState &v, std::ostream &os)
{
  os << "IEntityFilter::MovementState {\n";
  printOpt("enabled", v.enabled, os);
  os << "  state: ";
  print(v.state, os);
  os << "\n";
  os << "}\n";
}

void print(const IEntityFilter::NPCGroup &v, std::ostream &os)
{
  os << "IEntityFilter::NPCGroup {\n";
  printOpt("enabled", v.enabled, os);
  printOpt("includeGroups", v.includeGroups, os);
  printOpt("excludeGroups", v.excludeGroups, os);
  os << "}\n";
}

void print(const IEntityFilter::Not &v, std::ostream &os)
{
  os << "IEntityFilter::Not {\n";
  printOpt("enabled", v.enabled, os);
  os << "  filter: ";
  print(v.filter.type, os);
  os << "\n";
  os << "}\n";
}

void print(const IEntityFilter::Or &v, std::ostream &os)
{
  os << "IEntityFilter::Or {\n";
  printOpt("enabled", v.enabled, os);
  os << "  filters: [" << v.filters.size() << " entries]\n";
  os << "}\n";
}

void print(const IEntityFilter::SpotsMe &v, std::ostream &os)
{
  os << "IEntityFilter::SpotsMe {\n";
  printOpt("enabled", v.enabled, os);
  printOpt("viewAngle", v.viewAngle, os);
  if (v.viewTest)
  {
    os << "  viewTest: ";
    print(*v.viewTest, os);
    os << "\n";
  }
  printOpt("testLineOfSight", v.testLineOfSight, os);
  os << "}\n";
}

void print(const IEntityFilter::StandingOnBlock &v, std::ostream &os)
{
  os << "IEntityFilter::StandingOnBlock {\n";
  printOpt("enabled", v.enabled, os);
  printOpt("blockSet", v.blockSet, os);
  os << "}\n";
}

void print(const IEntityFilter::Stat &v, std::ostream &os)
{
  os << "IEntityFilter::Stat {\n";
  printOpt("enabled", v.enabled, os);
  os << "  stat: " << v.stat << "\n";
  os << "  statTarget: ";
  print(v.statTarget, os);
  os << "\n";
  os << "  relativeTo: " << v.relativeTo << "\n";
  os << "  relativeToTarget: ";
  print(v.relativeToTarget, os);
  os << "\n";
  printVec("valueRange", v.valueRange, os);
  os << "}\n";
}

void print(const IEntityFilter::ViewSector &v, std::ostream &os)
{
  os << "IEntityFilter::ViewSector {\n";
  printOpt("enabled", v.enabled, os);
  printOpt("viewSector", v.viewSector, os);
  os << "}\n";
}

void print(Sensor::Type v, std::ostream &os)
{
  switch (v)
  {
  case Sensor::Type::AdjustPosition:
    os << "AdjustPosition";
    break;
  case Sensor::Type::Age:
    os << "Age";
    break;
  case Sensor::Type::Alarm:
    os << "Alarm";
    break;
  case Sensor::Type::And:
    os << "And";
    break;
  case Sensor::Type::Animation:
    os << "Animation";
    break;
  case Sensor::Type::Any:
    os << "Any";
    break;
  case Sensor::Type::Beacon:
    os << "Beacon";
    break;
  case Sensor::Type::Block:
    os << "Block";
    break;
  case Sensor::Type::BlockChange:
    os << "BlockChange";
    break;
  case Sensor::Type::BlockType:
    os << "BlockType";
    break;
  case Sensor::Type::CanInteract:
    os << "CanInteract";
    break;
  case Sensor::Type::CanPlaceBlock:
    os << "CanPlaceBlock";
    break;
  case Sensor::Type::CombatActionEvaluator:
    os << "CombatActionEvaluator";
    break;
  case Sensor::Type::Count:
    os << "Count";
    break;
  case Sensor::Type::Damage:
    os << "Damage";
    break;
  case Sensor::Type::DroppedItem:
    os << "DroppedItem";
    break;
  case Sensor::Type::EntityEvent:
    os << "EntityEvent";
    break;
  case Sensor::Type::Flag:
    os << "Flag";
    break;
  case Sensor::Type::FlockCombatDamage:
    os << "FlockCombatDamage";
    break;
  case Sensor::Type::FlockLeader:
    os << "FlockLeader";
    break;
  case Sensor::Type::HasHostileTargetMemory:
    os << "HasHostileTargetMemory";
    break;
  case Sensor::Type::HasInteracted:
    os << "HasInteracted";
    break;
  case Sensor::Type::HasTask:
    os << "HasTask";
    break;
  case Sensor::Type::InAir:
    os << "InAir";
    break;
  case Sensor::Type::InWater:
    os << "InWater";
    break;
  case Sensor::Type::InflictedDamage:
    os << "InflictedDamage";
    break;
  case Sensor::Type::InteractionContext:
    os << "InteractionContext";
    break;
  case Sensor::Type::IsBackingAway:
    os << "IsBackingAway";
    break;
  case Sensor::Type::IsBusy:
    os << "IsBusy";
    break;
  case Sensor::Type::Kill:
    os << "Kill";
    break;
  case Sensor::Type::Leash:
    os << "Leash";
    break;
  case Sensor::Type::Light:
    os << "Light";
    break;
  case Sensor::Type::Mob:
    os << "Mob";
    break;
  case Sensor::Type::Nav:
    os << "Nav";
    break;
  case Sensor::Type::Not:
    os << "Not";
    break;
  case Sensor::Type::OnGround:
    os << "OnGround";
    break;
  case Sensor::Type::Or:
    os << "Or";
    break;
  case Sensor::Type::Path:
    os << "Path";
    break;
  case Sensor::Type::Player:
    os << "Player";
    break;
  case Sensor::Type::Random:
    os << "Random";
    break;
  case Sensor::Type::ReadPosition:
    os << "ReadPosition";
    break;
  case Sensor::Type::SearchRay:
    os << "SearchRay";
    break;
  case Sensor::Type::Self:
    os << "Self";
    break;
  case Sensor::Type::State:
    os << "State";
    break;
  case Sensor::Type::Switch:
    os << "Switch";
    break;
  case Sensor::Type::Target:
    os << "Target";
    break;
  case Sensor::Type::Time:
    os << "Time";
    break;
  case Sensor::Type::Timer:
    os << "Timer";
    break;
  case Sensor::Type::ValueProviderWrapper:
    os << "ValueProviderWrapper";
    break;
  case Sensor::Type::Weather:
    os << "Weather";
    break;
  }
}

void print(Sensor::Alarm::AlarmFlag v, std::ostream &os)
{
  switch (v)
  {
  case Sensor::Alarm::AlarmFlag::Set:
    os << "Set";
    break;
  case Sensor::Alarm::AlarmFlag::Unset:
    os << "Unset";
    break;
  case Sensor::Alarm::AlarmFlag::Passed:
    os << "Passed";
    break;
  }
}

void print(Sensor::Animation::AnimationFlag v, std::ostream &os)
{
  switch (v)
  {
  case Sensor::Animation::AnimationFlag::Status:
    os << "Status";
    break;
  case Sensor::Animation::AnimationFlag::Action:
    os << "Action";
    break;
  case Sensor::Animation::AnimationFlag::Face:
    os << "Face";
    break;
  }
}

void print(Sensor::BlockChange::BlockChangeEventTypeFlag v, std::ostream &os)
{
  switch (v)
  {
  case Sensor::BlockChange::BlockChangeEventTypeFlag::Destruction:
    os << "Destruction";
    break;
  case Sensor::BlockChange::BlockChangeEventTypeFlag::Interaction:
    os << "Interaction";
    break;
  case Sensor::BlockChange::BlockChangeEventTypeFlag::Damage:
    os << "Damage";
    break;
  }
}

void print(Sensor::CanPlaceBlock::CanPlaceBlockFlag v, std::ostream &os)
{
  switch (v)
  {
  case Sensor::CanPlaceBlock::CanPlaceBlockFlag::BodyPosition:
    os << "BodyPosition";
    break;
  case Sensor::CanPlaceBlock::CanPlaceBlockFlag::FootPosition:
    os << "FootPosition";
    break;
  case Sensor::CanPlaceBlock::CanPlaceBlockFlag::HeadPosition:
    os << "HeadPosition";
    break;
  }
}

void print(Sensor::DroppedItem::DroppedItemFlag v, std::ostream &os)
{
  switch (v)
  {
  case Sensor::DroppedItem::DroppedItemFlag::Neutral:
    os << "Neutral";
    break;
  case Sensor::DroppedItem::DroppedItemFlag::Ignore:
    os << "Ignore";
    break;
  case Sensor::DroppedItem::DroppedItemFlag::Like:
    os << "Like";
    break;
  case Sensor::DroppedItem::DroppedItemFlag::Love:
    os << "Love";
    break;
  case Sensor::DroppedItem::DroppedItemFlag::Dislike:
    os << "Dislike";
    break;
  }
}

void print(Sensor::EntityEvent::EntityEventFlag v, std::ostream &os)
{
  switch (v)
  {
  case Sensor::EntityEvent::EntityEventFlag::Death:
    os << "Death";
    break;
  case Sensor::EntityEvent::EntityEventFlag::Interaction:
    os << "Interaction";
    break;
  case Sensor::EntityEvent::EntityEventFlag::Damage:
    os << "Damage";
    break;
  }
}

void print(Sensor::InflictedDamage::InflictedDamageFlag v, std::ostream &os)
{
  switch (v)
  {
  case Sensor::InflictedDamage::InflictedDamageFlag::FlockLeader:
    os << "FlockLeader";
    break;
  case Sensor::InflictedDamage::InflictedDamageFlag::Self:
    os << "Self";
    break;
  case Sensor::InflictedDamage::InflictedDamageFlag::Flock:
    os << "Flock";
    break;
  }
}

void print(Sensor::Nav::NavStatesFlag v, std::ostream &os)
{
  switch (v)
  {
  case Sensor::Nav::NavStatesFlag::Progressing:
    os << "Progressing";
    break;
  case Sensor::Nav::NavStatesFlag::Init:
    os << "Init";
    break;
  case Sensor::Nav::NavStatesFlag::At_Goal:
    os << "At_Goal";
    break;
  case Sensor::Nav::NavStatesFlag::Blocked:
    os << "Blocked";
    break;
  case Sensor::Nav::NavStatesFlag::Aborted:
    os << "Aborted";
    break;
  case Sensor::Nav::NavStatesFlag::Defer:
    os << "Defer";
    break;
  }
}

void print(Sensor::Path::PathTypeFlag v, std::ostream &os)
{
  switch (v)
  {
  case Sensor::Path::PathTypeFlag::CurrentPrefabPath:
    os << "CurrentPrefabPath";
    break;
  case Sensor::Path::PathTypeFlag::TransientPath:
    os << "TransientPath";
    break;
  case Sensor::Path::PathTypeFlag::AnyPrefabPath:
    os << "AnyPrefabPath";
    break;
  case Sensor::Path::PathTypeFlag::WorldPath:
    os << "WorldPath";
    break;
  }
}

void print(Sensor::Timer::TimerStateFlag v, std::ostream &os)
{
  switch (v)
  {
  case Sensor::Timer::TimerStateFlag::Paused:
    os << "Paused";
    break;
  case Sensor::Timer::TimerStateFlag::Running:
    os << "Running";
    break;
  case Sensor::Timer::TimerStateFlag::Stopped:
    os << "Stopped";
    break;
  case Sensor::Timer::TimerStateFlag::Any:
    os << "Any";
    break;
  }
}

void print(const Sensor::Sensor *v, std::ostream &os)
{
  switch (v->type)
  {
  case Sensor::Type::AdjustPosition:
    print(static_cast<const Sensor::AdjustPosition *>(v), os);
    break;
  case Sensor::Type::Age:
    print(static_cast<const Sensor::Age *>(v), os);
    break;
  case Sensor::Type::Alarm:
    print(static_cast<const Sensor::Alarm *>(v), os);
    break;
  case Sensor::Type::And:
    print(static_cast<const Sensor::And *>(v), os);
    break;
  case Sensor::Type::Animation:
    print(static_cast<const Sensor::Animation *>(v), os);
    break;
  case Sensor::Type::Any:
    print(static_cast<const Sensor::Any *>(v), os);
    break;
  case Sensor::Type::Beacon:
    print(static_cast<const Sensor::Beacon *>(v), os);
    break;
  case Sensor::Type::Block:
    print(static_cast<const Sensor::Block *>(v), os);
    break;
  case Sensor::Type::BlockChange:
    print(static_cast<const Sensor::BlockChange *>(v), os);
    break;
  case Sensor::Type::BlockType:
    print(static_cast<const Sensor::BlockType *>(v), os);
    break;
  case Sensor::Type::CanInteract:
    print(static_cast<const Sensor::CanInteract *>(v), os);
    break;
  case Sensor::Type::CanPlaceBlock:
    print(static_cast<const Sensor::CanPlaceBlock *>(v), os);
    break;
  case Sensor::Type::CombatActionEvaluator:
    print(static_cast<const Sensor::CombatActionEvaluator *>(v), os);
    break;
  case Sensor::Type::Count:
    print(static_cast<const Sensor::Count *>(v), os);
    break;
  case Sensor::Type::Damage:
    print(static_cast<const Sensor::Damage *>(v), os);
    break;
  case Sensor::Type::DroppedItem:
    print(static_cast<const Sensor::DroppedItem *>(v), os);
    break;
  case Sensor::Type::EntityEvent:
    print(static_cast<const Sensor::EntityEvent *>(v), os);
    break;
  case Sensor::Type::Flag:
    print(static_cast<const Sensor::Flag *>(v), os);
    break;
  case Sensor::Type::FlockCombatDamage:
    print(static_cast<const Sensor::FlockCombatDamage *>(v), os);
    break;
  case Sensor::Type::FlockLeader:
    print(static_cast<const Sensor::FlockLeader *>(v), os);
    break;
  case Sensor::Type::HasHostileTargetMemory:
    print(static_cast<const Sensor::HasHostileTargetMemory *>(v), os);
    break;
  case Sensor::Type::HasInteracted:
    print(static_cast<const Sensor::HasInteracted *>(v), os);
    break;
  case Sensor::Type::HasTask:
    print(static_cast<const Sensor::HasTask *>(v), os);
    break;
  case Sensor::Type::InAir:
    print(static_cast<const Sensor::InAir *>(v), os);
    break;
  case Sensor::Type::InWater:
    print(static_cast<const Sensor::InWater *>(v), os);
    break;
  case Sensor::Type::InflictedDamage:
    print(static_cast<const Sensor::InflictedDamage *>(v), os);
    break;
  case Sensor::Type::InteractionContext:
    print(static_cast<const Sensor::InteractionContext *>(v), os);
    break;
  case Sensor::Type::IsBackingAway:
    print(static_cast<const Sensor::IsBackingAway *>(v), os);
    break;
  case Sensor::Type::IsBusy:
    print(static_cast<const Sensor::IsBusy *>(v), os);
    break;
  case Sensor::Type::Kill:
    print(static_cast<const Sensor::Kill *>(v), os);
    break;
  case Sensor::Type::Leash:
    print(static_cast<const Sensor::Leash *>(v), os);
    break;
  case Sensor::Type::Light:
    print(static_cast<const Sensor::Light *>(v), os);
    break;
  case Sensor::Type::Mob:
    print(static_cast<const Sensor::Mob *>(v), os);
    break;
  case Sensor::Type::Nav:
    print(static_cast<const Sensor::Nav *>(v), os);
    break;
  case Sensor::Type::Not:
    print(static_cast<const Sensor::Not *>(v), os);
    break;
  case Sensor::Type::OnGround:
    print(static_cast<const Sensor::OnGround *>(v), os);
    break;
  case Sensor::Type::Or:
    print(static_cast<const Sensor::Or *>(v), os);
    break;
  case Sensor::Type::Path:
    print(static_cast<const Sensor::Path *>(v), os);
    break;
  case Sensor::Type::Player:
    print(static_cast<const Sensor::Player *>(v), os);
    break;
  case Sensor::Type::Random:
    print(static_cast<const Sensor::Random *>(v), os);
    break;
  case Sensor::Type::ReadPosition:
    print(static_cast<const Sensor::ReadPosition *>(v), os);
    break;
  case Sensor::Type::SearchRay:
    print(static_cast<const Sensor::SearchRay *>(v), os);
    break;
  case Sensor::Type::Self:
    print(static_cast<const Sensor::Self *>(v), os);
    break;
  case Sensor::Type::State:
    print(static_cast<const Sensor::State *>(v), os);
    break;
  case Sensor::Type::Switch:
    print(static_cast<const Sensor::Switch *>(v), os);
    break;
  case Sensor::Type::Target:
    print(static_cast<const Sensor::Target *>(v), os);
    break;
  case Sensor::Type::Time:
    print(static_cast<const Sensor::Time *>(v), os);
    break;
  case Sensor::Type::Timer:
    print(static_cast<const Sensor::Timer *>(v), os);
    break;
  case Sensor::Type::ValueProviderWrapper:
    print(static_cast<const Sensor::ValueProviderWrapper *>(v), os);
    break;
  case Sensor::Type::Weather:
    print(static_cast<const Sensor::Weather *>(v), os);
    break;
  }
}

void print(const Sensor::AdjustPosition *v, std::ostream &os)
{
  os << "Sensor::AdjustPosition {\n";
  printOpt("once", v->once, os);
  printOpt("enabled", v->enabled, os);
  os << "  sensor:{ ";
  if (v->sensor)
    print(v->sensor.get(), os);
  os << "}\n";
  printVec("offset", v->offset, os);
  os << "}\n";
}

void print(const Sensor::Age *v, std::ostream &os)
{
  os << "Sensor::Age {\n";
  printOpt("once", v->once, os);
  printOpt("enabled", v->enabled, os);
  printVec("ageRange", v->ageRange, os);
  os << "}\n";
}

void print(const Sensor::Alarm *v, std::ostream &os)
{
  os << "Sensor::Alarm {\n";
  printOpt("once", v->once, os);
  printOpt("enabled", v->enabled, os);
  os << "  name: " << v->name << "\n";
  os << "  state: ";
  print(v->state, os);
  os << "\n";
  printOpt("clear", v->clear, os);
  os << "}\n";
}

void print(const Sensor::And *v, std::ostream &os)
{
  os << "Sensor::And {\n";
  printOpt("once", v->once, os);
  printOpt("enabled", v->enabled, os);
  os << "  sensors: [" << v->sensors.size() << " entries]\n";
  printOpt("autoUnlockTargetSlot", v->autoUnlockTargetSlot, os);
  os << "}\n";
}

void print(const Sensor::Animation *v, std::ostream &os)
{
  os << "Sensor::Animation {\n";
  printOpt("once", v->once, os);
  printOpt("enabled", v->enabled, os);
  os << "  slot: ";
  print(v->slot, os);
  os << "\n";
  os << "  animation: " << v->animation << "\n";
  os << "}\n";
}

void print(const Sensor::Any *v, std::ostream &os)
{
  os << "Sensor::Any {\n";
  printOpt("once", v->once, os);
  printOpt("enabled", v->enabled, os);
  os << "}\n";
}

void print(const Sensor::Beacon *v, std::ostream &os)
{
  os << "Sensor::Beacon {\n";
  printOpt("once", v->once, os);
  printOpt("enabled", v->enabled, os);
  os << "  message: " << v->message << "\n";
  printOpt("range", v->range, os);
  printOpt("targetSlot", v->targetSlot, os);
  printOpt("consumeMessage", v->consumeMessage, os);
  os << "}\n";
}

void print(const Sensor::Block *v, std::ostream &os)
{
  os << "Sensor::Block {\n";
  printOpt("once", v->once, os);
  printOpt("enabled", v->enabled, os);
  os << "  blocks: " << v->blocks << "\n";
  os << "  range: " << v->range << "\n";
  printOpt("max height", v->maxHeight, os);
  printOpt("random", v->random, os);
  printOpt("reserve", v->reserve, os);
  os << "}\n";
}

void print(const Sensor::BlockChange *v, std::ostream &os)
{
  os << "Sensor::BlockChange {\n";
  printOpt("once", v->once, os);
  printOpt("enabled", v->enabled, os);
  os << "  range: " << v->range << "\n";
  os << "  searchType: ";
  print(v->searchType, os);
  os << "\n";
  printOpt("targetSlot", v->targetSlot, os);
  os << "  blockSet: " << v->blockSet << "\n";
  if (v->eventType)
  {
    os << "  eventType: ";
    print(*v->eventType, os);
    os << "\n";
  }
  os << "}\n";
}

void print(const Sensor::BlockType *v, std::ostream &os)
{
  os << "Sensor::BlockType {\n";
  printOpt("once", v->once, os);
  printOpt("enabled", v->enabled, os);
  os << "  sensor:{ ";
  if (v->sensor)
    print(v->sensor.get(), os);
  os << "}\n";
  os << "  blockSet: " << v->blockSet << "\n";
  os << "}\n";
}

void print(const Sensor::CanInteract *v, std::ostream &os)
{
  os << "Sensor::CanInteract {\n";
  printOpt("once", v->once, os);
  printOpt("enabled", v->enabled, os);
  os << "  viewSector: " << v->viewSector << "\n";
  os << "  attitudes: [";
  for (size_t i = 0; i < v->attitudes.size(); ++i)
  {
    if (i)
      os << ", ";
    print(v->attitudes[i], os);
  }
  os << "]\n}\n";
}

void print(const Sensor::CanPlaceBlock *v, std::ostream &os)
{
  os << "Sensor::CanPlaceBlock {\n";
  printOpt("once", v->once, os);
  printOpt("enabled", v->enabled, os);
  os << "  direction: ";
  print(v->direction, os);
  os << "\n";
  if (v->offset)
  {
    os << "  offset: ";
    print(*v->offset, os);
    os << "\n";
  }
  printOpt("retryDelay", v->retryDelay, os);
  printOpt("allowEmptyMaterials", v->allowEmptyMaterials, os);
  os << "}\n";
}

void print(const Sensor::CombatActionEvaluator *v, std::ostream &os)
{
  os << "Sensor::CombatActionEvaluator {\n";
  printOpt("once", v->once, os);
  printOpt("enabled", v->enabled, os);
  os << "  targetInRange: " << (v->targetInRange ? "true" : "false") << "\n";
  printOpt("allowableDeviation", v->allowableDeviation, os);
  os << "}\n";
}

void print(const Sensor::Count *v, std::ostream &os)
{
  os << "Sensor::Count {\n";
  printOpt("once", v->once, os);
  printOpt("enabled", v->enabled, os);
  printVec("count", v->count, os);
  printVec("range", v->range, os);
  printOpt("includeGroups", v->includeGroups, os);
  printOpt("excludeGroups", v->excludeGroups, os);
  os << "}\n";
}

void print(const Sensor::Damage *v, std::ostream &os)
{
  os << "Sensor::Damage {\n";
  printOpt("once", v->once, os);
  printOpt("enabled", v->enabled, os);
  printOpt("combat", v->combat, os);
  printOpt("friendly", v->friendly, os);
  printOpt("drowning", v->drowning, os);
  printOpt("environment", v->environment, os);
  printOpt("other", v->other, os);
  printOpt("targetSlot", v->targetSlot, os);
  os << "}\n";
}

void print(const Sensor::DroppedItem *v, std::ostream &os)
{
  os << "Sensor::DroppedItem {\n";
  printOpt("once", v->once, os);
  printOpt("enabled", v->enabled, os);
  os << "  range: " << v->range << "\n";
  os << "  viewSector: " << v->viewSector << "\n";
  printOpt("lineOfSight", v->lineOfSight, os);
  printOpt("items", v->items, os);
  if (v->attitudes)
  {
    os << "  attitudes: [";
    for (size_t i = 0; i < v->attitudes->size(); ++i)
    {
      if (i)
        os << ", ";
      print((*v->attitudes)[i], os);
    }
    os << "]\n";
  }
  os << "}\n";
}

void print(const Sensor::EntityEvent *v, std::ostream &os)
{
  os << "Sensor::EntityEvent {\n";
  printOpt("once", v->once, os);
  printOpt("enabled", v->enabled, os);
  os << "  range: " << v->range << "\n";
  if (v->searchType)
  {
    os << "  searchType: ";
    print(*v->searchType, os);
    os << "\n";
  }
  printOpt("targetSlot", v->targetSlot, os);
  os << "  npcGroup: " << v->npcGroup << "\n";
  os << "  eventType: ";
  print(v->eventType, os);
  os << "\n";
  printOpt("flockOnly", v->flockOnly, os);
  os << "}\n";
}

void print(const Sensor::Flag *v, std::ostream &os)
{
  os << "Sensor::Flag {\n";
  printOpt("once", v->once, os);
  printOpt("enabled", v->enabled, os);
  os << "  name: " << v->name << "\n";
  printOpt("set", v->set, os);
  os << "}\n";
}

void print(const Sensor::FlockCombatDamage *v, std::ostream &os)
{
  os << "Sensor::FlockCombatDamage {\n";
  printOpt("once", v->once, os);
  printOpt("enabled", v->enabled, os);
  printOpt("leaderOnly", v->leaderOnly, os);
  os << "}\n";
}

void print(const Sensor::FlockLeader *v, std::ostream &os)
{
  os << "Sensor::FlockLeader {\n";
  printOpt("once", v->once, os);
  printOpt("enabled", v->enabled, os);
  os << "}\n";
}

void print(const Sensor::HasHostileTargetMemory *v, std::ostream &os)
{
  os << "Sensor::HasHostileTargetMemory {\n";
  printOpt("once", v->once, os);
  printOpt("enabled", v->enabled, os);
  os << "}\n";
}

void print(const Sensor::HasInteracted *v, std::ostream &os)
{
  os << "Sensor::HasInteracted {\n";
  printOpt("once", v->once, os);
  printOpt("enabled", v->enabled, os);
  os << "}\n";
}

void print(const Sensor::HasTask *v, std::ostream &os)
{
  os << "Sensor::HasTask {\n";
  printOpt("once", v->once, os);
  printOpt("enabled", v->enabled, os);
  printVec("taskById", v->taskById, os);
  os << "}\n";
}

void print(const Sensor::InAir *v, std::ostream &os)
{
  os << "Sensor::InAir {\n";
  printOpt("once", v->once, os);
  printOpt("enabled", v->enabled, os);
  os << "}\n";
}

void print(const Sensor::InWater *v, std::ostream &os)
{
  os << "Sensor::InWater {\n";
  printOpt("once", v->once, os);
  printOpt("enabled", v->enabled, os);
  os << "}\n";
}

void print(const Sensor::InflictedDamage *v, std::ostream &os)
{
  os << "Sensor::InflictedDamage {\n";
  printOpt("once", v->once, os);
  printOpt("enabled", v->enabled, os);
  if (v->target)
  {
    os << "  target: ";
    print(*v->target, os);
    os << "\n";
  }
  printOpt("friendlyFire", v->friendlyFire, os);
  os << "}\n";
}

void print(const Sensor::InteractionContext *v, std::ostream &os)
{
  os << "Sensor::InteractionContext {\n";
  printOpt("once", v->once, os);
  printOpt("enabled", v->enabled, os);
  os << "  context: " << v->context << "\n";
  os << "}\n";
}

void print(const Sensor::IsBackingAway *v, std::ostream &os)
{
  os << "Sensor::IsBackingAway {\n";
  printOpt("once", v->once, os);
  printOpt("enabled", v->enabled, os);
  os << "}\n";
}

void print(const Sensor::IsBusy *v, std::ostream &os)
{
  os << "Sensor::IsBusy {\n";
  printOpt("once", v->once, os);
  printOpt("enabled", v->enabled, os);
  os << "}\n";
}

void print(const Sensor::Kill *v, std::ostream &os)
{
  os << "Sensor::Kill {\n";
  printOpt("once", v->once, os);
  printOpt("enabled", v->enabled, os);
  printOpt("targetSlot", v->targetSlot, os);
  os << "}\n";
}

void print(const Sensor::Leash *v, std::ostream &os)
{
  os << "Sensor::Leash {\n";
  printOpt("once", v->once, os);
  printOpt("enabled", v->enabled, os);
  os << "  range: " << v->range << "\n";
  os << "}\n";
}

void print(const Sensor::Light *v, std::ostream &os)
{
  os << "Sensor::Light {\n";
  printOpt("once", v->once, os);
  printOpt("enabled", v->enabled, os);
  printOpt("lightRange", v->lightRange, os);
  printOpt("skyLightRange", v->skyLightRange, os);
  printOpt("sunlightRange", v->sunlightRange, os);
  printOpt("redLightRange", v->redLightRange, os);
  printOpt("greenLightRange", v->greenLightRange, os);
  printOpt("blueLightRange", v->blueLightRange, os);
  printOpt("targetSlot", v->targetSlot, os);
  os << "}\n";
}

void print(const Sensor::Mob *v, std::ostream &os)
{
  os << "Sensor::Mob {\n";
  printOpt("once", v->once, os);
  printOpt("enabled", v->enabled, os);
  printOpt("minRange", v->minRange, os);
  os << "  range: " << v->range << "\n";
  printOpt("lockedOnTarget", v->lockedOnTarget, os);
  printOpt("lockedTargetSlot", v->lockedTargetSlot, os);
  printOpt("autoUnlockTarget", v->autoUnlockTarget, os);
  printOpt("onlyLockedTarget", v->onlyLockedTarget, os);
  printOpt("ignoredTargetSlot", v->ignoredTargetSlot, os);
  printOpt("useProjectedDistance", v->useProjectedDistance, os);
  printOpt("getPlayers", v->getPlayers, os);
  printOpt("getNPCs", v->getNPCs, os);
  printOpt("excludeOwnType", v->excludeOwnType, os);
  os << "}\n";
}

void print(const Sensor::Nav *v, std::ostream &os)
{
  os << "Sensor::Nav {\n";
  printOpt("once", v->once, os);
  printOpt("enabled", v->enabled, os);
  if (v->navStates)
  {
    os << "  navStates: [";
    for (size_t i = 0; i < v->navStates->size(); ++i)
    {
      if (i)
        os << ", ";
      print((*v->navStates)[i], os);
    }
    os << "]\n";
  }
  printOpt("throttleDuration", v->throttleDuration, os);
  printOpt("targetDelta", v->targetDelta, os);
  os << "}\n";
}

void print(const Sensor::Not *v, std::ostream &os)
{
  os << "Sensor::Not {\n";
  printOpt("once", v->once, os);
  printOpt("enabled", v->enabled, os);
  os << "  sensor:{ ";
  if (v->sensor)
    print(v->sensor.get(), os);
  os << "}\n";
  printOpt("useTargetSlot", v->useTargetSlot, os);
  printOpt("autoUnlockTargetSlot", v->autoUnlockTargetSlot, os);
  os << "}\n";
}

void print(const Sensor::OnGround *v, std::ostream &os)
{
  os << "Sensor::OnGround {\n";
  printOpt("once", v->once, os);
  printOpt("enabled", v->enabled, os);
  os << "}\n";
}

void print(const Sensor::Or *v, std::ostream &os)
{
  os << "Sensor::Or {\n";
  printOpt("once", v->once, os);
  printOpt("enabled", v->enabled, os);
  os << "  sensors: [" << v->sensors.size() << " entries]\n";
  printOpt("autoUnlockTargetSlot", v->autoUnlockTargetSlot, os);
  os << "}\n";
}

void print(const Sensor::Path *v, std::ostream &os)
{
  os << "Sensor::Path {\n";
  printOpt("once", v->once, os);
  printOpt("enabled", v->enabled, os);
  printOpt("path", v->path, os);
  printOpt("range", v->range, os);
  if (v->pathType)
  {
    os << "  pathType: ";
    print(*v->pathType, os);
    os << "\n";
  }
  os << "}\n";
}

void print(const Sensor::Player *v, std::ostream &os)
{
  os << "Sensor::Player {\n";
  printOpt("once", v->once, os);
  printOpt("enabled", v->enabled, os);
  printOpt("minRange", v->minRange, os);
  os << "  range: " << v->range << "\n";
  printOpt("lockedOnTarget", v->lockedOnTarget, os);
  printOpt("lockedTargetSlot", v->lockedTargetSlot, os);
  printOpt("autoUnlockTarget", v->autoUnlockTarget, os);
  printOpt("onlyLockedTarget", v->onlyLockedTarget, os);
  printOpt("ignoredTargetSlot", v->ignoredTargetSlot, os);
  printOpt("useProjectedDistance", v->useProjectedDistance, os);
  os << "}\n";
}

void print(const Sensor::Random *v, std::ostream &os)
{
  os << "Sensor::Random {\n";
  printOpt("once", v->once, os);
  printOpt("enabled", v->enabled, os);
  printVec("trueDurationRange", v->trueDurationRange, os);
  printVec("falseDurationRange", v->falseDurationRange, os);
  os << "}\n";
}

void print(const Sensor::ReadPosition *v, std::ostream &os)
{
  os << "Sensor::ReadPosition {\n";
  printOpt("once", v->once, os);
  printOpt("enabled", v->enabled, os);
  os << "  slot: " << v->slot << "\n";
  printOpt("minRange", v->minRange, os);
  os << "  range: " << v->range << "\n";
  printOpt("useMarkedTarget", v->useMarkedTarget, os);
  os << "}\n";
}

void print(const Sensor::SearchRay *v, std::ostream &os)
{
  os << "Sensor::SearchRay {\n";
  printOpt("once", v->once, os);
  printOpt("enabled", v->enabled, os);
  os << "  name: " << v->name << "\n";
  os << "  angle: " << v->angle << "\n";
  os << "  range: " << v->range << "\n";
  os << "  blocks: " << v->blocks << "\n";
  printOpt("minRetestAngle", v->minRetestAngle, os);
  printOpt("minRetestMove", v->minRetestMove, os);
  printOpt("throttleTime", v->throttleTime, os);
  os << "}\n";
}

void print(const Sensor::Self *v, std::ostream &os)
{
  os << "Sensor::Self {\n";
  printOpt("once", v->once, os);
  printOpt("enabled", v->enabled, os);
  os << "}\n";
}

void print(const Sensor::State *v, std::ostream &os)
{
  os << "Sensor::State {\n";
  printOpt("once", v->once, os);
  printOpt("enabled", v->enabled, os);
  os << "  state: " << v->state << "\n";
  printOpt("ignoreMissingSetState", v->ignoreMissingSetState, os);
  os << "}\n";
}

void print(const Sensor::Switch *v, std::ostream &os)
{
  os << "Sensor::Switch {\n";
  printOpt("once", v->once, os);
  printOpt("enabled", v->enabled, os);
  os << "  switchCheck: " << (v->switchCheck ? "true" : "false") << "\n";
  os << "}\n";
}

void print(const Sensor::Target *v, std::ostream &os)
{
  os << "Sensor::Target {\n";
  printOpt("once", v->once, os);
  printOpt("enabled", v->enabled, os);
  printOpt("targetSlot", v->targetSlot, os);
  os << "  range: " << v->range << "\n";
  printOpt("autoUnlockTarget", v->autoUnlockTarget, os);
  os << "}\n";
}

void print(const Sensor::Time *v, std::ostream &os)
{
  os << "Sensor::Time {\n";
  printOpt("once", v->once, os);
  printOpt("enabled", v->enabled, os);
  printVec("period", v->period, os);
  printOpt("checkDay", v->checkDay, os);
  printOpt("checkYear", v->checkYear, os);
  printOpt("scaleDayTimeRange", v->scaleDayTimeRange, os);
  os << "}\n";
}

void print(const Sensor::Timer *v, std::ostream &os)
{
  os << "Sensor::Timer {\n";
  printOpt("once", v->once, os);
  printOpt("enabled", v->enabled, os);
  os << "  name: " << v->name << "\n";
  if (v->state)
  {
    os << "  state: ";
    print(*v->state, os);
    os << "\n";
  }
  printOpt("timeRemainingRange", v->timeRemainingRange, os);
  os << "}\n";
}

void print(const Sensor::ValueProviderWrapper *v, std::ostream &os)
{
  os << "Sensor::ValueProviderWrapper {\n";
  printOpt("once", v->once, os);
  printOpt("enabled", v->enabled, os);
  printOpt("passValues", v->passValues, os);
  os << "  sensor:{ ";
  if (v->sensor)
    print(v->sensor.get(), os);
  os << "}\n";
  os << "  valueToParameterMappings: [" << v->valueToParameterMappings.size() << " entries]\n";
  os << "}\n";
}

void print(const Sensor::Weather *v, std::ostream &os)
{
  os << "Sensor::Weather {\n";
  printOpt("once", v->once, os);
  printOpt("enabled", v->enabled, os);
  printVec("weathers", v->weathers, os);
  os << "}\n";
}

void print(Action::Type v, std::ostream &os)
{
  switch (v)
  {
  case Action::Type::AddToHostileTargetMemory:
    os << "AddToHostileTargetMemory";
    break;
  case Action::Type::Appearance:
    os << "Appearance";
    break;
  case Action::Type::ApplyEntityEffect:
    os << "ApplyEntityEffect";
    break;
  case Action::Type::CombatAbility:
    os << "CombatAbility";
    break;
  case Action::Type::CompleteTask:
    os << "CompleteTask";
    break;
  case Action::Type::Crouch:
    os << "Crouch";
    break;
  case Action::Type::DelayDespawn:
    os << "DelayDespawn";
    break;
  case Action::Type::Despawn:
    os << "Despawn";
    break;
  case Action::Type::Die:
    os << "Die";
    break;
  case Action::Type::DisplayName:
    os << "DisplayName";
    break;
  case Action::Type::DropItem:
    os << "DropItem";
    break;
  case Action::Type::FlockState:
    os << "FlockState";
    break;
  case Action::Type::FlockTarget:
    os << "FlockTarget";
    break;
  case Action::Type::IgnoreForAvoidance:
    os << "IgnoreForAvoidance";
    break;
  case Action::Type::Inventory:
    os << "Inventory";
    break;
  case Action::Type::JoinFlock:
    os << "JoinFlock";
    break;
  case Action::Type::LeaveFlock:
    os << "LeaveFlock";
    break;
  case Action::Type::LockOnInteractionTarget:
    os << "LockOnInteractionTarget";
    break;
  case Action::Type::Log:
    os << "Log";
    break;
  case Action::Type::ModelAttachment:
    os << "ModelAttachment";
    break;
  case Action::Type::Mount:
    os << "Mount";
    break;
  case Action::Type::Nothing:
    os << "Nothing";
    break;
  case Action::Type::Notify:
    os << "Notify";
    break;
  case Action::Type::OpenBarterShop:
    os << "OpenBarterShop";
    break;
  case Action::Type::OpenShop:
    os << "OpenShop";
    break;
  case Action::Type::OverrideAltitude:
    os << "OverrideAltitude";
    break;
  case Action::Type::OverrideAttitude:
    os << "OverrideAttitude";
    break;
  case Action::Type::ParentState:
    os << "ParentState";
    break;
  case Action::Type::PickUpItem:
    os << "PickUpItem";
    break;
  case Action::Type::PlaceBlock:
    os << "PlaceBlock";
    break;
  case Action::Type::PlaySound:
    os << "PlaySound";
    break;
  case Action::Type::Random:
    os << "Random";
    break;
  case Action::Type::RecomputePath:
    os << "RecomputePath";
    break;
  case Action::Type::ReleaseTarget:
    os << "ReleaseTarget";
    break;
  case Action::Type::Remove:
    os << "Remove";
    break;
  case Action::Type::ResetBlockSensors:
    os << "ResetBlockSensors";
    break;
  case Action::Type::ResetInstructions:
    os << "ResetInstructions";
    break;
  case Action::Type::ResetPath:
    os << "ResetPath";
    break;
  case Action::Type::ResetSearchRays:
    os << "ResetSearchRays";
    break;
  case Action::Type::Role:
    os << "Role";
    break;
  case Action::Type::Sequence:
    os << "Sequence";
    break;
  case Action::Type::SetAlarm:
    os << "SetAlarm";
    break;
  case Action::Type::SetBlockToPlace:
    os << "SetBlockToPlace";
    break;
  case Action::Type::SetFlag:
    os << "SetFlag";
    break;
  case Action::Type::SetInteractable:
    os << "SetInteractable";
    break;
  case Action::Type::SetLeashPosition:
    os << "SetLeashPosition";
    break;
  case Action::Type::SetMarkedTarget:
    os << "SetMarkedTarget";
    break;
  case Action::Type::SetStat:
    os << "SetStat";
    break;
  case Action::Type::StartObjective:
    os << "StartObjective";
    break;
  case Action::Type::State:
    os << "State";
    break;
  case Action::Type::StorePosition:
    os << "StorePosition";
    break;
  case Action::Type::Timeout:
    os << "Timeout";
    break;
  case Action::Type::TimerContinue:
    os << "TimerContinue";
    break;
  case Action::Type::TimerModify:
    os << "TimerModify";
    break;
  case Action::Type::TimerPause:
    os << "TimerPause";
    break;
  case Action::Type::TimerRestart:
    os << "TimerRestart";
    break;
  case Action::Type::TimerStart:
    os << "TimerStart";
    break;
  case Action::Type::TimerStop:
    os << "TimerStop";
    break;
  case Action::Type::ToggleStateEvaluator:
    os << "ToggleStateEvaluator";
    break;
  case Action::Type::TriggerSpawnBeacon:
    os << "TriggerSpawnBeacon";
    break;
  case Action::Type::TriggerSpawners:
    os << "TriggerSpawners";
    break;
  }
}

void print(Action::CompleteTask::CompleteTaskFlag v, std::ostream &os)
{
  switch (v)
  {
  case Action::CompleteTask::CompleteTaskFlag::Status:
    os << "Status";
    break;
  case Action::CompleteTask::CompleteTaskFlag::Action:
    os << "Action";
    break;
  case Action::CompleteTask::CompleteTaskFlag::Face:
    os << "Face";
    break;
  }
}

void print(Action::Inventory::OperationFlag v, std::ostream &os)
{
  switch (v)
  {
  case Action::Inventory::OperationFlag::Add:
    os << "Add";
    break;
  case Action::Inventory::OperationFlag::RemoveHeldItem:
    os << "RemoveHeldItem";
    break;
  case Action::Inventory::OperationFlag::SetHotbar:
    os << "SetHotbar";
    break;
  case Action::Inventory::OperationFlag::Equip:
    os << "Equip";
    break;
  case Action::Inventory::OperationFlag::ClearHeldItem:
    os << "ClearHeldItem";
    break;
  case Action::Inventory::OperationFlag::EquipOffHand:
    os << "EquipOffHand";
    break;
  case Action::Inventory::OperationFlag::Remove:
    os << "Remove";
    break;
  case Action::Inventory::OperationFlag::EquipHotbar:
    os << "EquipHotbar";
    break;
  case Action::Inventory::OperationFlag::SetOffHand:
    os << "SetOffHand";
    break;
  }
}

void print(const Action::Action *v, std::ostream &os)
{
  if (!v)
    return;

  switch (v->type)
  {
  case Action::Type::AddToHostileTargetMemory:
    print(static_cast<const Action::AddToHostileTargetMemory *>(v), os);
    break;
  case Action::Type::Appearance:
    print(static_cast<const Action::Appearance *>(v), os);
    break;
  case Action::Type::ApplyEntityEffect:
    print(static_cast<const Action::ApplyEntityEffect *>(v), os);
    break;
  case Action::Type::CombatAbility:
    print(static_cast<const Action::CombatAbility *>(v), os);
    break;
  case Action::Type::CompleteTask:
    print(static_cast<const Action::CompleteTask *>(v), os);
    break;
  case Action::Type::Crouch:
    print(static_cast<const Action::Crouch *>(v), os);
    break;
  case Action::Type::DelayDespawn:
    print(static_cast<const Action::DelayDespawn *>(v), os);
    break;
  case Action::Type::Despawn:
    print(static_cast<const Action::Despawn *>(v), os);
    break;
  case Action::Type::Die:
    print(static_cast<const Action::Die *>(v), os);
    break;
  case Action::Type::DisplayName:
    print(static_cast<const Action::DisplayName *>(v), os);
    break;
  case Action::Type::DropItem:
    print(static_cast<const Action::DropItem *>(v), os);
    break;
  case Action::Type::FlockState:
    print(static_cast<const Action::FlockState *>(v), os);
    break;
  case Action::Type::FlockTarget:
    print(static_cast<const Action::FlockTarget *>(v), os);
    break;
  case Action::Type::IgnoreForAvoidance:
    print(static_cast<const Action::IgnoreForAvoidance *>(v), os);
    break;
  case Action::Type::Inventory:
    print(static_cast<const Action::Inventory *>(v), os);
    break;
  case Action::Type::JoinFlock:
    print(static_cast<const Action::JoinFlock *>(v), os);
    break;
  case Action::Type::LeaveFlock:
    print(static_cast<const Action::LeaveFlock *>(v), os);
    break;
  case Action::Type::LockOnInteractionTarget:
    print(static_cast<const Action::LockOnInteractionTarget *>(v), os);
    break;
  case Action::Type::Log:
    print(static_cast<const Action::Log *>(v), os);
    break;
  case Action::Type::ModelAttachment:
    print(static_cast<const Action::ModelAttachment *>(v), os);
    break;
  case Action::Type::Mount:
    print(static_cast<const Action::Mount *>(v), os);
    break;
  case Action::Type::Nothing:
    print(static_cast<const Action::Nothing *>(v), os);
    break;
  case Action::Type::Notify:
    print(static_cast<const Action::Notify *>(v), os);
    break;
  case Action::Type::OpenBarterShop:
    print(static_cast<const Action::OpenBarterShop *>(v), os);
    break;
  case Action::Type::OpenShop:
    print(static_cast<const Action::OpenShop *>(v), os);
    break;
  case Action::Type::OverrideAltitude:
    print(static_cast<const Action::OverrideAltitude *>(v), os);
    break;
  case Action::Type::OverrideAttitude:
    print(static_cast<const Action::OverrideAttitude *>(v), os);
    break;
  case Action::Type::ParentState:
    print(static_cast<const Action::ParentState *>(v), os);
    break;
  case Action::Type::PickUpItem:
    print(static_cast<const Action::PickUpItem *>(v), os);
    break;
  case Action::Type::PlaceBlock:
    print(static_cast<const Action::PlaceBlock *>(v), os);
    break;
  case Action::Type::PlaySound:
    print(static_cast<const Action::PlaySound *>(v), os);
    break;
  case Action::Type::Random:
    print(static_cast<const Action::Random *>(v), os);
    break;
  case Action::Type::RecomputePath:
    print(static_cast<const Action::RecomputePath *>(v), os);
    break;
  case Action::Type::ReleaseTarget:
    print(static_cast<const Action::ReleaseTarget *>(v), os);
    break;
  case Action::Type::Remove:
    print(static_cast<const Action::Remove *>(v), os);
    break;
  case Action::Type::ResetBlockSensors:
    print(static_cast<const Action::ResetBlockSensors *>(v), os);
    break;
  case Action::Type::ResetInstructions:
    print(static_cast<const Action::ResetInstructions *>(v), os);
    break;
  case Action::Type::ResetPath:
    print(static_cast<const Action::ResetPath *>(v), os);
    break;
  case Action::Type::ResetSearchRays:
    print(static_cast<const Action::ResetSearchRays *>(v), os);
    break;
  case Action::Type::Role:
    print(static_cast<const Action::Role *>(v), os);
    break;
  case Action::Type::Sequence:
    print(static_cast<const Action::Sequence *>(v), os);
    break;
  case Action::Type::SetAlarm:
    print(static_cast<const Action::SetAlarm *>(v), os);
    break;
  case Action::Type::SetBlockToPlace:
    print(static_cast<const Action::SetBlockToPlace *>(v), os);
    break;
  case Action::Type::SetFlag:
    print(static_cast<const Action::SetFlag *>(v), os);
    break;
  case Action::Type::SetInteractable:
    print(static_cast<const Action::SetInteractable *>(v), os);
    break;
  case Action::Type::SetLeashPosition:
    print(static_cast<const Action::SetLeashPosition *>(v), os);
    break;
  case Action::Type::SetMarkedTarget:
    print(static_cast<const Action::SetMarkedTarget *>(v), os);
    break;
  case Action::Type::SetStat:
    print(static_cast<const Action::SetStat *>(v), os);
    break;
  case Action::Type::StartObjective:
    print(static_cast<const Action::StartObjective *>(v), os);
    break;
  case Action::Type::State:
    print(static_cast<const Action::State *>(v), os);
    break;
  case Action::Type::StorePosition:
    print(static_cast<const Action::StorePosition *>(v), os);
    break;
  case Action::Type::Timeout:
    print(static_cast<const Action::Timeout *>(v), os);
    break;
  case Action::Type::TimerContinue:
    print(static_cast<const Action::TimerContinue *>(v), os);
    break;
  case Action::Type::TimerModify:
    print(static_cast<const Action::TimerModify *>(v), os);
    break;
  case Action::Type::TimerPause:
    print(static_cast<const Action::TimerPause *>(v), os);
    break;
  case Action::Type::TimerRestart:
    print(static_cast<const Action::TimerRestart *>(v), os);
    break;
  case Action::Type::TimerStart:
    print(static_cast<const Action::TimerStart *>(v), os);
    break;
  case Action::Type::TimerStop:
    print(static_cast<const Action::TimerStop *>(v), os);
    break;
  case Action::Type::ToggleStateEvaluator:
    print(static_cast<const Action::ToggleStateEvaluator *>(v), os);
    break;
  case Action::Type::TriggerSpawnBeacon:
    print(static_cast<const Action::TriggerSpawnBeacon *>(v), os);
    break;
  case Action::Type::TriggerSpawners:
    print(static_cast<const Action::TriggerSpawners *>(v), os);
    break;
  }
}

void print(const Action::WeightedAction *v, std::ostream &os)
{
  os << "WeightedAction {\n";
  os << "  action:{ ";
  if (v->action)
    print(v->action.get(), os);
  os << "}\n";
  os << "  weight: " << v->weight << "\n";
  os << "}\n";
}

void print(const Action::ActionList *v, std::ostream &os)
{
  os << "ActionList { actions: [" << v->actions.size() << " entries] }\n";
}

void print(const Action::AddToHostileTargetMemory *v, std::ostream &os)
{
  os << "Action::AddToHostileTargetMemory {\n";
  printOpt("once", v->once, os);
  os << "}\n";
}

void print(const Action::Appearance *v, std::ostream &os)
{
  os << "Action::Appearance {\n";
  printOpt("once", v->once, os);
  os << "  appearance: " << v->appearance << "\n";
  os << "}\n";
}

void print(const Action::ApplyEntityEffect *v, std::ostream &os)
{
  os << "Action::ApplyEntityEffect {\n";
  printOpt("once", v->once, os);
  os << "  entityEffect: " << v->entityEffect << "\n";
  printOpt("useTarget", v->useTarget, os);
  os << "}\n";
}

void print(const Action::CombatAbility *v, std::ostream &os)
{
  os << "Action::CombatAbility {\n";
  printOpt("once", v->once, os);
  os << "}\n";
}

void print(const Action::CompleteTask *v, std::ostream &os)
{
  os << "Action::CompleteTask {\n";
  printOpt("once", v->once, os);
  os << "  slot: ";
  print(v->slot, os);
  os << "\n";
  printOpt("animation", v->animation, os);
  printOpt("playAnimation", v->playAnimation, os);
  os << "}\n";
}

void print(const Action::Crouch *v, std::ostream &os)
{
  os << "Action::Crouch {\n";
  printOpt("once", v->once, os);
  printOpt("crouch", v->crouch, os);
  os << "}\n";
}

void print(const Action::DelayDespawn *v, std::ostream &os)
{
  os << "Action::DelayDespawn {\n";
  printOpt("once", v->once, os);
  os << "  time: " << v->time << "\n";
  printOpt("shorten", v->shorten, os);
  os << "}\n";
}

void print(const Action::Despawn *v, std::ostream &os)
{
  os << "Action::Despawn {\n";
  printOpt("once", v->once, os);
  printOpt("force", v->force, os);
  os << "}\n";
}

void print(const Action::Die *v, std::ostream &os)
{
  os << "Action::Die {\n";
  printOpt("once", v->once, os);
  os << "}\n";
}

void print(const Action::DisplayName *v, std::ostream &os)
{
  os << "Action::DisplayName {\n";
  printOpt("once", v->once, os);
  os << "  displayName: " << v->displayName << "\n";
  os << "}\n";
}

void print(const Action::DropItem *v, std::ostream &os)
{
  os << "Action::DropItem {\n";
  printOpt("once", v->once, os);
  printOpt("delay", v->delay, os);
  printOpt("item", v->item, os);
  printOpt("dropList", v->dropList, os);
  printOpt("throwSpeed", v->throwSpeed, os);
  printOpt("distance", v->distance, os);
  printOpt("dropSector", v->dropSector, os);
  printOpt("pitchHigh", v->pitchHigh, os);
  os << "}\n";
}

void print(const Action::FlockState *v, std::ostream &os)
{
  os << "Action::FlockState {\n";
  printOpt("once", v->once, os);
  os << "  state: " << v->state << "\n";
  os << "}\n";
}

void print(const Action::FlockTarget *v, std::ostream &os)
{
  os << "Action::FlockTarget {\n";
  printOpt("once", v->once, os);
  printOpt("clear", v->clear, os);
  printOpt("targetSlot", v->targetSlot, os);
  os << "}\n";
}

void print(const Action::IgnoreForAvoidance *v, std::ostream &os)
{
  os << "Action::IgnoreForAvoidance {\n";
  printOpt("once", v->once, os);
  os << "  targetSlot: " << v->targetSlot << "\n";
  os << "}\n";
}

void print(const Action::Inventory *v, std::ostream &os)
{
  os << "Action::Inventory {\n";
  printOpt("once", v->once, os);
  if (v->operation)
  {
    os << "  operation: ";
    print(*v->operation, os);
    os << "\n";
  }
  printOpt("count", v->count, os);
  printOpt("item", v->item, os);
  printOpt("useTarget", v->useTarget, os);
  printOpt("slot", v->slot, os);
  os << "}\n";
}

void print(const Action::JoinFlock *v, std::ostream &os)
{
  os << "Action::JoinFlock {\n";
  printOpt("once", v->once, os);
  printOpt("forceJoin", v->forceJoin, os);
  os << "}\n";
}

void print(const Action::LeaveFlock *v, std::ostream &os)
{
  os << "Action::LeaveFlock {\n";
  printOpt("once", v->once, os);
  os << "}\n";
}

void print(const Action::LockOnInteractionTarget *v, std::ostream &os)
{
  os << "Action::LockOnInteractionTarget {\n";
  printOpt("once", v->once, os);
  os << "  targetSlot: " << v->targetSlot << "\n";
  os << "}\n";
}

void print(const Action::Log *v, std::ostream &os)
{
  os << "Action::Log {\n";
  printOpt("once", v->once, os);
  os << "  message: " << v->message << "\n";
  os << "}\n";
}

void print(const Action::ModelAttachment *v, std::ostream &os)
{
  os << "Action::ModelAttachment {\n";
  printOpt("once", v->once, os);
  os << "  slot: " << v->slot << "\n";
  os << "  attachment: " << v->attachment << "\n";
  os << "}\n";
}

void print(const Action::Mount *v, std::ostream &os)
{
  os << "Action::Mount {\n";
  printOpt("once", v->once, os);
  os << "  anchorX: " << v->anchorX << "\n";
  os << "  anchorY: " << v->anchorY << "\n";
  os << "  anchorZ: " << v->anchorZ << "\n";
  os << "  movementConfig: " << v->movementConfig << "\n";
  os << "}\n";
}

void print(const Action::Nothing *, std::ostream &os)
{
  os << "Action::Nothing {}\n";
}

void print(const Action::Notify *v, std::ostream &os)
{
  os << "Action::Notify {\n";
  printOpt("once", v->once, os);
  os << "  message: " << v->message << "\n";
  os << "  slot: " << v->slot << "\n";
  os << "}\n";
}

void print(const Action::OpenBarterShop *v, std::ostream &os)
{
  os << "Action::OpenBarterShop {\n";
  printOpt("once", v->once, os);
  os << "  shop: " << v->shop << "\n";
  os << "}\n";
}

void print(const Action::OpenShop *v, std::ostream &os)
{
  os << "Action::OpenShop {\n";
  printOpt("once", v->once, os);
  os << "  shop: " << v->shop << "\n";
  os << "}\n";
}

void print(const Action::OverrideAltitude *v, std::ostream &os)
{
  os << "Action::OverrideAltitude {\n";
  printOpt("once", v->once, os);
  printVec("desiredAltitudeRange", v->desiredAltitudeRange, os);
  os << "}\n";
}

void print(const Action::OverrideAttitude *v, std::ostream &os)
{
  os << "Action::OverrideAttitude {\n";
  printOpt("once", v->once, os);
  os << "  attitude: ";
  print(v->attitude, os);
  os << "\n";
  os << "  duration: " << v->duration << "\n";
  os << "}\n";
}

void print(const Action::ParentState *v, std::ostream &os)
{
  os << "Action::ParentState {\n";
  printOpt("once", v->once, os);
  os << "  state: " << v->state << "\n";
  os << "}\n";
}

void print(const Action::PickUpItem *v, std::ostream &os)
{
  os << "Action::PickUpItem {\n";
  printOpt("once", v->once, os);
  printOpt("delay", v->delay, os);
  os << "  range: " << v->range << "\n";
  printOpt("hoover", v->hoover, os);
  printVec("items", v->items, os);
  os << "}\n";
}

void print(const Action::PlaceBlock *v, std::ostream &os)
{
  os << "Action::PlaceBlock {\n";
  printOpt("once", v->once, os);
  os << "  range: " << v->range << "\n";
  printOpt("allowEmptyMaterials", v->allowEmptyMaterials, os);
  os << "}\n";
}

void print(const Action::PlaySound *v, std::ostream &os)
{
  os << "Action::PlaySound {\n";
  printOpt("once", v->once, os);
  os << "  soundEventId: " << v->soundEventId << "\n";
  os << "}\n";
}

void print(const Action::Random *v, std::ostream &os)
{
  os << "Action::Random {\n";
  printOpt("once", v->once, os);
  os << "  actions: [" << v->actions.size() << " entries]\n";
  os << "}\n";
}

void print(const Action::RecomputePath *v, std::ostream &os)
{
  os << "Action::RecomputePath {\n";
  printOpt("once", v->once, os);
  os << "}\n";
}

void print(const Action::ReleaseTarget *v, std::ostream &os)
{
  os << "Action::ReleaseTarget {\n";
  printOpt("once", v->once, os);
  os << "  targetSlot: " << v->targetSlot << "\n";
  os << "}\n";
}

void print(const Action::Remove *v, std::ostream &os)
{
  os << "Action::Remove {\n";
  printOpt("once", v->once, os);
  printOpt("useTarget", v->useTarget, os);
  os << "}\n";
}

void print(const Action::ResetBlockSensors *v, std::ostream &os)
{
  os << "Action::ResetBlockSensors {\n";
  printOpt("once", v->once, os);
  printVec("blockSets", v->blockSets, os);
  os << "}\n";
}

void print(const Action::ResetInstructions *v, std::ostream &os)
{
  os << "Action::ResetInstructions {\n";
  printOpt("once", v->once, os);
  printOpt("instructions", v->instructions, os);
  os << "}\n";
}

void print(const Action::ResetPath *v, std::ostream &os)
{
  os << "Action::ResetPath {\n";
  printOpt("once", v->once, os);
  os << "}\n";
}

void print(const Action::ResetSearchRays *v, std::ostream &os)
{
  os << "Action::ResetSearchRays {\n";
  printOpt("once", v->once, os);
  printVec("names", v->names, os);
  os << "}\n";
}

void print(const Action::Role *v, std::ostream &os)
{
  os << "Action::Role {\n";
  printOpt("once", v->once, os);
  os << "  role: " << v->role << "\n";
  printOpt("changeAppearance", v->changeAppearance, os);
  printOpt("state", v->state, os);
  os << "}\n";
}

void print(const Action::Sequence *v, std::ostream &os)
{
  os << "Action::Sequence {\n";
  printOpt("once", v->once, os);
  printOpt("blocking", v->blocking, os);
  printOpt("atomic", v->atomic, os);
  os << "  actions: [" << v->actions.actions.size() << " entries]\n";
  os << "}\n";
}

void print(const Action::SetAlarm *v, std::ostream &os)
{
  os << "Action::SetAlarm {\n";
  printOpt("once", v->once, os);
  os << "  name: " << v->name << "\n";
  printVec("durationRange", v->durationRange, os);
  os << "}\n";
}

void print(const Action::SetBlockToPlace *v, std::ostream &os)
{
  os << "Action::SetBlockToPlace {\n";
  printOpt("once", v->once, os);
  os << "  block: " << v->block << "\n";
  os << "}\n";
}

void print(const Action::SetFlag *v, std::ostream &os)
{
  os << "Action::SetFlag {\n";
  printOpt("once", v->once, os);
  os << "  name: " << v->name << "\n";
  printOpt("setTo", v->setTo, os);
  os << "}\n";
}

void print(const Action::SetInteractable *v, std::ostream &os)
{
  os << "Action::SetInteractable {\n";
  printOpt("once", v->once, os);
  printOpt("interactable", v->interactable, os);
  printOpt("hint", v->hint, os);
  printOpt("showPrompt", v->showPrompt, os);
  os << "}\n";
}

void print(const Action::SetLeashPosition *v, std::ostream &os)
{
  os << "Action::SetLeashPosition {\n";
  printOpt("once", v->once, os);
  printOpt("toCurrent", v->toCurrent, os);
  printOpt("toTarget", v->toTarget, os);
  os << "}\n";
}

void print(const Action::SetMarkedTarget *v, std::ostream &os)
{
  os << "Action::SetMarkedTarget {\n";
  printOpt("once", v->once, os);
  os << "  targetSlot: " << v->targetSlot << "\n";
  os << "}\n";
}

void print(const Action::SetStat *v, std::ostream &os)
{
  os << "Action::SetStat {\n";
  printOpt("once", v->once, os);
  os << "  stat: " << v->stat << "\n";
  os << "  value: " << v->value << "\n";
  printOpt("add", v->add, os);
  os << "}\n";
}

void print(const Action::StartObjective *v, std::ostream &os)
{
  os << "Action::StartObjective {\n";
  printOpt("once", v->once, os);
  os << "  objective: " << v->objective << "\n";
  os << "}\n";
}

void print(const Action::State *v, std::ostream &os)
{
  os << "Action::State {\n";
  printOpt("once", v->once, os);
  os << "  state: " << v->state << "\n";
  printOpt("clearState", v->clearState, os);
  os << "}\n";
}

void print(const Action::StorePosition *v, std::ostream &os)
{
  os << "Action::StorePosition {\n";
  printOpt("once", v->once, os);
  os << "  slot: " << v->slot << "\n";
  os << "}\n";
}

void print(const Action::Timeout *v, std::ostream &os)
{
  os << "Action::Timeout {\n";
  printOpt("once", v->once, os);
  printVec("delay", v->delay, os);
  printOpt("delayAfter", v->delayAfter, os);
  os << "  action:{ ";
  if (v->action)
    print(v->action.get(), os);
  os << "}\n";
  os << "}\n";
}

void print(const Action::TimerContinue *v, std::ostream &os)
{
  os << "Action::TimerContinue {\n";
  printOpt("once", v->once, os);
  os << "  name: " << v->name << "\n";
  os << "}\n";
}

void print(const Action::TimerModify *v, std::ostream &os)
{
  os << "Action::TimerModify {\n";
  printOpt("once", v->once, os);
  os << "  name: " << v->name << "\n";
  printOpt("addValue", v->addValue, os);
  printOpt("maxValue", v->maxValue, os);
  printOpt("rate", v->rate, os);
  printOpt("setValue", v->setValue, os);
  printOpt("repeating", v->repeating, os);
  os << "}\n";
}

void print(const Action::TimerPause *v, std::ostream &os)
{
  os << "Action::TimerPause {\n";
  printOpt("once", v->once, os);
  os << "  name: " << v->name << "\n";
  os << "}\n";
}

void print(const Action::TimerRestart *v, std::ostream &os)
{
  os << "Action::TimerRestart {\n";
  printOpt("once", v->once, os);
  os << "  name: " << v->name << "\n";
  os << "}\n";
}

void print(const Action::TimerStart *v, std::ostream &os)
{
  os << "Action::TimerStart {\n";
  printOpt("once", v->once, os);
  os << "  name: " << v->name << "\n";
  printOpt("startValueRange", v->startValueRange, os);
  printOpt("restartValueRange", v->restartValueRange, os);
  printOpt("rate", v->rate, os);
  printOpt("repeating", v->repeating, os);
  os << "}\n";
}

void print(const Action::TimerStop *v, std::ostream &os)
{
  os << "Action::TimerStop {\n";
  printOpt("once", v->once, os);
  os << "  name: " << v->name << "\n";
  os << "}\n";
}

void print(const Action::ToggleStateEvaluator *v, std::ostream &os)
{
  os << "Action::ToggleStateEvaluator {\n";
  printOpt("once", v->once, os);
  printOpt("enabled", v->enabled, os);
  os << "}\n";
}

void print(const Action::TriggerSpawnBeacon *v, std::ostream &os)
{
  os << "Action::TriggerSpawnBeacon {\n";
  printOpt("once", v->once, os);
  os << "  beaconSpawn: " << v->beaconSpawn << "\n";
  os << "  range: " << v->range << "\n";
  printOpt("targetSlot", v->targetSlot, os);
  os << "}\n";
}

void print(const Action::TriggerSpawners *v, std::ostream &os)
{
  os << "Action::TriggerSpawners {\n";
  printOpt("once", v->once, os);
  printOpt("spawnMarker", v->spawnMarker, os);
  os << "  range: " << v->range << "\n";
  if (v->count)
    os << "  count: " << *v->count << "\n";
  os << "}\n";
}

void print(BodyMotion::Type v, std::ostream &os)
{
  switch (v)
  {
  case BodyMotion::Type::AimCharge:
    os << "AimCharge";
    break;
  case BodyMotion::Type::MaintainDistance:
    os << "MaintainDistance";
    break;
  case BodyMotion::Type::MatchLook:
    os << "MatchLook";
    break;
  case BodyMotion::Type::Nothing:
    os << "Nothing";
    break;
  case BodyMotion::Type::Path:
    os << "Path";
    break;
  case BodyMotion::Type::Sequence:
    os << "Sequence";
    break;
  case BodyMotion::Type::Timer:
    os << "Timer";
    break;
  case BodyMotion::Type::Wander:
    os << "Wander";
    break;
  case BodyMotion::Type::WanderInCircle:
    os << "WanderInCircle";
    break;
  case BodyMotion::Type::WanderInRect:
    os << "WanderInRect";
    break;
  }
}

void print(BodyMotion::MovementFlag v, std::ostream &os)
{
  switch (v)
  {
  case BodyMotion::MovementFlag::Backward:
    os << "Backward";
    break;
  case BodyMotion::MovementFlag::Random:
    os << "Random";
    break;
  case BodyMotion::MovementFlag::Forward:
    os << "Forward";
    break;
  case BodyMotion::MovementFlag::Any:
    os << "Any";
    break;
  }
}

void print(BodyMotion::PathShapeFlag v, std::ostream &os)
{
  switch (v)
  {
  case BodyMotion::PathShapeFlag::Chain:
    os << "Chain";
    break;
  case BodyMotion::PathShapeFlag::Line:
    os << "Line";
    break;
  case BodyMotion::PathShapeFlag::Loop:
    os << "Loop";
    break;
  case BodyMotion::PathShapeFlag::Points:
    os << "Points";
    break;
  }
}

void print(const BodyMotion::BodyMotion &v, std::ostream &os)
{
  os << "BodyMotion { type: ";
  print(v.type, os);
  os << " }\n";
}

void print(const BodyMotion::AimCharge &v, std::ostream &os)
{
  os << "BodyMotion::AimCharge {\n";
  printOpt("relativeTurnSpeed", v.relativeTurnSpeed, os);
  os << "}\n";
}

void print(const BodyMotion::MaintainDistance &v, std::ostream &os)
{
  os << "BodyMotion::MaintainDistance {\n";
  printVec("desiredDistanceRange", v.desiredDistanceRange, os);
  printOpt("targetDistanceFactor", v.targetDistanceFactor, os);
  printOpt("moveThreshold", v.moveThreshold, os);
  printOpt("relativeForwardsSpeed", v.relativeForwardsSpeed, os);
  printOpt("relativeBackwardsSpeed", v.relativeBackwardsSpeed, os);
  printOpt("moveTowardsSlowdownThreshold", v.moveTowardsSlowdownThreshold, os);
  printOpt("strafingDurationRange", v.strafingDurationRange, os);
  printOpt("strafingFrequencyRange", v.strafingFrequencyRange, os);
  os << "}\n";
}

void print(const BodyMotion::MatchLook &, std::ostream &os)
{
  os << "BodyMotion::MatchLook {}\n";
}

void print(const BodyMotion::Nothing &, std::ostream &os)
{
  os << "BodyMotion::Nothing {}\n";
}

void print(const BodyMotion::Path &v, std::ostream &os)
{
  os << "BodyMotion::Path {\n";
  printOpt("startAtNearestNode", v.startAtNearestNode, os);
  printOpt("minRelSpeed", v.minRelSpeed, os);
  printOpt("maxRelSpeed", v.maxRelSpeed, os);
  if (v.direction)
  {
    os << "  direction: ";
    print(*v.direction, os);
    os << "\n";
  }
  if (v.shape)
  {
    os << "  shape: ";
    print(*v.shape, os);
    os << "\n";
  }
  printOpt("minNodeDelay", v.minNodeDelay, os);
  printOpt("maxNodeDelay", v.maxNodeDelay, os);
  printOpt("useNodeViewDirection", v.useNodeViewDirection, os);
  printOpt("nodePauseScaleRange", v.nodePauseScaleRange, os);
  printOpt("nodePauseExtraPercentRange", v.nodePauseExtraPercentRange, os);
  printOpt("pickRandomAngle", v.pickRandomAngle, os);
  if (v.viewSegments)
    os << "  viewSegments: " << *v.viewSegments << "\n";
  os << "}\n";
}

void print(const BodyMotion::Sequence &v, std::ostream &os)
{
  os << "BodyMotion::Sequence {\n";
  printOpt("looped", v.looped, os);
  os << "  motions: [" << v.motions.size() << " entries]\n";
  os << "}\n";
}

void print(const BodyMotion::Timer &v, std::ostream &os)
{
  os << "BodyMotion::Timer {\n";
  printOpt("time", v.time, os);
  os << "  motion.type: ";
  print(v.motion.type, os);
  os << "\n";
  os << "}\n";
}

void print(const BodyMotion::Wander &v, std::ostream &os)
{
  os << "BodyMotion::Wander {\n";
  printOpt("minWalkTime", v.minWalkTime, os);
  printOpt("maxWalkTime", v.maxWalkTime, os);
  printOpt("minHeadingChange", v.minHeadingChange, os);
  printOpt("maxHeadingChange", v.maxHeadingChange, os);
  printOpt("relaxHeadingChange", v.relaxHeadingChange, os);
  printOpt("relativeSpeed", v.relativeSpeed, os);
  printOpt("minMoveDistance", v.minMoveDistance, os);
  printOpt("stopDistance", v.stopDistance, os);
  printOpt("avoidBlockDamage", v.avoidBlockDamage, os);
  printOpt("relaxedMoveConstraints", v.relaxedMoveConstraints, os);
  printOpt("desiredAltitudeWeight", v.desiredAltitudeWeight, os);
  os << "}\n";
}

void print(const BodyMotion::WanderInCircle &v, std::ostream &os)
{
  os << "BodyMotion::WanderInCircle {\n";
  printOpt("minWalkTime", v.minWalkTime, os);
  printOpt("maxWalkTime", v.maxWalkTime, os);
  printOpt("minHeadingChange", v.minHeadingChange, os);
  printOpt("maxHeadingChange", v.maxHeadingChange, os);
  printOpt("relaxHeadingChange", v.relaxHeadingChange, os);
  printOpt("relativeSpeed", v.relativeSpeed, os);
  printOpt("minMoveDistance", v.minMoveDistance, os);
  printOpt("stopDistance", v.stopDistance, os);
  printOpt("avoidBlockDamage", v.avoidBlockDamage, os);
  printOpt("relaxedMoveConstraints", v.relaxedMoveConstraints, os);
  printOpt("desiredAltitudeWeight", v.desiredAltitudeWeight, os);
  printOpt("radius", v.radius, os);
  printOpt("useSphere", v.useSphere, os);
  os << "}\n";
}

void print(const BodyMotion::WanderInRect &v, std::ostream &os)
{
  os << "BodyMotion::WanderInRect {\n";
  printOpt("minWalkTime", v.minWalkTime, os);
  printOpt("maxWalkTime", v.maxWalkTime, os);
  printOpt("minHeadingChange", v.minHeadingChange, os);
  printOpt("maxHeadingChange", v.maxHeadingChange, os);
  printOpt("relaxHeadingChange", v.relaxHeadingChange, os);
  printOpt("relativeSpeed", v.relativeSpeed, os);
  printOpt("minMoveDistance", v.minMoveDistance, os);
  printOpt("stopDistance", v.stopDistance, os);
  printOpt("avoidBlockDamage", v.avoidBlockDamage, os);
  printOpt("relaxedMoveConstraints", v.relaxedMoveConstraints, os);
  printOpt("desiredAltitudeWeight", v.desiredAltitudeWeight, os);
  printOpt("width", v.width, os);
  printOpt("depth", v.depth, os);
  os << "}\n";
}

void print(HeadMotion::Type v, std::ostream &os)
{
  switch (v)
  {
  case HeadMotion::Type::Aim:
    os << "Aim";
    break;
  case HeadMotion::Type::Nothing:
    os << "Nothing";
    break;
  case HeadMotion::Type::Observe:
    os << "Observe";
    break;
  case HeadMotion::Type::Sequence:
    os << "Sequence";
    break;
  case HeadMotion::Type::Timer:
    os << "Timer";
    break;
  case HeadMotion::Type::Watch:
    os << "Watch";
    break;
  }
}

void print(const HeadMotion::HeadMotion &v, std::ostream &os)
{
  os << "HeadMotion { type: ";
  print(v.type, os);
  os << " }\n";
}

void print(const HeadMotion::Aim &v, std::ostream &os)
{
  os << "HeadMotion::Aim {\n";
  printOpt("relativeTurnSpeed", v.relativeTurnSpeed, os);
  os << "}\n";
}

void print(const HeadMotion::Nothing &, std::ostream &os)
{
  os << "HeadMotion::Nothing {}\n";
}

void print(const HeadMotion::Observe &v, std::ostream &os)
{
  os << "HeadMotion::Observe {\n";
  printVec("angleRange", v.angleRange, os);
  printOpt("pauseTimeRange", v.pauseTimeRange, os);
  printOpt("pickRandomAngle", v.pickRandomAngle, os);
  if (v.viewSegments)
    os << "  viewSegments: " << *v.viewSegments << "\n";
  printOpt("relativeTurnSpeed", v.relativeTurnSpeed, os);
  os << "}\n";
}

void print(const HeadMotion::Sequence &v, std::ostream &os)
{
  os << "HeadMotion::Sequence {\n";
  printOpt("looped", v.looped, os);
  os << "  motions: [" << v.motions.size() << " entries]\n";
  os << "}\n";
}

void print(const HeadMotion::Timer &v, std::ostream &os)
{
  os << "HeadMotion::Timer {\n";
  printOpt("time", v.time, os);
  os << "  motion.type: ";
  print(v.motion.type, os);
  os << "\n";
  os << "}\n";
}

void print(const HeadMotion::Watch &v, std::ostream &os)
{
  os << "HeadMotion::Watch {\n";
  printOpt("relativeTurnSpeed", v.relativeTurnSpeed, os);
  os << "}\n";
}

void print(Expression::Kind v, std::ostream &os)
{
  switch (v)
  {
  case Expression::Kind::Literal:
    os << "Literal";
    break;
  case Expression::Kind::Range:
    os << "Range";
    break;
  }
}

void print(const Expression &v, std::ostream &os)
{
  os << "Expression {\n";
  os << "  kind: ";
  print(v.kind, os);
  os << "\n";
  if (v.kind == Expression::Kind::Literal)
  {
    os << "  literal: ";
    std::visit([&os](const auto &val)
               {
      using T = std::decay_t<decltype(val)>;
      if constexpr (std::is_same_v<T, bool>)
        os << (val ? "true" : "false");
      else if constexpr (std::is_same_v<T, std::vector<std::string>>)
      {
        os << "[";
        for (size_t i = 0; i < val.size(); ++i) { if (i) os << ", "; os << val[i]; }
        os << "]";
      }
      else
        os << val; }, v.literal);
    os << "\n";
  }
  else
  {
    os << "  range: [" << v.range.min << ", " << v.range.max << "]\n";
  }
  os << "}\n";
}

void print(const ReferenceInstruction &v, std::ostream &os)
{
  os << "ReferenceInstruction {\n";
  os << "  referenceId: " << v.referenceId << "\n";
  os << "  overrides: [" << v.overrides.size() << " entries]\n";
  os << "}\n";
}

void print(const Instruction &v, std::ostream &os)
{
  os << "Instruction {\n";
  os << "  name: " << v.name << "\n";
  printOpt("comment", v.comment, os);
  printOpt("enabled", v.enabled, os);
  os << "  sensor:{ ";
  if (v.sensor)
    print(v.sensor.get(), os);
  os << "}\n";

  if (v.actions.size() > 0)
  {
    os << "  actions (size: " << v.actions.size() << "):{\n";

    for (auto &action : v.actions)
    {
      if (action)
        print(action.get());
    }

    os << "}\n";
  }
  else
  {
    os << "  actions (empty)\n";
  }

  printOpt("actionsBlocking", v.actionsBlocking, os);
  printOpt("actionsAtomic", v.actionsAtomic, os);
  os << "  instructions: [" << v.instructions.size() << " nested]\n";

  os << "  instructions (size: " << v.instructions.size() << "):{\n";

  for (auto &instruction : v.instructions)
  {
    print(instruction);
  }

  os << "}\n";

  printOpt("cont", v.cont, os);
  if (v.weight)
    os << "  weight: " << *v.weight << "\n";
  os << "}\n";
}

void print(const StateTransition &v, std::ostream &os)
{
  os << "StateTransition {\n";
  os << "  priority: " << v.priority << "\n";
  printVec("from", v.from, os);
  printVec("to", v.to, os);
  printOpt("enabled", v.enabled, os);
  os << "}\n";
}

void print(const RequiredAttributes &v, std::ostream &os)
{
  os << "RequiredAttributes {\n";
  os << "  maxHealth: " << v.maxHealth << "\n";
  os << "  appearance: " << v.appearance << "\n";
  os << "  nameTranslationKey: " << v.nameTranslationKey << "\n";
  printVec("busyStates", v.busyStates, os);
  os << "  motionControllerList: [" << v.motionControllerList.size() << " entries]\n";
  os << "}\n";
}

void print(const Attributes &v, std::ostream &os)
{
  os << "Attributes {\n";
  os << "  requiredAttributes:\n";
  print(v.requiredAttributes, os);
  printOpt("initialMotionController", v.initialMotionController, os);
  printOpt("displayNames", v.displayNames, os);
  printOpt("opaqueBlockSet", v.opaqueBlockSet, os);
  printOpt("knockbackScale", v.knockbackScale, os);
  printOpt("inventorySize", v.inventorySize, os);
  printOpt("hotbarSize", v.hotbarSize, os);
  printOpt("offhandSlots", v.offhandSlots, os);
  printOpt("hotbarItems", v.hotbarItems, os);
  printOpt("offhandItems", v.offhandItems, os);
  printOpt("possibleInventoryItems", v.possibleInventoryItems, os);
  printOpt("defaultOffhandSlot", v.defaultOffhandSlot, os);
  printOpt("dropList", v.dropList, os);
  printOpt("startState", v.startState, os);
  printOpt("defaultSubState", v.defaultSubState, os);
  printOpt("collisionDistance", v.collisionDistance, os);
  printOpt("combatConfig", v.combatConfig, os);
  printOpt("invulnerable", v.invulnerable, os);
  printOpt("pickupDropOnDeath", v.pickupDropOnDeath, os);
  printOpt("deathInteraction", v.deathInteraction, os);
  if (v.defaultPlayerAttitude)
  {
    os << "  defaultPlayerAttitude: ";
    print(*v.defaultPlayerAttitude, os);
    os << "\n";
  }
  if (v.defaultNPCAttitude)
  {
    os << "  defaultNPCAttitude: ";
    print(*v.defaultNPCAttitude, os);
    os << "\n";
  }
  if (v.attitudeGroup)
  {
    os << "  attitudeGroup: ";
    print(*v.attitudeGroup, os);
    os << "\n";
  }
  if (v.itemAttitudeGroup)
  {
    os << "  itemAttitudeGroup: ";
    print(*v.itemAttitudeGroup, os);
    os << "\n";
  }
  printOpt("corpseStaysInFlock", v.corpseStaysInFlock, os);
  if (v.instructions.has_value())
  {
    os << "  instructions (size: " << v.instructions->size() << "):{\n";

    for (auto &instruction : v.instructions.value())
    {
      print(instruction);
    }

    os << "}\n";
  }
  else
  {
    os << "  instructions (empty)\n";
  }

  printOpt("isMemory", v.isMemory, os);
  printOpt("memoriesCategory", v.memoriesCategory, os);
  printOpt("memoriesNameOverride", v.memoriesNameOverride, os);
  printOpt("spawnLockTime", v.spawnLockTime, os);
  os << "}\n";
}