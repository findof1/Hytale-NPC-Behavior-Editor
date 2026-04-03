#pragma once
#include <vector>
#include <memory>
#include "nodes.hpp"
#include "types.hpp"

struct SerializerValues
{
  using ActionSerializeFn = std::function<std::unique_ptr<General::Action::Action>(NodeItem *)>;
  QMap<QString, ActionSerializeFn> actionSerializers;
  using SensorSerializeFn = std::function<std::unique_ptr<General::Sensor::Sensor>(NodeItem *)>;
  QMap<QString, SensorSerializeFn> sensorSerializers;

  SerializerValues();
};

std::unique_ptr<General::Action::Action> serializeAction(SerializerValues *serializer, NodeScene *scene, NodeItem *targetNode, bool debug = false);
std::unique_ptr<General::Sensor::Sensor> serializeSensor(SerializerValues *serializer, NodeScene *scene, NodeItem *targetNode, bool debug = false);
General::Instruction serializeInstruction(SerializerValues *serializer, NodeScene *scene, InstructionNode *instructionNode, bool debug = false);
std::vector<General::Instruction> serializeInstructions(SerializerValues *serializer, NodeScene *scene, NodeItem *startNode, bool debug = false);