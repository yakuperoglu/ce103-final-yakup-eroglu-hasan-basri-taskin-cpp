#define ENABLE_LIBRARYSYSTEM_TEST

#include "gtest/gtest.h"
#include <sstream>
#include <limits>
#include "librarysystem.h"

class LibrarysystemTest : public ::testing::Test {
 protected:
  void SetUp() override {
    // Setup test data
  }

  void TearDown() override {
    // Clean up test data
  }
};

TEST_F(LibrarysystemTest, OutputsErrorMessageAndReturnsFalse) {
  std::istringstream simulatedInput("invalid input");
  std::ostringstream simulatedOutput;
  bool result = handleInputError(simulatedInput, simulatedOutput);
  std::string expectedOutput = "Invalid input. Please enter a number.\n";
  EXPECT_FALSE(result);
  EXPECT_EQ(simulatedOutput.str(), expectedOutput);
}

TEST_F(LibrarysystemTest, GetInputReturnsCorrectValue) {
  std::istringstream simulatedInput("42");
  int result = getInput(simulatedInput);
  EXPECT_EQ(result, 42);
}

TEST_F(LibrarysystemTest, GetInputHandlesInvalidInput) {
  std::istringstream simulatedInput("abc");
  int result = getInput(simulatedInput);
  EXPECT_TRUE(simulatedInput.fail());
}

TEST_F(LibrarysystemTest, PrintGuestMenuOutputsCorrectly) {
  std::ostringstream stream;
  printMenu menu;
  bool result = menu.printGuestMenu(stream);
  std::string expectedOutput = "\n1. View Catalog\n2. Return to Main Menu\n";
  EXPECT_TRUE(result);
  EXPECT_EQ(stream.str(), expectedOutput);
}

TEST_F(LibrarysystemTest, PrintMainMenuOutputsCorrectly) {
  std::ostringstream stream;
  printMenu menu;
  bool result = menu.printMainMenu(stream);
  std::string expectedOutput = "Welcome To Personal Library System\n\n"
                               "1. Login\n"
                               "2. Register\n"
                               "3. Guest Mode\n"
                               "4. Exit Program\n";
  EXPECT_TRUE(result);
  EXPECT_EQ(stream.str(), expectedOutput);
}

TEST_F(LibrarysystemTest, PrintUserMenuOutputsCorrectly) {
  std::ostringstream stream;
  printMenu menu;
  bool result = menu.printUserMenu(stream);
  std::string expectedOutput = "welcome to User Operations\n\n"
                               "1. Book Cataloging\n"
                               "2. Loan Management\n"
                               "3. WishList Management\n"
                               "4. Reading Tracker\n"
                               "5. Return Main Menu\n";
  EXPECT_TRUE(result);
  EXPECT_EQ(stream.str(), expectedOutput);
}



int main(int argc, char **argv) {
#ifdef ENABLE_LIBRARYSYSTEM_TEST
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
#else
  return 0;
#endif
}
