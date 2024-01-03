# Silly/CMakeLists.txt

# Get all source files in the current directory
file(GLOB SILLY_SOURCES "src/*.cpp" "src/*.h" "src/ECS/*.cpp" "src/ECS/*.h" "src/components/*.cpp" "src/components/*.h" "${CMAKE_SOURCE_DIR}/Sandbox/*.cpp" "${CMAKE_SOURCE_DIR}/Sandbox/*.h")

include(FetchContent)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

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
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb_image
    ${CMAKE_SOURCE_DIR}/Sandbox
    # /opt/homebrew/Cellar
)

add_custom_target(copy_res_directory ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets" "${CMAKE_CURRENT_BINARY_DIR}/assets"
        COMMENT "Copy assets directory to build tree"
        VERBATIM)



# find_package(glfw3 REQUIRED)
if(APPLE)
    set(ASSIMP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vendor/osx/assimp")
    
    target_include_directories(Silly PUBLIC ${ASSIMP_DIR}/include ${ASSIMP_DIR}/build/include)
    
    target_link_libraries(Silly PUBLIC ${ASSIMP_DIR}/build/bin/libassimp.5.3.0.dylib)
endif()

link_directories(${CMAKE_SOURCE_DIR}/Silly/vendor/windows)

find_package(ASSIMP REQUIRED)
message(STATUS "found assimp in" ${ASSIMP_INCLUDE_DIR})

if(WIN32)
    # target_include_directories(Silly PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendor/windows/assimp)
    
    # target_link_libraries(Silly PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendor/windows/assimp/lib/assimp-vc143-mtd.lib)

    set(LIBS assimp)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    target_include_directories(Silly PUBLIC ${ASSIMP_INCLUDE_DIR})
    configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/windows/assimp/config.h.in
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/windows/assimp/config.h
    )
endif()

target_link_libraries(Silly PUBLIC ${LIBS} glfw imgui glad glm)
