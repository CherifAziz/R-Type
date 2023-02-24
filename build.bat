@echo off

@REM call .\clean.bat

cmake -S . -B .\build\ -DCMAKE_TOOLCHAIN_FILE=%cd%\vcpkg\scripts\buildsystems\vcpkg.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build .\build\ --config Release
cmake --build .\build\ --target package
@REM cd build
@REM cpack --config CPackConfig.cmake -G ZIP
@REM cd ..
if not exist ".\build\Release\assets\" (
  mklink /j .\build\Release\assets\ .\assets\
)
move .\build\*.exe %cd%