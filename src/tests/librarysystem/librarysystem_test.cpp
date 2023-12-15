//#define ENABLE_LIBRARYSYSTEM_TEST  // Uncomment this line to enable the Librarysystem tests

#include "gtest/gtest.h"
#include "../../librarysystem/header/librarysystem.h"  // Adjust this include path based on your project structure

using namespace Coruh::Librarysystem;

class LibrarysystemTest : public ::testing::Test {
 protected:
  void SetUp() override {
    // Setup test data
  }

  void TearDown() override {
    // Clean up test data
  }
};

TEST_F(LibrarysystemTest, TestAdd) {
  double result = Librarysystem::add(5.0, 3.0);
  EXPECT_DOUBLE_EQ(result, 8.0);
}

TEST_F(LibrarysystemTest, TestSubtract) {
  double result = Librarysystem::subtract(5.0, 3.0);
  EXPECT_DOUBLE_EQ(result, 2.0);
}

TEST_F(LibrarysystemTest, TestMultiply) {
  double result = Librarysystem::multiply(5.0, 3.0);
  EXPECT_DOUBLE_EQ(result, 15.0);
}

TEST_F(LibrarysystemTest, TestDivide) {
  double result = Librarysystem::divide(6.0, 3.0);
  EXPECT_DOUBLE_EQ(result, 2.0);
}

TEST_F(LibrarysystemTest, TestDivideByZero) {
  EXPECT_THROW(Librarysystem::divide(5.0, 0.0), std::invalid_argument);
}

/**
 * @brief The main function of the test program.
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of command-line argument strings.
 * @return int The exit status of the program.
 */
int main(int argc, char **argv) {
#ifdef ENABLE_LIBRARYSYSTEM_TEST
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
#else
  return 0;
#endif
}
