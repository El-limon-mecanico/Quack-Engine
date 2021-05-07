@echo off
set COMPILEDIR=..\Src
set buildDir=.\build
set dllsMoveTo=.\..\..\..\bin

:: Creamos la carpeta build
mkdir %buildDir%
cd %buildDir%

:: Creamos el proyecto y lo compilamos en debug y release
cmake -DBUILD_CPU_DEMOS:BOOL="0" -DBUILD_BULLET2_DEMOS:BOOL="0" -DBUILD_OPENGL3_DEMOS:BOOL="0" -DUSE_MSVC_RUNTIME_LIBRARY_DLL:BOOL="1" %COMPILEDIR%
msbuild "BULLET_PHYSICS.sln" -p:configuration=Debug /maxcpucount
msbuild "BULLET_PHYSICS.sln" -p:configuration=Release /maxcpucount


echo BULLET compilado
cd ..