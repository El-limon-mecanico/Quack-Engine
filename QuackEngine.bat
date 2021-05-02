::@echo off
cls
set DIR=.\QuackEngineSol\dependencies\
set BAT=cMake.bat

set OGRE=.\Ogre\ 
set BULLET=.\Bullet\

cd %DIR%


cd %OGRE%
call %BAT%
cd ..\..
pause

cd %BULLET%

pause
call %BAT%
cd ..\..

pause
