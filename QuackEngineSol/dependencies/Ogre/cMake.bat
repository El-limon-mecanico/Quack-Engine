::@echo off
set COMPILEDIR=..\Src
set buildDir=.\build
set dllsMoveTo=.\..\..\..\bin

:: Creamos la carpeta build
mkdir %buildDir%
cd %buildDir%

:: Creamos el proyecto y lo compilamos en debug y release
cmake %COMPILEDIR% -A Win32
msbuild "OGRE.sln" -p:configuration=Debug -p:Platform=Win32
msbuild "OGRE.sln" -p:configuration=Release -p:Platform=Win32

::Movemos las .dll a QuackEngineSol
MOVE .\bin\debug\OgreMain_d.dll dllsMoveTo
MOVE .\bin\debug\SDL2.dll dllsMoveTo
MOVE .\bin\debug\OgreRTShaderSystem_d.dll dllsMoveTo
RenderSystem_GL_d
MOVE .\bin\release\OgreMain.dll dllsMoveTo
MOVE .\bin\release\zlib.dll dllsMoveTo

echo OGRE compilado
pause