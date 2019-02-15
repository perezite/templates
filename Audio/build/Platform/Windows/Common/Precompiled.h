#pragma once

#ifndef __INTELLISENSE__

	#ifdef _DEBUG
		#define _ITERATOR_DEBUG_LEVEL 0	// prevent slow stl debugging
	#endif

	#define _USE_MATH_DEFINES

	#include <iostream>
	#include <limits>
	#include <math.h>
	#include <stdlib.h>
	#include <stdarg.h>
	#include <memory.h>
	#include <sstream>
	#include <iomanip>
	#include <string>
	#include <algorithm>
	#include <vector>
	#include <tuple>
	#include <stdio.h>
	#include <time.h>
	#include <map>
	#include <array>
	#include <cstdlib>
	#include <stddef.h>
	#include <set>

	#ifdef WIN32
		#define NOMINMAX		// prevent redefinition of min/max by windows.h
		#include <windows.h>
		#include <direct.h>
	#endif

#endif
