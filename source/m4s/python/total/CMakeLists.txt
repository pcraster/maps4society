INCLUDE_DIRECTORIES(
  ${PCRTREE2_INCLUDE_DIRS}
  ${FERN_INCLUDE_DIRS}
)

SET(_SOURCES
  mapmaximum.cc
  mapminimum.cc
  maptotal.cc
)

ADD_LIBRARY(multicore_field_python_totals
  STATIC
    ${_SOURCES}
)




