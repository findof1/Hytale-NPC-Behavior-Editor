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

  SerializerValues();
};

General::Action::Action serializeAction(SerializerValues *serializer, NodeScene *scene, NodeItem *targetNode);
General::Sensor::Sensor serializeSensor(SerializerValues *serializer, NodeScene *scene, NodeItem *targetNode);
std::vector<General::Instruction> serializeInstructions(SerializerValues *serializer, NodeScene *scene, NodeItem *startNode);