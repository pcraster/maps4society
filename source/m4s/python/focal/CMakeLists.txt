INCLUDE_DIRECTORIES(
  ${PCRTREE2_INCLUDE_DIRS}
  ${FERN_INCLUDE_DIRS}
)

SET(_SOURCES
  slope.cc
  window4total.cc
  #upstream.cc
)

ADD_LIBRARY(multicore_field_python_focals
  STATIC
    ${_SOURCES}
)
