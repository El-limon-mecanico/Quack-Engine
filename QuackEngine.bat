::@echo off
cls
set DIR=.\QuackEngineSol\dependencies\
set BAT=build.bat

set OGRE=.\Ogre\ 
set BULLET=.\Bullet\
set CEGUI=.\CEGUI\

cd %DIR%


cd %OGRE%
call %BAT%
cd ..


cd %BULLET%
call %BAT%
cd ..

cd %CEGUI%
call %BAT%
cd ..


cd ..
msbuild "QuackEngineSol.sln" /p:configuration=Debug
msbuild "QuackEngineSol.sln" /p:configuration=Release
pause>nul
