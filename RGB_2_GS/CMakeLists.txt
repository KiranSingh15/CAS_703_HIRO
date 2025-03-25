cmake_minimum_required(VERSION 3.10)
project(RGB_2_GS)

# Use the next time only if the system variable of OpenCV_DIR is not set
# set(OpenCV_DIR C:/Applications/OpenCV/Version_4_11_0/opencv/build)

# Find Open CV Package
find_package(OpenCV REQUIRED)

#include directories from OpenCV package
include_directories(${OpenCV_INCLUDE_DIRS})

# create an executable
add_executable(${PROJECT_NAME} Main.cpp conv2GS.cpp gKernel.cpp laplacianFilter.cpp Slave.cpp Master.cpp timer.cpp imageOperations.cpp)

# link OpenCV libraries
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})