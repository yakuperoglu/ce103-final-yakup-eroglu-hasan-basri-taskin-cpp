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
        break;

      default:
        cout << "Invalid choice";
        break;
    }
  }

  return 0;
}
