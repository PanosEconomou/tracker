cmake_minimum_required(VERSION 3.12)
project(test)

# Set C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(EXECUTABLE test)

# Find OpenCV package
find_package(OpenCV 4 REQUIRED)

# Include OpenCV headers
include_directories(${OpenCV_INCLUDE_DIRS})

# Add your source code file(s)
add_executable(${EXECUTABLE} test.cpp)

# Link against OpenCV libraries
target_link_libraries(${EXECUTABLE} ${OpenCV_LIBRARIES})
