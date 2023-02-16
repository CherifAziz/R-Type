@echo off

if exist ".\build" (
  rmdir /s /q .\build
  echo "Suppression du dossier build"
)

if exist ".\rtype-1.0-win32.zip" (
  del .\rtype-1.0-win32.zip
  echo "Suppression du fichier zip"
)