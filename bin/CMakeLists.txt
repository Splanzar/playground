#AlgoEngine executable
file(GLOB binSrc
    "*.C"
)

add_executable(${EXE_FILE_NAME} ${binSrc})

set_target_properties("${EXE_FILE_NAME}" PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries("${EXE_FILE_NAME}" 
                                         ${Boost_LIBRARIES}
                                         ${PLATFORM_SPECIFIC_LIBRARIES}
                                         rt)
