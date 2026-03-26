#pragma once
#include <nlohmann/json.hpp>
#include "types.hpp"

namespace General
{
  NLOHMANN_JSON_SERIALIZE_ENUM(AttitudeFlag, {
                                                 {AttitudeFlag::Hostile, "Hostile"},
                                                 {AttitudeFlag::Revered, "Revered"},
                                                 {AttitudeFlag::Friendly, "Friendly"},
                                                 {AttitudeFlag::Ignore, "Ignore"},
                                                 {AttitudeFlag::Neutral, "Neutral"},
                                             })

  NLOHMANN_JSON_SERIALIZE_ENUM(DirectionFlag, {
                                                  {DirectionFlag::Left, "Left"},
                                                  {DirectionFlag::Backward, "Backward"},
                                                  {DirectionFlag::Right, "Right"},
                                                  {DirectionFlag::Forward, "Forward"},
                                              })

  NLOHMANN_JSON_SERIALIZE_ENUM(SearchTypeFlag, {
                                                   {SearchTypeFlag::NpcOnly, "NpcOnly"},
                                                   {SearchTypeFlag::PlayerFirst, "PlayerFirst"},
                                                   {SearchTypeFlag::PlayerOnly, "PlayerOnly"},
                                                   {SearchTypeFlag::NpcFirst, "NpcFirst"},
                                               })

  NLOHMANN_JSON_SERIALIZE_ENUM(ValueTypeFlag, {
                                                  {ValueTypeFlag::String, "String"},
                                                  {ValueTypeFlag::Double, "Double"},
                                                  {ValueTypeFlag::Int, "Int"},
                                              })

  void to_json(nlohmann::json &j, const MotionController &v);
  void from_json(const nlohmann::json &j, MotionController &v);

  void to_json(nlohmann::json &j, const ValueToParameterMapping &v);
  void from_json(const nlohmann::json &j, ValueToParameterMapping &v);

  namespace ISensorEntityPrioritiser
  {
    void to_json(nlohmann::json &j, const ISensorEntityPrioritiser &v);
    void from_json(const nlohmann::json &j, ISensorEntityPrioritiser &v);

    void to_json(nlohmann::json &j, const Attitude &v);
    void from_json(const nlohmann::json &j, Attitude &v);
  }

  namespace ISensorEntityCollector
  {
    void to_json(nlohmann::json &j, const ISensorEntityCollector &v);
    void from_json(const nlohmann::json &j, ISensorEntityCollector &v);

    void to_json(nlohmann::json &j, const CombatTargets &v);
    void from_json(const nlohmann::json &j, CombatTargets &v);
  }

  namespace IEntityFilter
  {
    NLOHMANN_JSON_SERIALIZE_ENUM(Type, {
                                           {Type::Altitude, "Altitude"},
                                           {Type::And, "And"},
                                           {Type::Attitude, "Attitude"},
                                           {Type::Combat, "Combat"},
                                           {Type::Flock, "Flock"},
                                           {Type::HeightDifference, "HeightDifference"},
                                           {Type::InsideBlock, "InsideBlock"},
                                           {Type::Inventory, "Inventory"},
                                           {Type::ItemInHand, "ItemInHand"},
                                           {Type::LineOfSight, "LineOfSight"},
                                           {Type::MovementState, "MovementState"},
                                           {Type::NPCGroup, "NPCGroup"},
                                           {Type::Not, "Not"},
                                           {Type::Or, "Or"},
                                           {Type::SpotsMe, "SpotsMe"},
                                           {Type::StandingOnBlock, "StandingOnBlock"},
                                           {Type::Stat, "Stat"},
                                           {Type::ViewSector, "ViewSector"},
                                       })

    NLOHMANN_JSON_SERIALIZE_ENUM(CombatModeFlag, {
                                                     {CombatModeFlag::Ranged, "Ranged"},
                                                     {CombatModeFlag::Charging, "Charging"},
                                                     {CombatModeFlag::Melee, "Melee"},
                                                     {CombatModeFlag::Blocking, "Blocking"},
                                                     {CombatModeFlag::Sequence, "Sequence"},
                                                     {CombatModeFlag::Attacking, "Attacking"},
                                                     {CombatModeFlag::Any, "Any"},
                                                     {CombatModeFlag::None, "None"},
                                                 })

    NLOHMANN_JSON_SERIALIZE_ENUM(FlockStatusFlag, {
                                                      {FlockStatusFlag::Leader, "Leader"},
                                                      {FlockStatusFlag::Follower, "Follower"},
                                                      {FlockStatusFlag::NotMember, "NotMember"},
                                                      {FlockStatusFlag::Member, "Member"},
                                                      {FlockStatusFlag::Any, "Any"},
                                                  })

    NLOHMANN_JSON_SERIALIZE_ENUM(FlockPlayerStatusFlag, {
                                                            {FlockPlayerStatusFlag::NotMember, "NotMember"},
                                                            {FlockPlayerStatusFlag::Member, "Member"},
                                                            {FlockPlayerStatusFlag::Any, "Any"},
                                                        })

    NLOHMANN_JSON_SERIALIZE_ENUM(ItemInHandFlag, {
                                                     {ItemInHandFlag::OffHand, "OffHand"},
                                                     {ItemInHandFlag::Main, "Main"},
                                                     {ItemInHandFlag::Both, "Both"},
                                                 })

    NLOHMANN_JSON_SERIALIZE_ENUM(MovementStateFlag, {
                                                        {MovementStateFlag::Walking, "Walking"},
                                                        {MovementStateFlag::Flying, "Flying"},
                                                        {MovementStateFlag::Running, "Running"},
                                                        {MovementStateFlag::Falling, "Falling"},
                                                        {MovementStateFlag::Idle, "Idle"},
                                                        {MovementStateFlag::Sprinting, "Sprinting"},
                                                        {MovementStateFlag::Crouching, "Crouching"},
                                                        {MovementStateFlag::Climbing, "Climbing"},
                                                        {MovementStateFlag::Any, "Any"},
                                                        {MovementStateFlag::Jumping, "Jumping"},
                                                    })

    NLOHMANN_JSON_SERIALIZE_ENUM(ViewTestFlag, {
                                                   {ViewTestFlag::View_Sector, "View_Sector"},
                                                   {ViewTestFlag::None, "None"},
                                                   {ViewTestFlag::View_Cone, "View_Cone"},
                                               })

    NLOHMANN_JSON_SERIALIZE_ENUM(StatFlag, {
                                               {StatFlag::Min, "Min"},
                                               {StatFlag::Max, "Max"},
                                               {StatFlag::Value, "Value"},
                                           })

    void to_json(nlohmann::json &j, const IEntityFilter &v);
    void from_json(const nlohmann::json &j, IEntityFilter &v);

    void to_json(nlohmann::json &j, const Altitude &v);
    void from_json(const nlohmann::json &j, Altitude &v);

    void to_json(nlohmann::json &j, const And &v);
    void from_json(const nlohmann::json &j, And &v);

    void to_json(nlohmann::json &j, const Attitude &v);
    void from_json(const nlohmann::json &j, Attitude &v);

    void to_json(nlohmann::json &j, const Combat &v);
    void from_json(const nlohmann::json &j, Combat &v);

    void to_json(nlohmann::json &j, const Flock &v);
    void from_json(const nlohmann::json &j, Flock &v);

    void to_json(nlohmann::json &j, const HeightDifference &v);
    void from_json(const nlohmann::json &j, HeightDifference &v);

    void to_json(nlohmann::json &j, const InsideBlock &v);
    void from_json(const nlohmann::json &j, InsideBlock &v);

    void to_json(nlohmann::json &j, const Inventory &v);
    void from_json(const nlohmann::json &j, Inventory &v);

    void to_json(nlohmann::json &j, const ItemInHand &v);
    void from_json(const nlohmann::json &j, ItemInHand &v);

    void to_json(nlohmann::json &j, const LineOfSight &v);
    void from_json(const nlohmann::json &j, LineOfSight &v);

    void to_json(nlohmann::json &j, const MovementState &v);
    void from_json(const nlohmann::json &j, MovementState &v);

    void to_json(nlohmann::json &j, const NPCGroup &v);
    void from_json(const nlohmann::json &j, NPCGroup &v);

    void to_json(nlohmann::json &j, const Not &v);
    void from_json(const nlohmann::json &j, Not &v);

    void to_json(nlohmann::json &j, const Or &v);
    void from_json(const nlohmann::json &j, Or &v);

    void to_json(nlohmann::json &j, const SpotsMe &v);
    void from_json(const nlohmann::json &j, SpotsMe &v);

    void to_json(nlohmann::json &j, const StandingOnBlock &v);
    void from_json(const nlohmann::json &j, StandingOnBlock &v);

    void to_json(nlohmann::json &j, const Stat &v);
    void from_json(const nlohmann::json &j, Stat &v);

    void to_json(nlohmann::json &j, const ViewSector &v);
    void from_json(const nlohmann::json &j, ViewSector &v);
  }

  namespace Sensor
  {
    NLOHMANN_JSON_SERIALIZE_ENUM(Type, {
                                           {Type::AdjustPosition, "AdjustPosition"},
                                           {Type::Age, "Age"},
                                           {Type::Alarm, "Alarm"},
                                           {Type::And, "And"},
                                           {Type::Animation, "Animation"},
                                           {Type::Any, "Any"},
                                           {Type::Beacon, "Beacon"},
                                           {Type::BlockChange, "BlockChange"},
                                           {Type::BlockType, "BlockType"},
                                           {Type::CanInteract, "CanInteract"},
                                           {Type::CanPlaceBlock, "CanPlaceBlock"},
                                           {Type::CombatActionEvaluator, "CombatActionEvaluator"},
                                           {Type::Count, "Count"},
                                           {Type::Damage, "Damage"},
                                           {Type::DroppedItem, "DroppedItem"},
                                           {Type::EntityEvent, "EntityEvent"},
                                           {Type::Flag, "Flag"},
                                           {Type::FlockCombatDamage, "FlockCombatDamage"},
                                           {Type::FlockLeader, "FlockLeader"},
                                           {Type::HasHostileTargetMemory, "HasHostileTargetMemory"},
                                           {Type::HasInteracted, "HasInteracted"},
                                           {Type::HasTask, "HasTask"},
                                           {Type::InAir, "InAir"},
                                           {Type::InWater, "InWater"},
                                           {Type::InflictedDamage, "InflictedDamage"},
                                           {Type::InteractionContext, "InteractionContext"},
                                           {Type::IsBackingAway, "IsBackingAway"},
                                           {Type::IsBusy, "IsBusy"},
                                           {Type::Kill, "Kill"},
                                           {Type::Leash, "Leash"},
                                           {Type::Light, "Light"},
                                           {Type::Mob, "Mob"},
                                           {Type::Nav, "Nav"},
                                           {Type::Not, "Not"},
                                           {Type::OnGround, "OnGround"},
                                           {Type::Or, "Or"},
                                           {Type::Path, "Path"},
                                           {Type::Player, "Player"},
                                           {Type::Random, "Random"},
                                           {Type::ReadPosition, "ReadPosition"},
                                           {Type::SearchRay, "SearchRay"},
                                           {Type::Self, "Self"},
                                           {Type::State, "State"},
                                           {Type::Switch, "Switch"},
                                           {Type::Target, "Target"},
                                           {Type::Time, "Time"},
                                           {Type::Timer, "Timer"},
                                           {Type::ValueProviderWrapper, "ValueProviderWrapper"},
                                           {Type::Weather, "Weather"},
                                       })

    NLOHMANN_JSON_SERIALIZE_ENUM(Alarm::AlarmFlag, {
                                                       {Alarm::AlarmFlag::Set, "Set"},
                                                       {Alarm::AlarmFlag::Unset, "Unset"},
                                                       {Alarm::AlarmFlag::Passed, "Passed"},
                                                   })

    NLOHMANN_JSON_SERIALIZE_ENUM(Animation::AnimationFlag, {
                                                               {Animation::AnimationFlag::Status, "Status"},
                                                               {Animation::AnimationFlag::Action, "Action"},
                                                               {Animation::AnimationFlag::Face, "Face"},
                                                           })

    NLOHMANN_JSON_SERIALIZE_ENUM(BlockChange::BlockChangeEventTypeFlag, {
                                                                            {BlockChange::BlockChangeEventTypeFlag::Destruction, "Destruction"},
                                                                            {BlockChange::BlockChangeEventTypeFlag::Interaction, "Interaction"},
                                                                            {BlockChange::BlockChangeEventTypeFlag::Damage, "Damage"},
                                                                        })

    NLOHMANN_JSON_SERIALIZE_ENUM(CanPlaceBlock::CanPlaceBlockFlag, {
                                                                       {CanPlaceBlock::CanPlaceBlockFlag::BodyPosition, "BodyPosition"},
                                                                       {CanPlaceBlock::CanPlaceBlockFlag::FootPosition, "FootPosition"},
                                                                       {CanPlaceBlock::CanPlaceBlockFlag::HeadPosition, "HeadPosition"},
                                                                   })

    NLOHMANN_JSON_SERIALIZE_ENUM(DroppedItem::DroppedItemFlag, {
                                                                   {DroppedItem::DroppedItemFlag::Neutral, "Neutral"},
                                                                   {DroppedItem::DroppedItemFlag::Ignore, "Ignore"},
                                                                   {DroppedItem::DroppedItemFlag::Like, "Like"},
                                                                   {DroppedItem::DroppedItemFlag::Love, "Love"},
                                                                   {DroppedItem::DroppedItemFlag::Dislike, "Dislike"},
                                                               })

    NLOHMANN_JSON_SERIALIZE_ENUM(EntityEvent::EntityEventFlag, {
                                                                   {EntityEvent::EntityEventFlag::Death, "Death"},
                                                                   {EntityEvent::EntityEventFlag::Interaction, "Interaction"},
                                                                   {EntityEvent::EntityEventFlag::Damage, "Damage"},
                                                               })

    NLOHMANN_JSON_SERIALIZE_ENUM(InflictedDamage::InflictedDamageFlag, {
                                                                           {InflictedDamage::InflictedDamageFlag::FlockLeader, "FlockLeader"},
                                                                           {InflictedDamage::InflictedDamageFlag::Self, "Self"},
                                                                           {InflictedDamage::InflictedDamageFlag::Flock, "Flock"},
                                                                       })

    NLOHMANN_JSON_SERIALIZE_ENUM(Nav::NavStatesFlag, {
                                                         {Nav::NavStatesFlag::Progressing, "Progressing"},
                                                         {Nav::NavStatesFlag::Init, "Init"},
                                                         {Nav::NavStatesFlag::At_Goal, "At_Goal"},
                                                         {Nav::NavStatesFlag::Blocked, "Blocked"},
                                                         {Nav::NavStatesFlag::Aborted, "Aborted"},
                                                         {Nav::NavStatesFlag::Defer, "Defer"},
                                                     })

    NLOHMANN_JSON_SERIALIZE_ENUM(Path::PathTypeFlag, {
                                                         {Path::PathTypeFlag::CurrentPrefabPath, "CurrentPrefabPath"},
                                                         {Path::PathTypeFlag::TransientPath, "TransientPath"},
                                                         {Path::PathTypeFlag::AnyPrefabPath, "AnyPrefabPath"},
                                                         {Path::PathTypeFlag::WorldPath, "WorldPath"},
                                                     })

    NLOHMANN_JSON_SERIALIZE_ENUM(Timer::TimerStateFlag, {
                                                            {Timer::TimerStateFlag::Paused, "Paused"},
                                                            {Timer::TimerStateFlag::Running, "Running"},
                                                            {Timer::TimerStateFlag::Stopped, "Stopped"},
                                                            {Timer::TimerStateFlag::Any, "Any"},
                                                        })

    nlohmann::json sensorToJson(const Sensor &s);
    std::unique_ptr<Sensor> sensorFromJson(const nlohmann::json &j);

    void to_json(nlohmann::json &j, const Sensor &v);

    void to_json(nlohmann::json &j, const AdjustPosition &v);
    void from_json(const nlohmann::json &j, AdjustPosition &v);

    void to_json(nlohmann::json &j, const Age &v);
    void from_json(const nlohmann::json &j, Age &v);

    void to_json(nlohmann::json &j, const Alarm &v);
    void from_json(const nlohmann::json &j, Alarm &v);

    void to_json(nlohmann::json &j, const And &v);
    void from_json(const nlohmann::json &j, And &v);

    void to_json(nlohmann::json &j, const Animation &v);
    void from_json(const nlohmann::json &j, Animation &v);

    void to_json(nlohmann::json &j, const Any &v);
    void from_json(const nlohmann::json &j, Any &v);

    void to_json(nlohmann::json &j, const Beacon &v);
    void from_json(const nlohmann::json &j, Beacon &v);

    void to_json(nlohmann::json &j, const BlockChange &v);
    void from_json(const nlohmann::json &j, BlockChange &v);

    void to_json(nlohmann::json &j, const BlockType &v);
    void from_json(const nlohmann::json &j, BlockType &v);

    void to_json(nlohmann::json &j, const CanInteract &v);
    void from_json(const nlohmann::json &j, CanInteract &v);

    void to_json(nlohmann::json &j, const CanPlaceBlock &v);
    void from_json(const nlohmann::json &j, CanPlaceBlock &v);

    void to_json(nlohmann::json &j, const CombatActionEvaluator &v);
    void from_json(const nlohmann::json &j, CombatActionEvaluator &v);

    void to_json(nlohmann::json &j, const Count &v);
    void from_json(const nlohmann::json &j, Count &v);

    void to_json(nlohmann::json &j, const Damage &v);
    void from_json(const nlohmann::json &j, Damage &v);

    void to_json(nlohmann::json &j, const DroppedItem &v);
    void from_json(const nlohmann::json &j, DroppedItem &v);

    void to_json(nlohmann::json &j, const EntityEvent &v);
    void from_json(const nlohmann::json &j, EntityEvent &v);

    void to_json(nlohmann::json &j, const Flag &v);
    void from_json(const nlohmann::json &j, Flag &v);

    void to_json(nlohmann::json &j, const FlockCombatDamage &v);
    void from_json(const nlohmann::json &j, FlockCombatDamage &v);

    void to_json(nlohmann::json &j, const FlockLeader &v);
    void from_json(const nlohmann::json &j, FlockLeader &v);

    void to_json(nlohmann::json &j, const HasHostileTargetMemory &v);
    void from_json(const nlohmann::json &j, HasHostileTargetMemory &v);

    void to_json(nlohmann::json &j, const HasInteracted &v);
    void from_json(const nlohmann::json &j, HasInteracted &v);

    void to_json(nlohmann::json &j, const HasTask &v);
    void from_json(const nlohmann::json &j, HasTask &v);

    void to_json(nlohmann::json &j, const InAir &v);
    void from_json(const nlohmann::json &j, InAir &v);

    void to_json(nlohmann::json &j, const InWater &v);
    void from_json(const nlohmann::json &j, InWater &v);

    void to_json(nlohmann::json &j, const InflictedDamage &v);
    void from_json(const nlohmann::json &j, InflictedDamage &v);

    void to_json(nlohmann::json &j, const InteractionContext &v);
    void from_json(const nlohmann::json &j, InteractionContext &v);

    void to_json(nlohmann::json &j, const IsBackingAway &v);
    void from_json(const nlohmann::json &j, IsBackingAway &v);

    void to_json(nlohmann::json &j, const IsBusy &v);
    void from_json(const nlohmann::json &j, IsBusy &v);

    void to_json(nlohmann::json &j, const Kill &v);
    void from_json(const nlohmann::json &j, Kill &v);

    void to_json(nlohmann::json &j, const Leash &v);
    void from_json(const nlohmann::json &j, Leash &v);

    void to_json(nlohmann::json &j, const Light &v);
    void from_json(const nlohmann::json &j, Light &v);

    void to_json(nlohmann::json &j, const Mob &v);
    void from_json(const nlohmann::json &j, Mob &v);

    void to_json(nlohmann::json &j, const Nav &v);
    void from_json(const nlohmann::json &j, Nav &v);

    void to_json(nlohmann::json &j, const Not &v);
    void from_json(const nlohmann::json &j, Not &v);

    void to_json(nlohmann::json &j, const OnGround &v);
    void from_json(const nlohmann::json &j, OnGround &v);

    void to_json(nlohmann::json &j, const Or &v);
    void from_json(const nlohmann::json &j, Or &v);

    void to_json(nlohmann::json &j, const Path &v);
    void from_json(const nlohmann::json &j, Path &v);

    void to_json(nlohmann::json &j, const Player &v);
    void from_json(const nlohmann::json &j, Player &v);

    void to_json(nlohmann::json &j, const Random &v);
    void from_json(const nlohmann::json &j, Random &v);

    void to_json(nlohmann::json &j, const ReadPosition &v);
    void from_json(const nlohmann::json &j, ReadPosition &v);

    void to_json(nlohmann::json &j, const SearchRay &v);
    void from_json(const nlohmann::json &j, SearchRay &v);

    void to_json(nlohmann::json &j, const Self &v);
    void from_json(const nlohmann::json &j, Self &v);

    void to_json(nlohmann::json &j, const State &v);
    void from_json(const nlohmann::json &j, State &v);

    void to_json(nlohmann::json &j, const Switch &v);
    void from_json(const nlohmann::json &j, Switch &v);

    void to_json(nlohmann::json &j, const Target &v);
    void from_json(const nlohmann::json &j, Target &v);

    void to_json(nlohmann::json &j, const Time &v);
    void from_json(const nlohmann::json &j, Time &v);

    void to_json(nlohmann::json &j, const Timer &v);
    void from_json(const nlohmann::json &j, Timer &v);

    void to_json(nlohmann::json &j, const ValueProviderWrapper &v);
    void from_json(const nlohmann::json &j, ValueProviderWrapper &v);

    void to_json(nlohmann::json &j, const Weather &v);
    void from_json(const nlohmann::json &j, Weather &v);
  }

  namespace Action
  {
    NLOHMANN_JSON_SERIALIZE_ENUM(Type, {
                                           {Type::AddToHostileTargetMemory, "AddToHostileTargetMemory"},
                                           {Type::Appearance, "Appearance"},
                                           {Type::ApplyEntityEffect, "ApplyEntityEffect"},
                                           {Type::CombatAbility, "CombatAbility"},
                                           {Type::CompleteTask, "CompleteTask"},
                                           {Type::Crouch, "Crouch"},
                                           {Type::DelayDespawn, "DelayDespawn"},
                                           {Type::Despawn, "Despawn"},
                                           {Type::Die, "Die"},
                                           {Type::DisplayName, "DisplayName"},
                                           {Type::DropItem, "DropItem"},
                                           {Type::FlockState, "FlockState"},
                                           {Type::FlockTarget, "FlockTarget"},
                                           {Type::IgnoreForAvoidance, "IgnoreForAvoidance"},
                                           {Type::Inventory, "Inventory"},
                                           {Type::JoinFlock, "JoinFlock"},
                                           {Type::LeaveFlock, "LeaveFlock"},
                                           {Type::LockOnInteractionTarget, "LockOnInteractionTarget"},
                                           {Type::Log, "Log"},
                                           {Type::ModelAttachment, "ModelAttachment"},
                                           {Type::Mount, "Mount"},
                                           {Type::Nothing, "Nothing"},
                                           {Type::Notify, "Notify"},
                                           {Type::OpenBarterShop, "OpenBarterShop"},
                                           {Type::OpenShop, "OpenShop"},
                                           {Type::OverrideAltitude, "OverrideAltitude"},
                                           {Type::OverrideAttitude, "OverrideAttitude"},
                                           {Type::ParentState, "ParentState"},
                                           {Type::PickUpItem, "PickUpItem"},
                                           {Type::PlaceBlock, "PlaceBlock"},
                                           {Type::PlaySound, "PlaySound"},
                                           {Type::Random, "Random"},
                                           {Type::RecomputePath, "RecomputePath"},
                                           {Type::ReleaseTarget, "ReleaseTarget"},
                                           {Type::Remove, "Remove"},
                                           {Type::ResetBlockSensors, "ResetBlockSensors"},
                                           {Type::ResetInstructions, "ResetInstructions"},
                                           {Type::ResetPath, "ResetPath"},
                                           {Type::ResetSearchRays, "ResetSearchRays"},
                                           {Type::Role, "Role"},
                                           {Type::Sequence, "Sequence"},
                                           {Type::SetAlarm, "SetAlarm"},
                                           {Type::SetBlockToPlace, "SetBlockToPlace"},
                                           {Type::SetFlag, "SetFlag"},
                                           {Type::SetInteractable, "SetInteractable"},
                                           {Type::SetLeashPosition, "SetLeashPosition"},
                                           {Type::SetMarkedTarget, "SetMarkedTarget"},
                                           {Type::SetStat, "SetStat"},
                                           {Type::StartObjective, "StartObjective"},
                                           {Type::State, "State"},
                                           {Type::StorePosition, "StorePosition"},
                                           {Type::Timeout, "Timeout"},
                                           {Type::TimerContinue, "TimerContinue"},
                                           {Type::TimerModify, "TimerModify"},
                                           {Type::TimerPause, "TimerPause"},
                                           {Type::TimerRestart, "TimerRestart"},
                                           {Type::TimerStart, "TimerStart"},
                                           {Type::TimerStop, "TimerStop"},
                                           {Type::ToggleStateEvaluator, "ToggleStateEvaluator"},
                                           {Type::TriggerSpawnBeacon, "TriggerSpawnBeacon"},
                                           {Type::TriggerSpawners, "TriggerSpawners"},
                                       })

    NLOHMANN_JSON_SERIALIZE_ENUM(CompleteTask::CompleteTaskFlag, {
                                                                     {CompleteTask::CompleteTaskFlag::Status, "Status"},
                                                                     {CompleteTask::CompleteTaskFlag::Action, "Action"},
                                                                     {CompleteTask::CompleteTaskFlag::Face, "Face"},
                                                                 })

    NLOHMANN_JSON_SERIALIZE_ENUM(Inventory::OperationFlag, {
                                                               {Inventory::OperationFlag::Add, "Add"},
                                                               {Inventory::OperationFlag::RemoveHeldItem, "RemoveHeldItem"},
                                                               {Inventory::OperationFlag::SetHotbar, "SetHotbar"},
                                                               {Inventory::OperationFlag::Equip, "Equip"},
                                                               {Inventory::OperationFlag::ClearHeldItem, "ClearHeldItem"},
                                                               {Inventory::OperationFlag::EquipOffHand, "EquipOffHand"},
                                                               {Inventory::OperationFlag::Remove, "Remove"},
                                                               {Inventory::OperationFlag::EquipHotbar, "EquipHotbar"},
                                                               {Inventory::OperationFlag::SetOffHand, "SetOffHand"},
                                                           })

    nlohmann::json actionToJson(const Action &a);
    std::unique_ptr<Action> actionFromJson(const nlohmann::json &j);

    void to_json(nlohmann::json &j, const Action &v);
    void to_json(nlohmann::json &j, const WeightedAction &v);
    void from_json(const nlohmann::json &j, WeightedAction &v);
    void to_json(nlohmann::json &j, const ActionList &v);
    void from_json(const nlohmann::json &j, ActionList &v);

    void to_json(nlohmann::json &j, const AddToHostileTargetMemory &v);
    void from_json(const nlohmann::json &j, AddToHostileTargetMemory &v);

    void to_json(nlohmann::json &j, const Appearance &v);
    void from_json(const nlohmann::json &j, Appearance &v);

    void to_json(nlohmann::json &j, const ApplyEntityEffect &v);
    void from_json(const nlohmann::json &j, ApplyEntityEffect &v);

    void to_json(nlohmann::json &j, const CombatAbility &v);
    void from_json(const nlohmann::json &j, CombatAbility &v);

    void to_json(nlohmann::json &j, const CompleteTask &v);
    void from_json(const nlohmann::json &j, CompleteTask &v);

    void to_json(nlohmann::json &j, const Crouch &v);
    void from_json(const nlohmann::json &j, Crouch &v);

    void to_json(nlohmann::json &j, const DelayDespawn &v);
    void from_json(const nlohmann::json &j, DelayDespawn &v);

    void to_json(nlohmann::json &j, const Despawn &v);
    void from_json(const nlohmann::json &j, Despawn &v);

    void to_json(nlohmann::json &j, const Die &v);
    void from_json(const nlohmann::json &j, Die &v);

    void to_json(nlohmann::json &j, const DisplayName &v);
    void from_json(const nlohmann::json &j, DisplayName &v);

    void to_json(nlohmann::json &j, const DropItem &v);
    void from_json(const nlohmann::json &j, DropItem &v);

    void to_json(nlohmann::json &j, const FlockState &v);
    void from_json(const nlohmann::json &j, FlockState &v);

    void to_json(nlohmann::json &j, const FlockTarget &v);
    void from_json(const nlohmann::json &j, FlockTarget &v);

    void to_json(nlohmann::json &j, const IgnoreForAvoidance &v);
    void from_json(const nlohmann::json &j, IgnoreForAvoidance &v);

    void to_json(nlohmann::json &j, const Inventory &v);
    void from_json(const nlohmann::json &j, Inventory &v);

    void to_json(nlohmann::json &j, const JoinFlock &v);
    void from_json(const nlohmann::json &j, JoinFlock &v);

    void to_json(nlohmann::json &j, const LeaveFlock &v);
    void from_json(const nlohmann::json &j, LeaveFlock &v);

    void to_json(nlohmann::json &j, const LockOnInteractionTarget &v);
    void from_json(const nlohmann::json &j, LockOnInteractionTarget &v);

    void to_json(nlohmann::json &j, const Log &v);
    void from_json(const nlohmann::json &j, Log &v);

    void to_json(nlohmann::json &j, const ModelAttachment &v);
    void from_json(const nlohmann::json &j, ModelAttachment &v);

    void to_json(nlohmann::json &j, const Mount &v);
    void from_json(const nlohmann::json &j, Mount &v);

    void to_json(nlohmann::json &j, const Nothing &v);
    void from_json(const nlohmann::json &j, Nothing &v);

    void to_json(nlohmann::json &j, const Notify &v);
    void from_json(const nlohmann::json &j, Notify &v);

    void to_json(nlohmann::json &j, const OpenBarterShop &v);
    void from_json(const nlohmann::json &j, OpenBarterShop &v);

    void to_json(nlohmann::json &j, const OpenShop &v);
    void from_json(const nlohmann::json &j, OpenShop &v);

    void to_json(nlohmann::json &j, const OverrideAltitude &v);
    void from_json(const nlohmann::json &j, OverrideAltitude &v);

    void to_json(nlohmann::json &j, const OverrideAttitude &v);
    void from_json(const nlohmann::json &j, OverrideAttitude &v);

    void to_json(nlohmann::json &j, const ParentState &v);
    void from_json(const nlohmann::json &j, ParentState &v);

    void to_json(nlohmann::json &j, const PickUpItem &v);
    void from_json(const nlohmann::json &j, PickUpItem &v);

    void to_json(nlohmann::json &j, const PlaceBlock &v);
    void from_json(const nlohmann::json &j, PlaceBlock &v);

    void to_json(nlohmann::json &j, const PlaySound &v);
    void from_json(const nlohmann::json &j, PlaySound &v);

    void to_json(nlohmann::json &j, const Random &v);
    void from_json(const nlohmann::json &j, Random &v);

    void to_json(nlohmann::json &j, const RecomputePath &v);
    void from_json(const nlohmann::json &j, RecomputePath &v);

    void to_json(nlohmann::json &j, const ReleaseTarget &v);
    void from_json(const nlohmann::json &j, ReleaseTarget &v);

    void to_json(nlohmann::json &j, const Remove &v);
    void from_json(const nlohmann::json &j, Remove &v);

    void to_json(nlohmann::json &j, const ResetBlockSensors &v);
    void from_json(const nlohmann::json &j, ResetBlockSensors &v);

    void to_json(nlohmann::json &j, const ResetInstructions &v);
    void from_json(const nlohmann::json &j, ResetInstructions &v);

    void to_json(nlohmann::json &j, const ResetPath &v);
    void from_json(const nlohmann::json &j, ResetPath &v);

    void to_json(nlohmann::json &j, const ResetSearchRays &v);
    void from_json(const nlohmann::json &j, ResetSearchRays &v);

    void to_json(nlohmann::json &j, const Role &v);
    void from_json(const nlohmann::json &j, Role &v);

    void to_json(nlohmann::json &j, const Sequence &v);
    void from_json(const nlohmann::json &j, Sequence &v);

    void to_json(nlohmann::json &j, const SetAlarm &v);
    void from_json(const nlohmann::json &j, SetAlarm &v);

    void to_json(nlohmann::json &j, const SetBlockToPlace &v);
    void from_json(const nlohmann::json &j, SetBlockToPlace &v);

    void to_json(nlohmann::json &j, const SetFlag &v);
    void from_json(const nlohmann::json &j, SetFlag &v);

    void to_json(nlohmann::json &j, const SetInteractable &v);
    void from_json(const nlohmann::json &j, SetInteractable &v);

    void to_json(nlohmann::json &j, const SetLeashPosition &v);
    void from_json(const nlohmann::json &j, SetLeashPosition &v);

    void to_json(nlohmann::json &j, const SetMarkedTarget &v);
    void from_json(const nlohmann::json &j, SetMarkedTarget &v);

    void to_json(nlohmann::json &j, const SetStat &v);
    void from_json(const nlohmann::json &j, SetStat &v);

    void to_json(nlohmann::json &j, const StartObjective &v);
    void from_json(const nlohmann::json &j, StartObjective &v);

    void to_json(nlohmann::json &j, const State &v);
    void from_json(const nlohmann::json &j, State &v);

    void to_json(nlohmann::json &j, const StorePosition &v);
    void from_json(const nlohmann::json &j, StorePosition &v);

    void to_json(nlohmann::json &j, const Timeout &v);
    void from_json(const nlohmann::json &j, Timeout &v);

    void to_json(nlohmann::json &j, const TimerContinue &v);
    void from_json(const nlohmann::json &j, TimerContinue &v);

    void to_json(nlohmann::json &j, const TimerModify &v);
    void from_json(const nlohmann::json &j, TimerModify &v);

    void to_json(nlohmann::json &j, const TimerPause &v);
    void from_json(const nlohmann::json &j, TimerPause &v);

    void to_json(nlohmann::json &j, const TimerRestart &v);
    void from_json(const nlohmann::json &j, TimerRestart &v);

    void to_json(nlohmann::json &j, const TimerStart &v);
    void from_json(const nlohmann::json &j, TimerStart &v);

    void to_json(nlohmann::json &j, const TimerStop &v);
    void from_json(const nlohmann::json &j, TimerStop &v);

    void to_json(nlohmann::json &j, const ToggleStateEvaluator &v);
    void from_json(const nlohmann::json &j, ToggleStateEvaluator &v);

    void to_json(nlohmann::json &j, const TriggerSpawnBeacon &v);
    void from_json(const nlohmann::json &j, TriggerSpawnBeacon &v);

    void to_json(nlohmann::json &j, const TriggerSpawners &v);
    void from_json(const nlohmann::json &j, TriggerSpawners &v);
  }

  namespace BodyMotion
  {
    NLOHMANN_JSON_SERIALIZE_ENUM(Type, {
                                           {Type::AimCharge, "AimCharge"},
                                           {Type::MaintainDistance, "MaintainDistance"},
                                           {Type::MatchLook, "MatchLook"},
                                           {Type::Nothing, "Nothing"},
                                           {Type::Path, "Path"},
                                           {Type::Sequence, "Sequence"},
                                           {Type::Timer, "Timer"},
                                           {Type::Wander, "Wander"},
                                           {Type::WanderInCircle, "WanderInCircle"},
                                           {Type::WanderInRect, "WanderInRect"},
                                       })

    NLOHMANN_JSON_SERIALIZE_ENUM(MovementFlag, {
                                                   {MovementFlag::Backward, "Backward"},
                                                   {MovementFlag::Random, "Random"},
                                                   {MovementFlag::Forward, "Forward"},
                                                   {MovementFlag::Any, "Any"},
                                               })

    NLOHMANN_JSON_SERIALIZE_ENUM(PathShapeFlag, {
                                                    {PathShapeFlag::Chain, "Chain"},
                                                    {PathShapeFlag::Line, "Line"},
                                                    {PathShapeFlag::Loop, "Loop"},
                                                    {PathShapeFlag::Points, "Points"},
                                                })

    void to_json(nlohmann::json &j, const BodyMotion &v);
    void from_json(const nlohmann::json &j, BodyMotion &v);

    void to_json(nlohmann::json &j, const AimCharge &v);
    void from_json(const nlohmann::json &j, AimCharge &v);

    void to_json(nlohmann::json &j, const MaintainDistance &v);
    void from_json(const nlohmann::json &j, MaintainDistance &v);

    void to_json(nlohmann::json &j, const MatchLook &v);
    void from_json(const nlohmann::json &j, MatchLook &v);

    void to_json(nlohmann::json &j, const Nothing &v);
    void from_json(const nlohmann::json &j, Nothing &v);

    void to_json(nlohmann::json &j, const Path &v);
    void from_json(const nlohmann::json &j, Path &v);

    void to_json(nlohmann::json &j, const Sequence &v);
    void from_json(const nlohmann::json &j, Sequence &v);

    void to_json(nlohmann::json &j, const Timer &v);
    void from_json(const nlohmann::json &j, Timer &v);

    void to_json(nlohmann::json &j, const Wander &v);
    void from_json(const nlohmann::json &j, Wander &v);

    void to_json(nlohmann::json &j, const WanderInCircle &v);
    void from_json(const nlohmann::json &j, WanderInCircle &v);

    void to_json(nlohmann::json &j, const WanderInRect &v);
    void from_json(const nlohmann::json &j, WanderInRect &v);
  }

  namespace HeadMotion
  {
    NLOHMANN_JSON_SERIALIZE_ENUM(Type, {
                                           {Type::Aim, "Aim"},
                                           {Type::Nothing, "Nothing"},
                                           {Type::Observe, "Observe"},
                                           {Type::Sequence, "Sequence"},
                                           {Type::Timer, "Timer"},
                                           {Type::Watch, "Watch"},
                                       })

    void to_json(nlohmann::json &j, const HeadMotion &v);
    void from_json(const nlohmann::json &j, HeadMotion &v);

    void to_json(nlohmann::json &j, const Aim &v);
    void from_json(const nlohmann::json &j, Aim &v);

    void to_json(nlohmann::json &j, const Nothing &v);
    void from_json(const nlohmann::json &j, Nothing &v);

    void to_json(nlohmann::json &j, const Observe &v);
    void from_json(const nlohmann::json &j, Observe &v);

    void to_json(nlohmann::json &j, const Sequence &v);
    void from_json(const nlohmann::json &j, Sequence &v);

    void to_json(nlohmann::json &j, const Timer &v);
    void from_json(const nlohmann::json &j, Timer &v);

    void to_json(nlohmann::json &j, const Watch &v);
    void from_json(const nlohmann::json &j, Watch &v);
  }

  void to_json(nlohmann::json &j, const Instruction &v);
  void from_json(const nlohmann::json &j, Instruction &v);

  void to_json(nlohmann::json &j, const StateTransition &v);
  void from_json(const nlohmann::json &j, StateTransition &v);

  void to_json(nlohmann::json &j, const RequiredAttributes &v);
  void from_json(const nlohmann::json &j, RequiredAttributes &v);

  void to_json(nlohmann::json &j, const Attributes &v);
  void from_json(const nlohmann::json &j, Attributes &v);
}