@echo off
set buildDir=.\build
set dllsMoveTo=.\..\..\..\bin

:: Creamos la carpeta build
mkdir %buildDir%
cd %buildDir%

::Movemos las .dll a QuackEngineSol
XCOPY /y /s fmod.dll %dllsMoveTo%
XCOPY /y /s fmodL.dll %dllsMoveTo%

echo FMOD "compilado"
cd..