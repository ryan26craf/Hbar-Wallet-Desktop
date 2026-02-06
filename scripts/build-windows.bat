@echo off
echo ========================================
echo HBAR Wallet Desktop - Windows Build
echo ========================================
echo.

REM Check for CMake
where cmake >nul 2>nul
if %ERRORLEVEL% NEQ 0 (
    echo Error: CMake not found! Please install CMake first.
    pause
    exit /b 1
)

REM Create build directory
if not exist build mkdir build
cd build

echo Configuring project...
cmake .. -G "Visual Studio 17 2022" -A x64 -DCMAKE_BUILD_TYPE=Release

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo Configuration failed!
    pause
    exit /b 1
)

echo.
echo Building project...
cmake --build . --config Release --parallel

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo Build failed!
    pause
    exit /b 1
)

echo.
echo ========================================
echo Build completed successfully!
echo ========================================
echo.
echo Binary location: build\bin\Release\HbarWalletDesktop.exe
echo.
pause
