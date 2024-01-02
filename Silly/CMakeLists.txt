# Silly/CMakeLists.txt

# Get all source files in the current directory
file(GLOB SILLY_SOURCES "src/*.cpp" "src/*.h")

include(FetchContent)

# Define the SILLY library using the detected source files
add_library(Silly STATIC ${SILLY_SOURCES})

FetchContent_Declare(
        imgui-glfw-glad-glm
        GIT_REPOSITORY https://github.com/cmmw/imgui-glfw-glad-glm.git
)
FetchContent_MakeAvailable(imgui-glfw-glad-glm)

# Include directories for Core (if needed)
target_include_directories(Silly PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/components
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor
    # /opt/homebrew/Cellar
)

# find_package(glfw3 REQUIRED)
target_link_libraries(Silly PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendor/assimp/lib/libassimp.5.3.0.dylib)
target_link_libraries(Silly PUBLIC glfw imgui glad glm)
