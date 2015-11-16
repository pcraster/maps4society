set(_SOURCES
    mapmaximum
    mapminimum
    maptotal
)

add_library(multicore_field_python_totals
    STATIC
        ${_SOURCES}
)
