#define ENABLE_LIBRARYSYSTEM_TEST

#include "gtest/gtest.h"
#include <sstream>
#include <limits>
#include "librarysystem.h"

class LibrarysystemTest : public ::testing::Test {
 protected:
  std::ostringstream out;
  std::istringstream in;
  void SetUp() override {
    out.str("");
    out.clear();
  }

  void TearDown() override {
    // Clean up test data
  }
  void simulateUserInput(const std::string &input) {
    in.str(input);
    in.clear();
  }
};

TEST_F(LibrarysystemTest, RegisterUserTest) {
  simulateUserInput("erman12\n12");
  EXPECT_TRUE(registerUser(in, out));
  std::string expectedOutput = "Enter email:";
  expectedOutput += "Enter password:";
  expectedOutput += "User registered successfully.\n";
  EXPECT_EQ(expectedOutput, out.str());
}

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
  bool result = printGuestMenu(stream);
  std::string expectedOutput = "Guest Operations\n\n"
                               "1. View Catalog\n"
                               "2. Return to Main Menu\n"
                               "Please enter a number to select:\n";
  EXPECT_TRUE(result);
  EXPECT_EQ(stream.str(), expectedOutput);
}

TEST_F(LibrarysystemTest, PrintMainMenuOutputsCorrectly) {
  std::ostringstream stream;
  bool result = printMainMenu(stream);
  std::string expectedOutput = "Welcome To Personal Library System\n\n"
                               "1. Login\n"
                               "2. Register\n"
                               "3. Guest Mode\n"
                               "4. Exit Program\n"
                               "Please enter a number to select:\n";
  EXPECT_TRUE(result);
  EXPECT_EQ(stream.str(), expectedOutput);
}

TEST_F(LibrarysystemTest, PrintUserMenuOutputsCorrectly) {
  std::ostringstream stream;
  bool result = printUserMenu(stream);
  std::string expectedOutput = "welcome to User Operations\n\n"
                               "1. Book Cataloging\n"
                               "2. Loan Management\n"
                               "3. WishList Management\n"
                               "4. Reading Tracker\n"
                               "5. Return Main Menu\n"
                               "Please enter a number to select:\n";
  EXPECT_TRUE(result);
  EXPECT_EQ(stream.str(), expectedOutput);
}

TEST_F(LibrarysystemTest, PrintBookCatalogingMenuOutputsCorrectly) {
  std::ostringstream stream;
  bool result = printBookCatalogingMenu(stream);
  std::string expectedOutput = "welcome to Book Operations\n\n"
                               "1. Add Book\n"
                               "2. Delete Book\n"
                               "3. Update Book\n"
                               "4. View Catalog\n"
                               "5. Return User Operations\n"
                               "Please enter a number to select:\n";
  EXPECT_TRUE(result);
  EXPECT_EQ(stream.str(), expectedOutput);
}

TEST_F(LibrarysystemTest, PrintLoanManagementMenuOutputsCorrectly) {
  std::ostringstream stream;
  bool result = printLoanManagementMenu(stream);
  std::string expectedOutput = "welcome to LoanManagement\n\n"
                               "1. Lend Book\n"
                               "2. Borrow Book\n"
                               "3. View Loans\n"
                               "4. Return User Operations\n"
                               "Please enter a number to select:\n";
  EXPECT_TRUE(result);
  EXPECT_EQ(stream.str(), expectedOutput);
}

TEST_F(LibrarysystemTest, PrintWishListMenuOutputsCorrectly) {
  std::ostringstream stream;
  bool result = printWishListMenu(stream);
  std::string expectedOutput = "welcome to WishlistManageMenu\n\n"
                               "1. View Wishlist\n"
                               "2. Add To Wishlist\n"
                               "3. Remove From Wishlist\n"
                               "4. Return User Operations\n"
                               "Please enter a number to select:\n";
  EXPECT_TRUE(result);
  EXPECT_EQ(stream.str(), expectedOutput);
}

TEST_F(LibrarysystemTest, PrintReadingTrackerMenuOutputsCorrectly) {
  std::ostringstream stream;
  bool result = printReadingTrackerMenu(stream);
  std::string expectedOutput = "welcome to ReadingTrackerMenu\n\n"
                               "1. Log Progress\n"
                               "2. Mark As Read\n"
                               "3. View History\n"
                               "4. Return User Operations\n"
                               "Please enter a number to select:\n";
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
