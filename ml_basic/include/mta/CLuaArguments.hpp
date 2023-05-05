#pragma once

extern "C" {
#   include <lua/lua.h>
}

#include <mta/CLuaArgument.hpp>
#include <vector>

class CLuaArguments {
    std::vector<CLuaArgument*> m_Arguments;
public:
    CLuaArguments() noexcept;
    CLuaArguments(const CLuaArguments& Arguments);
    ~CLuaArguments();

    const CLuaArguments& operator=(const CLuaArguments& Arguments);

    void ReadArguments(lua_State* luaVM, unsigned int uiIndexBegin = 1);
    void PushArguments(lua_State* luaVM) const;
    void PushArguments(CLuaArguments& Arguments);
    bool Call(lua_State* luaVM, const char* szFunction) const;

    CLuaArgument* PushNil();
    CLuaArgument* PushBoolean(bool bBool);
    CLuaArgument* PushNumber(double dNumber);
    CLuaArgument* PushString(const char* szString);
    CLuaArgument* PushUserData(void* pUserData);
    CLuaArgument* PushFunction(lua_CFunction function);

    void DeleteArguments();

    unsigned int Count() const noexcept;
    std::vector<CLuaArgument*>::const_iterator IterBegin() noexcept;
    std::vector<CLuaArgument*>::const_iterator IterEnd() noexcept;
};