echo off
set COMPILEDIR=..\dependencies
set buildDir=.\build
set dllsMoveTo=..\..\..\bin

:: Creamos la carpeta build

mkdir %buildDir%
cd %buildDir%

cmake -DCEGUI_BUILD_FREETYPE2:BOOL="1" -DCEGUI_BUILD_DEVIL:BOOL="1" -DCEGUI_BUILD_FREEIMAGE:BOOL="1" ..\Src\dependecies 
msbuild "CEGUI-DEPS.sln" /p:configuration=Debug /maxcpucount
msbuild "CEGUI-DEPS.sln" /p:configuration=Release /maxcpucount

mkdir %buildDir%
cd %buildDir%
:: Creamos el proyecto y lo compilamos en debug y release
cmake -DOGRE_LIB=%dllsMoveTo%\..\dependencies\Ogre\build\lib\Release\OgreMain.lib -DCMAKE_BUILD_TYPE:STRING="Debug" -DCEGUI_BUILD_APPLICATION_TEMPLATES:BOOL="0" -DOGRE_PLUGIN_DIR_DBG:STRING=%dllsMoveTo%\..\dependencies\Ogre\build\lib\Debug\OgreMain_d.lib -DOGRE_H_PATH:PATH="..\..\Ogre\Src\OgreMain\include" -DOGRE_H_BUILD_SETTINGS_PATH:PATH="..\..\Ogre\build\include" ..\Src\cegui-0.8.7
cmake -DCEGUI_BUILD_RENDERER_OGRE:BOOL="1" -DOGRE_H_PATH:PATH="..\Ogre\src\OgreMain\include" -DOGRE_H_BUILD_SETTINGS_PATH:PATH="..\Ogre\build\include" -DOGRE_LIB:FILEPATH="..\Ogre\build\lib\Release\OgreMain.lib" -DOGRE_LIB_DBG:FILEPATH="..\Ogre\build\lib\Debug\OgreMain_d.lib" -S src\ -B build\

set "source=.\cegui\include\CEGUI\Config.h"
powershell -Command "(gc %source%) -replace 'define CEGUI_OGRE_VERSION_MAJOR 0', 'define CEGUI_OGRE_VERSION_MAJOR 1' | Out-File -encoding ASCII %source%"
powershell -Command "(gc %source%) -replace 'define CEGUI_OGRE_VERSION_MINOR 0', 'define CEGUI_OGRE_VERSION_MINOR 12' | Out-File -encoding ASCII %source%"
powershell -Command "(gc %source%) -replace 'define CEGUI_OGRE_VERSION_PATCH 0', 'define CEGUI_OGRE_VERSION_PATCH 11' | Out-File -encoding ASCII %source%"


msbuild "cegui.sln" /p:configuration=Release /maxcpucount
msbuild "cegui.sln" /p:configuration=Debug /maxcpucount

cd ..
echo WIP: no hago nada de momento