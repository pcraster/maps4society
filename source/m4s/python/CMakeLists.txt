ADD_SUBDIRECTORY(local)
ADD_SUBDIRECTORY(focal)
ADD_SUBDIRECTORY(scripts)


INCLUDE_DIRECTORIES(
  ${_PCRTREE2_ROOT_INCLUDE}/pcraster_model_engine
  ${_PCRTREE2_ROOT_INCLUDE}/pcraster_python
  ${_PCRTREE2_ROOT_INCLUDE}/pcrgeo
  ${_PCRTREE2_ROOT_INCLUDE}/include
  ${_PCRTREE2_ROOT_INCLUDE}/pcrcom
  ${FERN_INCLUDE_DIRS}
)


SET(_SOURCES
  execution_policy
  pcraster_multicore
)


ADD_LIBRARY(_pcraster_multicore SHARED ${_SOURCES})


ADD_DEPENDENCIES(_pcraster_multicore
  multicore_field
  multicore_field_python_focals
  multicore_field_python_locals
)


TARGET_LINK_LIBRARIES(_pcraster_multicore
  multicore_field
  multicore_field_python_focals
  multicore_field_python_locals
  ${PCRTREE2_MODELENGINE_LIBRARY}
  ${PCRTREE2_PYTHON_LIBRARY}
  ${BOOST_PYTHON_LIBRARY}
#  ${BOOST_CHRONO_LIBRARY}
  ${FERN_LIBRARIES}
)


CONFIGURE_PYTHON_EXTENSION(_pcraster_multicore
    "_pcraster_multicore"
)
