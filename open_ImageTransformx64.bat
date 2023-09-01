@echo off
set PATH=%PATH%;%~dp0Dependencies\opencv\build\x64\vc16\bin
start devenv "%~dp0ImageTransform.sln"
