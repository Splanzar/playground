cmake_minimum_required(VERSION 2.8)
project(algoengine_backend)

# configuration values for the project
include(scripts/config.cmake)

# dependencies
include(scripts/deps.cmake)

# project own's directories
include_directories(include)
add_subdirectory(bin)

