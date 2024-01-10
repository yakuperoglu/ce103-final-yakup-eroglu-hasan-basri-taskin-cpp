/**
 * @file librarysystem.h
 * @brief Header file for the Personal Library System.
 *
 * This file defines constants and includes necessary headers for the implementation
 * of the Personal Library System. It also sets a maximum size for character arrays
 * used in the structures.
 */

#ifndef LIBRARYSYSTEM_H
#define LIBRARYSYSTEM_H

#define MAX_STRINGSIZE 100 /**< Maximum size for character arrays in the structures. */

#include <iostream>

/**
 * @namespace std
 * @brief The standard C++ library namespace.
 *
 * This namespace contains the Standard C++ Library functions and objects.
 */
using namespace std;

/**
 * @brief Structure representing a book in the library.
 */
typedef struct {
  int id; /**< Unique identifier for the book. */
  char name[MAX_STRINGSIZE]; /**< Name of the book. */
  bool isMarked; /**< Flag indicating whether the book is marked (read) or not. */
} Book;

/**
 * @brief Structure representing a user in the library system.
 */
typedef struct {
  char email[MAX_STRINGSIZE]; /**< Email of the user. */
  char password[MAX_STRINGSIZE]; /**< Password of the user. */
} User;

/**
 * @brief Gets input from the user.
 *
 * @param in Input stream object.
 * @return Integer input obtained from the user.
 */
int getInput(istream &in);

/**
 * @brief Pauses execution and waits for the user to press any key to continue.
 *
 * @param in Input stream object.
 * @param out Output stream object.
 * @return Returns true after the user presses a key.
 */
bool enterToContunie(istream &in, ostream &out);

/**
 * @brief Generates a new unique ID for books based on existing IDs.
 *
 * @return New unique ID for books.
 */
int getNewId();

/**
 * @brief Handles input errors by clearing the input stream and displaying an error message.
 *
 * @param in Input stream object.
 * @param out Output stream object.
 * @return Returns false to indicate an input error.
 */
bool handleInputError(istream &in, ostream &out);

/**
 * @brief Displays the main menu and redirects the user based on their choice.
 *
 * @param in Input stream object.
 * @param out Output stream object.
 * @return Returns 0 when the user chooses to exit the program.
 */
int mainMenu(istream &in, ostream &out);

/**
 * @brief Redirects the user to specific operations based on their choice in the user menu.
 *
 * @param in Input stream object.
 * @param out Output stream object.
 * @return Returns 0 when the user chooses to return to the main menu.
 */
bool userOperations(istream &in, ostream &out);

/**
 * @brief Redirects a guest user to specific operations based on their choice in the guest menu.
 *
 * @param in Input stream object.
 * @param out Output stream object.
 * @return Returns false when the guest chooses to exit.
 */
bool guestOperation(istream &in, ostream &out);

/**
 * @brief Registers a new user in the library system.
 *
 * @param in Input stream object.
 * @param out Output stream object.
 * @return Returns true if user registration is successful.
 */
bool registerUser(istream &in, ostream &out);

/**
 * @brief Logs in a user to the library system.
 *
 * @param in Input stream object.
 * @param out Output stream object.
 * @return Returns true if login is successful.
 */
bool loginUser(istream &in, ostream &out);

/**
 * @brief Handles the book cataloging menu, allowing users to perform operations on books.
 *
 * @param input Input stream object.
 * @param output Output stream object.
 * @return Returns true when the user chooses to return to the main menu.
 */
bool bookCatalogingMenu(istream &input, ostream &output);

/**
 * @brief Handles the loan management menu, allowing users to lend and borrow books.
 *
 * @param input Input stream object.
 * @param output Output stream object.
 * @return Returns true when the user chooses to return to the main menu.
 */
bool loanManagementMenu(istream &input, ostream &output);

/**
 * @brief Handles the wishlist menu, allowing users to manage their book wishlists.
 *
 * @param input Input stream object.
 * @param output Output stream object.
 * @return Returns false when the user chooses to exit the wishlist menu.
 */
bool wishListMenu(istream &input, ostream &output);

/**
 * @brief Handles the reading tracker menu, allowing users to track their reading progress.
 *
 * @param input Input stream object.
 * @param output Output stream object.
 * @return Returns 0 when the user chooses to return to the main menu.
 */
bool readingTrackerMenu(istream &input, ostream &output);

/**
 * @brief Prints the main menu screen.
 *
 * @param out Output stream object.
 * @return Returns true after printing the main menu.
 */
bool printMainMenu(ostream &out);

/**
 * @brief Prints the guest menu screen.
 *
 * @param out Output stream object.
 * @return Returns true after printing the guest menu.
 */
bool printGuestMenu(ostream &out);

bool printUserMenu(ostream &out);
bool printBookCatalogingMenu(ostream &out);
bool printLoanManagementMenu(ostream &out);
bool printWishListMenu(ostream &out);
bool printReadingTrackerMenu(ostream &out);

bool addBook(istream &in, ostream &out);
bool updateBook(istream &in, ostream &out);
bool deleteBook(istream &in, ostream &out);
bool viewCatalog(istream &in, ostream &out);
bool viewCatalogForFunc(istream &in, ostream &out);

bool lendBook(istream &in, ostream &out);
bool borrowBook(istream &in, ostream &out);
bool viewLoans(istream &in, ostream &out);
bool viewLoansForFunc(istream &in, ostream &out);

bool listWishList(istream &in, ostream &out);
bool listWishListForFunc(istream &in, ostream &out);
bool addToWishList(istream &in, ostream &out);
bool removeFromWishList(istream &in, ostream &out);

bool listUnMarkedBooks(istream &in, ostream &out);
bool logProgress(istream &in, ostream &out);
bool markAsRead(istream &in, ostream &out);
bool viewHistory(istream &in, ostream &out);
#endif
