cmake_minimum_required(VERSION 3.10)
project(imageProcessor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_executable(imageProcessor ${SRC_FILES})

target_include_directories(imageProcessor PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(imageProcessor PRIVATE ${OpenCV_LIBS})
