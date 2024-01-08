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

bool clearPreviousValue(istream &in, ostream &out) {
  in.ignore(numeric_limits<streamsize>::max(), '\n');
  in.get();
  return true;
}

bool enterToContunie(ostream &out) {
  out << "\nPress any key to continue";
  clearPreviousValue(cin, out);
  return true;
}

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
}// menu which is RegisterUser

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
      userOperations(in, out);
      return true;
    }
  }

  fclose(file);
  out << "Login failed: User not found or wrong password." << endl;
  return false;
}// menu which is LoginUser.

bool bookCatalogingMenu(istream &in, ostream &out) {
  int choice;

  while (true) {
    printBookCatalogingMenu(out);
    choice = getInput(in);

    if (in.fail()) {
      handleInputError(in, out);
      continue;
    }

    switch (choice) {
      case 1:
        addBook(in, out);
        break;

      case 2:
        deleteBook(in, out);
        break;

      case 3:
        updateBook(in, out);
        break;

      case 4:
        viewCatalog(in, out);
        break;

      case 5:
        return true;
        break;

      default:
        out << "Invalid option. Please try again.\n";
        break;
    }
  }
}

bool loanManagementMenu(istream &in, ostream &out) {
  int choice;

  while (true) {
    printLoanManagementMenu(out);
    choice = getInput(in);

    if (in.fail()) {
      handleInputError(in, out);
      continue;
    }

    switch (choice) {
      case 1:
        lendBook(in, out);
        break;

      case 2:
        borrowBook(in, out);
        break;

      case 3:
        viewLoans(in, out);
        break;

      case 4:
        return true;
        break;

      default:
        out << "Invalid option. Please try again.\n";
    }
  }
}

bool wishListMenu(istream &in, ostream &out) {
  int choice;

  while (true) {
    printWishListMenu(out);
    choice = getInput(in);

    if (in.fail()) {
      handleInputError(in, out);
      continue;
    }

    switch (choice) {
      case 1:
        listWishList(in, out);
        break;

      case 2:
        addToWishList(in, out);
        break;

      case 3:
        removeFromWishList(in, out);
        break;

      case 4:
        return false;

      default:
        out << "Invalid option. Please try again.\n";
        break;
    }
  }
}

bool readingTrackerMenu(istream &in, ostream &out) {
  int choice;

  while (true) {
    printReadingTrackerMenu(out);
    choice = getInput(in);

    if (in.fail()) {
      handleInputError(in, out);
      continue;
    }

    switch (choice) {
      case 1:
        logProgress(in, out);
        break;

      case 2:
        markAsRead(in, out);
        break;

      case 3:
        viewHistory(in, out);
        break;

      case 4:
        return 0;

      default:
        break;
    }
  }
}// menu which is ReadingTracker.

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
}// prints screen WishListMenu.

bool printReadingTrackerMenu(ostream &out) {
  clearScreen();
  out << "welcome to ReadingTrackerMenu\n\n";
  out << "1. Log Progress\n";
  out << "2. Mark As Read\n";
  out << "3. View History\n";
  out << "4. Return User Operations\n";
  out << "Please enter a number to select:\n";
  return true;
}// prints screen ReadingTrackerMenu.

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
}// fucntion that gets new id for books.

bool addBook(istream &in, ostream &out) {
  clearScreen();
  Book book;
  out << "Please enter the name of the book you want to add: ";
  in.ignore(numeric_limits<streamsize>::max(), '\n');
  in.getline(book.name, sizeof(book.name));
  book.id = getNewId();
  book.isMarked = false;
  FILE *file = fopen("Books.bin", "ab");

  if (!file) {
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
}// Function that allows us to add books to Books.bin.

bool deleteBook(istream &in, ostream &out) {
  clearScreen();

  if (viewCatalogForFunc(in, out) == false) {
    return false;
  }

  int id;
  out << "\nPlease enter the number of the book you want to delete: ";
  in >> id;

  if (in.fail()) {
    in.clear();
    in.ignore(numeric_limits<streamsize>::max(), '\n');
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
    out << "Book deleted successfully." << endl;
  } else {
    cerr << "Book with ID " << id << " not found." << endl;
    remove("temp.bin"); // Clean up the temporary file as it's not needed
  }

  return found;
}// Function that allows us to delete books from Books.bin

bool updateBook(istream &in, ostream &out) {
  clearScreen();

  if (viewCatalogForFunc(in, out) == false) {
    return false;
  }

  int id;
  out << ("\nPlease enter the number of the book you want to update: ");
  in >> id;
  FILE *file = fopen("Books.bin", "rb+");

  if (file == NULL) {
    perror("Cannot open file");
    return 0;
  }

  Book book;
  int found = 0;

  while (fread(&book, sizeof(Book), 1, file)) {
    if (book.id == id) {
      out << ("Please enter the new name of the book: ");
      in.getline(book.name, sizeof(book.name));
      fseek(file, -sizeof(Book), SEEK_CUR);
      fwrite(&book, sizeof(Book), 1, file);
      found = 1;
      break;
    }
  }

  fclose(file);

  if (!found) {
    out << ("Book not found.\n");
    return false;
  }

  return true;
}// Function that allows us to change the books in Books.bin.

bool viewCatalog(istream &in, ostream &out) {
  clearScreen();
  FILE *file = fopen("Books.bin", "rb");

  if (file == NULL) {
    return false;
  }

  Book book;

  while (fread(&book, sizeof(Book), 1, file)) {
    out << book.id << "." << book.name << "\n";
  }

  fclose(file);
  out << "\nPress enter to return to Main Menu";
  in.ignore(numeric_limits<streamsize>::max(), '\n');
  in.get();
  return true;
}// function that show us all books in Books.bin.

bool viewCatalogForFunc(istream &in, ostream &out) {
  FILE *file = fopen("Books.bin", "rb");
  Book book;

  if (!file) {
    return false;
  }

  while (fread(&book, sizeof(Book), 1, file)) {
    out << book.id << "." << book.name << "\n";
  }

  fclose(file);
  return true;
}// this function is actualy same as viewCatalog but its for function.

bool listWishList(istream &in, ostream &out) {
  clearScreen();
  FILE *file = fopen("wishlist.bin", "rb");

  if (!file) {
    return false;
  }

  Book book;
  out << "Wishlist:\n";

  while (fread(&book, sizeof(Book), 1, file)) {
    out << book.id << " " << book.name << endl;
  }

  fclose(file);
  out << "\nPress Enter to exit.\n";
  in.ignore(numeric_limits<streamsize>::max(), '\n');
  in.get();
  return true;
}// function that show us all books in Wishlist.bin.

bool listWishListForFunc(istream &in, ostream &out) {
  FILE *file = fopen("wishlist.bin", "rb");

  if (!file) {
    return false;
  }

  Book book;
  out << "Wishlist:\n";

  while (fread(&book, sizeof(Book), 1, file)) {
    out << book.id << " " << book.name << endl;
  }

  fclose(file);
  return true;
}// this function is actualy same as viewWishList but its for function.

bool addToWishList(istream &in, ostream &out) {
  clearScreen();

  if (viewCatalogForFunc(in, out) == false) {
    return false;
  }

  int id;
  out << "Enter the ID of the book to add to the wishlist: ";
  in >> id;
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
    out << "Book added to the wishlist.\n";
  } else {
    out << "Book not found.\n";
  }

  return found;
}// This function shows the books in Books.bin and allows the book with the selected id to be added to the wishlist.

bool removeFromWishList(istream &in, ostream &out) {
  clearScreen();

  if (listWishListForFunc(in, out) == false) {
    return false;
  }

  int id;
  out << "Enter the ID of the book to remove from the wishlist: ";
  in >> id;
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
    out << "Book removed from the wishlist.\n";
  } else {
    out << "Book not found.\n";
  }

  return found;
}// This function shows the books in Wishlist.bin and allows the book with the selected id to be deleted to the wishlist.

bool borrowBook(istream &in, ostream &out) {
  clearScreen();

  if (viewCatalogForFunc(in, out) == false) {
    return false;
  }

  int id;
  out << ("\nPlease enter the ID of the book you want to borrow: ");
  in >> id;
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
    out << ("Book not found.\n");
    return false;
  }

  return true;
}// this function allows us to retrieve books from Books.bin and the purchased book is deleted from Books.bin until it is returned.

bool lendBook(istream &in, ostream &out) {
  clearScreen();

  if (viewLoansForFunc(in, out) == false) {
    return false;
  }

  int id;
  out << ("\nPlease enter the ID of the book you want to return: ");
  in >> id;
  FILE *loansFile = fopen("Loans.bin", "rb");
  FILE *tempFile = fopen("temp.bin", "wb");
  FILE *booksFile = fopen("Books.bin", "ab");

  if (!loansFile || !tempFile || !booksFile) {
    out << ("Error opening files.\n");
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
    out << ("Book not found.\n");
    return false;
  }

  out << ("Book returned successfully.\n");
  return true;
}//This function returns the borrowed book.

bool viewLoans(istream &in, ostream &out) {
  clearScreen();
  FILE *file = fopen("Loans.bin", "rb");
  Book book;

  if (!file) {
    return false;
  }

  out << ("Loaned Books:\n");

  while (fread(&book, sizeof(Book), 1, file)) {
    out << book.id << "." << book.name << "\n";
  }

  fclose(file);
  out << ("\nPress any key to return to Main Menu");
  in.ignore(numeric_limits<streamsize>::max(), '\n');
  in.get();
  return true;
}// this function shows borrowed books.

bool viewLoansForFunc(istream &in, ostream &out) {
  FILE *file = fopen("Loans.bin", "rb");
  Book book;

  if (!file) {
    return false;
  }

  while (fread(&book, sizeof(Book), 1, file)) {
    out << book.id << "." << book.name << "\n";
  }

  fclose(file);
  return true;
}// this func is same as viewLoans but its for func.

bool logProgress(istream &in, ostream &out) {
  clearScreen();
  FILE *file = fopen("Books.bin", "rb");

  if (!file) {
    cerr << "There are no books or could not open the books file.\n";
    enterToContunie(out);
    return false;
  }

  Book book;
  int bookCount = 0;

  while (fread(&book, sizeof(Book), 1, file)) {
    bookCount++;
    cout << book.id << ". " << book.name << " (";

    if (book.isMarked) {
      cout << "Read";
    } else {
      cout << "Unread";
    }

    cout << ")\n";
  }

  fclose(file);

  if (bookCount == 0) {
    cout << "There are no books.\n";
  }

  enterToContunie(out);
  return true;
}

bool markAsRead(istream &in, ostream &out) {
  clearScreen();

  if (!listUnMarkedBooks(in, out)) {
    cout << "There are no unmarked books.\n";
    enterToContunie(out);
    return false;
  }

  int bookId;
  cout << "\nEnter the ID of the book to mark as read: ";
  cin >> bookId;
  FILE *file = fopen("Books.bin", "r+b"); // Open file as read and write permission

  if (!file) {
    cerr << "Could not open the books file.\n";
    enterToContunie(out);
    return false;
  }

  Book book;

  while (fread(&book, sizeof(Book), 1, file)) {
    if (book.id == bookId && book.isMarked == false) {
      book.isMarked = true; // Set the isMarked parameter
      // If we want to write changes, we have to go back and write
      fseek(file, -static_cast<long>(sizeof(Book)), SEEK_CUR);
      fwrite(&book, sizeof(Book), 1, file);
      fclose(file);
      return true;
    }
  }

  fclose(file);
  return false;
}

bool listUnMarkedBooks(istream &in, ostream &out) {
  FILE *file = fopen("Books.bin", "rb");

  if (!file) {
    cerr << "Could not open the books file.\n";
    return false;
  }

  Book book;
  bool hasUnMarkedBooks = false;
  cout << "Unmarked Books:\n";

  while (fread(&book, sizeof(Book), 1, file)) {
    if (!book.isMarked) {
      hasUnMarkedBooks = true;
      cout << "ID: " << book.id << "\tName: " << book.name << endl;
    }
  }

  fclose(file);
  return hasUnMarkedBooks;
}

bool viewHistory(istream &in, ostream &out) {
  clearScreen();
  FILE *file = fopen("Books.bin", "rb");

  if (!file) {
    cerr << "There are no books or could not open the books file.\n";
    enterToContunie(out);
    return false;
  }

  Book book;
  bool hasMarkedBooks = false;
  cout << "Marked Books:\n";

  while (fread(&book, sizeof(Book), 1, file)) {
    if (book.isMarked) {
      hasMarkedBooks = true;
      cout << "ID: " << book.id << "\tName: " << book.name << endl;
    }
  }

  fclose(file);
  enterToContunie(out);
  return hasMarkedBooks;
}

bool userOperations(istream &in, ostream &out) {
  int choice;

  while (true) {
    clearScreen();
    printUserMenu(out);
    choice = getInput(in);

    if (in.fail()) {
      handleInputError(in, out);
      continue;
    }

    switch (choice) {
      case 1:
        bookCatalogingMenu(in, out);
        break;

      case 2:
        loanManagementMenu(in, out);
        break;

      case 3:
        wishListMenu(in, out);
        break;

      case 4:
        readingTrackerMenu(in, out);
        break;

      case 5:
        return 0;
        break;

      default:
        break;
    }
  }

  return true;
}// this function provides redirects in user operations.

bool guestOperation(istream &in, ostream &out) {
  int choice;

  while (true) {
    printGuestMenu(out);
    choice = getInput(in);

    if (in.fail()) {
      handleInputError(in, out);
      continue;
    }

    switch (choice) {
      case 1:
        clearScreen();
        viewCatalog(in, out);
        break; // Moved this break here

      case 2:
        return 0;

      default:
        out << "Invalid choice. Please try again.\n";
        break;
    }
  }

  return false;
}// this function provides redirects in guest operations.

int mainMenu(istream &in, ostream &out) {
  int choice;

  while (true) {
    printMainMenu(out);
    choice = getInput(in);

    if (in.fail()) {
      handleInputError(in, out);
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
        out << "Guest Operations\n";
        guestOperation(in, out);
        break;

      case 4:
        clearScreen();
        out << "ExitProgram\n";
        return 0;

      default:
        out << "Invalid choice";
        break;
    }
  }
}// this function provides redirects in MainMenu.
