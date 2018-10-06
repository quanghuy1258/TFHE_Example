#include <iostream>
#include <gtest/gtest.h>

#include "Alice.h"
#include "Cloud.h"
#include "Verif.h"

TEST(InitTest, ExampleTest) {
  std::cout << "Hello World" << std::endl;
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
