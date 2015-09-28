#CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

#PROJECT(pcraster_multicore)

#SET(CMAKE_MODULE_PATH
#  $ENV{CMAKE_MODULE_PATH}
#  ${CMAKE_CURRENT_SOURCE_DIR}/environment/cmake
#)

# use the PCRaster configuration
#INCLUDE(Site)
#INCLUDE(UsePCRasterDal)
#INCLUDE(UseBoost)
#INCLUDE(UsePython)
find_package(PythonLibs)#Python)

# we need to accesss project's own libraries
find_package(Pcrtree2)
find_package(Boost)

### # to use some of the algorithms
### FIND_PACKAGE(Fern)

# these flags are required
set(CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} -fPIC -Wall -Wextra -Wcast-qual -Wwrite-strings -Werror=strict-aliasing -std=c++1y -O3")

add_subdirectory(wrapper)
add_subdirectory(python)
