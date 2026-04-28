@echo off
pushd "%~dp0\.."
call "%~dp0\..\vendor\bin\premake\premake5.exe" vs2022
popd
PAUSE