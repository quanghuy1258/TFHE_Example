#ifndef SIMPLE_TIMER_H
#define SIMPLE_TIMER_H

#include <chrono>
#include <iostream>

#define GET_CURRENT_TIME std::chrono::system_clock::now
#define DECLARE_TIMING(s)                                                      \
  auto time_##s = GET_CURRENT_TIME();                                          \
  auto timeDiff_##s = GET_CURRENT_TIME() - time_##s
#define START_TIMING(s) time_##s = GET_CURRENT_TIME()
#define STOP_TIMING(s) timeDiff_##s = GET_CURRENT_TIME() - time_##s
#define PRINT_TIMING(s)                                                        \
  std::cerr.imbue(std::locale(""));                                            \
  std::cerr << #s " = " << timeDiff_##s.count() << " ns\n"

#endif
