#pragma once
#include <vector>
#include "nodes.hpp"
#include "types.hpp"

struct SerializerValues
{
  using ActionSerializeFn = std::function<General::Action::Action(NodeItem *)>;
  QMap<QString, ActionSerializeFn> actionSerializers;
  using SensorSerializeFn = std::function<General::Sensor::Sensor(NodeItem *)>;
  QMap<QString, SensorSerializeFn> sensorSerializers;

  SerializerValues()
  {
    sensorSerializers["AdjustPosition"] = [](NodeItem *n) -> General::Sensor::Sensor
    {
      return static_cast<SensorNodes::AdjustPositionNode *>(n)->serialize();
    };
    sensorSerializers["Age"] = [](NodeItem *n) -> General::Sensor::Sensor
    {
      return static_cast<SensorNodes::AgeNode *>(n)->serialize();
    };
    sensorSerializers["Alarm"] = [](NodeItem *n) -> General::Sensor::Sensor
    {
      return static_cast<SensorNodes::AlarmNode *>(n)->serialize();
    };
    sensorSerializers["And"] = [](NodeItem *n) -> General::Sensor::Sensor
    {
      return static_cast<SensorNodes::AndNode *>(n)->serialize();
    };
    sensorSerializers["Animation"] = [](NodeItem *n) -> General::Sensor::Sensor
    {
      return static_cast<SensorNodes::AnimationNode *>(n)->serialize();
    };
    sensorSerializers["Any"] = [](NodeItem *n) -> General::Sensor::Sensor
    {
      return static_cast<SensorNodes::AnyNode *>(n)->serialize();
    };
    sensorSerializers["Beacon"] = [](NodeItem *n) -> General::Sensor::Sensor
    {
      return static_cast<SensorNodes::BeaconNode *>(n)->serialize();
    };
    sensorSerializers["BlockChange"] = [](NodeItem *n) -> General::Sensor::Sensor
    {
      return static_cast<SensorNodes::BlockChangeNode *>(n)->serialize();
    };
    sensorSerializers["BlockType"] = [](NodeItem *n) -> General::Sensor::Sensor
    {
      return static_cast<SensorNodes::BlockTypeNode *>(n)->serialize();
    };
    sensorSerializers["CanInteract"] = [](NodeItem *n) -> General::Sensor::Sensor
    {
      return static_cast<SensorNodes::CanInteractNode *>(n)->serialize();
    };
    sensorSerializers["CanPlaceBlock"] = [](NodeItem *n) -> General::Sensor::Sensor
    {
      return static_cast<SensorNodes::CanPlaceBlockNode *>(n)->serialize();
    };
    sensorSerializers["CombatActionEvaluator"] = [](NodeItem *n) -> General::Sensor::Sensor
    {
      return static_cast<SensorNodes::CombatActionEvaluatorNode *>(n)->serialize();
    };
    sensorSerializers["Count"] = [](NodeItem *n) -> General::Sensor::Sensor
    {
      return static_cast<SensorNodes::CountNode *>(n)->serialize();
    };
    sensorSerializers["Damage"] = [](NodeItem *n) -> General::Sensor::Sensor
    {
      return static_cast<SensorNodes::DamageNode *>(n)->serialize();
    };
    sensorSerializers["DroppedItem"] = [](NodeItem *n) -> General::Sensor::Sensor
    {
      return static_cast<SensorNodes::DroppedItemNode *>(n)->serialize();
    };
    sensorSerializers["EntityEvent"] = [](NodeItem *n) -> General::Sensor::Sensor
    {
      return static_cast<SensorNodes::EntityEventNode *>(n)->serialize();
    };
    sensorSerializers["Flag"] = [](NodeItem *n) -> General::Sensor::Sensor
    {
      return static_cast<SensorNodes::FlagNode *>(n)->serialize();
    };
    sensorSerializers["FlockCombatDamage"] = [](NodeItem *n) -> General::Sensor::Sensor
    {
      return static_cast<SensorNodes::FlockCombatDamageNode *>(n)->serialize();
    };
    sensorSerializers["FlockLeader"] = [](NodeItem *n) -> General::Sensor::Sensor
    {
      return static_cast<SensorNodes::FlockLeaderNode *>(n)->serialize();
    };
    sensorSerializers["HasHostileTargetMemory"] = [](NodeItem *n) -> General::Sensor::Sensor
    {
      return static_cast<SensorNodes::HasHostileTargetMemoryNode *>(n)->serialize();
    };
    sensorSerializers["HasInteracted"] = [](NodeItem *n) -> General::Sensor::Sensor
    {
      return static_cast<SensorNodes::HasInteractedNode *>(n)->serialize();
    };
    sensorSerializers["HasTask"] = [](NodeItem *n) -> General::Sensor::Sensor
    {
      return static_cast<SensorNodes::HasTaskNode *>(n)->serialize();
    };
    sensorSerializers["InAir"] = [](NodeItem *n) -> General::Sensor::Sensor
    {
      return static_cast<SensorNodes::InAirNode *>(n)->serialize();
    };
    sensorSerializers["InWater"] = [](NodeItem *n) -> General::Sensor::Sensor
    {
      return static_cast<SensorNodes::InWaterNode *>(n)->serialize();
    };
    sensorSerializers["InflictedDamage"] = [](NodeItem *n) -> General::Sensor::Sensor
    {
      return static_cast<SensorNodes::InflictedDamageNode *>(n)->serialize();
    };
    sensorSerializers["InteractionContext"] = [](NodeItem *n) -> General::Sensor::Sensor
    {
      return static_cast<SensorNodes::InteractionContextNode *>(n)->serialize();
    };
    sensorSerializers["IsBackingAway"] = [](NodeItem *n) -> General::Sensor::Sensor
    {
      return static_cast<SensorNodes::IsBackingAwayNode *>(n)->serialize();
    };
    sensorSerializers["IsBusy"] = [](NodeItem *n) -> General::Sensor::Sensor
    {
      return static_cast<SensorNodes::IsBusyNode *>(n)->serialize();
    };
    sensorSerializers["Kill"] = [](NodeItem *n) -> General::Sensor::Sensor
    {
      return static_cast<SensorNodes::KillNode *>(n)->serialize();
    };
    sensorSerializers["Leash"] = [](NodeItem *n) -> General::Sensor::Sensor
    {
      return static_cast<SensorNodes::LeashNode *>(n)->serialize();
    };
    sensorSerializers["Light"] = [](NodeItem *n) -> General::Sensor::Sensor
    {
      return static_cast<SensorNodes::LightNode *>(n)->serialize();
    };
    sensorSerializers["Mob"] = [](NodeItem *n) -> General::Sensor::Sensor
    {
      return static_cast<SensorNodes::MobNode *>(n)->serialize();
    };
    sensorSerializers["Nav"] = [](NodeItem *n) -> General::Sensor::Sensor
    {
      return static_cast<SensorNodes::NavNode *>(n)->serialize();
    };
    sensorSerializers["Not"] = [](NodeItem *n) -> General::Sensor::Sensor
    {
      return static_cast<SensorNodes::NotNode *>(n)->serialize();
    };
    sensorSerializers["OnGround"] = [](NodeItem *n) -> General::Sensor::Sensor
    {
      return static_cast<SensorNodes::OnGroundNode *>(n)->serialize();
    };
    sensorSerializers["Or"] = [](NodeItem *n) -> General::Sensor::Sensor
    {
      return static_cast<SensorNodes::OrNode *>(n)->serialize();
    };
    sensorSerializers["Path"] = [](NodeItem *n) -> General::Sensor::Sensor
    {
      return static_cast<SensorNodes::PathNode *>(n)->serialize();
    };
    sensorSerializers["Player"] = [](NodeItem *n) -> General::Sensor::Sensor
    {
      return static_cast<SensorNodes::PlayerNode *>(n)->serialize();
    };
    sensorSerializers["Random"] = [](NodeItem *n) -> General::Sensor::Sensor
    {
      return static_cast<SensorNodes::RandomNode *>(n)->serialize();
    };
    sensorSerializers["ReadPosition"] = [](NodeItem *n) -> General::Sensor::Sensor
    {
      return static_cast<SensorNodes::ReadPositionNode *>(n)->serialize();
    };
    sensorSerializers["SearchRay"] = [](NodeItem *n) -> General::Sensor::Sensor
    {
      return static_cast<SensorNodes::SearchRayNode *>(n)->serialize();
    };
    sensorSerializers["Self"] = [](NodeItem *n) -> General::Sensor::Sensor
    {
      return static_cast<SensorNodes::SelfNode *>(n)->serialize();
    };
    sensorSerializers["State"] = [](NodeItem *n) -> General::Sensor::Sensor
    {
      return static_cast<SensorNodes::StateNode *>(n)->serialize();
    };
    sensorSerializers["Switch"] = [](NodeItem *n) -> General::Sensor::Sensor
    {
      return static_cast<SensorNodes::SwitchNode *>(n)->serialize();
    };
    sensorSerializers["Target"] = [](NodeItem *n) -> General::Sensor::Sensor
    {
      return static_cast<SensorNodes::TargetNode *>(n)->serialize();
    };
    sensorSerializers["Time"] = [](NodeItem *n) -> General::Sensor::Sensor
    {
      return static_cast<SensorNodes::TimeNode *>(n)->serialize();
    };
    sensorSerializers["Timer"] = [](NodeItem *n) -> General::Sensor::Sensor
    {
      return static_cast<SensorNodes::TimerNode *>(n)->serialize();
    };
    sensorSerializers["ValueProviderWrapper"] = [](NodeItem *n) -> General::Sensor::Sensor
    {
      return static_cast<SensorNodes::ValueProviderWrapperNode *>(n)->serialize();
    };
    sensorSerializers["Weather"] = [](NodeItem *n) -> General::Sensor::Sensor
    {
      return static_cast<SensorNodes::WeatherNode *>(n)->serialize();
    };
    actionSerializers["AddToHostileTargetMemory"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::AddToHostileTargetMemoryNode *>(n)->serialize();
    };
    actionSerializers["Appearance"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::AppearanceNode *>(n)->serialize();
    };
    actionSerializers["ApplyEntityEffect"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::ApplyEntityEffectNode *>(n)->serialize();
    };
    actionSerializers["CombatAbility"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::CombatAbilityNode *>(n)->serialize();
    };
    actionSerializers["CompleteTask"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::CompleteTaskNode *>(n)->serialize();
    };
    actionSerializers["Crouch"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::CrouchNode *>(n)->serialize();
    };
    actionSerializers["DelayDespawn"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::DelayDespawnNode *>(n)->serialize();
    };
    actionSerializers["Despawn"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::DespawnNode *>(n)->serialize();
    };
    actionSerializers["Die"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::DieNode *>(n)->serialize();
    };
    actionSerializers["DisplayName"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::DisplayNameNode *>(n)->serialize();
    };
    actionSerializers["DropItem"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::DropItemNode *>(n)->serialize();
    };
    actionSerializers["FlockState"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::FlockStateNode *>(n)->serialize();
    };
    actionSerializers["FlockTarget"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::FlockTargetNode *>(n)->serialize();
    };
    actionSerializers["IgnoreForAvoidance"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::IgnoreForAvoidanceNode *>(n)->serialize();
    };
    actionSerializers["Inventory"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::InventoryNode *>(n)->serialize();
    };
    actionSerializers["JoinFlock"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::JoinFlockNode *>(n)->serialize();
    };
    actionSerializers["LeaveFlock"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::LeaveFlockNode *>(n)->serialize();
    };
    actionSerializers["LockOnInteractionTarget"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::LockOnInteractionTargetNode *>(n)->serialize();
    };
    actionSerializers["Log"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::LogNode *>(n)->serialize();
    };
    actionSerializers["ModelAttachment"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::ModelAttachmentNode *>(n)->serialize();
    };
    actionSerializers["Mount"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::MountNode *>(n)->serialize();
    };
    actionSerializers["Nothing"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::NothingNode *>(n)->serialize();
    };
    actionSerializers["Notify"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::NotifyNode *>(n)->serialize();
    };
    actionSerializers["OpenBarterShop"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::OpenBarterShopNode *>(n)->serialize();
    };
    actionSerializers["OpenShop"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::OpenShopNode *>(n)->serialize();
    };
    actionSerializers["OverrideAltitude"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::OverrideAltitudeNode *>(n)->serialize();
    };
    actionSerializers["OverrideAttitude"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::OverrideAttitudeNode *>(n)->serialize();
    };
    actionSerializers["ParentState"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::ParentStateNode *>(n)->serialize();
    };
    actionSerializers["PickUpItem"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::PickUpItemNode *>(n)->serialize();
    };
    actionSerializers["PlaceBlock"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::PlaceBlockNode *>(n)->serialize();
    };
    actionSerializers["PlaySound"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::PlaySoundNode *>(n)->serialize();
    };
    actionSerializers["Random"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::RandomNode *>(n)->serialize();
    };
    actionSerializers["RecomputePath"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::RecomputePathNode *>(n)->serialize();
    };
    actionSerializers["ReleaseTarget"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::ReleaseTargetNode *>(n)->serialize();
    };
    actionSerializers["Remove"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::RemoveNode *>(n)->serialize();
    };
    actionSerializers["ResetBlockSensors"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::ResetBlockSensorsNode *>(n)->serialize();
    };
    actionSerializers["ResetInstructions"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::ResetInstructionsNode *>(n)->serialize();
    };
    actionSerializers["ResetPath"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::ResetPathNode *>(n)->serialize();
    };
    actionSerializers["ResetSearchRays"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::ResetSearchRaysNode *>(n)->serialize();
    };
    actionSerializers["Role"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::RoleNode *>(n)->serialize();
    };
    actionSerializers["Sequence"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::SequenceNode *>(n)->serialize();
    };
    actionSerializers["SetAlarm"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::SetAlarmNode *>(n)->serialize();
    };
    actionSerializers["SetBlockToPlace"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::SetBlockToPlaceNode *>(n)->serialize();
    };
    actionSerializers["SetFlag"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::SetFlagNode *>(n)->serialize();
    };
    actionSerializers["SetInteractable"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::SetInteractableNode *>(n)->serialize();
    };
    actionSerializers["SetLeashPosition"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::SetLeashPositionNode *>(n)->serialize();
    };
    actionSerializers["SetMarkedTarget"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::SetMarkedTargetNode *>(n)->serialize();
    };
    actionSerializers["SetStat"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::SetStatNode *>(n)->serialize();
    };
    actionSerializers["StartObjective"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::StartObjectiveNode *>(n)->serialize();
    };
    actionSerializers["State"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::StateNode *>(n)->serialize();
    };
    actionSerializers["StorePosition"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::StorePositionNode *>(n)->serialize();
    };
    actionSerializers["Timeout"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::TimeoutNode *>(n)->serialize();
    };
    actionSerializers["TimerContinue"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::TimerContinueNode *>(n)->serialize();
    };
    actionSerializers["TimerModify"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::TimerModifyNode *>(n)->serialize();
    };
    actionSerializers["TimerPause"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::TimerPauseNode *>(n)->serialize();
    };
    actionSerializers["TimerRestart"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::TimerRestartNode *>(n)->serialize();
    };
    actionSerializers["TimerStart"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::TimerStartNode *>(n)->serialize();
    };
    actionSerializers["TimerStop"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::TimerStopNode *>(n)->serialize();
    };
    actionSerializers["ToggleStateEvaluator"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::ToggleStateEvaluatorNode *>(n)->serialize();
    };
    actionSerializers["TriggerSpawnBeacon"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::TriggerSpawnBeaconNode *>(n)->serialize();
    };
    actionSerializers["TriggerSpawners"] = [](NodeItem *n) -> General::Action::Action
    {
      return static_cast<ActionNodes::TriggerSpawnersNode *>(n)->serialize();
    };
  }
};

General::Action::Action serializeAction(SerializerValues *serializer, NodeScene *scene, NodeItem *targetNode)
{
  if (!targetNode)
    return;

  QString type = targetNode->nodeType();
  if (serializer->actionSerializers.contains(type))
  {
    return serializer->actionSerializers[type](targetNode);
  }
}

General::Sensor::Sensor serializeSensor(SerializerValues *serializer, NodeScene *scene, NodeItem *targetNode)
{
  if (!targetNode)
    return;

  QString type = targetNode->nodeType();
  if (serializer->sensorSerializers.contains(type))
  {
    return serializer->sensorSerializers[type](targetNode);
  }
}

std::vector<General::Instruction> serializeInstructions(SerializerValues *serializer, NodeScene *scene, NodeItem *startNode)
{
  std::vector<General::Instruction> result;

  if (!startNode)
    return result;

  auto instrNode = dynamic_cast<InstructionNode *>(startNode);
  if (!instrNode)
    return result;

  General::Instruction instrData = instrNode->serialize();

  for (auto &link : scene->links)
  {
    if (link.startNode->parentItem() != startNode)
      continue;

    NodeItem *targetNode = dynamic_cast<NodeItem *>(link.endNode->parentItem());
    if (!targetNode)
      continue;

    auto childInstructions = serializeInstructions(serializer, scene, targetNode);
    instrData.instructions.insert(instrData.instructions.end(),
                                  childInstructions.begin(),
                                  childInstructions.end());

    QString socketName = link.startNode->getName();
    if (socketName == "Sensor")
    {
      instrData.sensor = serializeSensor(serializer, scene, targetNode);
    }
    else if (socketName == "Body Motion")
    {
      // auto bodyNode = dynamic_cast<BodyMotionNodes::BodyMotionNode *>(targetNode);
      // if (bodyNode)
      //   instrData.bodyMotion = bodyNode->serialize();
    }
    else if (socketName == "Head Motion")
    {
      // auto headNode = dynamic_cast<HeadMotionNodes::HeadMotionNode *>(targetNode);
      // if (headNode)
      //   instrData.headMotion = headNode->serialize();
    }
    else if (socketName == "Actions")
    {
      instrData.actions.emplace_back(serializeAction(serializer, scene, targetNode));
    }
  }

  result.push_back(instrData);
  return result;
}