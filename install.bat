@echo off

@REM if not "%PROCESSOR_ARCHITECTURE%" == "AMD64" (
@REM   echo "Ce script doit être exécuté sur un système 64-bits."
@REM   exit /b 1
@REM )

git --version || (winget install -e --id Git.Git)

@REM powershell.exe -Command "Set-ExecutionPolicy Bypass -Scope Process -Force"
@REM powershell.exe -Command "[System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072"
@REM powershell.exe -Command "((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))"
@REM powershell.exe -Command "iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))"

call RefreshEnv.cmd

cmake --version || (choco install cmake --installargs 'ADD_CMAKE_TO_PATH=System')

if not exist ".\vcpkg" (
  git clone https://github.com/Microsoft/vcpkg.git
  cd vcpkg
  call .\bootstrap-vcpkg.bat -disableMetrics
  cd ..
) else (
  cd vcpkg
  git pull
  call .\bootstrap-vcpkg.bat -disableMetrics
  cd ..
)

call RefreshEnv.cmd

.\vcpkg\vcpkg.exe install boost-serialization:x64-windows
.\vcpkg\vcpkg.exe install boost-system:x64-windows
.\vcpkg\vcpkg.exe install boost-asio:x64-windows
.\vcpkg\vcpkg.exe install boost-uuid:x64-windows
.\vcpkg\vcpkg.exe install sfml:x64-windows
.\vcpkg\vcpkg.exe integrate install

echo "executing build.bat"
call ".\build.bat"