#pragma once

// wrapper for code which messes up intellisense in visual studio 2015
class CheesyHelper
{
public:
	static void Log(const char* fmt, ...);
};
