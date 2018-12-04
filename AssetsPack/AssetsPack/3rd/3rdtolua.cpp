#include "3rdtolua.h"

extern "C"
{
#include "lfs/lfs.h"
}
#include "md5/md5_tolua.h"


int register_all_3rdpackages(lua_State* tolua_S)
{
	luaopen_lfs(tolua_S);
	tolua_md5_open(tolua_S);

	return 1;
}
