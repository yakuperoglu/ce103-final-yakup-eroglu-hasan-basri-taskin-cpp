#include "../header/librarysystem.h"
#include <stdio.h>
#include <iostream>

using namespace std;

int Deneme::admin_UserMenu() {
  int choice;
  cout << "Welcome to PersonalLibrarySystem \n" << "Please Select User Or Admin";
  cin >> choice;

  switch (choice) {
    case(1): {
      cout << "User";
    }

    case(2): {
      cout << "Admin";
    }

    case(3): {
      cout << "merhaba";
    }

    default:
      break;
  }

  return 0;
}
