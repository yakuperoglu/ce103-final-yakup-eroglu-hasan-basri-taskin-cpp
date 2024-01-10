/**
 * @file librarysystem.cpp
 * @brief Implementation file for the Library System.
 *
 * This file contains the implementation of the Library System, including functions
 * for clearing the console screen and other utility functions.
 */
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

/**
 * @brief Clears the console screen.
 *
 * This function is a utility to clear the console screen. It uses platform-specific
 * commands to clear the screen for both Windows and non-Windows systems.
 */
void clearScreen() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}// this function clears the console

/**
 * @brief Waits for a key press from the user to continue and returns true.
 *
 * @param in Input stream object.
 * @param out Output stream object.
 * @return Returns true when the user presses any key, otherwise returns false.
 *
 * This function waits for a key press from the user, allowing the program to pause.
 * @code
 * if (enterToContunie(cin, cout)) {
 *     // Continue with the program logic
 * }
 * @endcode
 */
bool enterToContunie(istream &in, ostream &out) {
  out << "\nPress any key to continue";
  in.ignore(numeric_limits<streamsize>::max(), '\n');
  in.get();
  return true;
}

/**
 * @brief Handles input errors by clearing the input stream and displaying an error message.
 *
 * @param in Input stream object.
 * @param out Output stream object.
 * @return Returns false after clearing input and displaying an error message.
 *
 * This function is designed to handle input errors, specifically when the user enters
 * letters instead of numbers. It clears the input stream, ignores any remaining characters
 * up to the newline, and prints an error message to the output stream.
 * @code
 * if (!handleInputError(cin, cout)) {
 *     // Handle the error or prompt the user for input again
 * }
 * @endcode
 */
bool handleInputError(istream &in, ostream &out) {
  in.clear();
  in.ignore(numeric_limits<streamsize>::max(), '\n');
  out << "Invalid input. Please enter a number.\n";
  return false;
}// This function prevents entering letters instead of numbers.

/**
 * @brief Gets an integer input from the user.
 *
 * @param in Input stream object.
 * @return The integer input obtained from the user.
 *
 * This function prompts the user to enter an integer through the specified input stream.
 * It retrieves the user's input and returns the entered integer.
 * @code
 * int userChoice = getInput(cin);
 * // Now 'userChoice' contains the integer entered by the user
 * @endcode
 */
int getInput(istream &in) {
  int choice;
  in >> choice;
  return choice;
}// this function gets input from user.

/**
 * @brief Registers a new user by obtaining email and password from the user.
 *
 * @param in Input stream object.
 * @param out Output stream object.
 * @return Returns true if the user registration is successful, false otherwise.
 *
 * This function prompts the user to enter their email and password, creates a new User
 * object, and stores the user information in a binary file named "users.bin".
 * @code
 * if (registerUser(cin, cout)) {
 *     // User registered successfully
 * } else {
 *     // Error handling for user registration failure
 * }
 * @endcode
 */
bool registerUser(istream &in, ostream &out) {
  User newUser;
  out << "Enter email:";
  in.ignore(numeric_limits<streamsize>::max(), '\n');
  in.getline(newUser.email, 100);
  out << "Enter password:";
  in.getline(newUser.password, 100);
  FILE *file = fopen("users.bin", "ab");

  if (file == NULL) return false;

  fwrite(&newUser, sizeof(User), 1, file);
  fclose(file);
  out << "User registered successfully." << endl;
  return true;
}// menu which is RegisterUser

/**
 * @brief Allows a user to log in by providing email and password.
 *
 * @param in Input stream object.
 * @param out Output stream object.
 * @return Returns true if the login is successful, false otherwise.
 *
 * This function prompts the user to enter their email and password, reads user information
 * from a binary file named "users.bin," and checks if the provided credentials match any
 * registered user. If a match is found, the user is logged in, and user operations are performed.
 * @code
 * if (loginUser(cin, cout)) {
 *     // User logged in successfully
 * } else {
 *     // Error handling for login failure
 * }
 * @endcode
 */
bool loginUser(istream &in, ostream &out) {
  char email[100];
  char password[100];
  out << "Enter email:";
  in.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore new line character
  in.getline(email, 100);
  out << "Enter password:";
  in.getline(password, 100);
  FILE *file = fopen("users.bin", "rb");

  if (file == NULL) return false;

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

/**
 * @brief Displays a book cataloging menu and performs corresponding actions based on user input.
 *
 * @param in Input stream object.
 * @param out Output stream object.
 * @return Returns true when the user chooses to exit the book cataloging menu.
 *
 * This function continuously displays a menu for book cataloging operations, reads the user's choice,
 * and performs the corresponding action. The menu includes options to add, delete, update, or view the catalog.
 * @code
 * if (bookCatalogingMenu(cin, cout)) {
 *     // User chose to exit the book cataloging menu
 * } else {
 *     // Additional logic or error handling
 * }
 * @endcode
 */
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

      default:
        out << "Invalid option. Please try again.\n";
        break;
    }
  }
}

/**
 * @brief Displays a loan management menu and performs corresponding actions based on user input.
 *
 * @param in Input stream object.
 * @param out Output stream object.
 * @return Returns true when the user chooses to exit the loan management menu.
 *
 * This function continuously displays a menu for loan management operations, reads the user's choice,
 * and performs the corresponding action. The menu includes options to lend, borrow, or view loans.
 * @code
 * if (loanManagementMenu(cin, cout)) {
 *     // User chose to exit the loan management menu
 * } else {
 *     // Additional logic or error handling
 * }
 * @endcode
 */
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

      default:
        out << "Invalid option. Please try again.\n";
    }
  }
}

/**
 * @brief Displays a wishlist menu and performs corresponding actions based on user input.
 *
 * @param in Input stream object.
 * @param out Output stream object.
 * @return Returns false when the user chooses to exit the wishlist menu.
 *
 * This function continuously displays a menu for wishlist operations, reads the user's choice,
 * and performs the corresponding action. The menu includes options to list, add to, or remove from the wishlist.
 * @code
 * if (!wishListMenu(cin, cout)) {
 *     // User chose to exit the wishlist menu
 * } else {
 *     // Additional logic or error handling
 * }
 * @endcode
 */
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

/**
 * @brief Displays a reading tracker menu and performs corresponding actions based on user input.
 *
 * @param in Input stream object.
 * @param out Output stream object.
 * @return Returns 0 when the user chooses to exit the reading tracker menu.
 *
 * This function continuously displays a menu for reading tracker operations, reads the user's choice,
 * and performs the corresponding action. The menu includes options to log progress, mark as read,
 * or view reading history.
 * @code
 * if (readingTrackerMenu(cin, cout) == 0) {
 *     // User chose to exit the reading tracker menu
 * } else {
 *     // Additional logic or error handling
 * }
 * @endcode
 */
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

/**
 * @brief Prints the menu for guest operations.
 *
 * @param out Output stream object.
 * @return Returns true after printing the menu.
 *
 * This function clears the screen and prints the guest menu options,
 * prompting the user to select an operation (view catalog or return to the main menu).
 * It returns true after printing the menu.
 * @code
 * if (printGuestMenu(cout)) {
 *     // Guest menu printed successfully
 * } else {
 *     // Error handling or additional logic
 * }
 * @endcode
 */
bool printGuestMenu(ostream &out) {
  clearScreen();
  out << "Guest Operations\n\n";
  out << "1. View Catalog\n";
  out << "2. Return to Main Menu\n";
  out << "Please enter a number to select:\n";
  return true;
}// prints screen GuestMenu.

/**
 * @brief Prints the main menu screen and prompts the user to make a selection.
 *
 * @param out Output stream object.
 * @return Always returns true after printing the main menu.
 *
 * This function clears the screen and displays the main menu options, prompting the user
 * to select an option by entering a number. The options include login, register, guest mode, and exit.
 * @code
 * if (printMainMenu(cout)) {
 *     // Main menu printed successfully
 * } else {
 *     // Error handling or additional logic
 * }
 * @endcode
 */
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

/**
 * @brief Prints the user operations menu screen and prompts the user to make a selection.
 *
 * @param out Output stream object.
 * @return Always returns true after printing the user operations menu.
 *
 * This function clears the screen and displays options for user operations, such as book cataloging,
 * loan management, wishlist management, reading tracker, and returning to the main menu.
 * @code
 * if (printUserMenu(cout)) {
 *     // User operations menu printed successfully
 * } else {
 *     // Error handling or additional logic
 * }
 * @endcode
 */
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

/**
 * @brief Prints the book cataloging menu screen and prompts the user to make a selection.
 *
 * @param out Output stream object.
 * @return Always returns true after printing the book cataloging menu.
 *
 * This function clears the screen and displays options for book cataloging operations, such as
 * adding a book, deleting a book, updating a book, viewing the catalog, and returning to user operations.
 * @code
 * if (printBookCatalogingMenu(cout)) {
 *     // Book cataloging menu printed successfully
 * } else {
 *     // Error handling or additional logic
 * }
 * @endcode
 */
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

/**
 * @brief Prints the loan management menu screen and prompts the user to make a selection.
 *
 * @param out Output stream object.
 * @return Always returns true after printing the loan management menu.
 *
 * This function clears the screen and displays options for loan management operations, such as
 * lending a book, borrowing a book, viewing loans, and returning to user operations.
 * @code
 * if (printLoanManagementMenu(cout)) {
 *     // Loan management menu printed successfully
 * } else {
 *     // Error handling or additional logic
 * }
 * @endcode
 */
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

/**
 * @brief Prints the wishlist management menu screen and prompts the user to make a selection.
 *
 * @param out Output stream object.
 * @return Always returns true after printing the wishlist management menu.
 *
 * This function clears the screen and displays options for wishlist management operations, such as
 * viewing the wishlist, adding to the wishlist, removing from the wishlist, and returning to user operations.
 * @code
 * if (printWishListMenu(cout)) {
 *     // Wishlist management menu printed successfully
 * } else {
 *     // Error handling or additional logic
 * }
 * @endcode
 */
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

/**
 * @brief Prints the reading tracker menu screen and prompts the user to make a selection.
 *
 * @param out Output stream object.
 * @return Always returns true after printing the reading tracker menu.
 *
 * This function clears the screen and displays options for reading tracker operations, such as
 * logging progress, marking as read, viewing history, and returning to user operations.
 * @code
 * if (printReadingTrackerMenu(cout)) {
 *     // Reading tracker menu printed successfully
 * } else {
 *     // Error handling or additional logic
 * }
 * @endcode
 */
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

/**
 * @brief Retrieves a new unique identifier for books.
 *
 * @return Returns an integer representing a new unique identifier for books.
 *
 * This function reads the existing book IDs from the "Books.bin" file, finds the highest ID,
 * and returns a new unique ID for a book by incrementing the highest existing ID.
 * If the file does not exist, it returns 1 as the starting ID.
 * @code
 * int newBookId = getNewId();
 * // Use 'newBookId' as the ID for a new book
 * @endcode
 */
int getNewId() {
  int lastId = 0;
  FILE *file = fopen("Books.bin", "rb");

  if (file == nullptr) return 1;

  Book book;

  while (fread(&book, sizeof(Book), 1, file) == 1)  if (book.id > lastId)  lastId = book.id;

  fclose(file);
  return lastId + 1;
}// fucntion that gets new id for books.

/**
 * @brief Adds a new book to the book catalog.
 *
 * @param in Input stream object.
 * @param out Output stream object.
 * @return Returns true if the book is added successfully, false otherwise.
 *
 * This function prompts the user to enter the name of the book, assigns a new unique ID to the book,
 * and adds the book to the "Books.bin" file. It returns true on success and false on failure.
 * @code
 * if (addBook(cin, cout)) {
 *     // Book added successfully
 * } else {
 *     // Error handling or additional logic
 * }
 * @endcode
 */
bool addBook(istream &in, ostream &out) {
  clearScreen();
  Book book;
  out << "Please enter the name of the book you want to add: ";
  in.ignore(numeric_limits<streamsize>::max(), '\n');
  in.getline(book.name, sizeof(book.name));
  book.id = getNewId();
  book.isMarked = false;
  FILE *file = fopen("Books.bin", "ab");

  if (!file) return false;

  fwrite(&book, sizeof(Book), 1, file);

  if (file == nullptr) return false;

  fclose(file);
  out << "Book added successfully." << endl;
  return true;
}// Function that allows us to add books to Books.bin.

/**
 * @brief Deletes a book from the book catalog based on the provided ID.
 *
 * @param in Input stream object.
 * @param out Output stream object.
 * @return Returns true if the book is deleted successfully, false otherwise.
 *
 * This function displays the catalog, prompts the user to enter the ID of the book to delete,
 * and removes the specified book from the "Books.bin" file. It returns true on success and false on failure.
 * @code
 * if (deleteBook(cin, cout)) {
 *     // Book deleted successfully
 * } else {
 *     // Error handling or additional logic
 * }
 * @endcode
 */
bool deleteBook(istream &in, ostream &out) {
  clearScreen();

  if (viewCatalogForFunc(out) == false)  return false;

  int id;
  out << "\nPlease enter the number of the book you want to delete: ";
  in >> id;

  if (in.fail()) {
    in.clear();
    in.ignore(numeric_limits<streamsize>::max(), '\n');
    out << "You must enter a numeric ID." << endl;
    return false;
  }

  FILE *file = fopen("Books.bin", "rb");
  FILE *tempFile = fopen("temp.bin", "wb");

  if (!file || !tempFile) return false;

  Book book;
  bool found = false;

  while (fread(&book, sizeof(Book), 1, file)) {
    if (book.id != id) fwrite(&book, sizeof(Book), 1, tempFile);
    else {
      found = true;
    }
  }

  fclose(file);
  fclose(tempFile);

  if (found) {
    remove("Books.bin");
    rename("temp.bin", "Books.bin");
    out << "Book deleted successfully." << endl;
  } else
    out << "Book with ID " << id << " not found." << endl;

  {
    remove("temp.bin");
  }// Clean up the temporary file as it's not needed
  return found;
}// Function that allows us to delete books from Books.bin

/**
 * @brief Updates the name of a book in the catalog based on the provided ID.
 *
 * @param in Input stream object.
 * @param out Output stream object.
 * @return Returns true if the book is updated successfully, false otherwise.
 *
 * This function displays the catalog, prompts the user to enter the ID of the book to update,
 * and allows the user to input a new name for the book. It updates the book's name in the "Books.bin" file.
 * @code
 * if (updateBook(cin, cout)) {
 *     // Book updated successfully
 * } else {
 *     // Error handling or additional logic
 * }
 * @endcode
 */
bool updateBook(istream &in, ostream &out) {
  clearScreen();

  if (viewCatalogForFunc(out) == false) return false;

  int id;
  out << ("\nPlease enter the number of the book you want to update: ");
  in >> id;
  FILE *file = fopen("Books.bin", "rb+");

  if (file == NULL) return 0;

  Book book;
  int found = 0;

  while (fread(&book, sizeof(Book), 1, file)) {
    if (book.id == id) {
      out << ("Please enter the new name of the book: ");
      in >> book.name;
      fseek(file, -sizeof(Book), SEEK_CUR);
      fwrite(&book, sizeof(Book), 1, file);
      found = 1;
      break;
    }
  }

  fclose(file);

  if (!found) return false;

  return true;
}// Function that allows us to change the books in Books.bin.

/**
 * @brief Displays the catalog of books from the "Books.bin" file.
 *
 * @param in Input stream object (unused).
 * @param out Output stream object.
 * @return Returns true if the catalog is displayed successfully, false otherwise.
 *
 * This function reads and prints the ID and name of each book in the "Books.bin" file.
 * It prompts the user to press enter to return to the main menu after displaying the catalog.
 * @code
 * if (viewCatalog(cin, cout)) {
 *     // Catalog displayed successfully
 * } else {
 *     // Error handling or additional logic
 * }
 * @endcode
 */
bool viewCatalog(istream &in, ostream &out) {
  clearScreen();
  FILE *file = fopen("Books.bin", "rb");

  if (file == NULL) return false;

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
    cout << "There are no books or could not open the books file.\n";
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
    cout << "Could not open the books file.\n";
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
    cout << "Could not open the books file.\n";
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
    cout << "There are no books or could not open the books file.\n";
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
