#include "serialization.hpp"
#include <iostream>

SerializerValues::SerializerValues()
{
  sensorSerializers["AdjustPosition"] = [](NodeItem *n) -> std::unique_ptr<General::Sensor::Sensor>
  {
    return std::make_unique<General::Sensor::AdjustPosition>(static_cast<SensorNodes::AdjustPositionNode *>(n)->serialize());
  };
  sensorSerializers["Age"] = [](NodeItem *n) -> std::unique_ptr<General::Sensor::Sensor>
  {
    return std::make_unique<General::Sensor::Age>(static_cast<SensorNodes::AgeNode *>(n)->serialize());
  };
  sensorSerializers["Alarm"] = [](NodeItem *n) -> std::unique_ptr<General::Sensor::Sensor>
  {
    return std::make_unique<General::Sensor::Alarm>(static_cast<SensorNodes::AlarmNode *>(n)->serialize());
  };
  sensorSerializers["And"] = [](NodeItem *n) -> std::unique_ptr<General::Sensor::Sensor>
  {
    return std::make_unique<General::Sensor::And>(static_cast<SensorNodes::AndNode *>(n)->serialize());
  };
  sensorSerializers["Animation"] = [](NodeItem *n) -> std::unique_ptr<General::Sensor::Sensor>
  {
    return std::make_unique<General::Sensor::Animation>(static_cast<SensorNodes::AnimationNode *>(n)->serialize());
  };
  sensorSerializers["Any"] = [](NodeItem *n) -> std::unique_ptr<General::Sensor::Sensor>
  {
    return std::make_unique<General::Sensor::Any>(static_cast<SensorNodes::AnyNode *>(n)->serialize());
  };
  sensorSerializers["Beacon"] = [](NodeItem *n) -> std::unique_ptr<General::Sensor::Sensor>
  {
    return std::make_unique<General::Sensor::Beacon>(static_cast<SensorNodes::BeaconNode *>(n)->serialize());
  };
  sensorSerializers["BlockChange"] = [](NodeItem *n) -> std::unique_ptr<General::Sensor::Sensor>
  {
    return std::make_unique<General::Sensor::BlockChange>(static_cast<SensorNodes::BlockChangeNode *>(n)->serialize());
  };
  sensorSerializers["BlockType"] = [](NodeItem *n) -> std::unique_ptr<General::Sensor::Sensor>
  {
    return std::make_unique<General::Sensor::BlockType>(static_cast<SensorNodes::BlockTypeNode *>(n)->serialize());
  };
  sensorSerializers["CanInteract"] = [](NodeItem *n) -> std::unique_ptr<General::Sensor::Sensor>
  {
    return std::make_unique<General::Sensor::CanInteract>(static_cast<SensorNodes::CanInteractNode *>(n)->serialize());
  };
  sensorSerializers["CanPlaceBlock"] = [](NodeItem *n) -> std::unique_ptr<General::Sensor::Sensor>
  {
    return std::make_unique<General::Sensor::CanPlaceBlock>(static_cast<SensorNodes::CanPlaceBlockNode *>(n)->serialize());
  };
  sensorSerializers["CombatActionEvaluator"] = [](NodeItem *n) -> std::unique_ptr<General::Sensor::Sensor>
  {
    return std::make_unique<General::Sensor::CombatActionEvaluator>(static_cast<SensorNodes::CombatActionEvaluatorNode *>(n)->serialize());
  };
  sensorSerializers["Count"] = [](NodeItem *n) -> std::unique_ptr<General::Sensor::Sensor>
  {
    return std::make_unique<General::Sensor::Count>(static_cast<SensorNodes::CountNode *>(n)->serialize());
  };
  sensorSerializers["Damage"] = [](NodeItem *n) -> std::unique_ptr<General::Sensor::Sensor>
  {
    return std::make_unique<General::Sensor::Damage>(static_cast<SensorNodes::DamageNode *>(n)->serialize());
  };
  sensorSerializers["DroppedItem"] = [](NodeItem *n) -> std::unique_ptr<General::Sensor::Sensor>
  {
    return std::make_unique<General::Sensor::DroppedItem>(static_cast<SensorNodes::DroppedItemNode *>(n)->serialize());
  };
  sensorSerializers["EntityEvent"] = [](NodeItem *n) -> std::unique_ptr<General::Sensor::Sensor>
  {
    return std::make_unique<General::Sensor::EntityEvent>(static_cast<SensorNodes::EntityEventNode *>(n)->serialize());
  };
  sensorSerializers["Flag"] = [](NodeItem *n) -> std::unique_ptr<General::Sensor::Sensor>
  {
    return std::make_unique<General::Sensor::Flag>(static_cast<SensorNodes::FlagNode *>(n)->serialize());
  };
  sensorSerializers["FlockCombatDamage"] = [](NodeItem *n) -> std::unique_ptr<General::Sensor::Sensor>
  {
    return std::make_unique<General::Sensor::FlockCombatDamage>(static_cast<SensorNodes::FlockCombatDamageNode *>(n)->serialize());
  };
  sensorSerializers["FlockLeader"] = [](NodeItem *n) -> std::unique_ptr<General::Sensor::Sensor>
  {
    return std::make_unique<General::Sensor::FlockLeader>(static_cast<SensorNodes::FlockLeaderNode *>(n)->serialize());
  };
  sensorSerializers["HasHostileTargetMemory"] = [](NodeItem *n) -> std::unique_ptr<General::Sensor::Sensor>
  {
    return std::make_unique<General::Sensor::HasHostileTargetMemory>(static_cast<SensorNodes::HasHostileTargetMemoryNode *>(n)->serialize());
  };
  sensorSerializers["HasInteracted"] = [](NodeItem *n) -> std::unique_ptr<General::Sensor::Sensor>
  {
    return std::make_unique<General::Sensor::HasInteracted>(static_cast<SensorNodes::HasInteractedNode *>(n)->serialize());
  };
  sensorSerializers["HasTask"] = [](NodeItem *n) -> std::unique_ptr<General::Sensor::Sensor>
  {
    return std::make_unique<General::Sensor::HasTask>(static_cast<SensorNodes::HasTaskNode *>(n)->serialize());
  };
  sensorSerializers["InAir"] = [](NodeItem *n) -> std::unique_ptr<General::Sensor::Sensor>
  {
    return std::make_unique<General::Sensor::InAir>(static_cast<SensorNodes::InAirNode *>(n)->serialize());
  };
  sensorSerializers["InWater"] = [](NodeItem *n) -> std::unique_ptr<General::Sensor::Sensor>
  {
    return std::make_unique<General::Sensor::InWater>(static_cast<SensorNodes::InWaterNode *>(n)->serialize());
  };
  sensorSerializers["InflictedDamage"] = [](NodeItem *n) -> std::unique_ptr<General::Sensor::Sensor>
  {
    return std::make_unique<General::Sensor::InflictedDamage>(static_cast<SensorNodes::InflictedDamageNode *>(n)->serialize());
  };
  sensorSerializers["InteractionContext"] = [](NodeItem *n) -> std::unique_ptr<General::Sensor::Sensor>
  {
    return std::make_unique<General::Sensor::InteractionContext>(static_cast<SensorNodes::InteractionContextNode *>(n)->serialize());
  };
  sensorSerializers["IsBackingAway"] = [](NodeItem *n) -> std::unique_ptr<General::Sensor::Sensor>
  {
    return std::make_unique<General::Sensor::IsBackingAway>(static_cast<SensorNodes::IsBackingAwayNode *>(n)->serialize());
  };
  sensorSerializers["IsBusy"] = [](NodeItem *n) -> std::unique_ptr<General::Sensor::Sensor>
  {
    return std::make_unique<General::Sensor::IsBusy>(static_cast<SensorNodes::IsBusyNode *>(n)->serialize());
  };
  sensorSerializers["Kill"] = [](NodeItem *n) -> std::unique_ptr<General::Sensor::Sensor>
  {
    return std::make_unique<General::Sensor::Kill>(static_cast<SensorNodes::KillNode *>(n)->serialize());
  };
  sensorSerializers["Leash"] = [](NodeItem *n) -> std::unique_ptr<General::Sensor::Sensor>
  {
    return std::make_unique<General::Sensor::Leash>(static_cast<SensorNodes::LeashNode *>(n)->serialize());
  };
  sensorSerializers["Light"] = [](NodeItem *n) -> std::unique_ptr<General::Sensor::Sensor>
  {
    return std::make_unique<General::Sensor::Light>(static_cast<SensorNodes::LightNode *>(n)->serialize());
  };
  sensorSerializers["Mob"] = [](NodeItem *n) -> std::unique_ptr<General::Sensor::Sensor>
  {
    return std::make_unique<General::Sensor::Mob>(static_cast<SensorNodes::MobNode *>(n)->serialize());
  };
  sensorSerializers["Nav"] = [](NodeItem *n) -> std::unique_ptr<General::Sensor::Sensor>
  {
    return std::make_unique<General::Sensor::Nav>(static_cast<SensorNodes::NavNode *>(n)->serialize());
  };
  sensorSerializers["Not"] = [](NodeItem *n) -> std::unique_ptr<General::Sensor::Sensor>
  {
    return std::make_unique<General::Sensor::Not>(static_cast<SensorNodes::NotNode *>(n)->serialize());
  };
  sensorSerializers["OnGround"] = [](NodeItem *n) -> std::unique_ptr<General::Sensor::Sensor>
  {
    return std::make_unique<General::Sensor::OnGround>(static_cast<SensorNodes::OnGroundNode *>(n)->serialize());
  };
  sensorSerializers["Or"] = [](NodeItem *n) -> std::unique_ptr<General::Sensor::Sensor>
  {
    return std::make_unique<General::Sensor::Or>(static_cast<SensorNodes::OrNode *>(n)->serialize());
  };
  sensorSerializers["Path"] = [](NodeItem *n) -> std::unique_ptr<General::Sensor::Sensor>
  {
    return std::make_unique<General::Sensor::Path>(static_cast<SensorNodes::PathNode *>(n)->serialize());
  };
  sensorSerializers["Player"] = [](NodeItem *n) -> std::unique_ptr<General::Sensor::Sensor>
  {
    return std::make_unique<General::Sensor::Player>(static_cast<SensorNodes::PlayerNode *>(n)->serialize());
  };
  sensorSerializers["Random"] = [](NodeItem *n) -> std::unique_ptr<General::Sensor::Sensor>
  {
    return std::make_unique<General::Sensor::Random>(static_cast<SensorNodes::RandomNode *>(n)->serialize());
  };
  sensorSerializers["ReadPosition"] = [](NodeItem *n) -> std::unique_ptr<General::Sensor::Sensor>
  {
    return std::make_unique<General::Sensor::ReadPosition>(static_cast<SensorNodes::ReadPositionNode *>(n)->serialize());
  };
  sensorSerializers["SearchRay"] = [](NodeItem *n) -> std::unique_ptr<General::Sensor::Sensor>
  {
    return std::make_unique<General::Sensor::SearchRay>(static_cast<SensorNodes::SearchRayNode *>(n)->serialize());
  };
  sensorSerializers["Self"] = [](NodeItem *n) -> std::unique_ptr<General::Sensor::Sensor>
  {
    return std::make_unique<General::Sensor::Self>(static_cast<SensorNodes::SelfNode *>(n)->serialize());
  };
  sensorSerializers["State"] = [](NodeItem *n) -> std::unique_ptr<General::Sensor::Sensor>
  {
    return std::make_unique<General::Sensor::State>(static_cast<SensorNodes::StateNode *>(n)->serialize());
  };
  sensorSerializers["Switch"] = [](NodeItem *n) -> std::unique_ptr<General::Sensor::Sensor>
  {
    return std::make_unique<General::Sensor::Switch>(static_cast<SensorNodes::SwitchNode *>(n)->serialize());
  };
  sensorSerializers["Target"] = [](NodeItem *n) -> std::unique_ptr<General::Sensor::Sensor>
  {
    return std::make_unique<General::Sensor::Target>(static_cast<SensorNodes::TargetNode *>(n)->serialize());
  };
  sensorSerializers["Time"] = [](NodeItem *n) -> std::unique_ptr<General::Sensor::Sensor>
  {
    return std::make_unique<General::Sensor::Time>(static_cast<SensorNodes::TimeNode *>(n)->serialize());
  };
  sensorSerializers["Timer"] = [](NodeItem *n) -> std::unique_ptr<General::Sensor::Sensor>
  {
    return std::make_unique<General::Sensor::Timer>(static_cast<SensorNodes::TimerNode *>(n)->serialize());
  };
  sensorSerializers["ValueProviderWrapper"] = [](NodeItem *n) -> std::unique_ptr<General::Sensor::Sensor>
  {
    return std::make_unique<General::Sensor::ValueProviderWrapper>(static_cast<SensorNodes::ValueProviderWrapperNode *>(n)->serialize());
  };
  sensorSerializers["Weather"] = [](NodeItem *n) -> std::unique_ptr<General::Sensor::Sensor>
  {
    return std::make_unique<General::Sensor::Weather>(static_cast<SensorNodes::WeatherNode *>(n)->serialize());
  };

  actionSerializers["AddToHostileTargetMemory"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::AddToHostileTargetMemory>(static_cast<ActionNodes::AddToHostileTargetMemoryNode *>(n)->serialize());
  };
  actionSerializers["Appearance"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::Appearance>(static_cast<ActionNodes::AppearanceNode *>(n)->serialize());
  };
  actionSerializers["ApplyEntityEffect"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::ApplyEntityEffect>(static_cast<ActionNodes::ApplyEntityEffectNode *>(n)->serialize());
  };
  actionSerializers["CombatAbility"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::CombatAbility>(static_cast<ActionNodes::CombatAbilityNode *>(n)->serialize());
  };
  actionSerializers["CompleteTask"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::CompleteTask>(static_cast<ActionNodes::CompleteTaskNode *>(n)->serialize());
  };
  actionSerializers["Crouch"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::Crouch>(static_cast<ActionNodes::CrouchNode *>(n)->serialize());
  };
  actionSerializers["DelayDespawn"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::DelayDespawn>(static_cast<ActionNodes::DelayDespawnNode *>(n)->serialize());
  };
  actionSerializers["Despawn"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::Despawn>(static_cast<ActionNodes::DespawnNode *>(n)->serialize());
  };
  actionSerializers["Die"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::Die>(static_cast<ActionNodes::DieNode *>(n)->serialize());
  };
  actionSerializers["DisplayName"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::DisplayName>(static_cast<ActionNodes::DisplayNameNode *>(n)->serialize());
  };
  actionSerializers["DropItem"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::DropItem>(static_cast<ActionNodes::DropItemNode *>(n)->serialize());
  };
  actionSerializers["FlockState"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::FlockState>(static_cast<ActionNodes::FlockStateNode *>(n)->serialize());
  };
  actionSerializers["FlockTarget"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::FlockTarget>(static_cast<ActionNodes::FlockTargetNode *>(n)->serialize());
  };
  actionSerializers["IgnoreForAvoidance"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::IgnoreForAvoidance>(static_cast<ActionNodes::IgnoreForAvoidanceNode *>(n)->serialize());
  };
  actionSerializers["Inventory"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::Inventory>(static_cast<ActionNodes::InventoryNode *>(n)->serialize());
  };
  actionSerializers["JoinFlock"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::JoinFlock>(static_cast<ActionNodes::JoinFlockNode *>(n)->serialize());
  };
  actionSerializers["LeaveFlock"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::LeaveFlock>(static_cast<ActionNodes::LeaveFlockNode *>(n)->serialize());
  };
  actionSerializers["LockOnInteractionTarget"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::LockOnInteractionTarget>(static_cast<ActionNodes::LockOnInteractionTargetNode *>(n)->serialize());
  };
  actionSerializers["Log"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::Log>(static_cast<ActionNodes::LogNode *>(n)->serialize());
  };
  actionSerializers["ModelAttachment"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::ModelAttachment>(static_cast<ActionNodes::ModelAttachmentNode *>(n)->serialize());
  };
  actionSerializers["Mount"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::Mount>(static_cast<ActionNodes::MountNode *>(n)->serialize());
  };
  actionSerializers["Nothing"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::Nothing>(static_cast<ActionNodes::NothingNode *>(n)->serialize());
  };
  actionSerializers["Notify"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::Notify>(static_cast<ActionNodes::NotifyNode *>(n)->serialize());
  };
  actionSerializers["OpenBarterShop"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::OpenBarterShop>(static_cast<ActionNodes::OpenBarterShopNode *>(n)->serialize());
  };
  actionSerializers["OpenShop"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::OpenShop>(static_cast<ActionNodes::OpenShopNode *>(n)->serialize());
  };
  actionSerializers["OverrideAltitude"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::OverrideAltitude>(static_cast<ActionNodes::OverrideAltitudeNode *>(n)->serialize());
  };
  actionSerializers["OverrideAttitude"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::OverrideAttitude>(static_cast<ActionNodes::OverrideAttitudeNode *>(n)->serialize());
  };
  actionSerializers["ParentState"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::ParentState>(static_cast<ActionNodes::ParentStateNode *>(n)->serialize());
  };
  actionSerializers["PickUpItem"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::PickUpItem>(static_cast<ActionNodes::PickUpItemNode *>(n)->serialize());
  };
  actionSerializers["PlaceBlock"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::PlaceBlock>(static_cast<ActionNodes::PlaceBlockNode *>(n)->serialize());
  };
  actionSerializers["PlaySound"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::PlaySound>(static_cast<ActionNodes::PlaySoundNode *>(n)->serialize());
  };
  actionSerializers["Random"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::Random>(static_cast<ActionNodes::RandomNode *>(n)->serialize());
  };
  actionSerializers["RecomputePath"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::RecomputePath>(static_cast<ActionNodes::RecomputePathNode *>(n)->serialize());
  };
  actionSerializers["ReleaseTarget"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::ReleaseTarget>(static_cast<ActionNodes::ReleaseTargetNode *>(n)->serialize());
  };
  actionSerializers["Remove"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::Remove>(static_cast<ActionNodes::RemoveNode *>(n)->serialize());
  };
  actionSerializers["ResetBlockSensors"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::ResetBlockSensors>(static_cast<ActionNodes::ResetBlockSensorsNode *>(n)->serialize());
  };
  actionSerializers["ResetInstructions"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::ResetInstructions>(static_cast<ActionNodes::ResetInstructionsNode *>(n)->serialize());
  };
  actionSerializers["ResetPath"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::ResetPath>(static_cast<ActionNodes::ResetPathNode *>(n)->serialize());
  };
  actionSerializers["ResetSearchRays"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::ResetSearchRays>(static_cast<ActionNodes::ResetSearchRaysNode *>(n)->serialize());
  };
  actionSerializers["Role"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::Role>(static_cast<ActionNodes::RoleNode *>(n)->serialize());
  };
  actionSerializers["Sequence"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::Sequence>(static_cast<ActionNodes::SequenceNode *>(n)->serialize());
  };
  actionSerializers["SetAlarm"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::SetAlarm>(static_cast<ActionNodes::SetAlarmNode *>(n)->serialize());
  };
  actionSerializers["SetBlockToPlace"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::SetBlockToPlace>(static_cast<ActionNodes::SetBlockToPlaceNode *>(n)->serialize());
  };
  actionSerializers["SetFlag"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::SetFlag>(static_cast<ActionNodes::SetFlagNode *>(n)->serialize());
  };
  actionSerializers["SetInteractable"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::SetInteractable>(static_cast<ActionNodes::SetInteractableNode *>(n)->serialize());
  };
  actionSerializers["SetLeashPosition"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::SetLeashPosition>(static_cast<ActionNodes::SetLeashPositionNode *>(n)->serialize());
  };
  actionSerializers["SetMarkedTarget"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::SetMarkedTarget>(static_cast<ActionNodes::SetMarkedTargetNode *>(n)->serialize());
  };
  actionSerializers["SetStat"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::SetStat>(static_cast<ActionNodes::SetStatNode *>(n)->serialize());
  };
  actionSerializers["StartObjective"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::StartObjective>(static_cast<ActionNodes::StartObjectiveNode *>(n)->serialize());
  };
  actionSerializers["State"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::State>(static_cast<ActionNodes::StateNode *>(n)->serialize());
  };
  actionSerializers["StorePosition"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::StorePosition>(static_cast<ActionNodes::StorePositionNode *>(n)->serialize());
  };
  actionSerializers["Timeout"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::Timeout>(static_cast<ActionNodes::TimeoutNode *>(n)->serialize());
  };
  actionSerializers["TimerContinue"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::TimerContinue>(static_cast<ActionNodes::TimerContinueNode *>(n)->serialize());
  };
  actionSerializers["TimerModify"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::TimerModify>(static_cast<ActionNodes::TimerModifyNode *>(n)->serialize());
  };
  actionSerializers["TimerPause"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::TimerPause>(static_cast<ActionNodes::TimerPauseNode *>(n)->serialize());
  };
  actionSerializers["TimerRestart"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::TimerRestart>(static_cast<ActionNodes::TimerRestartNode *>(n)->serialize());
  };
  actionSerializers["TimerStart"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::TimerStart>(static_cast<ActionNodes::TimerStartNode *>(n)->serialize());
  };
  actionSerializers["TimerStop"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::TimerStop>(static_cast<ActionNodes::TimerStopNode *>(n)->serialize());
  };
  actionSerializers["ToggleStateEvaluator"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::ToggleStateEvaluator>(static_cast<ActionNodes::ToggleStateEvaluatorNode *>(n)->serialize());
  };
  actionSerializers["TriggerSpawnBeacon"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::TriggerSpawnBeacon>(static_cast<ActionNodes::TriggerSpawnBeaconNode *>(n)->serialize());
  };
  actionSerializers["TriggerSpawners"] = [](NodeItem *n) -> std::unique_ptr<General::Action::Action>
  {
    return std::make_unique<General::Action::TriggerSpawners>(static_cast<ActionNodes::TriggerSpawnersNode *>(n)->serialize());
  };
}

std::unique_ptr<General::Action::Action> serializeAction(SerializerValues *serializer, NodeScene *scene, NodeItem *targetNode)
{
  if (!targetNode)
    return nullptr;

  QString type = targetNode->nodeType();
  if (serializer->actionSerializers.contains(type))
  {
    std::unique_ptr<General::Action::Action> actionData = serializer->actionSerializers[type](targetNode);

    if (type == "Sequence" && actionData->type == General::Action::Type::Sequence)
    {
      General::Action::Sequence *sequenceActionData = static_cast<General::Action::Sequence *>(actionData.get());

      for (auto &link : scene->links)
      {
        if (link.startNode->parentItem() != targetNode)
          continue;

        NodeItem *targetNode2 = dynamic_cast<NodeItem *>(link.endNode->parentItem());

        QString socketName = link.startNode->getName();
        if (socketName == "Actions")
        {
          sequenceActionData->actions.actions.emplace_back(std::move(serializeAction(serializer, scene, targetNode2)));
        }
      }
    }

    if (type == "Timeout" && actionData->type == General::Action::Type::Timeout)
    {
      General::Action::Timeout *timeoutActionData = static_cast<General::Action::Timeout *>(actionData.get());

      for (auto &link : scene->links)
      {
        if (link.startNode->parentItem() != targetNode)
          continue;

        NodeItem *targetNode2 = dynamic_cast<NodeItem *>(link.endNode->parentItem());

        QString socketName = link.startNode->getName();
        if (socketName == "Action")
        {
          timeoutActionData->action = serializeAction(serializer, scene, targetNode2);
          break;
        }
      }
    }

    return actionData;
  }

  return nullptr;
}

std::unique_ptr<General::Sensor::Sensor> serializeSensor(SerializerValues *serializer, NodeScene *scene, NodeItem *targetNode)
{
  if (!targetNode)
    return nullptr;

  QString type = targetNode->nodeType();

  if (serializer->sensorSerializers.contains(type))
  {
    std::unique_ptr<General::Sensor::Sensor> sensorData = serializer->sensorSerializers[type](targetNode);

    if (type == "And")
    {
      General::Sensor::And *andSensorData = static_cast<General::Sensor::And *>(sensorData.get());

      for (auto &link : scene->links)
      {
        if (link.startNode->parentItem() != targetNode)
          continue;

        NodeItem *targetNode2 = dynamic_cast<NodeItem *>(link.endNode->parentItem());

        if (link.startNode->getName() == "Sensors")
          andSensorData->sensors.emplace_back(std::move(serializeSensor(serializer, scene, targetNode2)));
      }
    }
    else if (type == "Or")
    {
      General::Sensor::Or *orSensorData = static_cast<General::Sensor::Or *>(sensorData.get());

      for (auto &link : scene->links)
      {
        if (link.startNode->parentItem() != targetNode)
          continue;

        NodeItem *targetNode2 = dynamic_cast<NodeItem *>(link.endNode->parentItem());

        if (link.startNode->getName() == "Sensors")
          orSensorData->sensors.emplace_back(std::move(serializeSensor(serializer, scene, targetNode2)));
      }
    }
    else if (type == "BlockType")
    {
      General::Sensor::BlockType *blockTypeSensorData = static_cast<General::Sensor::BlockType *>(sensorData.get());

      for (auto &link : scene->links)
      {
        if (link.startNode->parentItem() != targetNode)
          continue;

        NodeItem *targetNode2 = dynamic_cast<NodeItem *>(link.endNode->parentItem());

        if (link.startNode->getName() == "Sensor")
        {
          blockTypeSensorData->sensor = serializeSensor(serializer, scene, targetNode2);
          break;
        }
      }
    }
    else if (type == "Not")
    {
      General::Sensor::Not *notSensorData = static_cast<General::Sensor::Not *>(sensorData.get());

      for (auto &link : scene->links)
      {
        if (link.startNode->parentItem() != targetNode)
          continue;

        NodeItem *targetNode2 = dynamic_cast<NodeItem *>(link.endNode->parentItem());

        if (link.startNode->getName() == "Sensor")
        {
          notSensorData->sensor = serializeSensor(serializer, scene, targetNode2);
          break;
        }
      }
    }
    else if (type == "ValueProviderWrapper")
    {
      General::Sensor::ValueProviderWrapper *valueProviderWrapperSensorData = static_cast<General::Sensor::ValueProviderWrapper *>(sensorData.get());

      for (auto &link : scene->links)
      {
        if (link.startNode->parentItem() != targetNode)
          continue;

        NodeItem *targetNode2 = dynamic_cast<NodeItem *>(link.endNode->parentItem());

        if (link.startNode->getName() == "Sensor")
        {
          valueProviderWrapperSensorData->sensor = serializeSensor(serializer, scene, targetNode2);
          break;
        }
      }
    }

    return sensorData;
  }

  return nullptr;
}

General::Instruction serializeInstruction(SerializerValues *serializer, NodeScene *scene, InstructionNode *instructionNode)
{
  General::Instruction instrData = instructionNode->serialize();

  for (auto &link : scene->links)
  {
    if (link.startNode->parentItem() != instructionNode)
      continue;

    NodeItem *targetNode = dynamic_cast<NodeItem *>(link.endNode->parentItem());
    if (!targetNode)
      continue;

    QString socketName = link.startNode->getName();
    if (socketName == "Instructions")
    {
      auto instrNode = dynamic_cast<InstructionNode *>(targetNode);
      if (!instrNode)
        continue;

      instrData.instructions.emplace_back(std::move(serializeInstruction(serializer, scene, instrNode)));
    }

    if (socketName == "Sensor")
    {
      instrData.sensor = serializeSensor(serializer, scene, targetNode);
    }
    else if (socketName == "Body Motion")
    {
      // TODO: Add this
    }
    else if (socketName == "Head Motion")
    {
      // TODO: Add this
    }
    else if (socketName == "Actions")
    {
      instrData.actions.emplace_back(std::move(serializeAction(serializer, scene, targetNode)));
    }
  }

  return instrData;
}

std::vector<General::Instruction> serializeInstructions(SerializerValues *serializer, NodeScene *scene, NodeItem *startNode)
{
  std::vector<General::Instruction> result;

  if (!startNode || startNode == nullptr)
    return result;

  auto rootNode = dynamic_cast<RootNode *>(startNode);
  if (!rootNode)
    return result;

  for (auto &rootLink : scene->links)
  {
    if (rootLink.startNode->parentItem() != rootNode)
      continue;

    auto instrNode = dynamic_cast<InstructionNode *>(rootLink.endNode->parentItem());
    if (!instrNode)
      continue;

    result.push_back(std::move(serializeInstruction(serializer, scene, instrNode)));
  }

  return result;
}