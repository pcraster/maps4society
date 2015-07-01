# Peacock is a project for building external software. It can be used to
# build the Boost libraries on all kinds of platform, for example. A
# PEACOCK_PREFIX CMake variable or environment variable can be set to
# point us to the root of the platform-specific files. By adding the
# current platform string to this prefix, we end up at the root of the
# header files and libraries.
# See also: https://github.com/geoneric/peacock

# If the PEACOCK_PREFIX CMake variable is not set, but an environment
# variable with that name is, then copy it to a CMake variable. This way
# the CMake variable takes precedence.
if((NOT PEACOCK_PREFIX) AND (DEFINED ENV{PEACOCK_PREFIX}))
    set(PEACOCK_PREFIX $ENV{PEACOCK_PREFIX})
endif()

if(PEACOCK_PREFIX)
    # # if cross compiling:
    # set(CMAKE_FIND_ROOT_PATH
    #     ${PEACOCK_PREFIX}/${peacock_target_platform})
    # else:
    set(CMAKE_PREFIX_PATH
        ${PEACOCK_PREFIX}/${peacock_target_platform}
        ${CMAKE_PREFIX_PATH}
    )
    message(STATUS "Probing Peacock builds in: ${PEACOCK_PREFIX}/${peacock_target_platform}")
    set(CMAKE_INCLUDE_DIRECTORIES_BEFORE TRUE)
endif()


if(M4S_FERN_REQUIRED)
    FIND_PACKAGE(Fern)
    include_directories(
        ${INCLUDE_DIRS}
    )
endif()
