#pragma once

extern "C" {
#   include <lua/lua.h>
}

class CLuaArgument {
    int m_iType{};
    bool m_bBoolean{};
    lua_Number m_Number{};
    char* m_szString{};
    void* m_pLightUserData{};
    lua_CFunction m_Function{};
public:
    CLuaArgument();
    CLuaArgument(bool bBool);
    CLuaArgument(double dNumber);
    CLuaArgument(const char* szString);
    CLuaArgument(void* pUserData);
    CLuaArgument(lua_CFunction function);
    CLuaArgument(const CLuaArgument& Argument);
    CLuaArgument(lua_State* luaVM, unsigned int uiArgument);
    ~CLuaArgument();

    const CLuaArgument& operator=(const CLuaArgument& Argument);
    bool operator==(const CLuaArgument& Argument);
    bool operator!=(const CLuaArgument& Argument);

    void Read(lua_State* luaVM, unsigned int uiArgument);
    void Push(lua_State* luaVM) const;

    int GetType() const noexcept;

    bool GetBoolean() const noexcept;
    lua_Number GetNumber() const noexcept;
    const char* GetString() const noexcept;
    void* GetLightUserData() const noexcept;
    lua_CFunction GetFunction() const noexcept;
};