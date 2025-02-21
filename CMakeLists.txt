cmake_minimum_required(VERSION 3.10)
project(millennium)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

# Use MinGW toolchain (if applicable)
if(MSYS)
set(CMAKE_CXX_COMPILER "x86_64-w64-mingw32-g++")
set(CMAKE_C_COMPILER "x86_64-w64-mingw32-gcc")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif()

# Find SFML package
find_package(SFML 2.6 REQUIRED graphics window system)

# Include directories for the project and SFML
include_directories(${PROJECT_SOURCE_DIR}/src/include)

# Add the executable and specify source files
add_executable(millennium
    src/main.cpp
    src/Engine.cpp
    src/Particle.cpp
    src/Logger.cpp
    src/QuadTree.cpp
)

# Link SFML libraries
target_link_libraries(millennium sfml-graphics sfml-window sfml-system)

# Include SFML headers
target_include_directories(millennium PRIVATE ${SFML_INCLUDE_DIR})

# Optional: Set library search directories if SFML isn't found automatically
# link_directories(${SFML_LIBRARY_DIR})