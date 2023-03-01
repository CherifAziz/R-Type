@echo off

if exist ".\build\Release" (
  rmdir /s /q .\build\Release
  echo "Suppression du dossier Release"
)
if exist ".\build\_CPack_Packages" (
  rmdir /s /q .\build\_CPack_Packages
  echo "Suppression des dossiers Release et _CPack_Packages"
)