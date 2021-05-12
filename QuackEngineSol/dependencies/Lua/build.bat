@echo off
set dllsMoveTo=.\..\..\bin

::Movemos las .dll a QuackEngineSol
XCOPY /y /s .\build\lua54.dll %dllsMoveTo%

echo Lua "compilado"