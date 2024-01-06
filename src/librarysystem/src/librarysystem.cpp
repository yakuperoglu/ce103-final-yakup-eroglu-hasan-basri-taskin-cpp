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
  in.ignore(numeric_limits<streamsize>::max(), '\n');
  in.getline(newUser.email, 100);
  out << "Enter password:";
  in.getline(newUser.password, 100);
  FILE *file = fopen("users.bin", "ab");

  if (file == NULL) {
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
  in.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore new line character
  in.getline(email, 100);
  out << "Enter password:";
  in.getline(password, 100);
  FILE *file = fopen("users.bin", "rb");

  if (file == NULL) {
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
  out << "Login failed: User not found or wrong password." << endl;
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
        break;

      case 2:
        deleteBook();
        break;

      case 3:
        updateBook();
        break;

      case 4:
        viewCatalog();
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
        break;

      case 2:
        borrowBook();
        break;

      case 3:
        viewLoans();
        break;

      case 4:
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
        break;

      case 2:
        addToWishList();
        break;

      case 3:
        removeFromWishList();
        break;

      case 4:
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
        break;

      case 2:
        markAsRead();
        break;

      case 3:
        viewHistory();
        break;

      case 4:
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

  if (file == nullptr) {
    return 1;
  }

  Book book;

  while (fread(&book, sizeof(Book), 1, file) == 1) {
    if (book.id > lastId) {
      lastId = book.id;
    }
  }

  fclose(file);
  return lastId + 1;
}

bool addBook() {
  clearScreen();
  Book book;
  cout << "Please enter the name of the book you want to add: ";
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cin.getline(book.name, sizeof(book.name));
  book.id = getNewId();
  FILE *file = fopen("Books.bin", "ab");

  if (!file) {
    cerr << "Unable to open or create the file 'Books.bin'." << endl;
    return false;
  }

  fwrite(&book, sizeof(Book), 1, file);

  if (ferror(file)) {
    perror("Failed to write to 'Books.bin'");
    fclose(file);
    return false;
  }

  fclose(file);
  cout << "Book added successfully." << endl;
  return true;
}

bool deleteBook() {
  clearScreen();
  viewCatalogForFunc();
  int id;
  cout << "Please enter the number of the book you want to delete: ";
  cin >> id;

  if (cin.fail()) {
    cin.clear(); // Clear the error flags
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard the rest of the line
    cerr << "You must enter a numeric ID." << endl;
    return false;
  }

  FILE *file = fopen("Books.bin", "rb");
  FILE *tempFile = fopen("temp.bin", "wb");

  if (!file || !tempFile) {
    cerr << "Error opening files." << endl;
    return false;
  }

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

  if (found) {
    remove("Books.bin");
    rename("temp.bin", "Books.bin");
    cout << "Book deleted successfully." << endl;
  } else {
    cerr << "Book with ID " << id << " not found." << endl;
    remove("temp.bin"); // Clean up the temporary file as it's not needed
  }

  return found;
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

  return true;
}

bool viewCatalog() {
  clearScreen();
  FILE *file = fopen("Books.bin", "rb");

  if (file == NULL) {
    cerr << "File couldn't be opened for reading." << endl;
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

  return found;
}

bool borrowBook() {
  clearScreen();
  viewCatalogForFunc();
  int id;
  printf("\nPlease enter the ID of the book you want to borrow: ");
  scanf("%d", &id);
  FILE *booksFile = fopen("Books.bin", "rb");
  FILE *loansFile = fopen("Loans.bin", "ab");
  FILE *tempFile = fopen("temp.bin", "wb");
  Book book;
  bool found = false;

  while (fread(&book, sizeof(Book), 1, booksFile)) {
    if (book.id == id) {
      fwrite(&book, sizeof(Book), 1, loansFile);
      found = true;
    } else {
      fwrite(&book, sizeof(Book), 1, tempFile);
    }
  }

  fclose(booksFile);
  fclose(loansFile);
  fclose(tempFile);
  remove("Books.bin");
  rename("temp.bin", "Books.bin");

  if (!found) {
    printf("Book not found.\n");
    return false;
  }

  return true;
}

bool lendBook() {
  clearScreen();
  viewLoansForFunc();
  int id;
  printf("\nPlease enter the ID of the book you want to return: ");
  scanf("%d", &id);
  FILE *loansFile = fopen("Loans.bin", "rb");
  FILE *tempFile = fopen("temp.bin", "wb");
  FILE *booksFile = fopen("Books.bin", "ab");

  if (!loansFile || !tempFile || !booksFile) {
    printf("Error opening files.\n");
    return false;
  }

  Book book;
  bool found = false;

  while (fread(&book, sizeof(Book), 1, loansFile)) {
    if (book.id != id) {
      fwrite(&book, sizeof(Book), 1, tempFile);
    } else {
      fwrite(&book, sizeof(Book), 1, booksFile);
      found = true;
    }
  }

  fclose(loansFile);
  fclose(tempFile);
  fclose(booksFile);
  remove("Loans.bin");
  rename("temp.bin", "Loans.bin");

  if (!found) {
    printf("Book not found.\n");
    return false;
  }

  printf("Book returned successfully.\n");
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
        break;

      case 2:
        loanManagementMenu();
        break;

      case 3:
        wishListMenu();
        break;

      case 4:
        readingTrackerMenu();
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
        return 0;

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
