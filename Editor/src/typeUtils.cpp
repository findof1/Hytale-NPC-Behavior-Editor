#include <QApplication>
#include <string>

#include "typeUtils.hpp"

QString attitudeFlagToString(General::AttitudeFlag flag)
{
  switch (flag)
  {
  case General::AttitudeFlag::Hostile:
    return "Hostile";
  case General::AttitudeFlag::Revered:
    return "Revered";
  case General::AttitudeFlag::Friendly:
    return "Friendly";
  case General::AttitudeFlag::Ignore:
    return "Ignore";
  case General::AttitudeFlag::Neutral:
    return "Neutral";
  }
  return "";
}

General::AttitudeFlag stringToAttitudeFlag(const QString &str)
{
  if (str == "Hostile")
    return General::AttitudeFlag::Hostile;
  if (str == "Revered")
    return General::AttitudeFlag::Revered;
  if (str == "Friendly")
    return General::AttitudeFlag::Friendly;
  if (str == "Ignore")
    return General::AttitudeFlag::Ignore;
  return General::AttitudeFlag::Neutral;
}

std::string attitudeFlagToStdString(General::AttitudeFlag flag)
{
  switch (flag)
  {
  case General::AttitudeFlag::Hostile:
    return "Hostile";
  case General::AttitudeFlag::Revered:
    return "Revered";
  case General::AttitudeFlag::Friendly:
    return "Friendly";
  case General::AttitudeFlag::Ignore:
    return "Ignore";
  case General::AttitudeFlag::Neutral:
    return "Neutral";
  }
  return "";
}