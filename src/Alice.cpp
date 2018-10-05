#include <cstdio>
#include <iostream>
#include <tfhe/tfhe.h>
#include <tfhe/tfhe_io.h>

#include "Alice.h"

bool generatingSavingParametersKeys(int minimum_lambda,
                                    const std::vector<uint32_t> &seed,
                                    const std::string &secret_key_file_name,
                                    const std::string &cloud_key_file_name) {
  try {
    // generate a keyset
    TFheGateBootstrappingParameterSet *params =
        new_default_gate_bootstrapping_parameters(minimum_lambda);

    // generate a random key
    tfhe_random_generator_setSeed(seed.data(), seed.size());
    TFheGateBootstrappingSecretKeySet *key =
        new_random_gate_bootstrapping_secret_keyset(params);

    // export the secret key to file for later use
    FILE *secret_key = fopen(secret_key_file_name.c_str(), "wb");
    export_tfheGateBootstrappingSecretKeySet_toFile(secret_key, key);
    fclose(secret_key);

    // export the cloud key to a file (for the cloud)
    FILE *cloud_key = fopen(cloud_key_file_name.c_str(), "wb");
    export_tfheGateBootstrappingCloudKeySet_toFile(cloud_key, &key->cloud);
    fclose(cloud_key);

    //clean up all pointers
    delete_gate_bootstrapping_secret_keyset(key);
    delete_gate_bootstrapping_parameters(params);
    return true;
  } catch (std::exception &ex) {
    std::cerr << "[generatingSavingParametersKeys] Exception: " << ex.what() << std::endl;
  } catch (...) {
    std::cerr << "[generatingSavingParametersKeys] Unknown exception" << std::endl;
  }
  return false;
}

bool encryptDataExportCiphertexts(int16_t plaintext1, int16_t plaintext2,
                                  const std::string &cloud_data_file_name) {
  try {
    // generate encrypt the 16 bits of 2017
    LweSample *ciphertext1 =
        new_gate_bootstrapping_ciphertext_array(16, params);
    for (int i = 0; i < 16; i++) {
      bootsSymEncrypt(&ciphertext1[i], (plaintext1 >> i) & 1, key);
    }

    // generate encrypt the 16 bits of 42
    LweSample *ciphertext2 =
        new_gate_bootstrapping_ciphertext_array(16, params);
    for (int i = 0; i < 16; i++) {
      bootsSymEncrypt(&ciphertext2[i], (plaintext2 >> i) & 1, key);
    }

    printf("Hi there! Today, I will ask the cloud what is the minimum between "
           "%d and %d\n",
           plaintext1, plaintext2);

    // exportv the 2x16 ciphertexts to a file (for the cloud)
    FILE *cloud_data = fopen(cloud_data_file_name.c_str(), "wb");
    for (int i = 0; i < 16; i++)
      export_gate_bootstrapping_ciphertext_toFile(cloud_data, &ciphertext1[i],
                                                  params);
    for (int i = 0; i < 16; i++)
      export_gate_bootstrapping_ciphertext_toFile(cloud_data, &ciphertext2[i],
                                                  params);
    fclose(cloud_data);

    // clean up all pointers
    delete_gate_bootstrapping_ciphertext_array(16, ciphertext2);
    delete_gate_bootstrapping_ciphertext_array(16, ciphertext1);

    return true;
  }  catch (std::exception &ex) {
    std::cerr << "[encryptDataExportCiphertexts] Exception: " << ex.what() << std::endl;
  } catch (...) {
    std::cerr << "[encryptDataExportCiphertexts] Unknown exception" << std::endl;
  }
  return false;
}

