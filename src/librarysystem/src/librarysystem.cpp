#include "../header/librarysystem.h"
#include <iostream>
#include <stdexcept>
#include "librarysystem.h"
#include <fstream>
#include <stdio.h>
#define MAX_STRING_LENGTH 100
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

bool printMenu::printGuestMenu(ostream &out) {
  out << "\n";
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
  out << "5. Return Main Menu\n";
  return true;
}// prints screen BookCatalogingMenu.

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

bool BookSystem::addBook() {
  cout << "hello";
  return 0;
}

bool BookSystem::deleteBook() {
  cout << "hello";
  return 0;
}

bool BookSystem::updateBook() {
  cout << "hello";
  return 0;
}

bool BookSystem::viewCatalog() {
  cout << "hello";
  return 0;
}

/*
User UserAuthentication::login(const char* email, const char* password) {
  const char* expectedEmail = "user@example.com";
  const char* expectedPassword = "12345";

  if (strcmp(email, expectedEmail) == 0 && strcmp(password, expectedPassword) == 0) {
  return ;
  }
  return ;
}


bool UserAuthentication::registerUser(const char* email, const char* name, const char* surname, const char* password) {

  if (email != nullptr && name != nullptr && surname != nullptr && password != nullptr) {

  return true;
  }
  return false;
}
*/
//dear hasan I couldnt do this part so � just send to you :))

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
        return 0;
        break;

      default:
        break;
    }
  }

  return 0;
}

bool operationsFunc::loanManagementMenu() {
  return 0;
}

bool operationsFunc::wishListMenu() {
  return 0;
}

bool operationsFunc::readingTrackerMenu() {
  return 0;
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
}

bool WishList::removeFromWishList() {
  return 0;
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

  return 0;
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
