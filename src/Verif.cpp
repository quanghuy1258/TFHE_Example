#include <cstdio>
#include <iostream>

#include "tfhe/tfhe.h"
#include "tfhe/tfhe_io.h"
#include "Verif.h"

bool readingDecryptingResult(
    int16_t &int_answer, std::string secret_key_file_name,
    std::string answer_data_file_name) {
  try {
    // reads the cloud key from file
    FILE *secret_key = fopen(secret_key_file_name.c_str(), "rb");
    TFheGateBootstrappingSecretKeySet *key =
        new_tfheGateBootstrappingSecretKeySet_fromFile(secret_key);
    fclose(secret_key);

    // if necessary, the params are inside the key
    const TFheGateBootstrappingParameterSet *params = key->params;

    // read the 16 ciphertexts of the result
    LweSample *answer = new_gate_bootstrapping_ciphertext_array(16, params);

    // import the 32 ciphertexts from the answer file
    FILE *answer_data = fopen(answer_data_file_name.c_str(), "rb");
    for (int i = 0; i < 16; i++)
      import_gate_bootstrapping_ciphertext_fromFile(answer_data, &answer[i],
                                                    params);
    fclose(answer_data);

    // decrypt and rebuild the 16 - bit plaintext answer
    for (int i = 0; i < 16; i++) {
      int ai = bootsSymDecrypt(&answer[i], key);
      int_answer |= (ai << i);
    }

    printf("And the result is: %d\n",int_answer);
    printf("I hope you remember what was the question!\n");

    // clean up all pointers
    delete_gate_bootstrapping_ciphertext_array(16, answer);
    delete_gate_bootstrapping_secret_keyset(key);

    return true;
  } catch (std::exception &ex) {
    std::cerr << "[readingDecryptingResult] Exception: " << ex.what() << std::endl;
  } catch (...) {
    std::cerr << "[readingDecryptingResult] Unknown exception" << std::endl;
  }
  return false;
}
