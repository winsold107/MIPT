cmake_minimum_required(VERSION 3.5.1)
project(3_semester_practic_formal_languages)

set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_BUILD_TYPE DEBUG)

# SETTING UP GOOGLE TEST BEGIN
# Instructions are taken from here <a href="http://kaizou.org/2014/11/gtest-cmake">Instructions link</a>}


# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
        ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)

include_directories("${gtest_SOURCE_DIR}/include")

# SETTING UP GOOGLE TEST END


include_directories(include)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

SET(SRC
        start.cpp
        src/solution.cpp
        )

SET(TESTS
        tests/tests.cpp
        )

SET(INCLUDE
        include/solution.h
        )

add_executable(solution ${SRC} ${INCLUDE} ${TESTS})
target_link_libraries(solution gtest_main)