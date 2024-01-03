cmake_minimum_required(VERSION 3.13)

project(SillyEngine)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

configure_file(configuration/root_directory.h.in configuration/root_directory.h)

configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/configuration/assets_directory.h.in
        ${CMAKE_CURRENT_BINARY_DIR}/configuration/assets_directory.h
)

include_directories(${CMAKE_BINARY_DIR}/configuration)

# Include Core directory
add_subdirectory(Silly)

# Include Main directory
add_subdirectory(Sillitor)
