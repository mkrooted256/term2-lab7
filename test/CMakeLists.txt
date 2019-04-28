set(GTEST_PATH googletest-release-1.8.1)

project(lab7)

add_subdirectory(${GTEST_PATH})
include_directories(${GTEST_PATH}/googletest/include)

add_executable(runTests Tests.cpp)
target_link_libraries(runTests gtest gtest_main)
target_link_libraries(runTests lab7lib)
