cmake_minimum_required(VERSION 3.13)

project(SillyEngine)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Include Core directory
add_subdirectory(Silly)

# Include Main directory
add_subdirectory(Sillitor)
