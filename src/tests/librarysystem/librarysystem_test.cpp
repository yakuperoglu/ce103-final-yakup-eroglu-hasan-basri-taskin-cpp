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
  }

  void simulateUserInput(const std::string &input) {
    in.str(input);
    in.clear();
  }
};
TEST_F(LibrarysystemTest, EnterToContinue_Success) {
  simulateUserInput("\n");
  EXPECT_TRUE(enterToContunie(in,out));
  std::string expectedOutput = "\nPress any key to continue";
  EXPECT_EQ(expectedOutput, out.str());
}

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

TEST_F(LibrarysystemTest, GetInputTrueTest) {
  std::istringstream simulatedInput("42");
  int results = getInput(simulatedInput);
  EXPECT_EQ(results, 42);
}

TEST_F(LibrarysystemTest, GetInputFalseTest) {
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

TEST_F(LibrarysystemTest, BookCatalogingMenu_AddBook) {
  simulateUserInput("1\nasd\n5\n5\n4\n");
  EXPECT_TRUE(bookCatalogingMenu(in, out));
  std::string expectedOutput =
    "welcome to Book Operations\n\n1. Add Book\n2. Delete Book\n3. Update Book\n4. View Catalog\n5. Return User Operations\nPlease enter a number to select:\nPlease enter the name of the book you want to add: Book added successfully.\nwelcome to Book Operations\n\n1. Add Book\n2. Delete Book\n3. Update Book\n4. View Catalog\n5. Return User Operations\nPlease enter a number to select:\n";
  EXPECT_EQ(expectedOutput, out.str());
}

TEST_F(LibrarysystemTest, BookCatalogingMenu_DeleteBook) {
  simulateUserInput("2\nasd\n5\n5\n4\n");
  EXPECT_TRUE(bookCatalogingMenu(in, out));
  std::string expectedOutput =
    "welcome to Book Operations\n\n1. Add Book\n2. Delete Book\n3. Update Book\n4. View Catalog\n5. Return User Operations\nPlease enter a number to select:\n1.2\n\nPlease enter the number of the book you want to delete: You must enter a numeric ID.\nwelcome to Book Operations\n\n1. Add Book\n2. Delete Book\n3. Update Book\n4. View Catalog\n5. Return User Operations\nPlease enter a number to select:\n";
  EXPECT_EQ(expectedOutput, out.str());
}

TEST_F(LibrarysystemTest, BookCatalogingMenu_DeleteBookfounfalse) {
  simulateUserInput("2\n50\n5\n5\n4\n");
  EXPECT_TRUE(bookCatalogingMenu(in, out));
  std::string expectedOutput =
    "welcome to Book Operations\n\n1. Add Book\n2. Delete Book\n3. Update Book\n4. View Catalog\n5. Return User Operations\nPlease enter a number to select:\n1.2\n\nPlease enter the number of the book you want to delete: Book with ID 99 not found.\nwelcome to Book Operations\n\n1. Add Book\n2. Delete Book\n3. Update Book\n4. View Catalog\n5. Return User Operations\nPlease enter a number to select:\n";
  EXPECT_EQ(expectedOutput, out.str());
}

TEST_F(LibrarysystemTest, BookCatalogingMenu_DeleteBookfoundtrue) {
  simulateUserInput("2\n7\n5\n5\n4\n");
  EXPECT_TRUE(bookCatalogingMenu(in, out));
  std::string expectedOutput =
    "welcome to Book Operations\n\n1. Add Book\n2. Delete Book\n3. Update Book\n4. View Catalog\n5. Return User Operations\nPlease enter a number to select:\n\nPlease enter the number of the book you want to delete: Book with ID 5 not found.\nwelcome to Book Operations\n\n1. Add Book\n2. Delete Book\n3. Update Book\n4. View Catalog\n5. Return User Operations\nPlease enter a number to select:\n";
  EXPECT_EQ(expectedOutput, out.str());
}

TEST_F(LibrarysystemTest, BookCatalogingMenu_DeleteBookSucces) {
  simulateUserInput("2\n3\n5\n5\n4\n");
  EXPECT_TRUE(bookCatalogingMenu(in, out));
  std::string expectedOutput =
    "welcome to Book Operations\n\n1. Add Book\n2. Delete Book\n3. Update Book\n4. View Catalog\n5. Return User Operations\nPlease enter a number to select:\n1.2\n\nPlease enter the number of the book you want to delete: Book deleted successfully.\nwelcome to Book Operations\n\n1. Add Book\n2. Delete Book\n3. Update Book\n4. View Catalog\n5. Return User Operations\nPlease enter a number to select:\n";
  EXPECT_EQ(expectedOutput, out.str());
}

TEST_F(LibrarysystemTest, BookCatalogingMenu_UpdateBook) {
  simulateUserInput("3\n6\n5\n5\n4\n");
  EXPECT_TRUE(bookCatalogingMenu(in, out));
  std::string expectedOutput =
    "welcome to Book Operations\n\n1. Add Book\n2. Delete Book\n3. Update Book\n4. View Catalog\n5. Return User Operations\nPlease enter a number to select:\n\nPlease enter the number of the book you want to update: welcome to Book Operations\n\n1. Add Book\n2. Delete Book\n3. Update Book\n4. View Catalog\n5. Return User Operations\nPlease enter a number to select:\n";
  EXPECT_EQ(expectedOutput, out.str());
}

TEST_F(LibrarysystemTest, BookCatalogingMenu_ViewCatalog) {
  simulateUserInput("4\nasd\n5\n5\n4\n");
  EXPECT_TRUE(bookCatalogingMenu(in, out));
  std::string expectedOutput =
    "welcome to Book Operations\n\n1. Add Book\n2. Delete Book\n3. Update Book\n4. View Catalog\n5. Return User Operations\nPlease enter a number to select:\n\nPress enter to return to Main Menuwelcome to Book Operations\n\n1. Add Book\n2. Delete Book\n3. Update Book\n4. View Catalog\n5. Return User Operations\nPlease enter a number to select:\nInvalid input. Please enter a number.\nwelcome to Book Operations\n\n1. Add Book\n2. Delete Book\n3. Update Book\n4. View Catalog\n5. Return User Operations\nPlease enter a number to select:\n";
  EXPECT_EQ(expectedOutput, out.str());
}

TEST_F(LibrarysystemTest, BookCatalogingMenu_InvalidOption) {
  simulateUserInput("9\n5\n5\n4\n"); // Simulating user selecting an invalid option
  EXPECT_TRUE(bookCatalogingMenu(in, out));
  std::string expectedOutput =
    "welcome to Book Operations\n\n1. Add Book\n2. Delete Book\n3. Update Book\n4. View Catalog\n5. Return User Operations\nPlease enter a number to select:\nInvalid option. Please try again.\nwelcome to Book Operations\n\n1. Add Book\n2. Delete Book\n3. Update Book\n4. View Catalog\n5. Return User Operations\nPlease enter a number to select:\n";
  EXPECT_EQ(expectedOutput, out.str());
}

TEST_F(LibrarysystemTest, BookCatalogingMenu_Infail) {
  simulateUserInput("a\n5\n5\n4\n"); // Simulating user selecting an invalid option
  EXPECT_TRUE(bookCatalogingMenu(in, out));
  std::string expectedOutput =
    "welcome to Book Operations\n\n1. Add Book\n2. Delete Book\n3. Update Book\n4. View Catalog\n5. Return User Operations\nPlease enter a number to select:\nInvalid input. Please enter a number.\nwelcome to Book Operations\n\n1. Add Book\n2. Delete Book\n3. Update Book\n4. View Catalog\n5. Return User Operations\nPlease enter a number to select:\n";
  EXPECT_EQ(expectedOutput, out.str());
}

TEST_F(LibrarysystemTest, BookCatalogingMenu_ExitMenu) {
  simulateUserInput("5\n"); // Simulating user selecting 'Return User Operations'
  EXPECT_TRUE(bookCatalogingMenu(in, out));
}

TEST_F(LibrarysystemTest, LoanManagementMenu_LendBook) {
  simulateUserInput("1\n1\n4\n5\n4\n"); // Simulating user selecting 'Lend Book'
  EXPECT_TRUE(loanManagementMenu(in, out));
  std::string expectedOutput =
    "welcome to LoanManagement\n\n1. Lend Book\n2. Borrow Book\n3. View Loans\n4. Return User Operations\nPlease enter a number to select:\n\nPlease enter the ID of the book you want to return: welcome to LoanManagement\n\n1. Lend Book\n2. Borrow Book\n3. View Loans\n4. Return User Operations\nPlease enter a number to select:\n";
  EXPECT_EQ(expectedOutput, out.str());
}

TEST_F(LibrarysystemTest, LoanManagementMenu_ViewLoans) {
  simulateUserInput("3\n\n4\n5\n4\n"); // Simulating user selecting 'View Loans'
  EXPECT_TRUE(loanManagementMenu(in, out));
  std::string expectedOutput =
    "welcome to LoanManagement\n\n1. Lend Book\n2. Borrow Book\n3. View Loans\n4. Return User Operations\nPlease enter a number to select:\nLoaned Books:\n\nPress any key to return to Main Menuwelcome to LoanManagement\n\n1. Lend Book\n2. Borrow Book\n3. View Loans\n4. Return User Operations\nPlease enter a number to select:\n";
  EXPECT_EQ(expectedOutput, out.str());
}

TEST_F(LibrarysystemTest, LoanManagementMenu_BorrowBook) {
  simulateUserInput("2\n\n4\n5\n4\n");
  EXPECT_TRUE(loanManagementMenu(in, out));
  std::string expectedOutput =
    "welcome to LoanManagement\n\n1. Lend Book\n2. Borrow Book\n3. View Loans\n4. Return User Operations\nPlease enter a number to select:\n\nPlease enter the ID of the book you want to borrow: welcome to LoanManagement\n\n1. Lend Book\n2. Borrow Book\n3. View Loans\n4. Return User Operations\nPlease enter a number to select:\nInvalid option. Please try again.\nwelcome to LoanManagement\n\n1. Lend Book\n2. Borrow Book\n3. View Loans\n4. Return User Operations\nPlease enter a number to select:\n";
  EXPECT_EQ(expectedOutput, out.str());
}

TEST_F(LibrarysystemTest, LoanManagementMenu_default) {
  simulateUserInput("87\n\n4\n5\n4\n");
  EXPECT_TRUE(loanManagementMenu(in, out));
  std::string expectedOutput =
    "welcome to LoanManagement\n\n1. Lend Book\n2. Borrow Book\n3. View Loans\n4. Return User Operations\nPlease enter a number to select:\nInvalid option. Please try again.\nwelcome to LoanManagement\n\n1. Lend Book\n2. Borrow Book\n3. View Loans\n4. Return User Operations\nPlease enter a number to select:\n";
  EXPECT_EQ(expectedOutput, out.str());
}

TEST_F(LibrarysystemTest, LoanManagementMenu_Infail) {
  simulateUserInput("a\n\n4\n5\n4\n");
  EXPECT_TRUE(loanManagementMenu(in, out));
  std::string expectedOutput =
    "welcome to LoanManagement\n\n1. Lend Book\n2. Borrow Book\n3. View Loans\n4. Return User Operations\nPlease enter a number to select:\nInvalid input. Please enter a number.\nwelcome to LoanManagement\n\n1. Lend Book\n2. Borrow Book\n3. View Loans\n4. Return User Operations\nPlease enter a number to select:\n";
  EXPECT_EQ(expectedOutput, out.str());
}

TEST_F(LibrarysystemTest, LoanManagementMenu_ExitMenu) {
  simulateUserInput("4\n5\n4\n"); // Simulating user selecting 'Return to Main Menu'
  EXPECT_TRUE(loanManagementMenu(in, out));
}

TEST_F(LibrarysystemTest, wishListMenu_listWishlist) {
  simulateUserInput("1\n\n4\n5\n4\n");
  EXPECT_FALSE(wishListMenu(in, out));
  std::string expectedOutput =
    "welcome to WishlistManageMenu\n\n1. View Wishlist\n2. Add To Wishlist\n3. Remove From Wishlist\n4. Return User Operations\nPlease enter a number to select:\nWishlist:\n1 2\n1 2\n\nPress Enter to exit.\nwelcome to WishlistManageMenu\n\n1. View Wishlist\n2. Add To Wishlist\n3. Remove From Wishlist\n4. Return User Operations\nPlease enter a number to select:\n";
  EXPECT_EQ(expectedOutput, out.str());
}

TEST_F(LibrarysystemTest, wishListMenu_addToWishlist) {
  simulateUserInput("2\n6\n4\n5\n4\n");
  EXPECT_FALSE(wishListMenu(in, out));
  std::string expectedOutput =
    "welcome to WishlistManageMenu\n\n1. View Wishlist\n2. Add To Wishlist\n3. Remove From Wishlist\n4. Return User Operations\nPlease enter a number to select:\nEnter the ID of the book to add to the wishlist: Book not found.\nwelcome to WishlistManageMenu\n\n1. View Wishlist\n2. Add To Wishlist\n3. Remove From Wishlist\n4. Return User Operations\nPlease enter a number to select:\n";
  EXPECT_EQ(expectedOutput, out.str());
}

TEST_F(LibrarysystemTest, wishListMenu_RemoveFromWishlist) {
  simulateUserInput("3\n5\n4\n5\n4\n");
  EXPECT_FALSE(wishListMenu(in, out));
  std::string expectedOutput =
    "welcome to WishlistManageMenu\n\n1. View Wishlist\n2. Add To Wishlist\n3. Remove From Wishlist\n4. Return User Operations\nPlease enter a number to select:\nWishlist:\nEnter the ID of the book to remove from the wishlist: Book not found.\nwelcome to WishlistManageMenu\n\n1. View Wishlist\n2. Add To Wishlist\n3. Remove From Wishlist\n4. Return User Operations\nPlease enter a number to select:\n";
  EXPECT_EQ(expectedOutput, out.str());
}

TEST_F(LibrarysystemTest, wishListMenu_RemoveFromWishlistfoundtrue) {
  simulateUserInput("3\n2\n4\n5\n4\n");
  EXPECT_FALSE(wishListMenu(in, out));
  std::string expectedOutput =
    "welcome to WishlistManageMenu\n\n1. View Wishlist\n2. Add To Wishlist\n3. Remove From Wishlist\n4. Return User Operations\nPlease enter a number to select:\nWishlist:\n1 2\n1 2\nEnter the ID of the book to remove from the wishlist: Book not found.\nwelcome to WishlistManageMenu\n\n1. View Wishlist\n2. Add To Wishlist\n3. Remove From Wishlist\n4. Return User Operations\nPlease enter a number to select:\n";
  EXPECT_EQ(expectedOutput, out.str());
}

TEST_F(LibrarysystemTest, wishListMenu_InvalidInput) {
  simulateUserInput("98\n4\n5\n4\n");
  EXPECT_FALSE(wishListMenu(in, out));
  std::string expectedOutput =
    "welcome to WishlistManageMenu\n\n1. View Wishlist\n2. Add To Wishlist\n3. Remove From Wishlist\n4. Return User Operations\nPlease enter a number to select:\nInvalid option. Please try again.\nwelcome to WishlistManageMenu\n\n1. View Wishlist\n2. Add To Wishlist\n3. Remove From Wishlist\n4. Return User Operations\nPlease enter a number to select:\n";
  EXPECT_EQ(expectedOutput, out.str());
}

TEST_F(LibrarysystemTest, wishListMenu_Infail) {
  simulateUserInput("a\n4\n5\n4\n");
  EXPECT_FALSE(wishListMenu(in, out));
  std::string expectedOutput =
    "welcome to WishlistManageMenu\n\n1. View Wishlist\n2. Add To Wishlist\n3. Remove From Wishlist\n4. Return User Operations\nPlease enter a number to select:\nInvalid input. Please enter a number.\nwelcome to WishlistManageMenu\n\n1. View Wishlist\n2. Add To Wishlist\n3. Remove From Wishlist\n4. Return User Operations\nPlease enter a number to select:\n";
  EXPECT_EQ(expectedOutput, out.str());
}

TEST_F(LibrarysystemTest, readingTrackerMenu_logProgress) {
  simulateUserInput("1\nn4\n5\n4\n");
  EXPECT_FALSE(readingTrackerMenu(in, out));
  std::string expectedOutput =
    "welcome to ReadingTrackerMenu\n\n1. Log Progress\n2. Mark As Read\n3. View History\n4. Return User Operations\nPlease enter a number to select:\nThere are no books.\n\nPress any key to continuewelcome to ReadingTrackerMenu\n\n1. Log Progress\n2. Mark As Read\n3. View History\n4. Return User Operations\nPlease enter a number to select:\n";
  EXPECT_EQ(expectedOutput, out.str());
}

TEST_F(LibrarysystemTest, readingTrackerMenu_MarkAsRead) {
  simulateUserInput("asd\n2\n2\n2\n5\n4\n");
  addBook(in, out);
  EXPECT_FALSE(readingTrackerMenu(in, out));
  std::string expectedOutput =
    "Please enter the name of the book you want to add: Book added successfully.\nwelcome to ReadingTrackerMenu\n\n1. Log Progress\n2. Mark As Read\n3. View History\n4. Return User Operations\nPlease enter a number to select:\nUnmarked Books:\nID: 1\tName: 2\n\nEnter the ID of the book to mark as read: welcome to ReadingTrackerMenu\n\n1. Log Progress\n2. Mark As Read\n3. View History\n4. Return User Operations\nPlease enter a number to select:\nwelcome to ReadingTrackerMenu\n\n1. Log Progress\n2. Mark As Read\n3. View History\n4. Return User Operations\nPlease enter a number to select:\n";
  EXPECT_EQ(expectedOutput, out.str());
}

TEST_F(LibrarysystemTest, readingTrackerMenu_ViewHistory) {
  simulateUserInput("3\n\n\n4\n5\n4\n");
  EXPECT_FALSE(readingTrackerMenu(in, out));
  std::string expectedOutput =
    "welcome to ReadingTrackerMenu\n\n1. Log Progress\n2. Mark As Read\n3. View History\n4. Return User Operations\nPlease enter a number to select:\nMarked Books:\n\nPress any key to continuewelcome to ReadingTrackerMenu\n\n1. Log Progress\n2. Mark As Read\n3. View History\n4. Return User Operations\nPlease enter a number to select:\n";
  EXPECT_EQ(expectedOutput, out.str());
}

TEST_F(LibrarysystemTest, readingTrackerMenu_Infail) {
  simulateUserInput("a\n\n\n4\n5\n4\n");
  EXPECT_FALSE(readingTrackerMenu(in, out));
  std::string expectedOutput =
    "welcome to ReadingTrackerMenu\n\n1. Log Progress\n2. Mark As Read\n3. View History\n4. Return User Operations\nPlease enter a number to select:\nInvalid input. Please enter a number.\nwelcome to ReadingTrackerMenu\n\n1. Log Progress\n2. Mark As Read\n3. View History\n4. Return User Operations\nPlease enter a number to select:\n";
  EXPECT_EQ(expectedOutput, out.str());
}

TEST_F(LibrarysystemTest, MainMenu_RegisterUser) {
  simulateUserInput("2\n\n\n4\n");
  EXPECT_EQ(0, mainMenu(in, out));
  std::string expectedOutput =
    "Welcome To Personal Library System\n\n1. Login\n2. Register\n3. Guest Mode\n4. Exit Program\nPlease enter a number to select:\nEnter email:Enter password:User registered successfully.\nWelcome To Personal Library System\n\n1. Login\n2. Register\n3. Guest Mode\n4. Exit Program\nPlease enter a number to select:\nExitProgram\n";
  EXPECT_EQ(expectedOutput, out.str());
}

TEST_F(LibrarysystemTest, MainMenu_LoginUser) {
  simulateUserInput("1\n\n\n5\n4\n");
  EXPECT_EQ(0, mainMenu(in, out));
  std::string expectedOutput =
    "Welcome To Personal Library System\n\n1. Login\n2. Register\n3. Guest Mode\n4. Exit Program\nPlease enter a number to select:\nEnter email:Enter password:Login success.\nwelcome to User Operations\n\n1. Book Cataloging\n2. Loan Management\n3. WishList Management\n4. Reading Tracker\n5. Return Main Menu\nPlease enter a number to select:\nWelcome To Personal Library System\n\n1. Login\n2. Register\n3. Guest Mode\n4. Exit Program\nPlease enter a number to select:\nExitProgram\n";
  EXPECT_EQ(expectedOutput, out.str());
}

TEST_F(LibrarysystemTest, MainMenu_LoginUserFail) {
  simulateUserInput("1\naasdasdasdasd\n\n5\n4\n");
  EXPECT_EQ(0, mainMenu(in, out));
  std::string expectedOutput =
    "Welcome To Personal Library System\n\n1. Login\n2. Register\n3. Guest Mode\n4. Exit Program\nPlease enter a number to select:\nEnter email:Enter password:Login failed: User not found or wrong password.\nWelcome To Personal Library System\n\n1. Login\n2. Register\n3. Guest Mode\n4. Exit Program\nPlease enter a number to select:\nInvalid choiceWelcome To Personal Library System\n\n1. Login\n2. Register\n3. Guest Mode\n4. Exit Program\nPlease enter a number to select:\nExitProgram\n";
  EXPECT_EQ(expectedOutput, out.str());
}

TEST_F(LibrarysystemTest, MainMenu_GuestOperation) {
  simulateUserInput("3\n1\n\n2\n4\n"); // Simulating user selecting 'Guest Operation'
  EXPECT_EQ(0, mainMenu(in, out));
  std::string expectedOutput =
    "Welcome To Personal Library System\n\n1. Login\n2. Register\n3. Guest Mode\n4. Exit Program\nPlease enter a number to select:\nGuest Operations\nGuest Operations\n\n1. View Catalog\n2. Return to Main Menu\nPlease enter a number to select:\n1.2\n\nPress enter to return to Main MenuGuest Operations\n\n1. View Catalog\n2. Return to Main Menu\nPlease enter a number to select:\nWelcome To Personal Library System\n\n1. Login\n2. Register\n3. Guest Mode\n4. Exit Program\nPlease enter a number to select:\nExitProgram\n";
  EXPECT_EQ(expectedOutput, out.str());
}

TEST_F(LibrarysystemTest, MainMenu_ExitProgram) {
  simulateUserInput("4\n"); // Simulating user selecting 'Exit Program'
  EXPECT_EQ(0, mainMenu(in, out));
  std::string expectedOutput = "Welcome To Personal Library System\n\n1. Login\n2. Register\n3. Guest Mode\n4. Exit Program\nPlease enter a number to select:\nExitProgram\n";
  EXPECT_EQ(expectedOutput, out.str());
}

TEST_F(LibrarysystemTest, MainMenu_InvalidChoice) {
  simulateUserInput("5\n4\n"); // Simulating user selecting an invalid option
  EXPECT_EQ(0, mainMenu(in, out));
  std::string expectedOutput =
    "Welcome To Personal Library System\n\n1. Login\n2. Register\n3. Guest Mode\n4. Exit Program\nPlease enter a number to select:\nInvalid choiceWelcome To Personal Library System\n\n1. Login\n2. Register\n3. Guest Mode\n4. Exit Program\nPlease enter a number to select:\nExitProgram\n";
  EXPECT_EQ(expectedOutput, out.str());
}

TEST_F(LibrarysystemTest, MainMenu_Infail) {
  simulateUserInput("asd\n4\n"); // Simulating user selecting an invalid option
  EXPECT_EQ(0, mainMenu(in, out));
  std::string expectedOutput =
    "Welcome To Personal Library System\n\n1. Login\n2. Register\n3. Guest Mode\n4. Exit Program\nPlease enter a number to select:\nInvalid input. Please enter a number.\nWelcome To Personal Library System\n\n1. Login\n2. Register\n3. Guest Mode\n4. Exit Program\nPlease enter a number to select:\nExitProgram\n";
  EXPECT_EQ(expectedOutput, out.str());
}

TEST_F(LibrarysystemTest, GuestOperation_ReturnToMainMenu) {
  simulateUserInput("2\n4\n");
  EXPECT_EQ(0, guestOperation(in, out));
  std::string expectedOutput = "Guest Operations\n\n1. View Catalog\n2. Return to Main Menu\nPlease enter a number to select:\n";
  EXPECT_EQ(expectedOutput, out.str());
}

TEST_F(LibrarysystemTest, GuestOperation_InvalidChoice) {
  simulateUserInput("3\n2\n4\n");
  EXPECT_EQ(0, guestOperation(in, out));
  std::string expectedOutput =
    "Guest Operations\n\n1. View Catalog\n2. Return to Main Menu\nPlease enter a number to select:\nInvalid choice. Please try again.\nGuest Operations\n\n1. View Catalog\n2. Return to Main Menu\nPlease enter a number to select:\n";
  EXPECT_EQ(expectedOutput, out.str());
}

TEST_F(LibrarysystemTest, GuestOperation_Infail) {
  simulateUserInput("a\n2\n4\n");
  EXPECT_EQ(0, guestOperation(in, out));
  std::string expectedOutput =
    "Guest Operations\n\n1. View Catalog\n2. Return to Main Menu\nPlease enter a number to select:\nInvalid input. Please enter a number.\nGuest Operations\n\n1. View Catalog\n2. Return to Main Menu\nPlease enter a number to select:\n";
  EXPECT_EQ(expectedOutput, out.str());
}

TEST_F(LibrarysystemTest, UserOperations_BookCatalogingMenu) {
  simulateUserInput("1\n5\n5\n4\n"); // Simulating user selecting 'Book Cataloging'
  EXPECT_FALSE(userOperations(in, out));
  std::string expectedOutput =
    "welcome to User Operations\n\n1. Book Cataloging\n2. Loan Management\n3. WishList Management\n4. Reading Tracker\n5. Return Main Menu\nPlease enter a number to select:\nwelcome to Book Operations\n\n1. Add Book\n2. Delete Book\n3. Update Book\n4. View Catalog\n5. Return User Operations\nPlease enter a number to select:\nwelcome to User Operations\n\n1. Book Cataloging\n2. Loan Management\n3. WishList Management\n4. Reading Tracker\n5. Return Main Menu\nPlease enter a number to select:\n";
  EXPECT_EQ(expectedOutput, out.str());
}

TEST_F(LibrarysystemTest, UserOperations_LoanManagementMenu) {
  simulateUserInput("2\n4\n5\n4\n"); // Simulating user selecting 'Loan Management'
  EXPECT_FALSE(userOperations(in, out));
  std::string expectedOutput =
    "welcome to User Operations\n\n1. Book Cataloging\n2. Loan Management\n3. WishList Management\n4. Reading Tracker\n5. Return Main Menu\nPlease enter a number to select:\nwelcome to LoanManagement\n\n1. Lend Book\n2. Borrow Book\n3. View Loans\n4. Return User Operations\nPlease enter a number to select:\nwelcome to User Operations\n\n1. Book Cataloging\n2. Loan Management\n3. WishList Management\n4. Reading Tracker\n5. Return Main Menu\nPlease enter a number to select:\n";
  EXPECT_EQ(expectedOutput, out.str());
}

TEST_F(LibrarysystemTest, UserOperations_WishListMenu) {
  simulateUserInput("3\n4\n5\n4\n"); // Simulating user selecting 'Wish List'
  EXPECT_FALSE(userOperations(in, out));
  std::string expectedOutput =
    "welcome to User Operations\n\n1. Book Cataloging\n2. Loan Management\n3. WishList Management\n4. Reading Tracker\n5. Return Main Menu\nPlease enter a number to select:\nwelcome to WishlistManageMenu\n\n1. View Wishlist\n2. Add To Wishlist\n3. Remove From Wishlist\n4. Return User Operations\nPlease enter a number to select:\nwelcome to User Operations\n\n1. Book Cataloging\n2. Loan Management\n3. WishList Management\n4. Reading Tracker\n5. Return Main Menu\nPlease enter a number to select:\n";
  EXPECT_EQ(expectedOutput, out.str());
}

TEST_F(LibrarysystemTest, UserOperations_ReadingTrackerMenu) {
  simulateUserInput("4\n4\n5\n4\n"); // Simulating user selecting 'Reading Tracker'
  EXPECT_FALSE(userOperations(in, out));
  std::string expectedOutput =
    "welcome to User Operations\n\n1. Book Cataloging\n2. Loan Management\n3. WishList Management\n4. Reading Tracker\n5. Return Main Menu\nPlease enter a number to select:\nwelcome to ReadingTrackerMenu\n\n1. Log Progress\n2. Mark As Read\n3. View History\n4. Return User Operations\nPlease enter a number to select:\nwelcome to User Operations\n\n1. Book Cataloging\n2. Loan Management\n3. WishList Management\n4. Reading Tracker\n5. Return Main Menu\nPlease enter a number to select:\n";
  EXPECT_EQ(expectedOutput, out.str());
}

TEST_F(LibrarysystemTest, UserOperations_Infail) {
  simulateUserInput("a\n\n5\n4\n");
  EXPECT_FALSE(userOperations(in, out));
  std::string expectedOutput =
    "welcome to User Operations\n\n1. Book Cataloging\n2. Loan Management\n3. WishList Management\n4. Reading Tracker\n5. Return Main Menu\nPlease enter a number to select:\nInvalid input. Please enter a number.\nwelcome to User Operations\n\n1. Book Cataloging\n2. Loan Management\n3. WishList Management\n4. Reading Tracker\n5. Return Main Menu\nPlease enter a number to select:\n";
  EXPECT_EQ(expectedOutput, out.str());
}

TEST_F(LibrarysystemTest, UserOperations_ReturnToMainMenu) {
  simulateUserInput("5\n4\n");
  EXPECT_FALSE(userOperations(in, out));
}

TEST_F(LibrarysystemTest, ViewLoansForFunc_Successful) {
  EXPECT_TRUE(viewLoansForFunc(out));
  std::string expectedOutput = "";
  EXPECT_EQ(expectedOutput, out.str());
}

TEST_F(LibrarysystemTest, RemoveFromWishList_NotSuccessful) {
  simulateUserInput("123\n");
  EXPECT_FALSE(removeFromWishList(in, out));
  std::string expectedOutput = "Wishlist:\nEnter the ID of the book to remove from the wishlist: Book not found.\n";
  EXPECT_EQ(expectedOutput, out.str());
}

TEST_F(LibrarysystemTest, RemoveFromWishList_BookNotFound) {
  simulateUserInput("999\n");
  EXPECT_FALSE(removeFromWishList(in, out));
  std::string expectedOutput = "Wishlist:\nEnter the ID of the book to remove from the wishlist: Book not found.\n";
  EXPECT_EQ(expectedOutput, out.str());
}

TEST_F(LibrarysystemTest, RemoveFromWishList_FileError) {
  EXPECT_FALSE(removeFromWishList(in, out));
}

TEST_F(LibrarysystemTest, AddToWishList_NotSuccessful) {
  simulateUserInput("123\n");
  EXPECT_FALSE(addToWishList(in, out));
  std::string expectedOutput = "1.2\nEnter the ID of the book to add to the wishlist: Book not found.\n";
  EXPECT_EQ(expectedOutput, out.str());
}

TEST_F(LibrarysystemTest, AddToWishList_BookNotFound) {
  simulateUserInput("1\n");
  EXPECT_FALSE(addToWishList(in, out));
  std::string expectedOutput = "Enter the ID of the book to add to the wishlist: Book not found.\n";
  EXPECT_EQ(expectedOutput, out.str());
}

TEST_F(LibrarysystemTest, AddToWishList_FileError) {
  EXPECT_FALSE(addToWishList(in, out));
}

int main(int argc, char **argv) {
#ifdef ENABLE_LIBRARYSYSTEM_TEST
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
#else
  return 0;
#endif
}
