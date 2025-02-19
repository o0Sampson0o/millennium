cmake_minimum_required(VERSION 3.10)
project(millennium)

set(CMAKE_GENERATOR_PLATFORM Win32)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Enable static linking
set(SFML_STATIC TRUE)

# Manually specify SFML paths
set(SFML_INCLUDE_DIR "C:/SFML-2.5.1/include")
set(SFML_LIBRARY_DIR "C:/SFML-2.5.1/lib")

include_directories(${PROJECT_SOURCE_DIR}/src/include)
include_directories(${SFML_INCLUDE_DIR})
link_directories(${SFML_LIBRARY_DIR})

# Add the executable
add_executable(millennium src/main.cpp src/Engine.cpp)

# Link SFML libraries with full paths
target_link_libraries(millennium PRIVATE
    "C:/SFML-2.5.1/lib/sfml-graphics.lib"
    "C:/SFML-2.5.1/lib/sfml-window.lib"
    "C:/SFML-2.5.1/lib/sfml-system.lib"
)
