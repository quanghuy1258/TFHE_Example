# benchmark
SET (BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "Message: Disable BENCHMARK_GTEST_TESTS")
ADD_SUBDIRECTORY (benchmark EXCLUDE_FROM_ALL)
