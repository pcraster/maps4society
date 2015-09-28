INCLUDE_DIRECTORIES(
  ${PCRTREE2_INCLUDE_DIRS}
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




