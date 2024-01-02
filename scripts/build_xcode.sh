#!/bin/bash

# Check if CMake is installed
if command -v cmake &> /dev/null; then
    # Get the CMake installation directory
    CMAKE_PATH=$(command -v cmake)
    echo "CMake found in $CMAKE_PATH, building Silly Engine..."
else
    echo "CMake is not installed. Downloading and installing CMake..."

    # Download the latest CMake release
    CMAKE_VERSION=$(curl -s https://api.github.com/repos/Kitware/CMake/releases/latest | grep '"tag_name":' | sed -E 's/.*"([^"]+)".*/\1/')
    wget "https://github.com/Kitware/CMake/releases/download/$CMAKE_VERSION/cmake-$CMAKE_VERSION-macos-universal.tar.gz" -P /tmp

    # Extract CMake
    tar -xzvf "/tmp/cmake-$CMAKE_VERSION-macos-universal.tar.gz" -C /tmp

    # Install CMake to /usr/local
    sudo mkdir -p /usr/local
    sudo mv "/tmp/cmake-$CMAKE_VERSION-macos-universal/CMake.app" /usr/local/

    # Add CMake to PATH in ~/.bash_profile
    echo 'export PATH="/usr/local/CMake.app/Contents/bin:$PATH"' >> ~/.bash_profile
    source ~/.bash_profile

    echo "CMake has been installed."
fi

# Change to your preferred directory
BUILD_DIR="../xcode_build"

# Create the build directory if it doesn't exist
mkdir -p "$BUILD_DIR"

# Generate Xcode project
cmake -G Xcode -S .. -B "$BUILD_DIR" -DIGG_IMGUI_TAG=v1.90-docking
