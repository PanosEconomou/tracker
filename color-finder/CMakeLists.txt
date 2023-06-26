cmake_minimum_required(VERSION 3.12)
project(colorFinder)

# Set C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(EXECUTABLE color-finder)

# Find OpenCV package
find_package(OpenCV 4 REQUIRED)

# Include OpenCV headers
include_directories(${OpenCV_INCLUDE_DIRS})

# Include the project headers
include_directories(${PROJECT_SOURCE_DIR}/include)

# Include the source and header files
file(GLOB sources "${PROJECT_SOURCE_DIR}/src/*.cpp")
file(GLOB headers "${PROJECT_SOURCE_DIR}/include/*.hpp")

# Add your source code file(s)
add_executable(${EXECUTABLE} main.cpp ${sources} ${headers})

# Link against OpenCV libraries
target_link_libraries(${EXECUTABLE} ${OpenCV_LIBRARIES})
