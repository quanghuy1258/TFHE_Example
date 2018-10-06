cmake_minimum_required(VERSION 3.0)

project(TFHE_Example)

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ENABLE_TESTS ON CACHE BOOL "Reuse googletest in tfhe repo :)))")
add_subdirectory(tfhe/src)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/tfhe/src/include)
include_directories(${GTEST_INCLUDE_DIRS})

file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE TEST_FILES ${PROJECT_SOURCE_DIR}/test/*.cpp)

add_executable(mainTest ${SRC_FILES} ${TEST_FILES})
target_link_libraries(mainTest gtest tfhe-spqlios-avx pthread)
add_test(AllTests mainTest)
