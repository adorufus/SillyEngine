cmake_minimum_required(VERSION 3.20)

project(SillyEngine)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

# Set the output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/sillyengine")

# Add source files
file(GLOB_RECURSE SOURCE_FILES "*.cpp")

# Add the Core project source files
file(GLOB_RECURSE CORE_SOURCE_FILES "core/*.cpp")
file(GLOB_RECURSE CORE_HEADER_FILES "core/*.h" "core/*.hpp")

# find_package(freetype REQUIRED)

# Add executable target
add_executable(SillyEngine ${SOURCE_FILES} ${CORE_SOURCE_FILES} ${CORE_HEADER_FILES})

add_library(STB_IMAGE "stb_image.cpp")
set(LIBS ${LIBS} STB_IMAGE)

add_library(GLAD "glad.c")
set(LIBS ${LIBS} GLAD)


# Add include directories
target_include_directories(SillyEngine PRIVATE
    "${CMAKE_SOURCE_DIR}/src"
    "${CMAKE_SOURCE_DIR}/core"
    "${CMAKE_SOURCE_DIR}/includes"
    "${CMAKE_SOURCE_DIR}/includes/imgui"
    "${CMAKE_SOURCE_DIR}/includes/imgui/backends"
)

# Add frameworks
target_link_libraries(SillyEngine PRIVATE
    "-framework CoreGraphics"
    "-framework CoreFoundation"
    "-framework CoreVideo"
    "-framework IOKit"
    "-framework Cocoa"
    "-framework OpenGL"
)


find_package(glm REQUIRED)
find_package(Freetype REQUIRED)
# find_package(imgui REQUIRED)

target_link_libraries(SillyEngine PRIVATE
        # glad::glad
        glm::glm
        # imgui::imgui
)

# Link with libraries from the libraries directory
target_link_libraries(SillyEngine PRIVATE
    "${CMAKE_SOURCE_DIR}/libraries/libglfw.3.3.dylib"
    "${CMAKE_SOURCE_DIR}/libraries/libassimp.5.3.0.dylib"
    # Add other libraries here as needed
)

# Set VS Code configurations
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
