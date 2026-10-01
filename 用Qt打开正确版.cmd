@echo off
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%~dp0configure_qt_build.ps1"
if errorlevel 1 (
    pause
    exit /b 1
)
start "" "C:\Qt\Tools\QtCreator\bin\qtcreator.exe" "C:\Users\35452\Desktop\DigitRecnition\CMakeLists.txt"
