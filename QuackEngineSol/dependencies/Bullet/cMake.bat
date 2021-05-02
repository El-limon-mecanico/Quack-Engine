::@echo off
set COMPILEDIR=..\Src
set buildDir=.\build
set dllsMoveTo=.\..\..\..\bin

:: Creamos la carpeta build
mkdir %buildDir%
cd %buildDir%

:: Creamos el proyecto y lo compilamos en debug y release
cmake %COMPILEDIR% -A Win32
msbuild "BULLET_PHYSICS.sln" -p:configuration=Debug -p:Platform=Win32
msbuild "BULLET_PHYSICS.sln" -p:configuration=Release -p:Platform=Win32

::Movemos las .dll a QuackEngineSol





echo BULLET compilado
pause