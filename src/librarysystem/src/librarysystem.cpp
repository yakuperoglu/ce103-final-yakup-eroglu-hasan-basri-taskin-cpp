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
  cout << "hello ";
  return 0;
}

bool userOperations() {
  return 0;
}

bool adminOperations() {
  return 0;
}

bool guestOperations() {
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
        cout << "User Operations";
        break;

      case 2:
        cout << "Admin Operations";
        break;

      case 3:
        cout << "Guest Operations";
        break;

      case 4:
        cout << "ExitProgram";
        return 0;
        break;

      default:
        cout << "Invalid choice";
        break;
    }
  }

  return 0;
}
