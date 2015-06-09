# this assumes a working PCRaster development setup

IF(DEFINED ENV{PCRTREE2})
  SET(_PCRTREE2_ROOT $ENV{PCRTREE2})
  SET(_PCRTREE2_ROOT_INCLUDE ${_PCRTREE2_ROOT}/sources)
  SET(_PCRTREE2_ROOT_LIB ${_PCRTREE2_ROOT}/lib)
ENDIF()


FIND_LIBRARY(PCRTREE2_MODELENGINE_LIBRARY
    NAMES pcraster_model_engine
    PATHS ${OBJECTS}/pcrtree2/bin
)


FIND_LIBRARY(PCRTREE2_PYTHON_LIBRARY
    NAMES _pcraster.so    # using '_pcraster' will not work
    PATHS ${OBJECTS}/pcrtree2/bin/pcraster
)
