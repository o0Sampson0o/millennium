cmake_minimum_required(VERSION 3.10)
project(millennium)

# Specify the platform for the generator
set(CMAKE_GENERATOR_PLATFORM Win32)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)

# Enable static linking for SFML
set(SFML_STATIC TRUE)

# Manually specify SFML include and library directories
set(SFML_INCLUDE_DIR "C:/SFML-2.5.1/include")
set(SFML_LIBRARY_DIR "C:/SFML-2.5.1/lib")

# Include directories for the project and SFML
include_directories(${PROJECT_SOURCE_DIR}/src/include)
include_directories(${SFML_INCLUDE_DIR})

# Link directories for SFML libraries
link_directories(${SFML_LIBRARY_DIR})

# Add the executable and specify source files
add_executable(millennium
    src/main.cpp
    src/Engine.cpp
    src/Particle.cpp
    src/Logger.cpp
)

# Link SFML libraries with full paths
target_link_libraries(millennium PRIVATE
    "C:/SFML-2.5.1/lib/sfml-graphics.lib"
    "C:/SFML-2.5.1/lib/sfml-window.lib"
    "C:/SFML-2.5.1/lib/sfml-system.lib"
)
