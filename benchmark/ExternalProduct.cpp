#include <benchmark/benchmark.h>

#include "tfhe.h"

#define M_PI 3.14159265358979323846

static void BM_ExternalProduct(benchmark::State &state) {
  // Prepare for benchmark
  //   Set parameters
  const double sd = (9e-9) / std::sqrt(2. / M_PI); // see TFHE
  TLweParams *tlwe_params = new_TLweParams(1024, 1, 0., 1.);
  TGswParams *params = new_TGswParams(2, 10, tlwe_params);
  //   Set number of TRLWE
  const int number_trlwe = state.range(0);
  //   Generate key
  TGswKey *key = new_TGswKey(params);
  tGswKeyGen(key);
  //   Generate 1 TRGSW cipher
  TGswSample *trgsw = new_TGswSample(params);
  tGswSymEncryptInt(trgsw, 0, sd, key);
  //   Generate TRLWE ciphers
  std::vector<TLweSample *> trlwe_list(number_trlwe);
  std::vector<TLweSample *> result_list(number_trlwe);
  for (int i = 0; i < number_trlwe; i++) {
    trlwe_list[i] = new_TLweSample(params->tlwe_params);
    result_list[i] = new_TLweSample(params->tlwe_params);
    tLweSymEncryptZero(trlwe_list[i], sd, &key->tlwe_key);
  }
  // Benchmark
  for (auto _ : state) {
    for (int it = 0; it < number_trlwe; it++)
      tGswExternProduct(result_list[it], trgsw, trlwe_list[it], params);
  }
  // Clean for benchmark
  //   Free TRLWE ciphers
  for (int i = 0; i < number_trlwe; i++) {
    delete_TLweSample(trlwe_list[i]);
    trlwe_list[i] = nullptr;
    delete_TLweSample(result_list[i]);
    result_list[i] = nullptr;
  }
  //   Free TRGSW cipher
  delete_TGswSample(trgsw);
  trgsw = nullptr;
  //   Free key
  delete_TGswKey(key);
  key = nullptr;
  //   Free parameters
  destroy_TGswParams(params);
  delete_TLweParams(tlwe_params);
}
BENCHMARK(BM_ExternalProduct)
    ->Arg(1)
    ->Arg(2)
    ->Arg(4)
    ->Arg(8)
    ->Arg(16)
    ->Arg(32)
    ->Arg(50)
    ->Arg(100)
    ->Arg(150)
    ->Arg(200);
