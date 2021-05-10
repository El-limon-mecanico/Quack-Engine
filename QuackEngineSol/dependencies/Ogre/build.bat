@echo off
set COMPILEDIR=..\Src
set buildDir=.\build
set dllsMoveTo=.\..\..\..\bin

:: Creamos la carpeta build
mkdir %buildDir%
cd %buildDir%

:: Creamos el proyecto y lo compilamos en debug y release
cmake -DOGRE_BUILD_RTSHADERSYSTEM_SHADERS:BOOL="1" -DOGRE_INSTALL_SAMPLES:BOOL="0" -DOGRE_BUILD_SAMPLES:BOOL="0" -DOGRE_BUILD_COMPONENT_BITES:BOOL="0" -DOGRE_BUILD_COMPONENT_RTSHADERSYSTEM:BOOL="1" %COMPILEDIR%
msbuild "OGRE.sln" /p:configuration=Debug
msbuild "OGRE.sln" /p:configuration=Release

::Movemos las .dll a QuackEngineSol
XCOPY /y /s .\bin\debug\OgreMain_d.dll %dllsMoveTo%
XCOPY /y /s .\bin\release\OgreMain.dll %dllsMoveTo%

XCOPY /y /s .\bin\debug\OgreRTShaderSystem_d.dll %dllsMoveTo%
XCOPY /y /s .\bin\release\OgreRTShaderSystem.dll %dllsMoveTo%

XCOPY /y /s .\bin\debug\Codec_STBI_d.dll %dllsMoveTo%
XCOPY /y /s .\bin\release\Codec_STBI.dll %dllsMoveTo%

XCOPY /y /s .\bin\debug\RenderSystem_Direct3D11_d.dll %dllsMoveTo%
XCOPY /y /s .\bin\release\RenderSystem_Direct3D11.dll %dllsMoveTo%

XCOPY /y /s .\bin\debug\RenderSystem_GL_d.dll %dllsMoveTo%
XCOPY /y /s .\bin\release\RenderSystem_GL.dll %dllsMoveTo%

XCOPY /y /s .\bin\debug\SDL2.dll %dllsMoveTo%
XCOPY /y /s .\bin\release\zlib.dll %dllsMoveTo%

echo OGRE compilado
cd..