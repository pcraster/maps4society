INCLUDE_DIRECTORIES(
   ${_PCRTREE2_ROOT_INCLUDE}/pcraster_model_engine
   ${_PCRTREE2_ROOT_INCLUDE}/include
   ${_PCRTREE2_ROOT_INCLUDE}/pcraster_python
   ${_PCRTREE2_ROOT_INCLUDE}/pcrgeo
   ${_PCRTREE2_ROOT_INCLUDE}/pcrcom
   #${_PCRTREE2_ROOT_INCLUDE}/app
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




