INCLUDE_DIRECTORIES(
  ${_PCRTREE2_ROOT_INCLUDE}/pcraster_model_engine
  ${_PCRTREE2_ROOT_INCLUDE}/include
  ${FERN_INCLUDE_DIRS}
)

SET(_SOURCES
  boolean.cc
  nominal.cc
  ordinal.cc
  scalar.cc
)

ADD_LIBRARY(multicore_field_python_type_conversions
  STATIC
    ${_SOURCES}
)




