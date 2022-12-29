cmake_minimum_required(VERSION 3.22)

set(CMAKE_C_STANDARD                99)
set(CMAKE_C_STANDARD_REQUIRED       ON)
set(CMAKE_C_EXTENSIONS              ON)
set(CMAKE_CXX_STANDARD              11)
set(CMAKE_CXX_STANDARD_REQUIRED     ON)
set(CMAKE_CXX_EXTENSIONS            ON)
set(PROJ_PATH                       ${CMAKE_CURRENT_SOURCE_DIR})
set(EXECUTABLE                      ${CMAKE_PROJECT_NAME})

project(hash_table)
enable_language(C CXX)

set(sources_SRCS
    ${PROJ_PATH}/src/_hash_table.c
    ${PROJ_PATH}/src/main.c
)

set(include_DIRS
    ${PROJ_PATH}/inc
)

add_executable(${EXECUTABLE} ${sources_SRCS})
target_include_directories(${EXECUTABLE} PRIVATE ${include_DIRS})
target_link_libraries(${EXECUTABLE} PRIVATE m)