# set C++11 compilation standard
set(CMAKE_CXX_STANDARD 11)


# Build type for cmake if it is release or debug.
if(CMAKE_BUILD_TYPE)
    if(CMAKE_BUILD_TYPE STREQUAL Release OR CMAKE_BUILD_TYPE STREQUAL RelWithDebInfo OR CMAKE_BUILD_TYPE STREQUAL MinSizeRel)
        set(TARGET_POSTFIX "")
        set(APP_COMPILE_TYPE release)
    else()
        set(TARGET_POSTFIX "d")
        set(APP_COMPILE_TYPE debug)
    endif()
else()
    set(TARGET_POSTFIX "d")
    set(APP_COMPILE_TYPE debug)
endif()



# Defining the name of the executable.
set(EXE_FILE_NAME "main")

# This will provide verbose output from make
set(CMAKE_VERBOSE_MAKEFILE ON)

# install directory for the project, where binary would be created
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/../install/")
