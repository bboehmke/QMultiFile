cmake_minimum_required(VERSION 3.0)
project(test_app)

# find dependencies
find_package(Qt4 REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# set source files
file(GLOB_RECURSE SRC_CPP "*.cpp")

# set build result
add_executable(${PROJECT_NAME} ${SRC_CPP})

# set include directories
include_directories(
    "../"
)

# set libraries
target_link_libraries(${PROJECT_NAME}
    Qt4::QtCore
    Qt4::QtTest

    QMultiFile
)

# set target properties
set_target_properties(${PROJECT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
add_test(${PROJECT_NAME} ${PROJECT_NAME})