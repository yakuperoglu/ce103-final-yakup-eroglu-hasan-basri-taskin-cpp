#ifndef LIBRARYSYSTEM_H
#define LIBRARYSYSTEM_H

#include <iostream>


using namespace std;

int getInput(istream &in);// gets input from user.

bool handleInputError(istream &in, ostream &out);// This function prevents entering letters instead of numbers.

int mainMenu();//Main Function.

bool userOperations();

bool registerUser();

bool loginUser();

const int maxStringSize = 100;

struct User {
  char email[maxStringSize];
  char password[maxStringSize];
};

struct UserAuthentication {
  bool registerUser(const User &newUser);
  bool loginUser(const char *email, const char *password);
};

struct operationsFunc {
  static bool bookCatalogingMenu();
  static bool loanManagementMenu();
  static bool wishListMenu();
  static bool readingTrackerMenu();
};

struct printMenu {
  static bool printMainMenu(ostream &out);
  static bool printGuestMenu(ostream &out);
  static bool printUserMenu(ostream &out);
  static bool printBookCatalogingMenu(ostream &out);
  static bool printLoanManagementMenu(ostream &out);
  static bool printWishListMenu(ostream &out);
  static bool printReadingTrackerMenu(ostream &out);
};

struct BookSystem {
  static bool addBook();
  static bool updateBook();
  static bool deleteBook();
  static bool viewCatalog();
};

struct LoanManagment {
  static bool lendBook();
  static bool borrowBook();
  static bool viewLoans();
};

struct WishList {
  static bool wishList();
  static bool addToWishList();
  static bool removeFromWishList();
};

struct ReadingTracker {
  static bool logProgress();
  static bool markAsRead();
  static bool viewHistory();
};

struct FileBinaryOperations {
  bool WriteFile();
  bool ReadFile();
  bool ConvertBinaryToText();
  bool ConvertTextToBinary();
};
#endif
