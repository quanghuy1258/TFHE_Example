#include <iostream>
#include <gtest/gtest.h>

#include "Alice.h"
#include "Cloud.h"
#include "Verif.h"

TEST(InitTest, ExampleTest) { std::cout << "Hello World" << std::endl; }

TEST(MainTest, DefaultTest) {
  int16_t ans = 0;
  EXPECT_TRUE(generatingSavingParametersKeys());
  EXPECT_TRUE(encryptDataExportCiphertexts());
  EXPECT_TRUE(importingCiphertextsPerformingComputations());
  EXPECT_TRUE(readingDecryptingResult(ans));
  EXPECT_TRUE(ans == 42);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
