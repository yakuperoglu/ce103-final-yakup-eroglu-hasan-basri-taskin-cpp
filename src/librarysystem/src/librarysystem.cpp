#include "../header/librarysystem.h"
#include <iostream>
#include <stdexcept>
#include "librarysystem.h"

#include <fstream>
#include <stdio.h>
using namespace std;

void clearScreen() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}
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
  fputc('\0', file); // Null karakter ekle
  fclose(file);
  return true;
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
// dear hasan I couldnt do this part so � just send to you :))

bool operationsFunc::bookCataLoging() {
  int choice;

  while (true) {
    clearScreen();
    cout << "welcome to User Operations\n\n";
    cout << "1. Add Book\n";
    cout << "2. Delete Book\n";
    cout << "3. Update Book\n";
    cout << "4. View Catalog\n";
    cout << "5. Return Main Menu\n";
    cin >> choice;

    if (cin.fail()) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Invalid input. Please enter a number.\n";
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

bool operationsFunc::loanManagement() {
  return 0;
}

bool operationsFunc::wishList() {
  return 0;
}

bool operationsFunc::readingTracker() {
  return 0;
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
    cout << "welcome to User Operations\n\n";
    cout << "1. Book Cataloging\n";
    cout << "2. Loan Management\n";
    cout << "3. WishList Management\n";
    cout << "4. Reading Tracker\n";
    cout << "5. Return Main Menu\n";
    cin >> choice;

    if (cin.fail()) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Invalid input. Please enter a number.\n";
      continue;
    }

    switch (choice) {
      case 1:
        operationsFunc::bookCataLoging();
        return 0;
        break;

      case 2:
        operationsFunc::loanManagement();
        return 0;
        break;

      case 3:
        operationsFunc::wishList();
        return 0;
        break;

      case 4:
        operationsFunc::readingTracker();
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
    cout << "\n";
    cout << "1. View Catalog\n";
    cout << "2. Return MainMenu\n";
    cin >> choice;

    if (cin.fail()) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Invalid input. Please enter a number.\n";
      clearScreen();
      continue;
    }

    switch (choice) {
      case 1:
        int choice2;
        clearScreen();
        BookSystem::viewCatalog();
        cout << "\n\n1 To Return MainMenu";
        cin >> choice2;

        switch (choice2) {
          case 1:
            return mainMenu();

          default:
            break;
        }

        break;

      case 2:
        return 0;

      default:
        cout << "Invalid choice. Please try again.\n";
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
