#define _CRT_SECURE_NO_WARNINGS
#include "../header/librarysystem.h"
#include <iostream>
#include <stdexcept>
#include "librarysystem.h"
#include <fstream>
#include <stdio.h>
#define MAX_STRING_LENGTH 100
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


bool UserAuthentication::writeUser(const User &user) {
  //The "ab" mode (append binary) option allows you to append data to the file as binary. If file doesn't exist it will create.
  FILE *file = fopen("users.bin", "ab");

  if (!file) {
    perror("File couldn't be opened");
    return false;
  }

  // Write Email and after that add a null character
  fwrite(user.email, sizeof(char), strlen(user.email), file);
  fputc('\0', file); // Null karakter ekle
  // Write Name and after that add a null character
  fwrite(user.name, sizeof(char), strlen(user.name), file);
  fputc('\0', file); // Null karakter ekle
  // Write SurName and after that add a null character
  fwrite(user.surname, sizeof(char), strlen(user.surname), file);
  fputc('\0', file); // Null karakter ekle
  // Write Password and after that add a null character
  fwrite(user.password, sizeof(char), strlen(user.password), file);
  fputc('\n', file);
  fclose(file);
  return true;
}
bool printMenu::printWishListMenu(ostream &out) {
  clearScreen();
  out << "welcome to WishlistManageMenu\n\n";
  out << "1. View Wishlist\n";
  out << "2. Add To Wishlist\n";
  out << "3. Remove From Wishlist\n";
  out << "4. Return User Operations\n";
  return true;
}
bool UserAuthentication::login(const char *email, const char *password) {
  FILE *file = fopen("users.bin", "rb");

  if (!file) {
    return false;
  }

  User user;

  // Here is we are reading user datas
  while (fread(&user, sizeof(User), 1, file)) {
    // Compares two C-strings and returns 0 if they are identical.
    // If not, it returns a non-zero value indicating the lexicographical difference between them.
    if (strcmp(user.email, email) == 0 && strcmp(user.password, password) == 0) {
      fclose(file);
      return true; // E-posta ve şifre eşleşti
    }
  }

  fclose(file);
  return false; // Eşleşme bulunamadı
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

bool operationsFunc::loginMenu() {
  while (true) {
    clearScreen();
    char email[MAX_STRING_LENGTH] = { };
    char password[MAX_STRING_LENGTH] = { };
    cout << "Please enter your email.\n";
    cin >> email;
    cout << "Please enter your password.\n";
    cin >> password;
    bool result = UserAuthentication::login(email, password);

    if (result) {
      printf("HELLOOOO GEÇTIN");
    } else {
      printf("HELLOOOOO SICTIN");
    }

    cout << "Press enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Önceki girişten kalanları temizle
    cin.get(); // Kullanıcıdan yeni bir giriş bekler (Enter tuşu bekler)
  }

  return false;
}


bool WishList::wishList() {
  return 0;
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
          // login func
          break;

        case 2:
          clearScreen();
          // register func
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

    return 0;
  }//guests can only view the catalog
  int mainMenu() {
    int choice;

    while (true) {
      clearScreen();
      cout << "Welcome To Personal Library System\n\n";
      cout << "1. Login\n";
      cout << "2. Register\n";
      cout << "3. Guest Mode\n";
      cout << "4. Exit Program\n";
      cin >> choice;

      if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number.\n";
        continue;
      }

      switch (choice) {
        case 1:
          clearScreen();
          operationsFunc::loginMenu();
          // login func
          break;

        case 2:
          clearScreen();
          // register func
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
          break;

        default:
          cout << "Invalid choice";
          break;
      }
    }

    return 0;
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