@echo off

if not "%PROCESSOR_ARCHITECTURE%" == "AMD64" (
  echo "Ce script doit être exécuté sur un système 64-bits."
  exit /b 1
)

git --version || (winget install -e --id Git.Git)

cmake --version || (winget install -e --id Kitware.CMake)

if not exist "%CD%\vcpkg" (
  git clone https://github.com/Microsoft/vcpkg.git
  cd vcpkg
  call .\bootstrap-vcpkg.bat
) else (
  cd vcpkgc
  git pull
  call .\bootstrap-vcpkg.bat
  cd ..
)

call vcpkg\vcpkg.exe install boost-serialization
call vcpkg\vcpkg.exe install boost-system
call vcpkg\vcpkg.exe install sfml
call vcpkg\vcpkg.exe integrate install
cmake -S . -B .\build\ -DCMAKE_TOOLCHAIN_FILE="%CD%\vcpkg\scripts\buildsystems\vcpkg.cmake" -DCMAKE_BUILD_TYPE=Release
cmake --build .\build\ --config Release
move assets build\Release\assets
mklink /H ".\rtype.lnk" "%CD%\build\Release\rtype.exe"
