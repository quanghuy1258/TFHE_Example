#ifndef ALICE_H
#define ALICE_H

#include <cstdint>
#include <string>
#include <vector>

bool generatingSavingParametersKeys(
    int minimum_lambda = 110,
    const std::vector<uint32_t> &seed = {314, 1592, 657},
    const std::string &secret_key_file_name = "secret.key",
    const std::string &cloud_key_file_name = "cloud.key");
bool encryptDataExportCiphertexts(
    int16_t plaintext1 = 2017, int16_t plaintext2 = 42,
    const std::string &cloud_data_file_name = "cloud.data");

#endif
