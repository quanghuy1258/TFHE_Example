#ifndef VERIF_H
#define VERIF_H

#include <cstdint>
#include <string>

bool readingDecryptingResult(int16_t &int_answer,
                             std::string secret_key_file_name = "secret.key",
                             std::string answer_data_file_name = "answer.data");

#endif
