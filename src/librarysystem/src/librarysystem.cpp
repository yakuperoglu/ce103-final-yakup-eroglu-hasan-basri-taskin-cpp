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
  in.ignore(numeric_limits<streamsize>::max(), '\n');
  out << "Invalid input. Please enter a number.\n";
  return false;
}// This function prevents entering letters instead of numbers.

int getInput(istream &in) {
  int choice;
  in >> choice;
  return choice;
}// this function gets input from user.

bool registerUser(istream &in, ostream &out) {
  User newUser;
  out << "Enter email:";
  in.ignore(numeric_limits<streamsize>::max(), '\n'); // Yeni satır karakterini yok say
  in.getline(newUser.email, 100);
  out << "Enter password:";
  in.getline(newUser.password, 100);
  FILE *file;
  errno_t err = fopen_s(&file, "users.bin", "ab");

  if (err != 0 || file == NULL) {
    cerr << "File couldn't be opened for writing." << endl;
    return false;
  }

  fwrite(&newUser, sizeof(User), 1, file);
  fclose(file);
  out << "User registered successfully." << endl;
  return true;
}

bool loginUser(istream &in, ostream &out) {
  char email[100];
  char password[100];
  out << "Enter email:";
  in.ignore(numeric_limits<streamsize>::max(), '\n'); // Yeni satır karakterini yok say
  in.getline(email, 100);
  out << "Enter password:";
  in.getline(password, 100);
  FILE *file;
  errno_t err = fopen_s(&file, "users.bin", "rb");

  if (err != 0 || file == NULL) {
    cerr << "File couldn't be opened for reading." << endl;
    out << "Login Failed.";
    return false;
  }

  User user;

  while (fread(&user, sizeof(User), 1, file)) {
    if (strcmp(user.email, email) == 0 && strcmp(user.password, password) == 0) {
      fclose(file);
      out << "Login success." << endl;
      userOperations();
      return true;
    }
  }

  fclose(file);
  cout << "Login failed: User not found or wrong password." << endl;
  return false;
}

bool bookCatalogingMenu() {
  int choice;

  while (true) {
    printBookCatalogingMenu(cout);
    choice = getInput(cin);

    if (cin.fail()) {
      handleInputError(cin, cout);
      continue;
    }

    switch (choice) {
      case 1:
        addBook();
        return 0;
        break;

      case 2:
        deleteBook();
        return 0;
        break;

      case 3:
        updateBook();
        return 0;
        break;

      case 4:
        viewCatalog();
        break;

      case 5:
        userOperations();
        break;

      default:
        break;
    }
  }

  return true;
}

bool loanManagementMenu() {
  int choice;

  while (true) {
    printLoanManagementMenu(cout);
    choice = getInput(cin);

    if (cin.fail()) {
      handleInputError(cin, cout);
      continue;
    }

    switch (choice) {
      case 1:
        lendBook();
        return 0;

      case 2:
        borrowBook();
        return 0;

      case 3:
        viewLoans();
        return 0;

      case 4:
        userOperations();
        return 0;

      default:
        break;
    }
  }

  return true;
}

bool wishListMenu() {
  int choice;

  while (true) {
    printWishListMenu(cout);
    choice = getInput(cin);

    if (cin.fail()) {
      handleInputError(cin, cout);
      continue;
    }

    switch (choice) {
      case 1:
        listWishList();
        return 0;

      case 2:
        addToWishList();
        return 0;

      case 3:
        removeFromWishList();
        return 0;

      case 4:
        userOperations();
        return 0;

      default:
        break;
    }
  }

  return true;
}

bool readingTrackerMenu() {
  int choice;

  while (true) {
    printReadingTrackerMenu(cout);
    choice = getInput(cin);

    if (cin.fail()) {
      handleInputError(cin, cout);
      continue;
    }

    switch (choice) {
      case 1:
        logProgress();
        return true;

      case 2:
        markAsRead();
        return true;

      case 3:
        viewHistory();
        return true;

      case 4:
        userOperations();
        return 0;

      default:
        break;
    }
  }

  return true;
}

bool printGuestMenu(ostream &out) {
  clearScreen();
  out << "Guest Operations\n\n";
  out << "1. View Catalog\n";
  out << "2. Return to Main Menu\n";
  out << "Please enter a number to select:\n";
  return true;
}// prints screen GuestMenu.

bool printMainMenu(ostream &out) {
  clearScreen();
  out << "Welcome To Personal Library System\n\n";
  out << "1. Login\n";
  out << "2. Register\n";
  out << "3. Guest Mode\n";
  out << "4. Exit Program\n";
  out << "Please enter a number to select:\n";
  return true;
}// prints screen MainMenu.

bool printUserMenu(ostream &out) {
  clearScreen();
  out << "welcome to User Operations\n\n";
  out << "1. Book Cataloging\n";
  out << "2. Loan Management\n";
  out << "3. WishList Management\n";
  out << "4. Reading Tracker\n";
  out << "5. Return Main Menu\n";
  out << "Please enter a number to select:\n";
  return true;
}// prints screen UserMenu.

bool printBookCatalogingMenu(ostream &out) {
  clearScreen();
  out << "welcome to Book Operations\n\n";
  out << "1. Add Book\n";
  out << "2. Delete Book\n";
  out << "3. Update Book\n";
  out << "4. View Catalog\n";
  out << "5. Return User Operations\n";
  out << "Please enter a number to select:\n";
  return true;
}// prints screen BookCatalogingMenu.

bool printLoanManagementMenu(ostream &out) {
  clearScreen();
  out << "welcome to LoanManagement\n\n";
  out << "1. Lend Book\n";
  out << "2. Borrow Book\n";
  out << "3. View Loans\n";
  out << "4. Return User Operations\n";
  out << "Please enter a number to select:\n";
  return true;
}// prints screen LoanManagementMenu.

bool printWishListMenu(ostream &out) {
  clearScreen();
  out << "welcome to WishlistManageMenu\n\n";
  out << "1. View Wishlist\n";
  out << "2. Add To Wishlist\n";
  out << "3. Remove From Wishlist\n";
  out << "4. Return User Operations\n";
  out << "Please enter a number to select:\n";
  return true;
}

bool printReadingTrackerMenu(ostream &out) {
  clearScreen();
  out << "welcome to ReadingTrackerMenu\n\n";
  out << "1. Log Progress\n";
  out << "2. Mark As Read\n";
  out << "3. View History\n";
  out << "4. Return User Operations\n";
  out << "Please enter a number to select:\n";
  return true;
}


int getNewId() {
  int lastId = 0;
  FILE *file = fopen("Books.bin", "rb");
  Book book;

  while (fread(&book, sizeof(Book), 1, file)) {
    if (book.id > lastId) lastId = book.id;
  }

  fclose(file);
  return lastId + 1;
}

bool addBook() {
  clearScreen();
  Book book;
  printf("Please enter the name of the book you want to add: ");
  scanf(" %[^\n]", book.name);
  book.id = getNewId(); // Function to generate a new ID (defined below)
  FILE *file = fopen("Books.bin", "ab");
  fwrite(&book, sizeof(Book), 1, file);
  fclose(file);
  bookCatalogingMenu();
  return true;
}

bool deleteBook() {
  clearScreen();
  viewCatalogForFunc();
  int id;
  printf("Please enter the number of the book you want to delete: ");
  scanf("%d", &id);
  // Reading the file and writing non-deleted items to a temporary file for deletion process.
  FILE *file = fopen("Books.bin", "rb");
  FILE *tempFile = fopen("temp.bin", "wb");
  Book book;

  while (fread(&book, sizeof(Book), 1, file)) {
    if (book.id != id) {
      fwrite(&book, sizeof(Book), 1, tempFile);
    }
  }

  fclose(file);
  fclose(tempFile);
  remove("Books.bin");
  rename("temp.bin", "Books.bin");
  bookCatalogingMenu();
  return true;
}

bool updateBook() {
  clearScreen();
  viewCatalogForFunc();
  int id;
  printf("Please enter the number of the book you want to update: ");
  scanf("%d", &id);
  FILE *file = fopen("Books.bin", "rb+");

  if (file == NULL) {
    perror("Cannot open file");
    return 0;
  }

  Book book;
  int found = 0;

  while (fread(&book, sizeof(Book), 1, file)) {
    if (book.id == id) {
      printf("Please enter the new name of the book: ");
      scanf(" %[^\n]", book.name);
      fseek(file, -sizeof(Book), SEEK_CUR);
      fwrite(&book, sizeof(Book), 1, file);
      found = 1;
      break;
    }
  }

  fclose(file);

  if (!found) {
    printf("Book not found.\n");
    return false;
  }

  bookCatalogingMenu();
  return true;
}

bool viewCatalog() {
  clearScreen();
  FILE *file;
  errno_t err = fopen_s(&file, "Books.bin", "rb");

  if (err != 0 || file == NULL) {
    cerr << "File couldn't be opened for writing." << endl;
    return false;
  }

  Book book;

  while (fread(&book, sizeof(Book), 1, file)) {
    printf("%d. %s\n", book.id, book.name);
  }

  fclose(file);
  cout << "\nPress any key to return to Main Menu";
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cin.get();
  return true;
}

bool viewCatalogForFunc() {
  FILE *file = fopen("Books.bin", "rb");
  Book book;

  while (fread(&book, sizeof(Book), 1, file)) {
    printf("%d. %s\n", book.id, book.name);
  }

  fclose(file);
  return true;
}

bool listWishList() {
  clearScreen();
  FILE *file = fopen("wishlist.bin", "rb");

  if (!file) {
    cout << "Wishlist file not found.\n";
    return false;
  }

  Book book;
  cout << "Wishlist:\n";

  while (fread(&book, sizeof(Book), 1, file)) {
    cout << book.id << " " << book.name << endl;
  }

  fclose(file);
  cout << "\nPress Enter to exit.\n";
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cin.get();
  wishListMenu();
  return true;
}

bool listWishListForFunc() {
  FILE *file = fopen("wishlist.bin", "rb");

  if (!file) {
    cout << "Wishlist file not found.\n";
    return false;
  }

  Book book;
  cout << "Wishlist:\n";

  while (fread(&book, sizeof(Book), 1, file)) {
    cout << book.id << " " << book.name << endl;
  }

  fclose(file);
  return true;
}

bool addToWishList() {
  clearScreen();
  viewCatalogForFunc();
  int id;
  cout << "Enter the ID of the book to add to the wishlist: ";
  cin >> id;
  FILE *file = fopen("Books.bin", "rb");
  FILE *wishlistFile = fopen("wishlist.bin", "ab");
  Book book;
  bool found = false;

  while (fread(&book, sizeof(Book), 1, file)) {
    if (book.id == id) {
      fwrite(&book, sizeof(Book), 1, wishlistFile);
      found = true;
      break;
    }
  }

  fclose(file);
  fclose(wishlistFile);

  if (found) {
    cout << "Book added to the wishlist.\n";
  } else {
    cout << "Book not found.\n";
  }

  wishListMenu();
  return found;
}

bool removeFromWishList() {
  clearScreen();
  listWishListForFunc();
  int id;
  cout << "Enter the ID of the book to remove from the wishlist: ";
  cin >> id;
  FILE *file = fopen("wishlist.bin", "rb");
  FILE *tempFile = fopen("temp.bin", "wb");
  Book book;
  bool found = false;

  while (fread(&book, sizeof(Book), 1, file)) {
    if (book.id != id) {
      fwrite(&book, sizeof(Book), 1, tempFile);
    } else {
      found = true;
    }
  }

  fclose(file);
  fclose(tempFile);
  remove("wishlist.bin");
  rename("temp.bin", "wishlist.bin");

  if (found) {
    cout << "Book removed from the wishlist.\n";
  } else {
    cout << "Book not found.\n";
  }

  wishListMenu();
  return found;
}

bool borrowBook() {
  return true;
}

bool lendBook() {
  clearScreen();
  viewLoansForFunc();
  int id;
  printf("Please enter the ID of the book you want to return: ");
  scanf("%d", &id);
  FILE *loansFile = fopen("Loans.bin", "rb");
  FILE *tempFile = fopen("temp.bin", "wb");
  Book book;
  bool found = false;

  while (fread(&book, sizeof(Book), 1, loansFile)) {
    if (book.id != id) {
      fwrite(&book, sizeof(Book), 1, tempFile);
    } else {
      found = true;
    }
  }

  fclose(loansFile);
  fclose(tempFile);
  remove("Loans.bin");
  rename("temp.bin", "Loans.bin");

  if (!found) {
    printf("Book not found.\n");
    return false;
  }

  loanManagementMenu();
  return true;
}

bool viewLoans() {
  clearScreen();
  FILE *file = fopen("Loans.bin", "rb");
  Book book;

  if (!file) {
    printf("Loans file not found.\n");
    return false;
  }

  printf("Loaned Books:\n");

  while (fread(&book, sizeof(Book), 1, file)) {
    printf("%d. %s\n", book.id, book.name);
  }

  fclose(file);
  printf("\nPress any key to return to Main Menu");
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cin.get();
  loanManagementMenu();
  return true;
}

bool viewLoansForFunc() {
  FILE *file = fopen("Loans.bin", "rb");
  Book book;

  if (!file) {
    printf("Loans file not found.\n");
    return false;
  }

  printf("Loaned Books:\n");

  while (fread(&book, sizeof(Book), 1, file)) {
    printf("%d. %s\n", book.id, book.name);
  }

  fclose(file);
  return true;
}

bool logProgress() {
  return true;
}

bool markAsRead() {
  return true;
}

bool viewHistory() {
  return true;
}

bool userOperations() {
  int choice;

  while (true) {
    clearScreen();
    printUserMenu(cout);
    choice = getInput(cin);

    if (cin.fail()) {
      handleInputError(cin, cout);
      continue;
    }

    switch (choice) {
      case 1:
        bookCatalogingMenu();
        return 0;
        break;

      case 2:
        loanManagementMenu();
        return 0;
        break;

      case 3:
        wishListMenu();
        return 0;
        break;

      case 4:
        readingTrackerMenu();
        return 0;
        break;

      case 5:
        mainMenu(cin, cout);
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
    printGuestMenu(cout);
    choice = getInput(cin);

    if (cin.fail()) {
      handleInputError(cin, cout);
      continue;
    }

    switch (choice) {
      case 1:
        clearScreen();
        viewCatalog();
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

int mainMenu(istream &in, ostream &out) {
  int choice;

  while (true) {
    printMainMenu(cout);
    choice = getInput(cin);

    if (cin.fail()) {
      handleInputError(cin, cout);
      continue;
    }

    switch (choice) {
      case 1:
        clearScreen();
        loginUser(in, out);
        break;

      case 2:
        clearScreen();
        registerUser(in, out);
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
