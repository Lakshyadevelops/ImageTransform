@echo off
set PATH=%PATH%;%~dp0Dependencies\opencv\build\x64\vc16\bin
set PATH=%PATH%;%~dp0Dependencies\TensorRT-8.6.1.6\lib
set CUDA_MODULE_LOADING=LAZY
start devenv "%~dp0ImageTransform.sln"
