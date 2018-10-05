cmake_minimum_required(VERSION 3.0)

project(TFHE_Example)

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_FLAGS "-Wall -O2 -DNDEBUG -fPIC")
set(CMAKE_LIBRARY_PATH "$ENV{LD_LIBRARY_PATH}")
set(CMAKE_INCLUDE_PATH "$ENV{C_INCLUDE_PATH}:$ENV{CPLUS_INCLUDE_PATH}")

enable_testing()
find_package(GTest REQUIRED)

string(REGEX REPLACE ":" ";" MY_INCLUDE "${CMAKE_INCLUDE_PATH}")

include_directories(${MY_INCLUDE})
include_directories(${PROJECT_SOURCE_DIR}/include)

string(REGEX REPLACE ":" ";" MY_LIBS "${CMAKE_LIBRARY_PATH}")

link_directories(${MY_LIBS})

file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE TEST_FILES ${PROJECT_SOURCE_DIR}/test/*.cpp)

add_executable(mainTest ${SRC_FILES} ${TEST_FILES})
target_link_libraries(mainTest ${GTEST_LIBRARIES} tfhe)
add_test(AllTests mainTest)
