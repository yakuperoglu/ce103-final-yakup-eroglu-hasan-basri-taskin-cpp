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

bool isValidEmail(const string &email) {
  // Basit bir e-posta formatı doğrulama
  const regex emailPattern(R"(^\w+([\.-]?\w+)*@\w+([\.-]?\w+)*(\.\w{2,3})+$)");
  return regex_match(email, emailPattern);
}

bool isValidPassword(const string &password) {
  // Şifre için minimum uzunluk kriteri
  const size_t minPasswordLength = 6;
  return password.length() >= minPasswordLength;
}

void registerUser() {
  string email, password;
  cout << "Please enter your email: ";
  cin >> email;
  cout << "Please enter your password: ";
  cin >> password;
  User newUser;
  strncpy(newUser.email, email.c_str(), sizeof(newUser.email) - 1);
  newUser.email[sizeof(newUser.email) - 1] = '\0';
  strncpy(newUser.password, password.c_str(), sizeof(newUser.password) - 1);
  newUser.password[sizeof(newUser.password) - 1] = '\0';
  UserAuthentication auth;

  if (auth.writeUser(newUser)) {
    cout << "Registration successful!" << endl;
  } else {
    cout << "Registration failed. Please try again." << endl;
  }
} // not ready to use

void login() {
  string email, password;
  cout << "Please enter your email: ";
  cin >> email;
  cout << "Please enter your password: ";
  cin >> password;

  // Girdi doğrulama
  if (!isValidEmail(email)) {
    cout << "Invalid email format." << endl;
    return;
  }

  if (!isValidPassword(password)) {
    cout << "Password must be at least 6 characters long." << endl;
    return;
  }

  UserAuthentication auth;
  User user = auth.readUser(email.c_str(), password.c_str());
  // Hata ayıklama için ek bilgileri yazdır
  cout << "Returned user email: " << user.email << endl;
  cout << "Returned user password: " << (strlen(user.password) != 0 ? "****" : "(none)") << endl;

  if (strlen(user.email) != 0) {
    cout << "Login successful!" << endl;
    userOperations(); // Kullanıcı işlemlerine yönlendir
  } else {
    cout << "Login failed. Please check your email and password." << endl;
  }
} // not ready to use

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

bool UserAuthentication::writeUser(const User &user) {
  FILE *file = fopen("users.bin", "ab");

  if (!file) {
    perror("File couldn't be opened");
    return false;
  }

  bool writeSuccess = true;

  // Write email and password followed by a null character, and check for write errors
  if (fwrite(user.email, sizeof(char), strlen(user.email), file) != strlen(user.email) ||
      fputc('\0', file) == EOF ||
      fwrite(user.password, sizeof(char), strlen(user.password), file) != strlen(user.password) ||
      fputc('\0', file) == EOF) {
    writeSuccess = false;
  }

  fclose(file); // Ensure file is always closed
  return writeSuccess;
}

User UserAuthentication::readUser(const char *email, const char *password) {
  FILE *file = fopen("users.bin", "rb");

  if (!file) {
    perror("File couldn't be opened");
    return User(); // Boş bir User nesnesi döndürür.
  }

  User user;
  char bufferEmail[maxStringSize];
  char bufferPassword[maxStringSize];
  bool userFound = false;

  while (!feof(file)) {
    // E-posta adresini ve şifreyi oku
    if (fscanf(file, "%99s\n", bufferEmail) == 1 && fscanf(file, "%99s\n", bufferPassword) == 1) {
      cout << "Debug - Read email: " << bufferEmail << ", password: [HIDDEN]" << endl;

      if (strcmp(bufferEmail, email) == 0 && strcmp(bufferPassword, password) == 0) {
        strncpy(user.email, bufferEmail, sizeof(user.email));
        strncpy(user.password, bufferPassword, sizeof(user.password));
        userFound = true;
        break;
      }
    } else {
      cout << "Error reading user data." << endl;
      break;
    }
  }

  fclose(file);
  return userFound ? user : User(); // Eğer kullanıcı bulunursa döndür, bulunamazsa boş bir User nesnesi döndür.
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
        return true;
        switch (choice2) {
          case 1:
            return mainMenu();
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
        userOperations();              // login();
        break;

      case 2:
        clearScreen();
        // registerUser();
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


