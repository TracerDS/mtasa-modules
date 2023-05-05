#pragma once

#include <config.hpp>
#include <functions.hpp>

MTAEXPORT bool DoPulse();
MTAEXPORT bool ShutdownModule();

MTAEXPORT void RegisterFunctions(lua_State* luaVM);
MTAEXPORT void ResourceStopping(lua_State* luaVM);
MTAEXPORT void ResourceStopped(lua_State* luaVM);