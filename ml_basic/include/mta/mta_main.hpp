#pragma once

#include <mta/ILuaModuleManager.hpp>
#include <mta/CLuaArguments.hpp>
#include <mta/init.hpp>

#ifdef _WIN32
#	define MTAEXPORT extern "C" __declspec(dllexport)
#else
#	define MTAEXPORT extern "C"
#endif
#define MAX_RESOURCE_LENGTH 256

#if defined(_M_X64) || defined(__x86_64__) || defined(_M_AMD64)
#	define ANY_x64
#	ifdef _WIN64
#		define WIN_x64
#	else
#		define LINUX_x64
#	endif
#else
#	define ANY_x86
#	ifdef _WIN32
#		define WIN_x86
#	else
#		define LINUX_x86
#	endif
#endif

extern ILuaModuleManager10* pModuleManager = NULL;

static std::string GetResourceName(lua_State* luaVM) noexcept;
static void* GetRootElement(lua_State* luaVM) noexcept;
static void* GetResourceRootElement(lua_State* luaVM) noexcept;