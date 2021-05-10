echo off
set buildDir=.\build
set dllsMoveTo=..\..\..\..\..\bin
set depsDir=.\dependecies\build
set cegui8=..\..\cegui-0.8.7
set dependenciesDir=%~dp0..\


mkdir %depsDir%
cd %depsDir%

:: Compilamos las dependencias *sigh*
cmake -DCEGUI_BUILD_GLEW:BOOL="1" -DCEGUI_BUILD_EXPAT:BOOL="1" -DCEGUI_BUILD_LUA:BOOL="0" -DCEGUI_BUILD_GLM:BOOL="1" -DCEGUI_BUILD_GLFW:BOOL="1" -DCEGUI_BUILD_PCRE:BOOL="1" -DCEGUI_BUILD_FREEIMAGE:BOOL="1" -DCEGUI_BUILD_DEVIL:BOOL="1" -DCEGUI_BUILD_FREETYPE2:BOOL="1" -DCEGUI_BUILD_SILLY:BOOL="1" ..\ 
msbuild "CEGUI-DEPS.sln" /p:configuration=Debug /maxcpucount
msbuild "CEGUI-DEPS.sln" /p:configuration=Release /maxcpucount
XCOPY /y /s .\dependencies %cegui8%\dependencies

:: Por fin podemos hacer cosas sobre cegui
cd %cegui8%

mkdir %buildDir%
cd %buildDir%
cmake -DCEGUI_SAMPLES_ENABLE_GAMEMENU_DEMO:BOOL="0" -DCEGUI_HAS_FREETYPE:BOOL="1" -DCEGUI_SAMPLES_ENABLE_INVENTORY_DEMO:BOOL="0" -DCEGUI_BUILD_RENDERER_OPENGL3:BOOL="1" -DCEGUI_SAMPLES_ENABLE_WIDGET_DEMO:BOOL="0" -DOGRE_LIB_DBG:FILEPATH="%dependenciesDir%\Ogre\build\lib\Debug\OgreMain_d.lib" -DCEGUI_SAMPLES_ENABLE_EFFECTS_DEMO:BOOL="0" -DCEGUI_BUILD_APPLICATION_TEMPLATES:BOOL="1" -DCEGUI_SAMPLES_ENABLE_TREE_DEMO:BOOL="0" -DCEGUI_SAMPLES_ENABLE_DRAGDROP_DEMO:BOOL="0" -DCEGUI_SAMPLES_ENABLE_FONT_DEMO:BOOL="0" -DCEGUI_HAS_DEFAULT_LOGGER:BOOL="1" -DCEGUI_SAMPLES_ENABLE_COMMON_DIALOGUES_DEMO:BOOL="0" -DCEGUI_BUILD_RENDERER_OGRE:BOOL="1" -DCEGUI_SAMPLES_ENABLE_TEXT_DEMO:BOOL="0" -DOGRE_H_PATH:PATH="%dependenciesDir%\Ogre\src\OgreMain\include" -DCEGUI_SAMPLES_ENABLE_EDITBOX_VALIDATION_DEMO:BOOL="0" -DCEGUI_SAMPLES_ENABLE_HELLO_WORLD_DEMO:BOOL="0" -DCEGUI_SAMPLES_ENABLE_HUD_DEMO:BOOL="0" -DCEGUI_HAS_PCRE_REGEX:BOOL="1" -DCEGUI_SAMPLES_ENABLE_MINESWEEPER_DEMO:BOOL="0" -DCEGUI_SAMPLES_ENABLE_LOOKNFEELOVERVIEW_DEMO:BOOL="0" -DOGRE_LIB:FILEPATH="%dependenciesDir%\Ogre\build\lib\Release\OgreMain.lib" -DCEGUI_SAMPLES_ENABLE_DEMO6:BOOL="0" -DCEGUI_SAMPLES_ENABLE_SCROLLABLEPANE_DEMO:BOOL="0" -DCEGUI_BUILD_IMAGECODEC_DEVIL:BOOL="1" -DCEGUI_SAMPLES_ENABLE_TABCONTROL_DEMO:BOOL="0" -DOGRE_H_BUILD_SETTINGS_PATH:PATH="%dependenciesDir%\Ogre\build\include" -DCEGUI_BUILD_IMAGECODEC_SILLY:BOOL="1" -DCEGUI_BUILD_IMAGECODEC_FREEIMAGE:BOOL="1" -DCEGUI_BUILD_XMLPARSER_EXPAT:BOOL="1" -DCEGUI_SAMPLES_ENABLED:BOOL="0" -DCEGUI_BUILD_RENDERER_OPENGL:BOOL="1" ..\
pause
::cmake -DOGRE_LIB=..\..\..\Ogre\build\lib\Release\OgreMain.lib -DCEGUI_BUILD_APPLICATION_TEMPLATES:BOOL="0" -DOGRE_LIB_DBG:PATH=..\..\..\Ogre\build\lib\Debug\OgreMain_d.lib -DOGRE_H_PATH:PATH=..\..\..\Ogre\Src\OgreMain\include -DOGRE_H_BUILD_SETTINGS_PATH:PATH=..\..\..\Ogre\build\include -DCEGUI_SAMPLES_ENABLE_EDITBOX_VALIDATION_DEMO:BOOL="0" -DCEGUI_SAMPLES_ENABLE_INVENTORY_DEMO:BOOL="0" -DCEGUI_SAMPLES_ENABLE_COMMON_DIALOGUES_DEMO:BOOL="0" -DCEGUI_SAMPLES_ENABLE_TREE_DEMO:BOOL="0" -DCEGUI_SAMPLES_ENABLE_LOOKNFEELOVERVIEW_DEMO:BOOL="0" -DCEGUI_SAMPLES_ENABLE_SCROLLABLEPANE_DEMO:BOOL="0" -DCEGUI_SAMPLES_ENABLE_HELLO_WORLD_DEMO:BOOL="0" -DCEGUI_SAMPLES_ENABLE_GAMEMENU_DEMO:BOOL="0" -DCEGUI_SAMPLES_ENABLE_HUD_DEMO:BOOL="0" -DCEGUI_SAMPLES_ENABLE_TABCONTROL_DEMO:BOOL="0" -DCEGUI_SAMPLES_ENABLED:BOOL="0" -DCEGUI_BUILD_RENDERER_OGRE:BOOL="1" -DCEGUI_SAMPLES_ENABLE_MINESWEEPER_DEMO:BOOL="0" -DCEGUI_SAMPLES_ENABLE_EFFECTS_DEMO:BOOL="0" -DCEGUI_SAMPLES_ENABLE_WIDGET_DEMO:BOOL="0" -DCEGUI_SAMPLES_ENABLE_DEMO6:BOOL="0" -DCEGUI_SAMPLES_ENABLE_TEXT_DEMO:BOOL="0" -DCEGUI_SAMPLES_ENABLE_DRAGDROP_DEMO:BOOL="0" -DCEGUI_SAMPLES_ENABLE_FONT_DEMO:BOOL="0" ..\

:: Cambiamos el Major, Minor y Patch del config.h
set "source=.\cegui\include\CEGUI\Config.h"
powershell -Command "(gc %source%) -replace 'define CEGUI_OGRE_VERSION_MAJOR 0', 'define CEGUI_OGRE_VERSION_MAJOR 1' | Out-File -encoding ASCII %source%"
powershell -Command "(gc %source%) -replace 'define CEGUI_OGRE_VERSION_MINOR 0', 'define CEGUI_OGRE_VERSION_MINOR 12' | Out-File -encoding ASCII %source%"
powershell -Command "(gc %source%) -replace 'define CEGUI_OGRE_VERSION_PATCH 0', 'define CEGUI_OGRE_VERSION_PATCH 11' | Out-File -encoding ASCII %source%"
pause
:: Compilamos CEGUI
msbuild "cegui.sln" /p:configuration=Release /maxcpucount
msbuild "cegui.sln" /p:configuration=Debug /maxcpucount

:: Ya tenemos dll. Ahora hay que moverlas
cd .\bin\
dir
pause


MOVE .\CEGUIBase-0.dll %dllsMoveTo%
MOVE .\CEGUIBase-0_d.dll %dllsMoveTo%

MOVE .\CEGUIExpatParser.dll %dllsMoveTo%
MOVE .\CEGUIExpatParser_d.dll %dllsMoveTo%

MOVE .\CEGUIOgreRenderer-0.dll %dllsMoveTo%
MOVE .\CEGUIOgreRenderer-0_d.dll %dllsMoveTo%

:: Ah y las dll escondidas en cegui-0.8.7\dependencies\bin
cd ..\..\dependencies\bin
MOVE .\FreeImage_d.dll %dllsMoveTo%
MOVE .\freetype.dll %dllsMoveTo%
MOVE .\freetype_d.dll %dllsMoveTo%

MOVE .\glew.dll %dllsMoveTo%
MOVE .\glew_d.dll %dllsMoveTo%

MOVE .\jpeg.dll %dllsMoveTo%
MOVE .\jpeg_d.dll %dllsMoveTo%

MOVE .\libexpat.dll %dllsMoveTo%
MOVE .\libexpat_d.dll %dllsMoveTo%

MOVE .\pcre.dll %dllsMoveTo%
MOVE .\pcre_d.dll %dllsMoveTo%


::cd ..
echo CEGUI compilado
