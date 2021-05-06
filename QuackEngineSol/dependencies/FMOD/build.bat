@echo off
set buildDir=.\build
set dllsMoveTo=.\..\..\..\bin

:: Creamos la carpeta build
mkdir %buildDir%
cd %buildDir%

::Movemos las .dll a QuackEngineSol
MOVE fmod.dll %dllsMoveTo%
MOVE fmodL.dll %dllsMoveTo%

echo FMOD "compilado"
cd..