# QuaZip_FOUND               - QuaZip library was found
# QuaZip_INCLUDE_DIRS        - Path to QuaZip include dir
# QuaZip_LIBRARIES           - List of QuaZip libraries

# check if library path already set
if (QuaZip_INCLUDE_DIRS AND QuaZip_LIBRARIES)
	set(QuaZip_FOUND TRUE)

else (QuaZip_INCLUDE_DIRS AND QuaZip_LIBRARIES)

    # set names of lib file
    set(QuaZip_NAMES curl curldll)

    # set lib path
    if (WIN32)
		FIND_PATH(QuaZip_LIBRARY_DIR
			WIN32_DEBUG_POSTFIX d
			NAMES libquazip.dll
			HINTS "C:/Programme/" "C:/Program Files"
			PATH_SUFFIXES QuaZip/lib
		)

		FIND_LIBRARY(QuaZip_LIBRARY
		    NAMES libquazip.dll
		    HINTS ${QuaZip_LIBRARY_DIR})
		FIND_PATH(QuaZip_INCLUDE_DIR
		    NAMES quazip.h
		    HINTS ${QuaZip_LIBRARY_DIR}/../ PATH_SUFFIXES include/quazip)
		FIND_PATH(QuaZip_ZLIB_INCLUDE_DIR
		    NAMES zlib.h)

    else (WIN32)
        FIND_LIBRARY(QuaZip_LIBRARY
            WIN32_DEBUG_POSTFIX d
            NAMES quazip
            HINTS /usr/lib /usr/lib64
        )
        FIND_PATH(QuaZip_INCLUDE_DIR
            NAMES quazip.h
            HINTS /usr/include /usr/local/include
            PATH_SUFFIXES quazip
        )
        FIND_PATH(QuaZip_ZLIB_INCLUDE_DIR
            NAMES zlib.h
            HINTS /usr/include /usr/local/include)

    endif (WIN32)
    
    # check if variables are valid
    INCLUDE(FindPackageHandleStandardArgs)
    find_package_handle_standard_args(QuaZip
        FOUND_VAR QuaZip_FOUND
        REQUIRED_VARS QuaZip_LIBRARY QuaZip_INCLUDE_DIR QuaZip_ZLIB_INCLUDE_DIR)

    # prepare lib for usage
    if(QuaZip_FOUND)
        set(QuaZip_INCLUDE_DIRS ${QuaZip_INCLUDE_DIR} ${QuaZip_ZLIB_INCLUDE_DIR})
        set(QuaZip_LIBRARIES ${QuaZip_LIBRARY})

        if(NOT TARGET QuaZip)
            add_library(QuaZip UNKNOWN IMPORTED)
            set_target_properties(QuaZip PROPERTIES
                IMPORTED_LOCATION "${QuaZip_LIBRARIES}"
                INTERFACE_INCLUDE_DIRECTORIES "${QuaZip_INCLUDE_DIRS}")
        endif()
    endif()

endif (QuaZip_INCLUDE_DIRS AND QuaZip_LIBRARIES)
