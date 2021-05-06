@echo off
set COMPILEDIR=..\Src
set buildDir=.\build
set dllsMoveTo=.\..\..\..\bin

:: Creamos la carpeta build
mkdir %buildDir%
cd %buildDir%

:: Creamos el proyecto y lo compilamos en debug y release
cmake -DOGRE_BUILD_PLUGIN_BSP:BOOL="0" -DOGRE_BUILD_COMPONENT_PAGING:BOOL="0" -DOGRE_BUILD_COMPONENT_OVERLAY_IMGUI:BOOL="0" -DOGRE_BUILD_RTSHADERSYSTEM_SHADERS:BOOL="0" -DOGRE_INSTALL_TOOLS:BOOL="0" -DOGRE_BUILD_TOOLS:BOOL="0" -DOGRE_BUILD_COMPONENT_TERRAIN:BOOL="0" -DOGRE_BUILD_COMPONENT_OVERLAY:BOOL="0" -DOGRE_BUILD_PLUGIN_ASSIMP:BOOL="0" -DOGRE_BUILD_PLUGIN_DOT_SCENE:BOOL="0" -DOGRE_BUILD_PLUGIN_OCTREE:BOOL="0" -DOGRE_INSTALL_SAMPLES:BOOL="0" -DOGRE_BUILD_SAMPLES:BOOL="0" -DOGRE_BUILD_COMPONENT_BITES:BOOL="0" -DOGRE_BUILD_PLUGIN_PCZ:BOOL="0" -DOGRE_BUILD_COMPONENT_RTSHADERSYSTEM:BOOL="0" -DOGRE_BUILD_PLUGIN_PFX:BOOL="0" %COMPILEDIR%
msbuild "OGRE.sln" /p:configuration=Debug
msbuild "OGRE.sln" /p:configuration=Release

::Movemos las .dll a QuackEngineSol
MOVE .\bin\debug\OgreMain_d.dll %dllsMoveTo%
MOVE .\bin\release\OgreMain.dll %dllsMoveTo%

MOVE .\bin\debug\OgreRTShaderSystem_d.dll %dllsMoveTo%
MOVE .\bin\release\OgreRTShaderSystem.dll %dllsMoveTo%

MOVE .\bin\debug\Codec_STBI_d.dll %dllsMoveTo%
MOVE .\bin\release\Codec_STBI.dll %dllsMoveTo%

MOVE .\bin\debug\RenderSystem_Direct3D11_d.dll %dllsMoveTo%
MOVE .\bin\release\RenderSystem_Direct3D11.dll %dllsMoveTo%

MOVE .\bin\debug\RenderSystem_GL_d.dll %dllsMoveTo%
MOVE .\bin\release\RenderSystem_GL.dll %dllsMoveTo%

MOVE .\bin\debug\SDL2.dll %dllsMoveTo%
MOVE .\bin\release\zlib.dll %dllsMoveTo%

echo OGRE compilado
cd..