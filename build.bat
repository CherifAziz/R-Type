@echo off

if exist ".\build\Release" (
  rmdir /s /q .\build\Release
  echo "Suppression du dossier Release"
)

if exist ".\build_CPack_Packages" (
  rmdir /s /q .\build_CPack_Packages
  echo "Suppression des dossiers Release et _CPack_Packages"
)

cmake -S . -B .\build\ -DCMAKE_TOOLCHAIN_FILE=%cd%\vcpkg\scripts\buildsystems\vcpkg.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build .\build\ --config Release --target package
if not exist ".\build\Release\assets\" (
  mklink /j .\build\Release\assets\ .\assets\
)
move .\build\*.exe %cd%