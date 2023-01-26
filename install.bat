@REM @echo off

@REM if not "%PROCESSOR_ARCHITECTURE%" == "AMD64" (
@REM   echo "Ce script doit être exécuté sur un système 64-bits."
@REM   exit /b 1
@REM )

@REM git --version || (winget install -e --id Git.Git)

@REM cmake --version || (winget install -e --id Kitware.CMake)

@REM rem if not exist "%CD%\vcpkg" (
@REM rem   echo putepute
@REM rem   git clone https://github.com/Microsoft/vcpkg.git
@REM rem   cd vcpkg
@REM rem   .\bootstrap-vcpkg.bat
@REM rem ) else (
@REM rem   cd vcpkgc
@REM rem   git pull
@REM rem   call .\bootstrap-vcpkg.bat
@REM rem   cd ..
@REM rem )

@REM call vcpkg\vcpkg.exe install boost-asio
@REM call vcpkg\vcpkg.exe install sfml
@REM call vcpkg\vcpkg.exe integrate install
cmake -S . -B .\build\ -DCMAKE_TOOLCHAIN_FILE="%CD%\vcpkg\scripts\buildsystems\vcpkg.cmake" -DCMAKE_BUILD_TYPE=Release
cmake --build .\build\ --config Release
move assets build\Release\assets
mklink /H ".\r-type_client.lnk" "%CD%\build\Release\r-type_client.exe"
mklink /H ".\r-type_server.lnk" "%CD%\build\Release\r-type_server.exe"
