cmake_minimum_required(VERSION 3.0)
project(QMultiFile)

# find dependencies
find_package(Qt4 REQUIRED)
find_package(QuaZip REQUIRED)

# enable qt file handling
set(CMAKE_AUTOMOC ON)

# set source files
file(GLOB_RECURSE SRC_CPP "*.cpp")

# set build result
add_library(${PROJECT_NAME} SHARED ${SRC_CPP})

# set include directories
include_directories(
    ${QMultiFile_INCLUDE_DIR}
)


# set libraries
target_link_libraries(${PROJECT_NAME}
    Qt4::QtCore

    QuaZip
)

# set target properties
set_target_properties(${PROJECT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# set target properties
set_target_properties(${PROJECT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
