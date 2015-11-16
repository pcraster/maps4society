set(_SOURCES
    boolean
    nominal
    ordinal
    scalar
)

add_library(multicore_field_python_type_conversions
    STATIC
        ${_SOURCES}
)
