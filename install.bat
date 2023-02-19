@echo off

git --version || (winget install -e --id Git.Git)

Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1%27))

call RefreshEnv.cmd

cmake --version || (choco install cmake --installargs 'ADD_CMAKE_TO_PATH=System')

makensis --version || choco install nsis -Y

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

call RefreshEnv.cmd

.\vcpkg\vcpkg.exe install boost-serialization
.\vcpkg\vcpkg.exe install boost-system
.\vcpkg\vcpkg.exe install sfml:x64-windows
.\vcpkg\vcpkg.exe integrate install

echo "executing build.bat"
call ".\build.bat"