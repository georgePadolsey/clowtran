cmake_minimum_required(VERSION 3.10)

project(CLOWTRAN VERSION 0.0.1)

include_directories(
    ${PROJECT_SOURCE_DIR}/includes
    ${PROEJCT_SOURCE_DIR}/src
)

# @todo change to dbeug variable
set(CMAKE_BUILD_TYPE Debug)

add_executable(clowtran src/lowtran_driver.cpp)

# target_link_libraries(clowtran PRIVATE "${PROJECT_SOURCE_DIR}/includes/libf2c/libf2c.a")


# target_include_directories(clowtran PRIVATE
                            # "${PROJECT_BINARY_DIR}"
                            # "${PROJECT_SOURCE_DIR}/includes/libf2c")

