@echo off

powershell -Command "Set-ExecutionPolicy Bypass -Scope Process -Force; iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))"

if not "%PROCESSOR_ARCHITECTURE%" == "AMD64" (
    echo "Ce script doit être exécuté sur un système 64-bits."
    exit /b 1
)

ping -n 1 google.com | find "TTL=" > nul
if %errorlevel% neq 0 (
    echo "Aucune connexion internet détectée. Vérifiez votre connexion et réessayez."
    exit /b 1
)

choco install vcpkg -y

choco install cmake -y

cd %cd%\vcpkg
git pull
vcpkg.exe bootstrap -disableMetrics
cd ..
vcpkg.exe install sfml
vcpkg.exe install boost-asio
vcpkg.exe upgrade

if not exist "C:\ProgramData\vcpkg\vcpkg.path.txt" (
    echo "" > C:\ProgramData\vcpkg\vcpkg.path.txt
)
vcpkg.exe integrate install

if exist "r-type_client.exe" (
    del "r-type_client.exe"
)
if exist "r-type_server.exe" (
    del "r-type_server.exe"
)
if exist "build\r-type_client.exe" (
    del "build\r-type_client.exe"
)
if exist "build\r-type_server.exe" (
    del "build\r-type_server.exe"
)

mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=%cd%\vcpkg\scripts\buildsystems\vcpkg.cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release

move "r-type_client.exe" ..
move "r-type_server.exe" ..