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

/**< Using the std namespace for convenience. */
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

/**
 * @brief Prints the user menu screen.
 *
 * @param out Output stream object.
 * @return Returns true after printing the user menu.
 */
bool printUserMenu(ostream &out);

/**
 * @brief Prints the book cataloging menu screen.
 *
 * @param out Output stream object.
 * @return Returns true after printing the book cataloging menu.
 */
bool printBookCatalogingMenu(ostream &out);

/**
 * @brief Prints the loan management menu screen.
 *
 * @param out Output stream object.
 * @return Returns true after printing the loan management menu.
 */
bool printLoanManagementMenu(ostream &out);

/**
 * @brief Prints the wishlist menu screen.
 *
 * @param out Output stream object.
 * @return Returns true after printing the wishlist menu.
 */
bool printWishListMenu(ostream &out);

/**
 * @brief Prints the reading tracker menu screen.
 *
 * @param out Output stream object.
 * @return Returns true after printing the reading tracker menu.
 */
bool printReadingTrackerMenu(ostream &out);

/**
 * @brief Adds a new book to the library catalog.
 *
 * @param in Input stream object.
 * @param out Output stream object.
 * @return Returns true if the book is added successfully.
 */
bool addBook(istream &in, ostream &out);

/**
 * @brief Updates the information of an existing book in the library catalog.
 *
 * @param in Input stream object.
 * @param out Output stream object.
 * @return Returns true if the book is updated successfully.
 */
bool updateBook(istream &in, ostream &out);

/**
 * @brief Deletes a book from the library catalog.
 *
 * @param in Input stream object.
 * @param out Output stream object.
 * @return Returns true if the book is deleted successfully.
 */
bool deleteBook(istream &in, ostream &out);

/**
 * @brief Displays the entire catalog of books in the library.
 *
 * @param in Input stream object.
 * @param out Output stream object.
 * @return Returns true if the catalog is displayed successfully.
 */
bool viewCatalog(istream &in, ostream &out);

/**
 * @brief Displays the entire catalog of books in the library (for function use).
 *
 * @param out Output stream object.
 * @return Returns true if the catalog is displayed successfully.
 */
bool viewCatalogForFunc(ostream &out);

/**
 * @brief Lends a book from the library catalog to a user.
 *
 * @param in Input stream object.
 * @param out Output stream object.
 * @return Returns true if the book is successfully lent.
 */
bool lendBook(istream &in, ostream &out);

/**
 * @brief Borrows a book from the library catalog by a user.
 *
 * @param in Input stream object.
 * @param out Output stream object.
 * @return Returns true if the book is successfully borrowed.
 */
bool borrowBook(istream &in, ostream &out);

/**
 * @brief Displays the list of books that are currently on loan.
 *
 * @param in Input stream object.
 * @param out Output stream object.
 * @return Returns true if the list of loans is displayed successfully.
 */
bool viewLoans(istream &in, ostream &out);

/**
 * @brief Displays the list of books that are currently on loan (for function use).
 *
 * @param out Output stream object.
 * @return Returns true if the list of loans is displayed successfully.
 */
bool viewLoansForFunc(ostream &out);

/**
 * @brief Displays the user's wishlist of books.
 *
 * @param in Input stream object.
 * @param out Output stream object.
 * @return Returns true if the wishlist is displayed successfully.
 */
bool listWishList(istream &in, ostream &out);

/**
 * @brief Displays the user's wishlist of books (for function use).
 *
 * @param out Output stream object.
 * @return Returns true if the wishlist is displayed successfully.
 */
bool listWishListForFunc(ostream &out);

/**
 * @brief Adds a book to the user's wishlist.
 *
 * @param in Input stream object.
 * @param out Output stream object.
 * @return Returns true if the book is successfully added to the wishlist.
 */
bool addToWishList(istream &in, ostream &out);

/**
 * @brief Removes a book from the user's wishlist.
 *
 * @param in Input stream object.
 * @param out Output stream object.
 * @return Returns true if the book is successfully removed from the wishlist.
 */
bool removeFromWishList(istream &in, ostream &out);

/**
 * @brief Displays the list of books that have not been marked as read.
 *
 * @param out Output stream object.
 * @return Returns true if the list of unmarked books is displayed successfully.
 */
bool listUnMarkedBooks(ostream &out);

/**
 * @brief Displays the user's reading progress and marked books.
 *
 * @param in Input stream object.
 * @param out Output stream object.
 * @return Returns true if the progress is displayed successfully.
 */
bool logProgress(istream &in, ostream &out);

/**
 * @brief Marks a book as read in the user's reading history.
 *
 * @param in Input stream object.
 * @param out Output stream object.
 * @return Returns true if the book is successfully marked as read.
 */
bool markAsRead(istream &in, ostream &out);

/**
 * @brief Displays the user's reading history of marked books.
 *
 * @param in Input stream object.
 * @param out Output stream object.
 * @return Returns true if the reading history is displayed successfully.
 */
bool viewHistory(istream &in, ostream &out);

#endif
