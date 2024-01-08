#ifndef LIBRARYSYSTEM_H
#define LIBRARYSYSTEM_H
#define MAX_STRINGSIZE 100
#include <iostream>

using namespace std;

typedef struct {
  int id;
  char name[MAX_STRINGSIZE];
  bool isMarked;
} Book;

typedef struct {
  char email[MAX_STRINGSIZE];
  char password[MAX_STRINGSIZE];
} User;

int getInput(istream &in);// gets input from user.

bool clearPreviousValue(istream &in, ostream &out);

bool enterToContunie(ostream &out);

int getNewId();

bool handleInputError(istream &in, ostream &out);// This function prevents entering letters instead of numbers.

int mainMenu(istream &in, ostream &out);// Main Function.

bool userOperations(istream &in, ostream &out);// holds some operations which user can do.

bool guestOperation(istream &in, ostream &out);

bool registerUser(istream &in, ostream &out);

bool loginUser(istream &in, ostream &out);

bool bookCatalogingMenu(istream &input, ostream &output);
bool loanManagementMenu(istream &input, ostream &output);
bool wishListMenu(istream &input, ostream &output);
bool readingTrackerMenu(istream &input, ostream &output);

bool printMainMenu(ostream &out);
bool printGuestMenu(ostream &out);
bool printUserMenu(ostream &out);
bool printBookCatalogingMenu(ostream &out);
bool printLoanManagementMenu(ostream &out);
bool printWishListMenu(ostream &out);
bool printReadingTrackerMenu(ostream &out);

bool addBook(istream &in, ostream &out);
bool updateBook(istream &in, ostream &out);
bool deleteBook(istream &in, ostream &out);
bool viewCatalog(istream &in, ostream &out);
bool viewCatalogForFunc(istream &in, ostream &out);

bool lendBook(istream &in, ostream &out);
bool borrowBook(istream &in, ostream &out);
bool viewLoans(istream &in, ostream &out);
bool viewLoansForFunc(istream &in, ostream &out);

bool listWishList(istream &in, ostream &out);
bool listWishListForFunc(istream &in, ostream &out);
bool addToWishList(istream &in, ostream &out);
bool removeFromWishList(istream &in, ostream &out);

bool listUnMarkedBooks(istream &in, ostream &out);
bool logProgress(istream &in, ostream &out);
bool markAsRead(istream &in, ostream &out);
bool viewHistory(istream &in, ostream &out);

#endif
