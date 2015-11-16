set(_SOURCES
    slope
    window4total
    #upstream
)

add_library(multicore_field_python_focals
    STATIC
        ${_SOURCES}
)
