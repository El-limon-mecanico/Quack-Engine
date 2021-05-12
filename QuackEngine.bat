@echo off
cls
set BAT=build.bat

cd .\QuackEngineSol\dependencies\

cd .\Ogre\
call %BAT%

cd ..\Bullet\
call %BAT%

cd ..\Lua\
call %BAT%

cd ..\FMOD\
call %BAT%

cd ..\CEGUI\
call %BAT%
cd ..\..

msbuild "QuackEngineSol.sln" /p:configuration=Debug
msbuild "QuackEngineSol.sln" /p:configuration=Release
pause
