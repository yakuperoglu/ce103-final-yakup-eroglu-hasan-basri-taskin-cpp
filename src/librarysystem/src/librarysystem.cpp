#include <iostream>
#include <stdexcept>
#include "librarysystem.h"
#include <stdio.h>

using namespace std;

void clearScreen() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

bool BookSystem::addBook() {
  cout << "hello ";
  return 0;
}

bool BookSystem::deleteBook() {
  cout << "hello ";
  return 0;
}

bool BookSystem::updateBook() {
  cout << "hello ";
  return 0;
}


bool userOperations() {
  int choice;

  while (true) {
    clearScreen();
    cout << "welcome to User Operations\n\n";
    cout << "1. Add Book\n";
    cout << "2. Delete Book\n";
    cout << "3. Update Book\n";
    cout << "4. Return Main Menu\n";
    cin >> choice;

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
        return 0;
        break;

      default:
        break;
    }
  }

  return 0;
}

bool adminOperations() {
  int choice;
  cin >> choice;

  while (true) {
    switch (choice) {
      case 1:
        return 0;
        break;

      default:
        break;
    }
  }

  return 0;
}

bool guestOperations() {
  int choice;
  cin >> choice;

  while (true) {
    switch (choice) {
      case 1:
        return 0;
        break;

      default:
        break;
    }
  }

  return 0;
}

int mainMenu() {
  int choice;

  while (true) {
    clearScreen();
    cout << "Welcome To Personal Library System\nPlease Login\n\n";
    cout << "1. User Operations\n";
    cout << "2. Admin Operations\n";
    cout << "3. Guest Opreations\n";
    cout << "4. Exit Program\n";
    cin >> choice;

    switch (choice) {
      case 1:
        clearScreen();
        cout << "User Operations\n";
        userOperations();
        break;

      case 2:
        clearScreen();
        cout << "Admin Operations\n";
        adminOperations();
        break;

      case 3:
        clearScreen();
        cout << "Guest Operations\n";
        guestOperations();
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
