include(PeacockPlatform)
include(DevBaseCompiler)
include(Maps4SocietyConfiguration)
include(DevBaseExternal)
include(Maps4SocietyExternal)
include(DevBaseMacro)


if(M4S_BUILD_TEST)
    enable_testing()
endif()


force_out_of_tree_build()


# include(Maps4SocietyCompiler)
# include(Maps4SocietyConfiguration)
# include(Maps4SocietyExternal)
# include(Maps4SocietyMacro)
