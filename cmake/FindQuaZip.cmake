# QuaZip_FOUND               - QuaZip library was found
# QuaZip_INCLUDE_DIRS        - Path to QuaZip include dir
# QuaZip_LIBRARIES           - List of QuaZip libraries

# Set ``QuaZip_ROOT_DIR`` to the root directory of an QuaZip installation.

set(_QuaZip_ROOT_HINTS
    ${QuaZip_ROOT_DIR}
    ENV QuaZip_ROOT_DIR
)

find_path(QuaZip_INCLUDE_DIR
    NAMES
        quazip/quazip.h
    HINTS
        ${_QuaZip_ROOT_HINTS}
    PATH_SUFFIXES
        include
)

if (WIN32)
    FIND_LIBRARY(QuaZip_LIBRARY
        NAMES libquazip.dll
        HINTS ${_QuaZip_ROOT_HINTS}
        PATH_SUFFIXES lib
    )

    FIND_PATH(QuaZip_INCLUDE_DIR
        NAMES quazip/quazip.h
        HINTS ${_QuaZip_ROOT_HINTS}
        PATH_SUFFIXES include
    )

else (WIN32)
    FIND_LIBRARY(QuaZip_LIBRARY
        WIN32_DEBUG_POSTFIX d
        NAMES quazip
        HINTS ${_QuaZip_ROOT_HINTS} /usr/ /usr/
        PATH_SUFFIXES lib lib64
    )
    FIND_PATH(QuaZip_INCLUDE_DIR
        NAMES quazip/quazip.h
        HINTS /usr /usr/local
        HINTS ${_QuaZip_ROOT_HINTS}
        PATH_SUFFIXES include
    )

endif (WIN32)

# check if variables are valid
INCLUDE(FindPackageHandleStandardArgs)
find_package_handle_standard_args(QuaZip
    FOUND_VAR QuaZip_FOUND
    REQUIRED_VARS QuaZip_LIBRARY QuaZip_INCLUDE_DIR)

# prepare lib for usage
if(QuaZip_FOUND)
    set(QuaZip_INCLUDE_DIRS ${QuaZip_INCLUDE_DIR})
    set(QuaZip_LIBRARIES ${QuaZip_LIBRARY})

    if(NOT TARGET QuaZip)
        add_library(QuaZip UNKNOWN IMPORTED)
        set_target_properties(QuaZip PROPERTIES
            IMPORTED_LOCATION "${QuaZip_LIBRARIES}"
            INTERFACE_INCLUDE_DIRECTORIES "${QuaZip_INCLUDE_DIRS}")
    endif()
endif()

