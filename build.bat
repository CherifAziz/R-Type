@echo off

call .\clean.bat

cmake -S . -B .\build\ -DCMAKE_TOOLCHAIN_FILE=%cd%\vcpkg\scripts\buildsystems\vcpkg.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build .\build\ --config Release --target package
if not exist ".\build\Release\assets\" (
  mklink /j .\build\Release\assets\ .\assets\
)
mv .\build\*.exe %cd%