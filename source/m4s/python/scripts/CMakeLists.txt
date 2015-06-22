set(_TARGET_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}/pcraster_multicore)

configure_file(__init__.py.in
    ${_TARGET_DIRECTORY}/__init__.py
    COPYONLY
)

configure_file(pcraster_multicore_operations.py.in
    ${_TARGET_DIRECTORY}/pcraster_multicore_operations.py
    COPYONLY
)

configure_file(pcraster_multicore.py.in
    ${_TARGET_DIRECTORY}/pcraster_multicore.py
    COPYONLY
)
