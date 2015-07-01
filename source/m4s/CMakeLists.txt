#CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

#PROJECT(pcraster_multicore)

#SET(CMAKE_MODULE_PATH
#  $ENV{CMAKE_MODULE_PATH}
#  ${CMAKE_CURRENT_SOURCE_DIR}/environment/cmake
#)

# use the PCRaster configuration
INCLUDE(Site)
INCLUDE(UsePCRasterDal)
INCLUDE(UseBoost)
INCLUDE(UsePython)

# we need to accesss the PCRaster model engine
FIND_PACKAGE(Pcrtree2)

### # to use some of the algorithms
### FIND_PACKAGE(Fern)

# shouldnt work this out of the box?
# check if g++ version test is in site.cmake
SET(CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wcast-qual -Wwrite-strings -Werror=strict-aliasing -std=c++1y -O3")

ADD_SUBDIRECTORY(wrapper)
ADD_SUBDIRECTORY(python)
