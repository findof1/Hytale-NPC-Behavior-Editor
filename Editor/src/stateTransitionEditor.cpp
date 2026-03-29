#include "stateTransitionEditor.hpp"

StateTransitionEditor::StateTransitionEditor(QWidget *parent) : QWidget(parent)
{
  prioritySpin = new QSpinBox;
  prioritySpin->setRange(0, 100000);

  fromEditor = new VectorEditor(
      []() -> QWidget *
      { return new QLineEdit; });

  toEditor = new VectorEditor(
      []() -> QWidget *
      { return new QLineEdit; });

  enabledCheck = new QCheckBox("Enabled");

  auto *form = new QFormLayout(this);
  form->setContentsMargins(0, 0, 0, 0);

  form->addRow("Priority:", prioritySpin);
  form->addRow("From States:", fromEditor);
  form->addRow("To States:", toEditor);
  form->addRow("Enabled:", enabledCheck);
}

General::StateTransition StateTransitionEditor::value() const
{
  General::StateTransition t;
  t.priority = prioritySpin->value();
  // t.from = fromEditor->value();
  // t.to = toEditor->value();

  t.enabled = enabledCheck->isChecked();

  return t;
}

void StateTransitionEditor::setValue(const General::StateTransition &t)
{
  prioritySpin->setValue(t.priority);
  // fromEditor->setValue(t.from);
  // toEditor->setValue(t.to);

  if (t.enabled.has_value())
  {
    enabledOptional->setEnabled(true);
    enabledCheck->setChecked(*t.enabled);
  }
  else
  {
    enabledOptional->setEnabled(false);
  }
}

nlohmann::json StateTransitionEditor::serialize()
{
  // nlohmann::json j;
  //   j = nlohmann::json{
  //       {"priority", priority},
  //       {"from", from},
  //       {"to", to}
  //   };
  //
  // if (enabled.has_value())
  //      j["enabled"] = enabled.value();
  //
  //  return j;
  return {};
}