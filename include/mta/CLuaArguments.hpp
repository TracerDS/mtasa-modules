#pragma once

#include <mta/CLuaArgument.hpp>
#include <vector>

class CLuaArguments {
    std::vector<CLuaArgument*> m_Arguments;
public:
    CLuaArguments() noexcept {};
    CLuaArguments(const CLuaArguments& Arguments) {
        // Copy all the arguments
        std::vector<CLuaArgument*>::const_iterator iter = Arguments.m_Arguments.begin();
        for (; iter != Arguments.m_Arguments.end(); iter++) {
            CLuaArgument* pArgument = new CLuaArgument(**iter);
            m_Arguments.push_back(pArgument);
        }
    }
    ~CLuaArguments() { DeleteArguments(); };

    const CLuaArguments& operator=(const CLuaArguments& Arguments) {
        // Clear our previous list if any
        DeleteArguments();

        // Copy all the arguments
        std::vector<CLuaArgument*>::const_iterator iter = Arguments.m_Arguments.begin();
        for (; iter != Arguments.m_Arguments.end(); iter++) {
            CLuaArgument* pArgument = new CLuaArgument(**iter);
            m_Arguments.push_back(pArgument);
        }

        // Return the given reference allowing for chaining
        return Arguments;
    }

    void ReadArguments(lua_State* luaVM, unsigned int uiIndexBegin = 1) {
        // Delete the previous arguments if any
        DeleteArguments();

        // Start reading arguments until there are none left
        while (lua_type(luaVM, uiIndexBegin) != LUA_TNONE) {
            // Create an argument, let it read out the argument and add it to our vector
            CLuaArgument* pArgument = new CLuaArgument(luaVM, uiIndexBegin++);
            m_Arguments.push_back(pArgument);
        }
    }

    void PushArguments(lua_State* luaVM) const {
        // Push all our arguments
        std::vector<CLuaArgument*>::const_iterator iter = m_Arguments.begin();
        for (; iter != m_Arguments.end(); iter++) (*iter)->Push(luaVM);
    }

    void PushArguments(CLuaArguments& Arguments) {
        std::vector<CLuaArgument*>::const_iterator iter = Arguments.IterBegin();
        for (; iter != Arguments.IterEnd(); iter++) {
            CLuaArgument* pArgument = new CLuaArgument(**iter);
            m_Arguments.push_back(pArgument);
        }
    }

    bool Call(lua_State* luaVM, const char* szFunction) const {
        assert(szFunction);

        // Add the function name to the stack and get the event from the table
        assert(luaVM);

        lua_pushstring(luaVM, szFunction);
        lua_gettable(luaVM, LUA_GLOBALSINDEX);

        // Push our arguments onto the stack
        PushArguments(luaVM);

        int iret = lua_pcall(luaVM, static_cast<int>(m_Arguments.size()), 0, 0);

        return iret != LUA_ERRRUN && iret != LUA_ERRMEM;
    }

    CLuaArgument* PushNil() {
        CLuaArgument* pArgument = new CLuaArgument;
        m_Arguments.push_back(pArgument);
        return pArgument;
    }

    CLuaArgument* PushBoolean(bool bBool) {
        CLuaArgument* pArgument = new CLuaArgument(bBool);
        m_Arguments.push_back(pArgument);
        return pArgument;
    }

    CLuaArgument* PushNumber(double dNumber) {
        CLuaArgument* pArgument = new CLuaArgument(dNumber);
        m_Arguments.push_back(pArgument);
        return pArgument;
    }

    CLuaArgument* PushString(const char* szString) {
        CLuaArgument* pArgument = new CLuaArgument(szString);
        m_Arguments.push_back(pArgument);
        return pArgument;
    }

    CLuaArgument* PushUserData(void* pUserData) {
        CLuaArgument* pArgument = new CLuaArgument(pUserData);
        m_Arguments.push_back(pArgument);
        return pArgument;
    }

    CLuaArgument* PushFunction(lua_CFunction function) {
        CLuaArgument* pArgument = new CLuaArgument(function);
        m_Arguments.push_back(pArgument);
        return pArgument;
    }

    void DeleteArguments() {
        // Delete each item
        std::vector<CLuaArgument*>::iterator iter = m_Arguments.begin();
        for (; iter != m_Arguments.end(); iter++) delete* iter;

        // Clear the vector
        m_Arguments.clear();
    }

    unsigned int Count() const noexcept {
        return static_cast<unsigned int>(m_Arguments.size());
    }
    std::vector<CLuaArgument*>::const_iterator IterBegin() noexcept {
        return m_Arguments.begin();
    }
    std::vector<CLuaArgument*>::const_iterator IterEnd() noexcept {
        return m_Arguments.end();
    }
};