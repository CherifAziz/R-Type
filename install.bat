@echo off

if not "%PROCESSOR_ARCHITECTURE%" == "AMD64" (
  echo "Ce script doit être exécuté sur un système 64-bits."
  exit /b 1
)

git --version || (winget install -e --id Git.Git)

set CMAKE_INSTALLER_URL=github.com/Kitware/CMake/releases/download/v3.25.0-rc1/cmake-3.25.0-rc1-windows-x86_64.msi

curl -o cmake_install.msi %CMAKE_INSTALLER_URL%

msiexec /q /i cmake_install.msi

setx /M PATH "%PATH%;C:\Program Files\CMake\bin"

if not exist ".\vcpkg" (
  git clone https://github.com/Microsoft/vcpkg.git
  cd vcpkg
  call .\bootstrap-vcpkg.bat -disableMetrics
) else (
  cd vcpkg
  git pull
  call .\bootstrap-vcpkg.bat -disableMetrics
  cd ..
)

.\vcpkg\vcpkg.exe install boost-serialization
.\vcpkg\vcpkg.exe install boost-system
.\vcpkg\vcpkg.exe install sfml
.\vcpkg\vcpkg.exe integrate install
cmake -S . -B .\build\ -DCMAKE_TOOLCHAIN_FILE=".\vcpkg\scripts\buildsystems\vcpkg.cmake" -DCMAKE_BUILD_TYPE=Release
cmake --build .\build\ --config Release
move assets build\Release\assets
mklink /H ".\rtype.lnk" ".\build\Release\rtype.exe"
