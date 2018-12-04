/*
** Lua binding: md5
** Generated automatically by tolua++-1.0.92 on Fri Nov 23 17:18:56 2018.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_md5_open (lua_State* tolua_S);

#include "md5.h"
#include "json/json_lua.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_MD5 (lua_State* tolua_S)
{
 MD5* self = (MD5*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"MD5");
}

/* method: new of class  MD5 */
#ifndef TOLUA_DISABLE_tolua_md5_MD5_new00
static int tolua_md5_MD5_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MD5",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   MD5* tolua_ret = (MD5*)  Mtolua_new((MD5)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"MD5");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  MD5 */
#ifndef TOLUA_DISABLE_tolua_md5_MD5_new00_local
static int tolua_md5_MD5_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MD5",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   MD5* tolua_ret = (MD5*)  Mtolua_new((MD5)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"MD5");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: update of class  MD5 */
#ifndef TOLUA_DISABLE_tolua_md5_MD5_update00
static int tolua_md5_MD5_update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MD5",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MD5* self = (MD5*)  tolua_tousertype(tolua_S,1,0);
  const char* input = ((const char*)  tolua_tostring(tolua_S,2,0));
  unsigned int length = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'update'", NULL);
#endif
  {
   self->update(input,length);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'update'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: update of class  MD5 */
#ifndef TOLUA_DISABLE_tolua_md5_MD5_update01
static int tolua_md5_MD5_update01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MD5",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  MD5* self = (MD5*)  tolua_tousertype(tolua_S,1,0);
  const string str = ((const string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'update'", NULL);
#endif
  {
   self->update(str);
   tolua_pushcppstring(tolua_S,(const char*)str);
  }
 }
 return 1;
tolua_lerror:
 return tolua_md5_MD5_update00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: toString of class  MD5 */
#ifndef TOLUA_DISABLE_tolua_md5_MD5_toString00
static int tolua_md5_MD5_toString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MD5",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MD5* self = (MD5*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'toString'", NULL);
#endif
  {
   string tolua_ret = (string)  self->toString();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'toString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: reset of class  MD5 */
#ifndef TOLUA_DISABLE_tolua_md5_MD5_reset00
static int tolua_md5_MD5_reset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MD5",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MD5* self = (MD5*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'reset'", NULL);
#endif
  {
   self->reset();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'reset'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: prettyJson */
#ifndef TOLUA_DISABLE_tolua_md5_prettyJson00
static int tolua_md5_prettyJson00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_iscppstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const std::string content = ((const std::string)  tolua_tocppstring(tolua_S,1,0));
  {
   std::string tolua_ret = (std::string)  prettyJson(content);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)content);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'prettyJson'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_md5_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"MD5","MD5","",tolua_collect_MD5);
  #else
  tolua_cclass(tolua_S,"MD5","MD5","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"MD5");
   tolua_function(tolua_S,"new",tolua_md5_MD5_new00);
   tolua_function(tolua_S,"new_local",tolua_md5_MD5_new00_local);
   tolua_function(tolua_S,".call",tolua_md5_MD5_new00_local);
   tolua_function(tolua_S,"update",tolua_md5_MD5_update00);
   tolua_function(tolua_S,"update",tolua_md5_MD5_update01);
   tolua_function(tolua_S,"toString",tolua_md5_MD5_toString00);
   tolua_function(tolua_S,"reset",tolua_md5_MD5_reset00);
  tolua_endmodule(tolua_S);
  tolua_function(tolua_S,"prettyJson",tolua_md5_prettyJson00);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_md5 (lua_State* tolua_S) {
 return tolua_md5_open(tolua_S);
};
#endif

