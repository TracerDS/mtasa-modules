#include <mta/mta_main.hpp>

std::string GetResourceName(lua_State* luaVM) noexcept {
	char resourceName[MAX_RESOURCE_LENGTH];
	pModuleManager->GetResourceName(luaVM, resourceName, MAX_RESOURCE_LENGTH);
	return std::string(resourceName);
}

void* GetRootElement(lua_State* luaVM) noexcept {
	lua_getglobal(luaVM, "root");
	return lua_touserdata(luaVM, -1);
}
void* GetResourceRootElement(lua_State* luaVM) noexcept {
	lua_getglobal(luaVM, "resourceRoot");
	return lua_touserdata(luaVM, -1);
}