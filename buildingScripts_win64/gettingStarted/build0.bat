@echo off

IF NOT EXIST ..\..\build mkdir ..\..\build
pushd ..\..\build

cl ..\src\01.gettingStarted\intro0\main.cpp ..\src\glad.c opengl32.lib glfw3.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /link /LIBPATH:"..\libs\lib-x64" glfw3_mt.lib

popd