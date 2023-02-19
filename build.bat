@echo off

call .\clean.bat

cmake -S . -B .\build\ -DCMAKE_TOOLCHAIN_FILE=%cd%\vcpkg\scripts\buildsystems\vcpkg.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build .\build\ --config Release
cd build
cpack --config CPackConfig.cmake -G ZIP
cd ..

if exist ".\rtype-setup.nsi" (
    del ".\rtype-setup.nsi"
)

if exist ".\R-Type-Setup.exe" (
    del ".\R-Type-Setup.exe"
)

echo Name "R-Type" > rtype-setup.nsi
echo OutFile "R-Type-Setup.exe" >> rtype-setup.nsi
echo Page Directory >> rtype-setup.nsi
echo Page InstFiles >> rtype-setup.nsi
echo Section >> rtype-setup.nsi
echo   SetOutPath "$INSTDIR\R-Type" >> rtype-setup.nsi
echo   File /r ".\build\Release\*.*" >> rtype-setup.nsi
echo SectionEnd >> rtype-setup.nsi
echo Section "adding assets">> rtype-setup.nsi
echo   SetOutPath "$INSTDIR\R-Type\assets" >> rtype-setup.nsi
echo   File ".\assets\" >> rtype-setup.nsi
echo SectionEnd >> rtype-setup.nsi

makensis rtype-setup.nsi

if not exist ".\build\Release\assets\" (
  mklink /j .\build\Release\assets\ .\assets\
)
move .\build\*.zip %cd%