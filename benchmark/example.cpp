#include <benchmark/benchmark.h>

static void BM_Example(benchmark::State &state) {
  for (auto _ : state) {
    int i = 0;
    while (i < 10) {
      i++;
    }
  }
}
BENCHMARK(BM_Example);
