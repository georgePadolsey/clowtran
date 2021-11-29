cmake_minimum_required(VERSION 3.19)

project(CLOWTRAN VERSION 0.0.1)

include_directories(
    ${PROJECT_SOURCE_DIR}/includes
    ${PROEJCT_SOURCE_DIR}/src
)




# https://stackoverflow.com/questions/10851247/how-do-i-activate-c-11-in-cmake
# IF (CMAKE_VERSION VERSION_LESS "3.8")
#     SET(CMAKE_CXX_STANDARD 14)
# ELSEIF (CMAKE_VERSION VERSION_LESS "3.11")
#     SET(CMAKE_CXX_STANDARD 17)
# ELSE()
#     SET(CMAKE_CXX_STANDARD 20)
# ENDIF()
SET(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# SET(CMAKE_CXX_EXTENSIONS OFF)

IF(APPLE)
  SET(CMAKE_OSX_ARCHITECTURES "x86_64;arm64" CACHE STRING "Build architectures for Mac OS X" FORCE)
ENDIF(APPLE)

find_package(Python COMPONENTS Interpreter Development NumPy REQUIRED)

# find_package(pybind11 CONFIG REQUIRED)

# @todo change to dbeug variable

# add_executable(clowtran src/lowtran_driver.cpp)



# target_include_directories(clowtran PRIVATE
                            # "${PROJECT_BINARY_DIR}"
                            # "${PROJECT_SOURCE_DIR}/includes/libf2c")

# target_link_libraries(clowtran PRIVATE "${PROJECT_SOURCE_DIR}/includes/libf2c/libf2c.a")

# Python_



# target_link_libraries(clowtran Python::Python Python::NumPy)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)



Python_add_library(clowtran MODULE src/lowtran_driver.cpp)

target_include_directories(clowtran PUBLIC
    ${Python_NumPy_INCLUDE_DIRS})




add_executable(clowtran_exe src/profile.cpp)

add_link_options(${Python_LINK_OPTIONS})


SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g")
# set_property(GLOBAL PROPERTY DEBUG_CONFIGURATIONS "Debug;UnitaryTest")
# find_package(easy_profiler REQUIRED)


# target_compile_definitions(clowtran PUBLIC "$<$<CONFIG:DEBUG>:DEBUG>")




