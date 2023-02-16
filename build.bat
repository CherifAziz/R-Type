@echo off

call .\clean.bat

cmake -S . -B .\build\ -DCMAKE_TOOLCHAIN_FILE=%cd%\vcpkg\scripts\buildsystems\vcpkg.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build .\build\ --config Release
cd build
cpack --config CPackConfig.cmake -G ZIP
cd ..
if not exist ".\build\Release\assets\" (
  mklink /j .\build\Release\assets\ .\assets\
)
move .\build\*.zip %cd%