#### Add all dependent libraries path here. These values to be changed by user ####
set(CMAKE_VERBOSE_MAKEFILE 1)
set(BOOST_ROOT "/home/ubuntu/dependencies/boost/")

#### Boost library dependency ####
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
set(Boost_NO_SYSTEM_PATHS ON)

if(POLICY CMP0020)
    cmake_policy(SET CMP0020 NEW)
endif()

find_package(Boost REQUIRED COMPONENTS system filesystem program_options date_time)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
else()
    print_error ("Please make sure you have Boost Installed" "Boost at ${BOOST_ROOT}")
endif ()

#### System library dependency ####
set(PLATFORM_SPECIFIC_LIBRARIES pthread)

#### Finally add cutomer library path in CMake library path and find them to be added in linker call ####
set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH}
    ${LEVELDB_LIB_PATH} ${LIBEVENT_LIB_PATH} ${QUICKFIX_LIB_PATH} ${GTEST_LIB_PATH}
)
