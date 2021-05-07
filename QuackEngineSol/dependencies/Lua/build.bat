@echo off
set dllsMoveTo=.\..\..\bin

::Movemos las .dll a QuackEngineSol
MOVE .\build\lua54.dll %dllsMoveTo%

echo Lua "compilado"