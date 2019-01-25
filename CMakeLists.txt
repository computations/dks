cmake_minimum_required(VERSION 2.6)

cmake_policy(SET CMP0048 NEW)
project(dks)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

find_package(Git QUIET)

if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive 
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} 
            RESULT_VARIABLE GIT_SUBMODULE_RESULT)
        if(NOT GIT_SUBMODULE_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMODULE_RESULT}")
        endif()
    endif()
endif()

add_subdirectory(lib)

add_subdirectory(src)

add_subdirectory(test)
