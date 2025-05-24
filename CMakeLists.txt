cmake_minimum_required(VERSION 3.20.0)
project(datastructs VERSION 0.1.0)

option(BUILD_TESTS "Build test programs" OFF)

set(PROJECT_BINARY_DIR ${PROJECT_BINARY_DIR}/build)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

set(CMAKE_C_VISIBILITY_PRESET hidden)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_STATIC_LIBRARY_PREFIX "lib")
set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_IMPORT_LIBRARY_PREFIX "lib")

FILE(GLOB src ${CMAKE_CURRENT_SOURCE_DIR}/src/* ${CMAKE_CURRENT_SOURCE_DIR}/src/**/*)
add_library(${PROJECT_NAME} STATIC ${src})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)
add_library(CTOOLS::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

if(${BUILD_TESTS})
FILE(GLOB tests ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.c)
    foreach(test ${tests})
        get_filename_component(testname ${test} NAME_WE)
        add_executable(${testname} ${test})
        target_link_libraries(${testname} CTOOLS::${PROJECT_NAME})
    endforeach(test ${tests})
endif()
