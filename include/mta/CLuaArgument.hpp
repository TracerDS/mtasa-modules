#pragma once

#include <lua/lua.hpp>
#include <mta/init.hpp>
#include <cassert>

class CLuaArgument {
    int m_iType{};
    bool m_bBoolean{};
    lua_Number m_Number{};
    char* m_szString{};
    void* m_pLightUserData{};
    lua_CFunction m_Function{};
public:
    CLuaArgument() : m_szString(NULL), m_iType(LUA_TNIL) {}
    CLuaArgument(bool bBool)
        : m_szString(NULL), m_iType(LUA_TBOOLEAN), m_bBoolean(bBool) {}
    CLuaArgument(double dNumber)
        : m_szString(NULL), m_iType(LUA_TNUMBER), m_Number(dNumber) {}
    CLuaArgument(const char* szString) : m_iType(LUA_TSTRING) {
        assert(szString);

        const auto size = strlen(szString) + 1;
        m_szString = new char[size];

        Helper::strcpy_s(m_szString, size, szString);
    }
    CLuaArgument(void* pUserData)
        : m_szString(NULL), m_iType(LUA_TLIGHTUSERDATA), m_pLightUserData(pUserData) {}
    CLuaArgument(lua_CFunction function)
        : m_szString(NULL), m_iType(LUA_TFUNCTION), m_Function(function) {}
    CLuaArgument(const CLuaArgument& Argument)
        : m_szString(NULL) { operator=(Argument); }
    CLuaArgument(lua_State* luaVM, unsigned int uiArgument)
        : m_szString(NULL) { Read(luaVM, uiArgument); }
    ~CLuaArgument() { if (m_szString) delete[] m_szString; }

    const CLuaArgument& operator=(const CLuaArgument& Argument) {
        // Destroy our old string if neccessary
        if (m_szString) { delete[] m_szString; m_szString = NULL; }

        // Set our variable equally to the copy class
        m_iType = Argument.m_iType;
        switch (m_iType) {
        case LUA_TBOOLEAN:
            m_bBoolean = Argument.m_bBoolean;
            break;
        case LUA_TLIGHTUSERDATA:
            m_pLightUserData = Argument.m_pLightUserData;
            break;
        case LUA_TNUMBER:
            m_Number = Argument.m_Number;
            break;
        case LUA_TSTRING:
            if (Argument.m_szString) {
                const auto len = strlen(Argument.m_szString) + 1;
                m_szString = new char[len];
                Helper::strcpy_s(m_szString, len, Argument.m_szString);
            }
            break;
        default: break;
        }

        // Return the given class allowing for chaining
        return Argument;
    }
    bool operator==(const CLuaArgument& Argument) {
        // If the types differ, they're not matching
        if (Argument.m_iType != m_iType) return false;

        // Compare the variables depending on the type
        switch (m_iType) {
        case LUA_TBOOLEAN:
            return m_bBoolean == Argument.m_bBoolean;
        case LUA_TLIGHTUSERDATA:
            return m_pLightUserData == Argument.m_pLightUserData;
        case LUA_TNUMBER:
            return m_Number == Argument.m_Number;
        case LUA_TSTRING:
            if (!m_szString)
                return Argument.m_szString == NULL;

            if (Argument.m_szString)
                return strcmp(m_szString, Argument.m_szString) == 0;
            else return false;
        }
        return true;
    }
    bool operator!=(const CLuaArgument& Argument) {
        return !(operator==(Argument));
    }


    void Read(lua_State* luaVM, unsigned int uiArgument) {
        // Eventually delete our previous string
        if (m_szString) {
            delete[] m_szString;
            m_szString = NULL;
        }

        // Grab the argument type
        m_iType = lua_type(luaVM, uiArgument);
        if (m_iType == LUA_TNONE) return;

        // Read out the content depending on the type
        switch (m_iType) {
        case LUA_TNIL: break;
        case LUA_TBOOLEAN:
            this->m_bBoolean = lua_toboolean(luaVM, uiArgument) ? true : false;
            break;
        case LUA_TLIGHTUSERDATA:
            this->m_pLightUserData = lua_touserdata(luaVM, uiArgument);
            break;
        case LUA_TNUMBER:
            this->m_Number = lua_tonumber(luaVM, uiArgument);
            break;
        case LUA_TSTRING: {
            // Grab the lua string and its size
            const char* szLuaString = lua_tostring(luaVM, uiArgument);
            const size_t sizeLuaString = strlen(szLuaString) + 1;

            // Allocate our buffer
            m_szString = new char[sizeLuaString];
            Helper::strncpy_s(m_szString, sizeLuaString, szLuaString);
            break;
        } default:
            this->m_iType = LUA_TNONE;
            break;
        }
    }


    void Push(lua_State* luaVM) const {
        // Got any type?
        if (m_iType == LUA_TNONE)
            return;

        // Push it depending on the type
        switch (m_iType) {
        case LUA_TNIL:
            lua_pushnil(luaVM);
            break;
        case LUA_TBOOLEAN:
            lua_pushboolean(luaVM, m_bBoolean);
            break;
        case LUA_TLIGHTUSERDATA:
            lua_pushlightuserdata(luaVM, m_pLightUserData);
            break;
        case LUA_TNUMBER:
            lua_pushnumber(luaVM, m_Number);
            break;
        case LUA_TSTRING:
            // Push the string if we got any
            if (m_szString) lua_pushstring(luaVM, m_szString);
            else lua_pushstring(luaVM, "");

            break;
        }
    }

    int GetType() const noexcept { return m_iType; };

    bool GetBoolean() const noexcept { return m_bBoolean; };
    lua_Number GetNumber() const noexcept { return m_Number; };
    const char* GetString() const noexcept { return m_szString; };
    void* GetLightUserData() const noexcept { return m_pLightUserData; };
    lua_CFunction GetFunction() const noexcept { return m_Function; }
};