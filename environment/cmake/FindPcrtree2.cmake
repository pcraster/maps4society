# This module defines the following CMake variables:
##   _FOUND
#  PCRTREE2_INCLUDE_DIRS
#  PCRTREE2_LIBRARIES
#



FIND_PATH(PCRTREE2_INCLUDE_DIRS
    NAMES pcrtree2/calc_spatial.h
    PATHS ${_PCRTREE2_ROOT_INCLUDE}
)

FIND_LIBRARY(PCRTREE2_MODELENGINE_LIBRARY
    NAMES pcraster_model_engine
    PATHS ${_PCRTREE2_ROOT_LIB}
)

FIND_LIBRARY(PCRTREE2_PYTHON_LIBRARY
    NAMES _pcraster.so
    #PATHS ${PCRTREE2_INCLUDE_DIRS}/../python/pcraster #${_PCRTREE2_ROOT_LIB}
    PATHS ${_PCRTREE2_ROOT_LIB} # /// todo check which one works with clean directory...
)


SET(PCRTREE2_LIBRARIES
    ${PCRTREE2_MODELENGINE_LIBRARY}
    ${PCRTREE2_PYTHON_LIBRARY}
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(PCRTREE2
    REQUIRED_VARS
        PCRTREE2_LIBRARIES
        PCRTREE2_INCLUDE_DIRS
)


# this assumes a working PCRaster development setup
# # # # # 
# # # # # IF(DEFINED ENV{PCRTREE2})
# # # # #   SET(_PCRTREE2_ROOT $ENV{PCRTREE2})
# # # # #   SET(_PCRTREE2_ROOT_INCLUDE ${_PCRTREE2_ROOT}/sources)
# # # # #   SET(_PCRTREE2_ROOT_LIB ${_PCRTREE2_ROOT}/lib)
# # # # # ENDIF()
# # # # # 
# # # # # 
# # # # # FIND_LIBRARY(PCRTREE2_MODELENGINE_LIBRARY
# # # # #     NAMES pcraster_model_engine
# # # # #     PATHS ${OBJECTS}/pcrtree2/bin
# # # # # )
# # # # # 
# # # # # 
# # # # # FIND_LIBRARY(PCRTREE2_PYTHON_LIBRARY
# # # # #     NAMES _pcraster.so    # using '_pcraster' will not work
# # # # #     PATHS ${OBJECTS}/pcrtree2/bin/pcraster
# # # # # )
