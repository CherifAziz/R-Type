@echo off

winget -v || (
  echo "please get winget and retry"
  exit 0
)

git --version || (winget install -e --id Git.Git)

choco --version || (
  powershell -Command "Set-ExecutionPolicy AllSigned"
  powershell -Command "Set-ExecutionPolicy Bypass -Scope Process -Force"
  powershell -Command "[System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072"
  powershell -Command "((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))"
  powershell -Command "iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))"
)

call RefreshEnv.cmd

choco upgrade chocolatey -y

call RefreshEnv.cmd

cmake --version || (choco install cmake -y)

makensis /version || (choco install nsis -y)

.\vcpkg\vcpkg.exe --version || if not exist ".\vcpkg" (
  git clone https://github.com/Microsoft/vcpkg.git
  cd vcpkg
  call .\bootstrap-vcpkg.bat -disableMetrics
  cd ..
) else (
  rmdir /s /q .\vcpkg
  git clone https://github.com/Microsoft/vcpkg.git
  cd vcpkg
  call .\bootstrap-vcpkg.bat -disableMetrics
  cd ..
)

call RefreshEnv.cmd


.\vcpkg\vcpkg.exe install boost-exception
.\vcpkg\vcpkg.exe install boost-serialization:x64-windows
.\vcpkg\vcpkg.exe install boost-system:x64-windows
.\vcpkg\vcpkg.exe install boost-asio:x64-windows
.\vcpkg\vcpkg.exe install boost-uuid:x64-windows
.\vcpkg\vcpkg.exe install sfml:x64-windows
.\vcpkg\vcpkg.exe integrate install

echo "executing build.bat"
call ".\build.bat"