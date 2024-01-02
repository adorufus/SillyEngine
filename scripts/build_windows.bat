@echo off

:: Check if CMake is installed
where cmake >nul 2>nul
if %ERRORLEVEL% equ 0 echo CMake found in %PATH%, building Silly Engine...
else (
    echo CMake is not installed. Downloading and installing CMake...

    :: Check PowerShell version
    powershell -Command "$PSVersionTable.PSVersion.Major" > temp_version.txt
    set /p ps_version=<temp_version.txt
    del temp_version.txt

    for /f "delims=" %%v in ('powershell -command "(Invoke-WebRequest -Uri 'https://api.github.com/repos/Kitware/CMake/releases/latest').Content | ConvertFrom-Json | Select -ExpandProperty tag_name"') do set "CMAKE_VERSION=%%v"

    if %ps_version% geq 7 (
        pwsh -Command "(New-Object System.Net.WebClient).DownloadFile('https://github.com/Kitware/CMake/releases/latest/download/cmake-%CMAKE_VERSION%-windows-x86_64.zip', 'C:\Temp\cmake.zip')"
        pwsh -Command "Expand-Archive -Path 'C:\Temp\cmake.zip' -DestinationPath 'C:\Temp\CMake'"
    ) else (
        powershell -Command "(New-Object System.Net.WebClient).DownloadFile('https://github.com/Kitware/CMake/releases/latest/download/cmake-%CMAKE_VERSION%-windows-x86_64.zip', 'C:\Temp\cmake.zip')"
        powershell -Command "Expand-Archive -Path 'C:\Temp\cmake.zip' -DestinationPath 'C:\Temp\CMake'"
    )

    :: Add CMake to PATH in Environment Variables
    setx PATH "%PATH%;C:\Temp\CMake\cmake-3.22.0-windows-x86_64\bin" -m

    echo CMake has been installed.
)

:: Create the build directory if it doesn't exist
mkdir ..\windows_build 2>nul

:: Generate Visual Studio 2017 2022 project
cmake -G "Visual Studio 17 2022" -S .. -B ../windows_build

echo Visual studio 2022 project generated!

echo Building the project for the first time, this might take a while.....
cmake --build ../windows_build

echo Building completed!

echo Copying dynamic library....

:: Check if the file exists before copying
if exist "..\windows_build\Silliter\Debug\" (
    :: Copy the file
    copy "..\Silly\vendor\windows\assimp\lib\assimp-vc143-mtd.lib" "..\windows_build\Silliter\Debug\"
) else (
    echo Destination directory not found.
)
