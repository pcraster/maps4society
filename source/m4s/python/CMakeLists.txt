add_subdirectory(local)
add_subdirectory(focal)
add_subdirectory(total)
add_subdirectory(type_conversion)
add_subdirectory(scripts)


set(_SOURCES
    execution_policy
    pcraster_multicore
)

add_library(_pcraster_multicore SHARED ${_SOURCES})

target_link_libraries(_pcraster_multicore
    multicore_field_python_totals
    multicore_field_python_focals
    multicore_field_python_locals
    multicore_field_python_type_conversions
    ${PCRTREE2_MODELENGINE_LIBRARY}
    ${PCRTREE2_PYTHON_LIBRARY}
    ${FERN_LIBRARIES}
    ${Boost_PYTHON_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${PYTHON_LIBRARIES}
)

configure_python_extension(_pcraster_multicore
    "_pcraster_multicore"
)
