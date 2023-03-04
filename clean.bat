@echo off

if exist ".\build\Release" (
  rmdir /s /q .\build\Release
  echo "Suppression du dossier build"
)
if exist ".\build\_CPack_Packages" (
  rmdir /s /q .\build\_CPack_Packages
)