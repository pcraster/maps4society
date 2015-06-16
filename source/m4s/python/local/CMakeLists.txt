INCLUDE_DIRECTORIES(
  ${_PCRTREE2_ROOT_INCLUDE}/pcraster_model_engine
  ${_PCRTREE2_ROOT_INCLUDE}/include
  ${_PCRTREE2_ROOT_INCLUDE}/pcraster_python
  ${_PCRTREE2_ROOT_INCLUDE}/pcrgeo
  ${_PCRTREE2_ROOT_INCLUDE}/pcrcom
  ${FERN_INCLUDE_DIRS}
)

SET(_SOURCES
  pow.cc
)

ADD_LIBRARY(multicore_field_python_locals
  STATIC
    ${_SOURCES}
)

