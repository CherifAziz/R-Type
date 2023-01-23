@echo off
net session >nul 2>&1
if %errorlevel% == 0 (
    echo Running as administrator
) else (
    echo Please run as administrator
    exit /b 1
)

ping -n 1 google.com >nul 2>&1
if %errorlevel% == 0 (
    echo Internet connection is available
) else (
    echo Please connect to the internet
    exit /b 1
)