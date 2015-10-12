find_package(Boost)
find_package(PythonLibs)

# we need to accesss project's own libraries
find_package(Pcrtree2)

# these flags are required
set(CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} -fPIC -Wall -Wextra -Wcast-qual -Wwrite-strings -Werror=strict-aliasing -std=c++1y -O3")

# obtained from Site.cmake
MACRO(CONFIGURE_PYTHON_EXTENSION EXTENTION_TARGET EXTENSION_NAME)
    SET_TARGET_PROPERTIES(${EXTENTION_TARGET}
        PROPERTIES
            OUTPUT_NAME "${EXTENSION_NAME}"
    )

    # Configure suffix and prefix, depending on the Python OS conventions.
    SET_TARGET_PROPERTIES(${EXTENTION_TARGET}
        PROPERTIES
            PREFIX ""
    )

    IF(WIN32)
        SET_TARGET_PROPERTIES(${EXTENTION_TARGET}
            PROPERTIES
                DEBUG_POSTFIX "_d"
                SUFFIX ".pyd"
        )
    ELSE(WIN32)
        SET_TARGET_PROPERTIES(${EXTENTION_TARGET}
            PROPERTIES
                SUFFIX ".so"
        )
    ENDIF(WIN32)
ENDMACRO()


add_subdirectory(wrapper)
add_subdirectory(python)
