cmake_minimum_required(VERSION 3.0)
project(QMultiFile)

# disable in source build
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES  ON)

# print message if in source build detected
if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(SEND_ERROR "In-source builds are not allowed.")
endif ()

# add additional find modules
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# set sub projects
add_subdirectory(qmultifile)
add_subdirectory(test_app)
