@echo off
for /f "delims=" %%v in ('powershell -command "(Invoke-WebRequest -Uri 'https://api.github.com/repos/Kitware/CMake/releases/latest').Content | ConvertFrom-Json | Select -ExpandProperty tag_name"') do set "CMAKE_VERSION=%%v"

set "CMAKE_VERSION=%CMAKE_VERSION:~1%"

:: Check if CMake is installed
where cmake >nul 2>nul
if %ERRORLEVEL% equ 0 echo CMake found, building Silly Engine... & goto generate
if %ERRORLEVEL% geq 1 goto install

:install
echo CMake is not installed. Downloading and installing CMake...

:: Check PowerShell version
powershell -Command "$PSVersionTable.PSVersion.Major" > temp_version.txt
set /p ps_version=<temp_version.txt
del temp_version.txt



echo found online cmake version %CMAKE_VERSION%

if %ps_version% geq 7 (
    pwsh -Command "(New-Object System.Net.WebClient).DownloadFile('https://github.com/Kitware/CMake/releases/download/v%CMAKE_VERSION%/cmake-%CMAKE_VERSION%-windows-x86_64.zip', 'C:\Temp\cmake.zip')"
    pwsh -Command "Expand-Archive -Path 'C:\Temp\cmake.zip' -DestinationPath 'C:\Temp\CMake'"
) else (
    powershell -Command "(New-Object System.Net.WebClient).DownloadFile('https://github.com/Kitware/CMake/releases/download/v%CMAKE_VERSION%/cmake-%CMAKE_VERSION%-windows-x86_64.zip', 'C:\Temp\cmake.zip')"
    powershell -Command "Expand-Archive -Path 'C:\Temp\cmake.zip' -DestinationPath 'C:\Temp\CMake'"
)

echo %ERRORLEVEL%

if %ERRORLEVEL% equ 0 goto addtopath
if %ERRORLEVEL% geq 1 echo failed to download cmake & exit /b 1


:addtopath
:: Add CMake to PATH in Environment Variables
set cmake_path=C:\Temp\CMake\cmake-%CMAKE_VERSION%-windows-x86_64\bin
set parent_dir=%cmake_path%\..\..

echo %cmake_path%

move %cmake_path% %parent_dir%

set final_cmake_path=C:\Temp\CMake\bin

setx CMAKE_ROOT "%final_cmake_path%" /M

set PATH=%PATH%;%final_cmake_path%

echo CMake has been installed.

goto generate

:generate

:: Create the build directory if it doesn't exist
mkdir ..\windows_build 2>nul

:: Generate Visual Studio 2017 2022 project
cmake -G "Visual Studio 17 2022" -S .. -B ../windows_build -DIGG_IMGUI_TAG=v1.90-docking

echo Visual Studio 2022 project generated!

echo Building the project for the first time, this might take a while.....
cmake --build ../windows_build

echo Building completed!

echo Copying dynamic library....

:: Check if the file exists before copying
if exist "..\windows_build\Sillitor\Debug\" (
    :: Copy the file
    copy "..\Silly\vendor\windows\assimp\lib\assimp-vc143-mtd.dll" "..\windows_build\Sillitor\Debug\"
) else (
    echo Destination directory not found.
)
