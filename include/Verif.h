#ifndef VERIF_H
#define VERIF_H

#include <cstdint>
#include <string>

bool readingDecryptingResult(
    const std::string &secret_key_file_name = "secret.key",
    const std::string &answer_data_file_name = "answer.data",
    int16_t &int_answer);

#endif
