#include <main.hpp>

MTAEXPORT bool InitModule(
	ILuaModule* pLuaModule,
	char* szModuleName,
	char* szAuthor,
	float* fVersion
) {
	pModule = pLuaModule;

	Helper::strncpy_s(szModuleName, MODULE_NAME, MAX_INFO_LENGTH); // Set module name
	Helper::strncpy_s(szAuthor, MODULE_AUTHOR, MAX_INFO_LENGTH); // Set module author
	*fVersion = MODULE_VERSION; // Set module version

	pModule->Printf("Module \"%s\" has been started!\n", MODULE_NAME);

	IAccountManager* accManager = pModule->GetAccountManager();
	auto accounts = accManager->GetAllAccounts();
	pModule->Printf("AccManager: %d\n", accounts.size());
	pModule->Printf("Didn't crash?\n");

	return true;
}

MTAEXPORT bool DoPulse() { return true; }
MTAEXPORT bool ShutdownModule() {
	pModule->Printf("Module \"%s\" is shutting down!\n", MODULE_NAME);
	return true;
}

MTAEXPORT void RegisterFunctions(lua_State* luaVM) {}
MTAEXPORT void ResourceStopping(lua_State* luaVM) {}
MTAEXPORT void ResourceStopped(lua_State* luaVM) {}