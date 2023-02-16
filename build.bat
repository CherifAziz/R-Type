@echo off

@REM if exist ".\build" (
@REM   rmdir /s /q .\build
@REM   echo "Suppression du dossier build"
@REM )

if exist ".\rtype-1.0-win32.zip" (
  del .\rtype-1.0-win32.zip
  echo "Suppression du fichier zip"
)

cmake -S . -B .\build\ -DCMAKE_TOOLCHAIN_FILE=%cd%\vcpkg\scripts\buildsystems\vcpkg.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build .\build\ --config Release
cd build
cpack --config CPackConfig.cmake -G ZIP
cd ..
if not exist ".\build\Release\assets\" (
  mklink /j .\build\Release\assets\ .\assets\
)
move .\build\*.zip %cd%