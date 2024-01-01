#define _CRT_SECURE_NO_WARNINGS
#include "../header/librarysystem.h"
#include <iostream>
#include <stdexcept>
#include "librarysystem.h"
#include <regex>
#include <fstream>
#include <stdio.h>
#include <limits>

using namespace std;

void clearScreen() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}// this function clears the console

bool handleInputError(istream &in, ostream &out) {
  in.clear();
  in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  out << "Invalid input. Please enter a number.\n";
  return false;
}// This function prevents entering letters instead of numbers.

int getInput(istream &in) {
  int choice;
  in >> choice;
  return choice;
}// this function gets input from user.

bool registerUser() {
  UserAuthentication auth;
  User newUser;
  cout << "Enter email: ";
  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Yeni satır karakterini yok say
  cin.getline(newUser.email, 100);
  cout << "Enter password: ";
  cin.getline(newUser.password, 100);

  if (auth.registerUser(newUser)) {
    cout << "User registered successfully." << endl;
    return true;
  } else {
    cout << "Failed to register user." << endl;
    return false;
  }
}

bool loginUser() {
  UserAuthentication auth;
  char email[100];
  char password[100];
  cout << "Enter email: ";
  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Yeni satır karakterini yok say
  cin.getline(email, 100);
  cout << "Enter password: ";
  cin.getline(password, 100);

  if (auth.loginUser(email, password)) {
    cout << "Login success." << endl;
    return true;
  } else {
    cout << "Login failed: User not found or wrong password." << endl;
    return false;
  }
}

bool operationsFunc::bookCatalogingMenu() {
  int choice;

  while (true) {
    printMenu::printBookCatalogingMenu(cout);
    choice = getInput(cin);

    if (cin.fail()) {
      handleInputError(cin, cout);
      continue;
    }

    switch (choice) {
      case 1:
        BookSystem::addBook();
        return 0;
        break;

      case 2:
        BookSystem::deleteBook();
        return 0;
        break;

      case 3:
        BookSystem::updateBook();
        return 0;
        break;

      case 4:
        BookSystem::viewCatalog();
        break;

      case 5:
        return userOperations();
        break;

      default:
        break;
    }
  }

  return true;
}

bool operationsFunc::loanManagementMenu() {
  int choice;

  while (true) {
    printMenu::printLoanManagementMenu(cout);
    choice = getInput(cin);

    if (cin.fail()) {
      handleInputError(cin, cout);
      continue;
    }

    switch (choice) {
      case 1:
        LoanManagment::lendBook();
        return 0;

      case 2:
        LoanManagment::borrowBook();
        return 0;

      case 3:
        LoanManagment::viewLoans();
        return 0;

      case 4:
        return userOperations();

      default:
        break;
    }
  }

  return true;
}

bool operationsFunc::wishListMenu() {
  int choice;

  while (true) {
    printMenu::printWishListMenu(cout);
    choice = getInput(cin);

    if (cin.fail()) {
      handleInputError(cin, cout);
      continue;
    }

    switch (choice) {
      case 1:
        WishList::wishList();
        return 0;

      case 2:
        WishList::addToWishList();
        return 0;

      case 3:
        WishList::removeFromWishList();
        return 0;

      case 4:
        return userOperations();

      default:
        break;
    }
  }

  return true;
}

bool operationsFunc::readingTrackerMenu() {
  int choice;

  while (true) {
    printMenu::printReadingTrackerMenu(cout);
    choice = getInput(cin);

    if (cin.fail()) {
      handleInputError(cin, cout);
      continue;
    }

    switch (choice) {
      case 1:
        ReadingTracker::logProgress();
        return true;

      case 2:
        ReadingTracker::markAsRead();
        return true;

      case 3:
        ReadingTracker::viewHistory();
        return true;

      case 4:
        return userOperations();

      default:
        break;
    }
  }

  return true;
}

bool printMenu::printGuestMenu(ostream &out) {
  clearScreen();
  out << "Guest Operations\n\n";
  out << "1. View Catalog\n";
  out << "2. Return to Main Menu\n";
  return true;
}// prints screen GuestMenu.

bool printMenu::printMainMenu(ostream &out) {
  clearScreen();
  out << "Welcome To Personal Library System\n\n";
  out << "1. Login\n";
  out << "2. Register\n";
  out << "3. Guest Mode\n";
  out << "4. Exit Program\n";
  return true;
}// prints screen MainMenu.

bool printMenu::printUserMenu(ostream &out) {
  clearScreen();
  out << "welcome to User Operations\n\n";
  out << "1. Book Cataloging\n";
  out << "2. Loan Management\n";
  out << "3. WishList Management\n";
  out << "4. Reading Tracker\n";
  out << "5. Return Main Menu\n";
  return true;
}// prints screen UserMenu.

bool printMenu::printBookCatalogingMenu(ostream &out) {
  clearScreen();
  out << "welcome to User Operations\n\n";
  out << "1. Add Book\n";
  out << "2. Delete Book\n";
  out << "3. Update Book\n";
  out << "4. View Catalog\n";
  out << "5. Return User Operations\n";
  return true;
}// prints screen BookCatalogingMenu.

bool printMenu::printLoanManagementMenu(ostream &out) {
  clearScreen();
  out << "welcome to LoanManagement\n\n";
  out << "1. Lend Book\n";
  out << "2. Borrow Book\n";
  out << "3. View Loans\n";
  out << "4. Return User Operations\n";
  return true;
}// prints screen LoanManagementMenu.

bool printMenu::printWishListMenu(ostream &out) {
  clearScreen();
  out << "welcome to WishlistManageMenu\n\n";
  out << "1. View Wishlist\n";
  out << "2. Add To Wishlist\n";
  out << "3. Remove From Wishlist\n";
  out << "4. Return User Operations\n";
  return true;
}

bool printMenu::printReadingTrackerMenu(ostream &out) {
  clearScreen();
  out << "welcome to ReadingTrackerMenu\n\n";
  out << "1. Log Progress\n";
  out << "2. Mark As Read\n";
  out << "3. View History\n";
  out << "4. Return User Operations\n";
  return true;
}

bool UserAuthentication::registerUser(const User &newUser) {
  FILE *file;
  errno_t err = fopen_s(&file, "users.bin", "ab");

  if (err != 0 || file == NULL) {
    cerr << "File couldn't be opened for writing." << endl;
    return false;
  }

  fwrite(&newUser, sizeof(User), 1, file);
  fclose(file);
  return true;
}

bool UserAuthentication::loginUser(const char *email, const char *password) {
  FILE *file;
  errno_t err = fopen_s(&file, "users.bin", "rb");

  if (err != 0 || file == NULL) {
    cerr << "File couldn't be opened for reading." << endl;
    return false;
  }

  User user;

  while (fread(&user, sizeof(User), 1, file)) {
    if (strcmp(user.email, email) == 0 && strcmp(user.password, password) == 0) {
      fclose(file);
      cout << "Login success." << std::endl;
      userOperations();
      return true;
    }
  }

  fclose(file);
  cout << "Login failed: User not found or wrong password." << endl;
  return false;
}

bool LoanManagment::borrowBook() {
  return true;
}

bool LoanManagment::lendBook() {
  return true;
}

bool LoanManagment::viewLoans() {
  return true;
}

bool BookSystem::addBook() {
  return true;
}

bool BookSystem::deleteBook() {
  return true;
}

bool BookSystem::updateBook() {
  return true;
}

bool BookSystem::viewCatalog() {
  cout << "empty";
  return true;
}

bool WishList::wishList() {
  return true;
}

bool WishList::addToWishList() {
  return true;
}

bool WishList::removeFromWishList() {
  return true;
}

bool ReadingTracker::logProgress() {
  return true;
}

bool ReadingTracker::markAsRead() {
  return true;
}

bool ReadingTracker::viewHistory() {
  return true;
}

bool userOperations() {
  int choice;

  while (true) {
    clearScreen();
    printMenu::printUserMenu(cout);
    choice = getInput(cin);

    if (cin.fail()) {
      handleInputError(cin, cout);
      continue;
    }

    switch (choice) {
      case 1:
        operationsFunc::bookCatalogingMenu();
        return 0;
        break;

      case 2:
        operationsFunc::loanManagementMenu();
        return 0;
        break;

      case 3:
        operationsFunc::wishListMenu();
        return 0;
        break;

      case 4:
        operationsFunc::readingTrackerMenu();
        return 0;
        break;

      case 5:
        return 0;
        break;

      default:
        break;
    }
  }

  return true;
}

bool guestOperation() {
  int choice;

  while (true) {
    printMenu::printGuestMenu(cout);
    choice = getInput(cin);

    if (cin.fail()) {
      handleInputError(cin, cout);
      continue;
    }

    switch (choice) {
      case 1:
        clearScreen();
        BookSystem::viewCatalog();
        cout << "\nPress any key to return to Main Menu";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        break; // Moved this break here

      case 2:
        return false;

      default:
        cout << "Invalid choice. Please try again.\n";
        break;
    }
  }

  return false;
}

int mainMenu() {
  int choice;

  while (true) {
    printMenu::printMainMenu(cout);
    choice = getInput(cin);

    if (cin.fail()) {
      handleInputError(cin, cout);
      continue;
    }

    switch (choice) {
      case 1:
        clearScreen();
        loginUser();
        break;

      case 2:
        clearScreen();
        registerUser();
        break;

      case 3:
        clearScreen();
        cout << "Guest Operations\n";
        guestOperation();
        break;

      case 4:
        clearScreen();
        cout << "ExitProgram\n";
        return 0;

      default:
        cout << "Invalid choice";
        break;
    }
  }
}
