::@echo off
cls
set DIR=.\QuackEngineSol\dependencies\
set BAT=build.bat
set DEPS=.\Ogre\ .\Bullet\ .\Lua\ .\FMOD\ .\CEGUI\



cd %DIR%

(for %%a in (%DEPS%) do ( 
   cd %%a
   call %BAT%
   cd..
))


cd ..
::msbuild "QuackEngineSol.sln" /p:configuration=Debug
::msbuild "QuackEngineSol.sln" /p:configuration=Release
pause>nul
