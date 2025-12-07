@echo off
cd /d "%~dp0"
if not exist "Build" mkdir Build
if not exist "Bin" mkdir Bin
cd Build

cmake ../Sources -G "Visual Studio 17 2022" -A x64

if %ERRORLEVEL% EQU 0 (
    echo Successfully generating project.
) else (
    echo Error generating project.
    pause
    exit /b 1
)
