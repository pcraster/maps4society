configure_file(__init__.py.in
    ${PROJECT_BINARY_DIR}/bin/pcraster5/multicore/__init__.py
    COPYONLY
)

configure_file(pcraster_multicore_operations.py.in
    ${PROJECT_BINARY_DIR}/bin/pcraster5/multicore/operations.py
    COPYONLY
)

configure_file(pcraster_multicore.py.in
    ${PROJECT_BINARY_DIR}/bin/pcraster5/multicore/operators.py
    COPYONLY
)
