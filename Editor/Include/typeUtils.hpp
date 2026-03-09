#pragma once
#include "types.hpp"
#include <QApplication>

QString attitudeFlagToString(General::AttitudeFlag flag);
General::AttitudeFlag stringToAttitudeFlag(const QString &str);

std::string attitudeFlagToStdString(General::AttitudeFlag flag);
