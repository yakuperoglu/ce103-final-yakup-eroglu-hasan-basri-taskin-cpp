#include "gtest/gtest.h"
#include "../../librarysystem/header/librarysystem.h"

using namespace Coruh::Librarysystem;

class LibrarysystemTest : public ::testing::Test {
 protected:
  void SetUp() override {
  }

  void TearDown() override {
  }
};

int main(int argc, char **argv) {
#ifdef ENABLE_LIBRARYSYSTEM_TEST
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
#else
  return 0;
#endif
}
