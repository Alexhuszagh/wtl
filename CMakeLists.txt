#   :author: The Regents of the University of California.
#   :license: Public Domain

cmake_minimum_required(VERSION 2.8)
project(wtl CXX)

# TESTS
# -----

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
file(GLOB WTL_TESTS test/*.cpp)

add_subdirectory(googletest)
add_executable(WtlTests ${WTL_TESTS})
target_link_libraries(WtlTests
    gtest
    gtest_main
)

add_custom_target(check_wtl
    COMMAND $<TARGET_FILE:WtlTests>
    DEPENDS WtlTests
)
