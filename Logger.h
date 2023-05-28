#pragma once
#include <iostream>
#include "GiphEnums.h"
class Logger {
public:
	static void Log(ReturnLogs returnLog);
	static void LogWithField(ReturnLogs returnLog, const std::string& field);
};

