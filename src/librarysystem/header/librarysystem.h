#ifndef LIBRARYSYSTEM_H
#define LIBRARYSYSTEM_H
#define MAX_STRINGSIZE 100
#include <iostream>

using namespace std;

typedef struct {
  int id;
  char name[MAX_STRINGSIZE];
} Book;

typedef struct {
  char email[MAX_STRINGSIZE];
  char password[MAX_STRINGSIZE];
} User;

int getInput(istream &in);// gets input from user.

int getNewId();

bool handleInputError(istream &in, ostream &out);// This function prevents entering letters instead of numbers.

int mainMenu(std::istream &in, std::ostream &out);// Main Function.

bool userOperations();// holds some operations which user can do.

bool registerUser(std::istream &in, std::ostream &out);

bool loginUser(std::istream &in, std::ostream &out);

bool writeRegisterUser(const User &newUser);

bool readLoginUser(const char *email, const char *password);

bool bookCatalogingMenu();
bool loanManagementMenu();
bool wishListMenu();
bool readingTrackerMenu();

bool printMainMenu(ostream &out);
bool printGuestMenu(ostream &out);
bool printUserMenu(ostream &out);
bool printBookCatalogingMenu(ostream &out);
bool printLoanManagementMenu(ostream &out);
bool printWishListMenu(ostream &out);
bool printReadingTrackerMenu(ostream &out);

bool addBook();
bool updateBook();
bool deleteBook();
bool viewCatalog();
bool viewCatalogForFunc();

bool lendBook();
bool borrowBook();
bool viewLoans();

bool wishList();
bool addToWishList();
bool removeFromWishList();

bool logProgress();
bool markAsRead();
bool viewHistory();

#endif
