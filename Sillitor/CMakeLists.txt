# Sillitor/CMakeLists.txt

# Define the Main executable
add_executable(Sillitor
    src/main.cpp
    # Add all your Main source files here
)

# Link the Main executable with Core library
target_link_libraries(Sillitor PRIVATE Silly)

if(WIN32)
    target_link_directories(Sillitor PRIVATE ${CMAKE_SOURCE_DIR}/Silly/vendor/windows/assimp/lib)
    target_link_libraries(Sillitor PRIVATE assimp.lib)
endif()
