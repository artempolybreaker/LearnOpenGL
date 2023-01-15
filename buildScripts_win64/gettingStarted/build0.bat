@echo off

IF %1.==. GOTO releaseBuild
IF %1==d GOTO developBuild

:releaseBuild
set @RootDir=..\..\..
IF NOT EXIST ..\..\build mkdir ..\..\build
pushd ..\..\src\01.gettingStarted\intro0
echo %cd%
cl /DRELEASE /std:c++17 main.cpp ..\..\glad.c /link opengl32.lib user32.lib gdi32.lib shell32.lib /LIBPATH:"%@RootDir%\libs\lib-x64" glfw3_mt.lib /out:..\..\..\build\gettingStarted01.exe
popd
GOTO End

:developBuild
pushd ..\..\src\01.gettingStarted\intro0
echo %cd%
cl /std:c++17 main.cpp ..\..\glad.c /link opengl32.lib user32.lib gdi32.lib shell32.lib /LIBPATH:"%@RootDir%\libs\lib-x64" glfw3_mt.lib
popd

:End