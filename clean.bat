@echo off

if exist ".\build" (
  rmdir /s /q .\build
  echo "Suppression du dossier build"
)