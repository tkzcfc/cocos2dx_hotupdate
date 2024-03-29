--------------------------------------------------------------
-- This file was automatically generated by Cocos Studio.
-- Do not make changes to this file.
-- All changes will be lost.
--------------------------------------------------------------

local luaExtend = require "LuaExtend"

-- using for layout to decrease count of local variables
local layout = nil
local localLuaFile = nil
local innerCSD = nil
local innerProject = nil
local localFrame = nil

local Result = {}
------------------------------------------------------------
-- function call description
-- create function caller should provide a function to 
-- get a callback function in creating scene process.
-- the returned callback function will be registered to 
-- the callback event of the control.
-- the function provider is as below :
-- Callback callBackProvider(luaFileName, node, callbackName)
-- parameter description:
-- luaFileName  : a string, lua file name
-- node         : a Node, event source
-- callbackName : a string, callback function name
-- the return value is a callback function
------------------------------------------------------------
function Result.create(callBackProvider)

local result={}
setmetatable(result, luaExtend)

--Create Scene
local Scene=cc.Node:create()
Scene:setName("Scene")

--Create LoadingBar_Percent
local LoadingBar_Percent = ccui.LoadingBar:create()
LoadingBar_Percent:loadTexture("Default/LoadingBarFile.png",0)
LoadingBar_Percent:ignoreContentAdaptWithSize(false)
LoadingBar_Percent:setPercent(80)
LoadingBar_Percent:setLayoutComponentEnabled(true)
LoadingBar_Percent:setName("LoadingBar_Percent")
LoadingBar_Percent:setTag(3)
LoadingBar_Percent:setCascadeColorEnabled(true)
LoadingBar_Percent:setCascadeOpacityEnabled(true)
LoadingBar_Percent:setPosition(480.0000, 332.8928)
LoadingBar_Percent:setColor({r = 255, g = 0, b = 0})
layout = ccui.LayoutComponent:bindLayoutComponent(LoadingBar_Percent)
layout:setPositionPercentXEnabled(true)
layout:setPositionPercentX(0.5000)
layout:setPositionPercentY(0.5201)
layout:setPercentWidth(0.7982)
layout:setPercentHeight(0.0219)
layout:setSize({width = 766.2472, height = 14.0000})
layout:setLeftMargin(96.8764)
layout:setRightMargin(96.8764)
layout:setTopMargin(300.1072)
layout:setBottomMargin(325.8928)
Scene:addChild(LoadingBar_Percent)

--Create Text_Percent
local Text_Percent = ccui.Text:create()
Text_Percent:ignoreContentAdaptWithSize(true)
Text_Percent:setTextAreaSize({width = 0, height = 0})
Text_Percent:setFontSize(20)
Text_Percent:setString([[Text Label]])
Text_Percent:setLayoutComponentEnabled(true)
Text_Percent:setName("Text_Percent")
Text_Percent:setTag(4)
Text_Percent:setCascadeColorEnabled(true)
Text_Percent:setCascadeOpacityEnabled(true)
Text_Percent:setPosition(480.0000, 307.0388)
layout = ccui.LayoutComponent:bindLayoutComponent(Text_Percent)
layout:setPositionPercentXEnabled(true)
layout:setPositionPercentX(0.5000)
layout:setPositionPercentY(0.4797)
layout:setPercentWidth(0.1042)
layout:setPercentHeight(0.0313)
layout:setSize({width = 100.0000, height = 20.0000})
layout:setLeftMargin(430.0000)
layout:setRightMargin(430.0000)
layout:setTopMargin(322.9612)
layout:setBottomMargin(297.0388)
Scene:addChild(Text_Percent)

--Create Button_Update
local Button_Update = ccui.Button:create()
Button_Update:ignoreContentAdaptWithSize(false)
Button_Update:loadTextureNormal("Default/Button_Normal.png",0)
Button_Update:loadTexturePressed("Default/Button_Press.png",0)
Button_Update:loadTextureDisabled("Default/Button_Disable.png",0)
Button_Update:setTitleFontSize(14)
Button_Update:setTitleText("check update")
Button_Update:setTitleColor({r = 65, g = 65, b = 70})
Button_Update:setScale9Enabled(true)
Button_Update:setCapInsets({x = 15, y = 11, width = 16, height = 14})
Button_Update:setLayoutComponentEnabled(true)
Button_Update:setName("Button_Update")
Button_Update:setTag(5)
Button_Update:setCascadeColorEnabled(true)
Button_Update:setCascadeOpacityEnabled(true)
Button_Update:setPosition(470.9892, 411.1047)
if callBackProvider~=nil then
      Button_Update:addClickEventListener(callBackProvider("MainScene.lua", Button_Update, "onClickUpdate"))
end
layout = ccui.LayoutComponent:bindLayoutComponent(Button_Update)
layout:setPositionPercentX(0.4906)
layout:setPositionPercentY(0.6299)
-- layout:setPercentWidth(0.1583)
-- layout:setPercentHeight(0.0563)
layout:setSize({width = 152.0099, height = 36.0000})
Scene:addChild(Button_Update)


--Create Button_Start
local Button_Start = ccui.Button:create()
Button_Start:ignoreContentAdaptWithSize(false)
Button_Start:loadTextureNormal("Default/Button_Normal.png",0)
Button_Start:loadTexturePressed("Default/Button_Press.png",0)
Button_Start:loadTextureDisabled("Default/Button_Disable.png",0)
Button_Start:setTitleFontSize(14)
Button_Start:setTitleText("start update")
Button_Start:setTitleColor({r = 65, g = 65, b = 70})
Button_Start:setScale9Enabled(true)
Button_Start:setCapInsets({x = 15, y = 11, width = 16, height = 14})
Button_Start:setLayoutComponentEnabled(true)
Button_Start:setName("Button_Start")
Button_Start:setTag(5)
Button_Start:setCascadeColorEnabled(true)
Button_Start:setCascadeOpacityEnabled(true)
Button_Start:setPosition(470.9892, 211.1047)
if callBackProvider~=nil then
      Button_Start:addClickEventListener(callBackProvider("MainScene.lua", Button_Start, "onClickStartUpdate"))
end
layout = ccui.LayoutComponent:bindLayoutComponent(Button_Start)
layout:setPositionPercentX(0.4906)
layout:setPositionPercentY(0.3299)
-- layout:setPercentWidth(0.1583)
-- layout:setPercentHeight(0.0563)
layout:setSize({width = 152.0099, height = 36.0000})
Scene:addChild(Button_Start)


--Create Button_Fix
local Button_Fix = ccui.Button:create()
Button_Fix:ignoreContentAdaptWithSize(false)
Button_Fix:loadTextureNormal("Default/Button_Normal.png",0)
Button_Fix:loadTexturePressed("Default/Button_Press.png",0)
Button_Fix:loadTextureDisabled("Default/Button_Disable.png",0)
Button_Fix:setTitleFontSize(14)
Button_Fix:setTitleText("update fix")
Button_Fix:setTitleColor({r = 65, g = 65, b = 70})
Button_Fix:setScale9Enabled(true)
Button_Fix:setCapInsets({x = 15, y = 11, width = 16, height = 14})
Button_Fix:setLayoutComponentEnabled(true)
Button_Fix:setName("Button_Fix")
Button_Fix:setTag(5)
Button_Fix:setCascadeColorEnabled(true)
Button_Fix:setCascadeOpacityEnabled(true)
Button_Fix:setPosition(470.9892, 151.1047)
if callBackProvider~=nil then
      Button_Fix:addClickEventListener(callBackProvider("MainScene.lua", Button_Fix, "onClickFixUpdate"))
end
layout = ccui.LayoutComponent:bindLayoutComponent(Button_Fix)
layout:setPositionPercentX(0.4906)
layout:setPositionPercentY(0.3299)
-- layout:setPercentWidth(0.1583)
-- layout:setPercentHeight(0.0563)
layout:setSize({width = 152.0099, height = 36.0000})
Scene:addChild(Button_Fix)

--Create Button_Enter
local Button_Enter = ccui.Button:create()
Button_Enter:ignoreContentAdaptWithSize(false)
Button_Enter:loadTextureNormal("Default/Button_Normal.png",0)
Button_Enter:loadTexturePressed("Default/Button_Press.png",0)
Button_Enter:loadTextureDisabled("Default/Button_Disable.png",0)
Button_Enter:setTitleFontSize(14)
Button_Enter:setTitleText("Button")
Button_Enter:setTitleColor({r = 65, g = 65, b = 70})
Button_Enter:setScale9Enabled(true)
Button_Enter:setCapInsets({x = 15, y = 11, width = 16, height = 14})
Button_Enter:setLayoutComponentEnabled(true)
Button_Enter:setName("Button_Enter")
Button_Enter:setTag(6)
Button_Enter:setCascadeColorEnabled(true)
Button_Enter:setCascadeOpacityEnabled(true)
Button_Enter:setPosition(473.5807, 107.6879)
if callBackProvider~=nil then
      Button_Enter:addClickEventListener(callBackProvider("MainScene.lua", Button_Enter, "onClickNextScene"))
end
layout = ccui.LayoutComponent:bindLayoutComponent(Button_Enter)
layout:setPositionPercentX(0.4933)
layout:setPositionPercentY(0.1683)
layout:setPercentWidth(0.1341)
layout:setPercentHeight(0.0563)
layout:setSize({width = 128.7394, height = 36.0000})
layout:setLeftMargin(409.2110)
layout:setRightMargin(422.0497)
layout:setTopMargin(514.3121)
layout:setBottomMargin(89.6879)
Scene:addChild(Button_Enter)

--Create Text_Status
local Text_Status = ccui.Text:create()
Text_Status:ignoreContentAdaptWithSize(true)
Text_Status:setTextAreaSize({width = 0, height = 0})
Text_Status:setFontSize(20)
Text_Status:setString([[Text Label]])
Text_Status:setLayoutComponentEnabled(true)
Text_Status:setName("Text_Status")
Text_Status:setTag(21)
Text_Status:setCascadeColorEnabled(true)
Text_Status:setCascadeOpacityEnabled(true)
Text_Status:setPosition(480.0001, 268.5964)
layout = ccui.LayoutComponent:bindLayoutComponent(Text_Status)
layout:setPositionPercentXEnabled(true)
layout:setPositionPercentX(0.5000)
layout:setPositionPercentY(0.4197)
layout:setPercentWidth(0.1042)
layout:setPercentHeight(0.0313)
layout:setSize({width = 100.0000, height = 20.0000})
layout:setLeftMargin(430.0001)
layout:setRightMargin(429.9999)
layout:setTopMargin(361.4036)
layout:setBottomMargin(258.5964)
Scene:addChild(Text_Status)

--Create Animation
result['animation'] = ccs.ActionTimeline:create()
  
result['animation']:setDuration(0)
result['animation']:setTimeSpeed(1.0000)
--Create Animation List

result['root'] = Scene
return result;
end

return Result

