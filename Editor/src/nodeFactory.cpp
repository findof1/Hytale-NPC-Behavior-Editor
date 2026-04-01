#include "nodeWidgets.hpp"
#include "nodes.hpp"

void NodeScene::initNodeFactory()
{
  nodeFactory["Instruction"] = [](NodeScene *s)
  {
    return std::make_shared<InstructionNode>(s);
  };

  nodeFactory["Comment"] = [](NodeScene *s)
  {
    return std::make_shared<CommentNode>(s);
  };

  nodeFactory["Sensors/Adjust Position"] = [](NodeScene *s)
  {
    return std::make_shared<SensorNodes::AdjustPositionNode>(s);
  };

  nodeFactory["Sensors/Age"] = [](NodeScene *s)
  {
    return std::make_shared<SensorNodes::AgeNode>(s);
  };

  nodeFactory["Sensors/Alarm"] = [](NodeScene *s)
  {
    return std::make_shared<SensorNodes::AlarmNode>(s);
  };

  nodeFactory["Sensors/And"] = [](NodeScene *s)
  {
    return std::make_shared<SensorNodes::AndNode>(s);
  };

  nodeFactory["Sensors/Animation"] = [](NodeScene *s)
  {
    return std::make_shared<SensorNodes::AnimationNode>(s);
  };

  nodeFactory["Sensors/Any"] = [](NodeScene *s)
  {
    return std::make_shared<SensorNodes::AnyNode>(s);
  };

  nodeFactory["Sensors/Beacon"] = [](NodeScene *s)
  {
    return std::make_shared<SensorNodes::BeaconNode>(s);
  };

  nodeFactory["Sensors/Block Change"] = [](NodeScene *s)
  {
    return std::make_shared<SensorNodes::BlockChangeNode>(s);
  };

  nodeFactory["Sensors/Block Type"] = [](NodeScene *s)
  {
    return std::make_shared<SensorNodes::BlockTypeNode>(s);
  };

  nodeFactory["Sensors/Can Interact"] = [](NodeScene *s)
  {
    return std::make_shared<SensorNodes::CanInteractNode>(s);
  };

  nodeFactory["Sensors/Can Place Block"] = [](NodeScene *s)
  {
    return std::make_shared<SensorNodes::CanPlaceBlockNode>(s);
  };

  nodeFactory["Sensors/Combat Action Evaluator"] = [](NodeScene *s)
  {
    return std::make_shared<SensorNodes::CombatActionEvaluatorNode>(s);
  };

  nodeFactory["Sensors/Count"] = [](NodeScene *s)
  {
    return std::make_shared<SensorNodes::CountNode>(s);
  };

  nodeFactory["Sensors/Damage"] = [](NodeScene *s)
  {
    return std::make_shared<SensorNodes::DamageNode>(s);
  };

  nodeFactory["Sensors/Dropped Item"] = [](NodeScene *s)
  {
    return std::make_shared<SensorNodes::DroppedItemNode>(s);
  };

  nodeFactory["Sensors/Entity Event"] = [](NodeScene *s)
  {
    return std::make_shared<SensorNodes::EntityEventNode>(s);
  };

  nodeFactory["Sensors/Flag"] = [](NodeScene *s)
  {
    return std::make_shared<SensorNodes::FlagNode>(s);
  };

  nodeFactory["Sensors/Flock Combat Damage"] = [](NodeScene *s)
  {
    return std::make_shared<SensorNodes::FlockCombatDamageNode>(s);
  };

  nodeFactory["Sensors/Flock Leader"] = [](NodeScene *s)
  {
    return std::make_shared<SensorNodes::FlockLeaderNode>(s);
  };

  nodeFactory["Sensors/Has Hostile Target Memory"] = [](NodeScene *s)
  {
    return std::make_shared<SensorNodes::HasHostileTargetMemoryNode>(s);
  };

  nodeFactory["Sensors/Has Interacted"] = [](NodeScene *s)
  {
    return std::make_shared<SensorNodes::HasInteractedNode>(s);
  };

  nodeFactory["Sensors/Has Task"] = [](NodeScene *s)
  {
    return std::make_shared<SensorNodes::HasTaskNode>(s);
  };

  nodeFactory["Sensors/In Air"] = [](NodeScene *s)
  {
    return std::make_shared<SensorNodes::InAirNode>(s);
  };

  nodeFactory["Sensors/In Water"] = [](NodeScene *s)
  {
    return std::make_shared<SensorNodes::InWaterNode>(s);
  };

  nodeFactory["Sensors/Inflicted Damage"] = [](NodeScene *s)
  {
    return std::make_shared<SensorNodes::InflictedDamageNode>(s);
  };

  nodeFactory["Sensors/Interaction Context"] = [](NodeScene *s)
  {
    return std::make_shared<SensorNodes::InteractionContextNode>(s);
  };

  nodeFactory["Sensors/Is Backing Away"] = [](NodeScene *s)
  {
    return std::make_shared<SensorNodes::IsBackingAwayNode>(s);
  };

  nodeFactory["Sensors/Is Busy"] = [](NodeScene *s)
  {
    return std::make_shared<SensorNodes::IsBusyNode>(s);
  };

  nodeFactory["Sensors/Kill"] = [](NodeScene *s)
  {
    return std::make_shared<SensorNodes::KillNode>(s);
  };

  nodeFactory["Sensors/Leash"] = [](NodeScene *s)
  {
    return std::make_shared<SensorNodes::LeashNode>(s);
  };

  nodeFactory["Sensors/Light"] = [](NodeScene *s)
  {
    return std::make_shared<SensorNodes::LightNode>(s);
  };

  nodeFactory["Sensors/Mob"] = [](NodeScene *s)
  {
    return std::make_shared<SensorNodes::MobNode>(s);
  };

  nodeFactory["Sensors/Nav"] = [](NodeScene *s)
  {
    return std::make_shared<SensorNodes::NavNode>(s);
  };

  nodeFactory["Sensors/Not"] = [](NodeScene *s)
  {
    return std::make_shared<SensorNodes::NotNode>(s);
  };

  nodeFactory["Sensors/On Ground"] = [](NodeScene *s)
  {
    return std::make_shared<SensorNodes::OnGroundNode>(s);
  };

  nodeFactory["Sensors/Or"] = [](NodeScene *s)
  {
    return std::make_shared<SensorNodes::OrNode>(s);
  };

  nodeFactory["Sensors/Path"] = [](NodeScene *s)
  {
    return std::make_shared<SensorNodes::PathNode>(s);
  };

  nodeFactory["Sensors/Player"] = [](NodeScene *s)
  {
    return std::make_shared<SensorNodes::PlayerNode>(s);
  };

  nodeFactory["Sensors/Random"] = [](NodeScene *s)
  {
    return std::make_shared<SensorNodes::RandomNode>(s);
  };

  nodeFactory["Sensors/Read Position"] = [](NodeScene *s)
  {
    return std::make_shared<SensorNodes::ReadPositionNode>(s);
  };

  nodeFactory["Sensors/Search Ray"] = [](NodeScene *s)
  {
    return std::make_shared<SensorNodes::SearchRayNode>(s);
  };

  nodeFactory["Sensors/Self"] = [](NodeScene *s)
  {
    return std::make_shared<SensorNodes::SelfNode>(s);
  };

  nodeFactory["Sensors/State"] = [](NodeScene *s)
  {
    return std::make_shared<SensorNodes::StateNode>(s);
  };

  nodeFactory["Sensors/Switch"] = [](NodeScene *s)
  {
    return std::make_shared<SensorNodes::SwitchNode>(s);
  };

  nodeFactory["Sensors/Target"] = [](NodeScene *s)
  {
    return std::make_shared<SensorNodes::TargetNode>(s);
  };

  nodeFactory["Sensors/Time"] = [](NodeScene *s)
  {
    return std::make_shared<SensorNodes::TimeNode>(s);
  };

  nodeFactory["Sensors/Timer"] = [](NodeScene *s)
  {
    return std::make_shared<SensorNodes::TimerNode>(s);
  };

  nodeFactory["Sensors/Value Provider Wrapper"] = [](NodeScene *s)
  {
    return std::make_shared<SensorNodes::ValueProviderWrapperNode>(s);
  };

  nodeFactory["Sensors/Weather"] = [](NodeScene *s)
  {
    return std::make_shared<SensorNodes::WeatherNode>(s);
  };

  nodeFactory["Actions/Add To Hostile Target Memory"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::AddToHostileTargetMemoryNode>(s);
  };

  nodeFactory["Actions/Appearance"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::AppearanceNode>(s);
  };

  nodeFactory["Actions/Apply Entity Effect"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::ApplyEntityEffectNode>(s);
  };

  nodeFactory["Actions/Combat Ability"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::CombatAbilityNode>(s);
  };

  nodeFactory["Actions/Complete Task"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::CompleteTaskNode>(s);
  };

  nodeFactory["Actions/Crouch"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::CrouchNode>(s);
  };

  nodeFactory["Actions/Delay Despawn"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::DelayDespawnNode>(s);
  };

  nodeFactory["Actions/Despawn"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::DespawnNode>(s);
  };

  nodeFactory["Actions/Die"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::DieNode>(s);
  };

  nodeFactory["Actions/Display Name"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::DisplayNameNode>(s);
  };

  nodeFactory["Actions/Drop Item"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::DropItemNode>(s);
  };

  nodeFactory["Actions/Flock State"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::FlockStateNode>(s);
  };

  nodeFactory["Actions/Flock Target"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::FlockTargetNode>(s);
  };

  nodeFactory["Actions/Ignore For Avoidance"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::IgnoreForAvoidanceNode>(s);
  };

  nodeFactory["Actions/Inventory"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::InventoryNode>(s);
  };

  nodeFactory["Actions/Join Flock"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::JoinFlockNode>(s);
  };

  nodeFactory["Actions/Leave Flock"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::LeaveFlockNode>(s);
  };

  nodeFactory["Actions/Lock On Interaction Target"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::LockOnInteractionTargetNode>(s);
  };

  nodeFactory["Actions/Log"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::LogNode>(s);
  };

  nodeFactory["Actions/Model Attachment"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::ModelAttachmentNode>(s);
  };

  nodeFactory["Actions/Mount"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::MountNode>(s);
  };

  nodeFactory["Actions/Nothing"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::NothingNode>(s);
  };

  nodeFactory["Actions/Notify"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::NotifyNode>(s);
  };

  nodeFactory["Actions/Open Barter Shop"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::OpenBarterShopNode>(s);
  };

  nodeFactory["Actions/Open Shop"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::OpenShopNode>(s);
  };

  nodeFactory["Actions/Override Altitude"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::OverrideAltitudeNode>(s);
  };

  nodeFactory["Actions/Override Attitude"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::OverrideAttitudeNode>(s);
  };

  nodeFactory["Actions/Parent State"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::ParentStateNode>(s);
  };

  nodeFactory["Actions/Pick Up Item"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::PickUpItemNode>(s);
  };

  nodeFactory["Actions/Place Block"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::PlaceBlockNode>(s);
  };

  nodeFactory["Actions/Play Sound"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::PlaySoundNode>(s);
  };

  nodeFactory["Actions/Random"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::RandomNode>(s);
  };

  nodeFactory["Actions/Recompute Path"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::RecomputePathNode>(s);
  };

  nodeFactory["Actions/Release Target"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::ReleaseTargetNode>(s);
  };

  nodeFactory["Actions/Remove"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::RemoveNode>(s);
  };

  nodeFactory["Actions/Reset Block Sensors"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::ResetBlockSensorsNode>(s);
  };

  nodeFactory["Actions/Reset Instructions"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::ResetInstructionsNode>(s);
  };

  nodeFactory["Actions/Reset Path"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::ResetPathNode>(s);
  };

  nodeFactory["Actions/Reset Search Rays"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::ResetSearchRaysNode>(s);
  };

  nodeFactory["Actions/Role"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::RoleNode>(s);
  };

  nodeFactory["Actions/Sequence"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::SequenceNode>(s);
  };

  nodeFactory["Actions/Set Alarm"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::SetAlarmNode>(s);
  };

  nodeFactory["Actions/Set Block To Place"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::SetBlockToPlaceNode>(s);
  };

  nodeFactory["Actions/Set Flag"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::SetFlagNode>(s);
  };

  nodeFactory["Actions/Set Interactable"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::SetInteractableNode>(s);
  };

  nodeFactory["Actions/Set Leash Position"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::SetLeashPositionNode>(s);
  };

  nodeFactory["Actions/Set Marked Target"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::SetMarkedTargetNode>(s);
  };

  nodeFactory["Actions/Set Stat"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::SetStatNode>(s);
  };

  nodeFactory["Actions/Start Objective"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::StartObjectiveNode>(s);
  };

  nodeFactory["Actions/State"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::StateNode>(s);
  };

  nodeFactory["Actions/Store Position"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::StorePositionNode>(s);
  };

  nodeFactory["Actions/Timeout"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::TimeoutNode>(s);
  };

  nodeFactory["Actions/Timer Continue"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::TimerContinueNode>(s);
  };

  nodeFactory["Actions/Timer Modify"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::TimerModifyNode>(s);
  };

  nodeFactory["Actions/Timer Pause"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::TimerPauseNode>(s);
  };

  nodeFactory["Actions/Timer Restart"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::TimerRestartNode>(s);
  };

  nodeFactory["Actions/Timer Start"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::TimerStartNode>(s);
  };

  nodeFactory["Actions/Timer Stop"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::TimerStopNode>(s);
  };

  nodeFactory["Actions/Toggle State Evaluator"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::ToggleStateEvaluatorNode>(s);
  };

  nodeFactory["Actions/Trigger Spawn Beacon"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::TriggerSpawnBeaconNode>(s);
  };

  nodeFactory["Actions/Trigger Spawners"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::TriggerSpawnersNode>(s);
  };

  nodeFactory["Actions/Weighted Action"] = [](NodeScene *s)
  {
    return std::make_shared<ActionNodes::WeightedActionNode>(s);
  };
}