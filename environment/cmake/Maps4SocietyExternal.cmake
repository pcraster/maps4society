if(M4S_PCRTREE2_REQUIRED)
    find_package(Pcrtree2 REQUIRED)

    if(NOT PCRTREE2_FOUND)
        message(FATAL_ERROR "PCRTREE2 libraries not found")
    endif()
endif()
