/*
** Lua binding: game_assets
** Generated automatically by tolua++-1.0.92 on Sun Oct 24 13:53:11 2021.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include <string>

/* Exported function */
TOLUA_API int  tolua_game_assets_open (lua_State* tolua_S);

#include "assets/AssetsManager.h"
#include "assets/Manifest.h"
#include "assets/AssetsEvent.h"
USING_NS_AS;

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_assets__AssetsManager (lua_State* tolua_S)
{
 assets::AssetsManager* self = (assets::AssetsManager*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"assets::ManifestAsset");
 tolua_usertype(tolua_S,"assets::AssetsManager");
 tolua_usertype(tolua_S,"assets::Manifest");
 
}

/* method: new of class  assets::AssetsManager */
#ifndef TOLUA_DISABLE_tolua_game_assets_assets_AssetsManager_new00
static int tolua_game_assets_assets_AssetsManager_new00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"assets::AssetsManager",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const std::string manifestUrl = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string storagePath = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
  const std::string platformName = ((const std::string)  tolua_tocppstring(tolua_S,4,0));
  {
   assets::AssetsManager* tolua_ret = (assets::AssetsManager*)  Mtolua_new((assets::AssetsManager)(manifestUrl,storagePath,platformName));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"assets::AssetsManager");
   tolua_pushcppstring(tolua_S,(const char*)manifestUrl);
   tolua_pushcppstring(tolua_S,(const char*)storagePath);
   tolua_pushcppstring(tolua_S,(const char*)platformName);
  }
 }
 return 4;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  assets::AssetsManager */
#ifndef TOLUA_DISABLE_tolua_game_assets_assets_AssetsManager_new00_local
static int tolua_game_assets_assets_AssetsManager_new00_local(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"assets::AssetsManager",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const std::string manifestUrl = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string storagePath = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
  const std::string platformName = ((const std::string)  tolua_tocppstring(tolua_S,4,0));
  {
   assets::AssetsManager* tolua_ret = (assets::AssetsManager*)  Mtolua_new((assets::AssetsManager)(manifestUrl,storagePath,platformName));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"assets::AssetsManager");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
   tolua_pushcppstring(tolua_S,(const char*)manifestUrl);
   tolua_pushcppstring(tolua_S,(const char*)storagePath);
   tolua_pushcppstring(tolua_S,(const char*)platformName);
  }
 }
 return 4;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  assets::AssetsManager */
#ifndef TOLUA_DISABLE_tolua_game_assets_assets_AssetsManager_delete00
static int tolua_game_assets_assets_AssetsManager_delete00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"assets::AssetsManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  assets::AssetsManager* self = (assets::AssetsManager*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: checkUpdate of class  assets::AssetsManager */
#ifndef TOLUA_DISABLE_tolua_game_assets_assets_AssetsManager_checkUpdate00
static int tolua_game_assets_assets_AssetsManager_checkUpdate00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"assets::AssetsManager",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LuaFunction",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  assets::AssetsManager* self = (assets::AssetsManager*)  tolua_tousertype(tolua_S,1,0);
  LuaFunction handle = (  LuaFunction(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'checkUpdate'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->checkUpdate(handle);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'checkUpdate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: startUpdate of class  assets::AssetsManager */
#ifndef TOLUA_DISABLE_tolua_game_assets_assets_AssetsManager_startUpdate00
static int tolua_game_assets_assets_AssetsManager_startUpdate00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"assets::AssetsManager",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LuaFunction",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  assets::AssetsManager* self = (assets::AssetsManager*)  tolua_tousertype(tolua_S,1,0);
  LuaFunction handle = (  LuaFunction(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'startUpdate'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->startUpdate(handle);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'startUpdate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: repair of class  assets::AssetsManager */
#ifndef TOLUA_DISABLE_tolua_game_assets_assets_AssetsManager_repair00
static int tolua_game_assets_assets_AssetsManager_repair00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"assets::AssetsManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  assets::AssetsManager* self = (assets::AssetsManager*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'repair'", NULL);
#endif
  {
   self->repair();
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'repair'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTotalSize of class  assets::AssetsManager */
#ifndef TOLUA_DISABLE_tolua_game_assets_assets_AssetsManager_getTotalSize00
static int tolua_game_assets_assets_AssetsManager_getTotalSize00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"assets::AssetsManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  assets::AssetsManager* self = (assets::AssetsManager*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTotalSize'", NULL);
#endif
  {
   double tolua_ret = (double)  self->getTotalSize();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTotalSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDownloadSize of class  assets::AssetsManager */
#ifndef TOLUA_DISABLE_tolua_game_assets_assets_AssetsManager_getDownloadSize00
static int tolua_game_assets_assets_AssetsManager_getDownloadSize00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"assets::AssetsManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  assets::AssetsManager* self = (assets::AssetsManager*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDownloadSize'", NULL);
#endif
  {
   double tolua_ret = (double)  self->getDownloadSize();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDownloadSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getUpdatePercent of class  assets::AssetsManager */
#ifndef TOLUA_DISABLE_tolua_game_assets_assets_AssetsManager_getUpdatePercent00
static int tolua_game_assets_assets_AssetsManager_getUpdatePercent00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"assets::AssetsManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  assets::AssetsManager* self = (assets::AssetsManager*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getUpdatePercent'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getUpdatePercent();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getUpdatePercent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getStoragePath of class  assets::AssetsManager */
#ifndef TOLUA_DISABLE_tolua_game_assets_assets_AssetsManager_getStoragePath00
static int tolua_game_assets_assets_AssetsManager_getStoragePath00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const assets::AssetsManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const assets::AssetsManager* self = (const assets::AssetsManager*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getStoragePath'", NULL);
#endif
  {
   const std::string tolua_ret = (const std::string)  self->getStoragePath();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getStoragePath'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLocalManifest of class  assets::AssetsManager */
#ifndef TOLUA_DISABLE_tolua_game_assets_assets_AssetsManager_getLocalManifest00
static int tolua_game_assets_assets_AssetsManager_getLocalManifest00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const assets::AssetsManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const assets::AssetsManager* self = (const assets::AssetsManager*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLocalManifest'", NULL);
#endif
  {
   assets::Manifest* tolua_ret = (assets::Manifest*)  self->getLocalManifest();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"assets::Manifest");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLocalManifest'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRemoteManifest of class  assets::AssetsManager */
#ifndef TOLUA_DISABLE_tolua_game_assets_assets_AssetsManager_getRemoteManifest00
static int tolua_game_assets_assets_AssetsManager_getRemoteManifest00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const assets::AssetsManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const assets::AssetsManager* self = (const assets::AssetsManager*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRemoteManifest'", NULL);
#endif
  {
   assets::Manifest* tolua_ret = (assets::Manifest*)  self->getRemoteManifest();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"assets::Manifest");
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRemoteManifest'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMaxConcurrentTask of class  assets::AssetsManager */
#ifndef TOLUA_DISABLE_tolua_game_assets_assets_AssetsManager_getMaxConcurrentTask00
static int tolua_game_assets_assets_AssetsManager_getMaxConcurrentTask00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"assets::AssetsManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  assets::AssetsManager* self = (assets::AssetsManager*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMaxConcurrentTask'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getMaxConcurrentTask();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMaxConcurrentTask'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMaxConcurrentTask of class  assets::AssetsManager */
#ifndef TOLUA_DISABLE_tolua_game_assets_assets_AssetsManager_setMaxConcurrentTask00
static int tolua_game_assets_assets_AssetsManager_setMaxConcurrentTask00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"assets::AssetsManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  assets::AssetsManager* self = (assets::AssetsManager*)  tolua_tousertype(tolua_S,1,0);
  const int max = ((const int)  tolua_tonumber(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMaxConcurrentTask'", NULL);
#endif
  {
   self->setMaxConcurrentTask(max);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMaxConcurrentTask'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setVerifyLuaCallback of class  assets::AssetsManager */
#ifndef TOLUA_DISABLE_tolua_game_assets_assets_AssetsManager_setVerifyLuaCallback00
static int tolua_game_assets_assets_AssetsManager_setVerifyLuaCallback00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"assets::AssetsManager",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LuaFunction",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  assets::AssetsManager* self = (assets::AssetsManager*)  tolua_tousertype(tolua_S,1,0);
  LuaFunction handle = (  LuaFunction(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setVerifyLuaCallback'", NULL);
#endif
  {
   self->setVerifyLuaCallback(handle);
  }
 }
 return 0;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setVerifyLuaCallback'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: md5 of class  assets::ManifestAsset */
#ifndef TOLUA_DISABLE_tolua_get_assets__ManifestAsset_md5
static int tolua_get_assets__ManifestAsset_md5(lua_State* tolua_S)
{
  assets::ManifestAsset* self = (assets::ManifestAsset*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'md5'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->md5);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: md5 of class  assets::ManifestAsset */
#ifndef TOLUA_DISABLE_tolua_set_assets__ManifestAsset_md5
static int tolua_set_assets__ManifestAsset_md5(lua_State* tolua_S)
{
  assets::ManifestAsset* self = (assets::ManifestAsset*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'md5'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->md5 = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: path of class  assets::ManifestAsset */
#ifndef TOLUA_DISABLE_tolua_get_assets__ManifestAsset_path
static int tolua_get_assets__ManifestAsset_path(lua_State* tolua_S)
{
  assets::ManifestAsset* self = (assets::ManifestAsset*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'path'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->path);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: path of class  assets::ManifestAsset */
#ifndef TOLUA_DISABLE_tolua_set_assets__ManifestAsset_path
static int tolua_set_assets__ManifestAsset_path(lua_State* tolua_S)
{
  assets::ManifestAsset* self = (assets::ManifestAsset*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'path'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->path = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: compressed of class  assets::ManifestAsset */
#ifndef TOLUA_DISABLE_tolua_get_assets__ManifestAsset_compressed
static int tolua_get_assets__ManifestAsset_compressed(lua_State* tolua_S)
{
  assets::ManifestAsset* self = (assets::ManifestAsset*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'compressed'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->compressed);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: compressed of class  assets::ManifestAsset */
#ifndef TOLUA_DISABLE_tolua_set_assets__ManifestAsset_compressed
static int tolua_set_assets__ManifestAsset_compressed(lua_State* tolua_S)
{
  assets::ManifestAsset* self = (assets::ManifestAsset*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'compressed'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->compressed = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: downloadSize of class  assets::ManifestAsset */
#ifndef TOLUA_DISABLE_tolua_get_assets__ManifestAsset_downloadSize
static int tolua_get_assets__ManifestAsset_downloadSize(lua_State* tolua_S)
{
  assets::ManifestAsset* self = (assets::ManifestAsset*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'downloadSize'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->downloadSize);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: downloadSize of class  assets::ManifestAsset */
#ifndef TOLUA_DISABLE_tolua_set_assets__ManifestAsset_downloadSize
static int tolua_set_assets__ManifestAsset_downloadSize(lua_State* tolua_S)
{
  assets::ManifestAsset* self = (assets::ManifestAsset*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'downloadSize'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->downloadSize = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: downloadState of class  assets::ManifestAsset */
#ifndef TOLUA_DISABLE_tolua_get_assets__ManifestAsset_downloadState
static int tolua_get_assets__ManifestAsset_downloadState(lua_State* tolua_S)
{
  assets::ManifestAsset* self = (assets::ManifestAsset*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'downloadState'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->downloadState);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: downloadState of class  assets::ManifestAsset */
#ifndef TOLUA_DISABLE_tolua_set_assets__ManifestAsset_downloadState
static int tolua_set_assets__ManifestAsset_downloadState(lua_State* tolua_S)
{
  assets::ManifestAsset* self = (assets::ManifestAsset*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'downloadState'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->downloadState = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: fileSize of class  assets::ManifestAsset */
#ifndef TOLUA_DISABLE_tolua_get_assets__ManifestAsset_unsigned_fileSize
static int tolua_get_assets__ManifestAsset_unsigned_fileSize(lua_State* tolua_S)
{
  assets::ManifestAsset* self = (assets::ManifestAsset*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'fileSize'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->fileSize);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: fileSize of class  assets::ManifestAsset */
#ifndef TOLUA_DISABLE_tolua_set_assets__ManifestAsset_unsigned_fileSize
static int tolua_set_assets__ManifestAsset_unsigned_fileSize(lua_State* tolua_S)
{
  assets::ManifestAsset* self = (assets::ManifestAsset*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'fileSize'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->fileSize = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: isLoaded of class  assets::Manifest */
#ifndef TOLUA_DISABLE_tolua_game_assets_assets_Manifest_isLoaded00
static int tolua_game_assets_assets_Manifest_isLoaded00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const assets::Manifest",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const assets::Manifest* self = (const assets::Manifest*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isLoaded'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isLoaded();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isLoaded'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getStrongUpdateURL of class  assets::Manifest */
#ifndef TOLUA_DISABLE_tolua_game_assets_assets_Manifest_getStrongUpdateURL00
static int tolua_game_assets_assets_Manifest_getStrongUpdateURL00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const assets::Manifest",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const assets::Manifest* self = (const assets::Manifest*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getStrongUpdateURL'", NULL);
#endif
  {
   const std::string tolua_ret = (const std::string)  self->getStrongUpdateURL();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getStrongUpdateURL'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getUpdateDescription of class  assets::Manifest */
#ifndef TOLUA_DISABLE_tolua_game_assets_assets_Manifest_getUpdateDescription00
static int tolua_game_assets_assets_Manifest_getUpdateDescription00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const assets::Manifest",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const assets::Manifest* self = (const assets::Manifest*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getUpdateDescription'", NULL);
#endif
  {
   const std::string tolua_ret = (const std::string)  self->getUpdateDescription();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getUpdateDescription'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getStrongUpdateDescription of class  assets::Manifest */
#ifndef TOLUA_DISABLE_tolua_game_assets_assets_Manifest_getStrongUpdateDescription00
static int tolua_game_assets_assets_Manifest_getStrongUpdateDescription00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const assets::Manifest",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const assets::Manifest* self = (const assets::Manifest*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getStrongUpdateDescription'", NULL);
#endif
  {
   const std::string tolua_ret = (const std::string)  self->getStrongUpdateDescription();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getStrongUpdateDescription'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRestartLevel of class  assets::Manifest */
#ifndef TOLUA_DISABLE_tolua_game_assets_assets_Manifest_getRestartLevel00
static int tolua_game_assets_assets_Manifest_getRestartLevel00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const assets::Manifest",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const assets::Manifest* self = (const assets::Manifest*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRestartLevel'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getRestartLevel();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRestartLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isLooseFileMode of class  assets::Manifest */
#ifndef TOLUA_DISABLE_tolua_game_assets_assets_Manifest_isLooseFileMode00
static int tolua_game_assets_assets_Manifest_isLooseFileMode00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const assets::Manifest",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const assets::Manifest* self = (const assets::Manifest*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isLooseFileMode'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isLooseFileMode();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isLooseFileMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPackageUrl of class  assets::Manifest */
#ifndef TOLUA_DISABLE_tolua_game_assets_assets_Manifest_getPackageUrl00
static int tolua_game_assets_assets_Manifest_getPackageUrl00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const assets::Manifest",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const assets::Manifest* self = (const assets::Manifest*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPackageUrl'", NULL);
#endif
  {
   const std::string tolua_ret = (const std::string)  self->getPackageUrl();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPackageUrl'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getManifestFileUrl of class  assets::Manifest */
#ifndef TOLUA_DISABLE_tolua_game_assets_assets_Manifest_getManifestFileUrl00
static int tolua_game_assets_assets_Manifest_getManifestFileUrl00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const assets::Manifest",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const assets::Manifest* self = (const assets::Manifest*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getManifestFileUrl'", NULL);
#endif
  {
   const std::string tolua_ret = (const std::string)  self->getManifestFileUrl();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getManifestFileUrl'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getVersion of class  assets::Manifest */
#ifndef TOLUA_DISABLE_tolua_game_assets_assets_Manifest_getVersion00
static int tolua_game_assets_assets_Manifest_getVersion00(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const assets::Manifest",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const assets::Manifest* self = (const assets::Manifest*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getVersion'", NULL);
#endif
  {
   const std::string tolua_ret = (const std::string)  self->getVersion();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#if COCOS2D_DEBUG >= 1
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getVersion'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_game_assets_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_module(tolua_S,"assets",0);
  tolua_beginmodule(tolua_S,"assets");
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"AssetsManager","assets::AssetsManager","",tolua_collect_assets__AssetsManager);
   #else
   tolua_cclass(tolua_S,"AssetsManager","assets::AssetsManager","",NULL);
   #endif
   tolua_beginmodule(tolua_S,"AssetsManager");
    tolua_constant(tolua_S,"UNCHECKED",assets::AssetsManager::UNCHECKED);
    tolua_constant(tolua_S,"CHECK_UPDATE",assets::AssetsManager::CHECK_UPDATE);
    tolua_constant(tolua_S,"WAIT_FOR_UPDATE",assets::AssetsManager::WAIT_FOR_UPDATE);
    tolua_constant(tolua_S,"UPDATING",assets::AssetsManager::UPDATING);
    tolua_constant(tolua_S,"UP_TO_DATE",assets::AssetsManager::UP_TO_DATE);
    tolua_function(tolua_S,"new",tolua_game_assets_assets_AssetsManager_new00);
    tolua_function(tolua_S,"new_local",tolua_game_assets_assets_AssetsManager_new00_local);
    tolua_function(tolua_S,".call",tolua_game_assets_assets_AssetsManager_new00_local);
    tolua_function(tolua_S,"delete",tolua_game_assets_assets_AssetsManager_delete00);
    tolua_function(tolua_S,"checkUpdate",tolua_game_assets_assets_AssetsManager_checkUpdate00);
    tolua_function(tolua_S,"startUpdate",tolua_game_assets_assets_AssetsManager_startUpdate00);
    tolua_function(tolua_S,"repair",tolua_game_assets_assets_AssetsManager_repair00);
    tolua_function(tolua_S,"getTotalSize",tolua_game_assets_assets_AssetsManager_getTotalSize00);
    tolua_function(tolua_S,"getDownloadSize",tolua_game_assets_assets_AssetsManager_getDownloadSize00);
    tolua_function(tolua_S,"getUpdatePercent",tolua_game_assets_assets_AssetsManager_getUpdatePercent00);
    tolua_function(tolua_S,"getStoragePath",tolua_game_assets_assets_AssetsManager_getStoragePath00);
    tolua_function(tolua_S,"getLocalManifest",tolua_game_assets_assets_AssetsManager_getLocalManifest00);
    tolua_function(tolua_S,"getRemoteManifest",tolua_game_assets_assets_AssetsManager_getRemoteManifest00);
    tolua_function(tolua_S,"getMaxConcurrentTask",tolua_game_assets_assets_AssetsManager_getMaxConcurrentTask00);
    tolua_function(tolua_S,"setMaxConcurrentTask",tolua_game_assets_assets_AssetsManager_setMaxConcurrentTask00);
    tolua_function(tolua_S,"setVerifyLuaCallback",tolua_game_assets_assets_AssetsManager_setVerifyLuaCallback00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"assets",0);
  tolua_beginmodule(tolua_S,"assets");
   tolua_cclass(tolua_S,"ManifestAsset","assets::ManifestAsset","",NULL);
   tolua_beginmodule(tolua_S,"ManifestAsset");
    tolua_variable(tolua_S,"md5",tolua_get_assets__ManifestAsset_md5,tolua_set_assets__ManifestAsset_md5);
    tolua_variable(tolua_S,"path",tolua_get_assets__ManifestAsset_path,tolua_set_assets__ManifestAsset_path);
    tolua_variable(tolua_S,"compressed",tolua_get_assets__ManifestAsset_compressed,tolua_set_assets__ManifestAsset_compressed);
    tolua_variable(tolua_S,"downloadSize",tolua_get_assets__ManifestAsset_downloadSize,tolua_set_assets__ManifestAsset_downloadSize);
    tolua_variable(tolua_S,"downloadState",tolua_get_assets__ManifestAsset_downloadState,tolua_set_assets__ManifestAsset_downloadState);
    tolua_variable(tolua_S,"fileSize",tolua_get_assets__ManifestAsset_unsigned_fileSize,tolua_set_assets__ManifestAsset_unsigned_fileSize);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"Manifest","assets::Manifest","",NULL);
   tolua_beginmodule(tolua_S,"Manifest");
    tolua_function(tolua_S,"isLoaded",tolua_game_assets_assets_Manifest_isLoaded00);
    tolua_function(tolua_S,"getStrongUpdateURL",tolua_game_assets_assets_Manifest_getStrongUpdateURL00);
    tolua_function(tolua_S,"getUpdateDescription",tolua_game_assets_assets_Manifest_getUpdateDescription00);
    tolua_function(tolua_S,"getStrongUpdateDescription",tolua_game_assets_assets_Manifest_getStrongUpdateDescription00);
    tolua_function(tolua_S,"getRestartLevel",tolua_game_assets_assets_Manifest_getRestartLevel00);
    tolua_function(tolua_S,"isLooseFileMode",tolua_game_assets_assets_Manifest_isLooseFileMode00);
    tolua_function(tolua_S,"getPackageUrl",tolua_game_assets_assets_Manifest_getPackageUrl00);
    tolua_function(tolua_S,"getManifestFileUrl",tolua_game_assets_assets_Manifest_getManifestFileUrl00);
    tolua_function(tolua_S,"getVersion",tolua_game_assets_assets_Manifest_getVersion00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"assets",0);
  tolua_beginmodule(tolua_S,"assets");
   tolua_constant(tolua_S,"ERROR_NO_LOCAL_MANIFEST",assets::ERROR_NO_LOCAL_MANIFEST);
   tolua_constant(tolua_S,"ERROR_DOWNLOAD_MANIFEST",assets::ERROR_DOWNLOAD_MANIFEST);
   tolua_constant(tolua_S,"ERROR_PARSE_MANIFEST",assets::ERROR_PARSE_MANIFEST);
   tolua_constant(tolua_S,"NEED_STRONG_UPDATE",assets::NEED_STRONG_UPDATE);
   tolua_constant(tolua_S,"NEW_VERSION_FOUND",assets::NEW_VERSION_FOUND);
   tolua_constant(tolua_S,"ALREADY_UP_TO_DATE",assets::ALREADY_UP_TO_DATE);
   tolua_constant(tolua_S,"ERROR_DECOMPRESS",assets::ERROR_DECOMPRESS);
   tolua_constant(tolua_S,"ERROR_DOWNLOAD",assets::ERROR_DOWNLOAD);
   tolua_constant(tolua_S,"ERROR_VERIF",assets::ERROR_VERIF);
   tolua_constant(tolua_S,"SUCCESS",assets::SUCCESS);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_game_assets (lua_State* tolua_S) {
 return tolua_game_assets_open(tolua_S);
};
#endif

