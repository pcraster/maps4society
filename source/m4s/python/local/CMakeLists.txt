INCLUDE_DIRECTORIES(
  ${_PCRTREE2_ROOT_INCLUDE}/pcraster_model_engine
  ${_PCRTREE2_ROOT_INCLUDE}/include
  ${_PCRTREE2_ROOT_INCLUDE}/pcraster_python
  ${_PCRTREE2_ROOT_INCLUDE}/pcrgeo
  ${_PCRTREE2_ROOT_INCLUDE}/pcrcom
  ${_PCRTREE2_ROOT_INCLUDE}/app
  ${FERN_INCLUDE_DIRS}
)

SET(_SOURCES
  utils.cc

  and.cc
#  or.cc
#  xor.cc
#  not.cc
#  defined.cc

#   add.cc
#   sub.cc
#   mul.cc
#   div.cc

#  equal.cc
#  unequal.cc
#  less.cc
#  less_equal.cc
#  greater.cc
#  greater_equal.cc
#  ifthen.cc
#  ifthenelse.cc

#   pow.cc
# 
#   cos.cc
#   sqrt.cc
)

ADD_LIBRARY(multicore_field_python_locals
  STATIC
    ${_SOURCES}
)
