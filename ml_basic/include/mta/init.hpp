#pragma once

#include <string>

#ifdef _WIN32
#	define strncpy_s(destination, source, size) \
		strncpy_s((destination), strlen((source)) + 1, (source), (size))
#	define strcpy_s(destination, source, size) \
		strcpy_s((destination), strlen((source)) + 1, (source))
#endif