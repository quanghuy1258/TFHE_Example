#ifndef CLOUD_H
#define CLOUD_H

#include <string>

bool importingCiphertextsPerformingComputations(
    const std::string &cloud_key_file_name = "cloud.key",
    const std::string &cloud_data_file_name = "cloud.data",
    const std::string &answer_data_file_name = "answer.data");

#endif
