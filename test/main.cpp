#include <iostream>
#include <gtest/gtest.h>

#include "Alice.h"
#include "Cloud.h"
#include "Verif.h"
#include "simple_timer.h"

TEST(InitTest, ExampleTest) { std::cout << "Hello World" << std::endl; }

TEST(MainTest, DefaultTest) {
  int16_t ans = 0;
  DECLARE_TIMING(generatingSavingParametersKeys);
  DECLARE_TIMING(encryptDataExportCiphertexts);
  DECLARE_TIMING(importingCiphertextsPerformingComputations);
  DECLARE_TIMING(readingDecryptingResult);

  START_TIMING(generatingSavingParametersKeys);
  EXPECT_TRUE(generatingSavingParametersKeys());
  STOP_TIMING(generatingSavingParametersKeys);

  START_TIMING(encryptDataExportCiphertexts);
  EXPECT_TRUE(encryptDataExportCiphertexts());
  STOP_TIMING(encryptDataExportCiphertexts);

  START_TIMING(importingCiphertextsPerformingComputations);
  EXPECT_TRUE(importingCiphertextsPerformingComputations());
  STOP_TIMING(importingCiphertextsPerformingComputations);

  START_TIMING(readingDecryptingResult);
  EXPECT_TRUE(readingDecryptingResult(ans));
  STOP_TIMING(readingDecryptingResult);

  PRINT_TIMING(generatingSavingParametersKeys);
  PRINT_TIMING(encryptDataExportCiphertexts);
  PRINT_TIMING(importingCiphertextsPerformingComputations);
  PRINT_TIMING(readingDecryptingResult);
  EXPECT_TRUE(ans == 42);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
