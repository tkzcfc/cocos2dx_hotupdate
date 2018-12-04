#include <iostream>


extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}
#include "3rd/3rdtolua.h"
#include "3rd/doit/doit_tolua.h"


void main()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	register_all_3rdpackages(L);

	lua_checkstack(L, 1000);

#ifndef TOLUA_RELEASE
	luaL_dofile(L, "main.lua");
#else
	tolua_doit_open(L);
#endif
	lua_close(L);

	system("pause");
}