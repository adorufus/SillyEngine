# Silly/CMakeLists.txt

# Get all source files in the current directory
file(GLOB SILLY_SOURCES "src/*.cpp" "src/*.h" "src/components/*.cpp" "src/components/*.h" "${CMAKE_SOURCE_DIR}/Sandbox/*.cpp" "${CMAKE_SOURCE_DIR}/Sandbox/*.h")

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
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb_image
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor
    ${CMAKE_SOURCE_DIR}/Sandbox
    # /opt/homebrew/Cellar
)



# find_package(glfw3 REQUIRED)
if(APPLE)
    set(ASSIMP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vendor/osx/assimp")
    
    target_include_directories(Silly PUBLIC ${ASSIMP_DIR}/include ${ASSIMP_DIR}/build/include)
    
    target_link_libraries(Silly PUBLIC ${ASSIMP_DIR}/build/bin/libassimp.5.3.0.dylib)
endif()

if(WIN32)
    target_include_directories(Silly PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendor/windows/assimp)
    
    target_link_libraries(Silly PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendor/windows/assimp/lib/assimp-vc143-mtd.lib)
endif()

target_link_libraries(Silly PUBLIC glfw imgui glad glm)
