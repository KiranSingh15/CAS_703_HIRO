cmake_minimum_required(VERSION 3.10)
project(imageProcessor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_executable(imageProcessor ${SRC_FILES})
target_include_directories(imageProcessor PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(imageProcessor PRIVATE ${OpenCV_LIBS})

# Définition du répertoire de sortie
set(OUTPUT_DIR "${CMAKE_SOURCE_DIR}/output")
set(TEST_SCRIPT "${CMAKE_SOURCE_DIR}/run_tests.sh")
set(PYTHON_SCRIPT "${CMAKE_SOURCE_DIR}/plot_results.py")

# Ajout d'une cible de test
add_custom_target(test
    COMMAND ${CMAKE_COMMAND} -E make_directory ${OUTPUT_DIR}
    COMMAND bash ${TEST_SCRIPT} ${CMAKE_BINARY_DIR}/imageProcessor ${OUTPUT_DIR}/results.txt
    COMMAND python3 ${PYTHON_SCRIPT}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running performance tests and generating graph..."
)
