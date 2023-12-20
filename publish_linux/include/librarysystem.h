#ifndef LIBRARYSYSTEM_H
#define LIBRARYSYSTEM_H

#include <string>

int mainMenu();

bool userOperations();

struct User {
  std::string email;
  std::string name;
  std::string surname;
};

struct UserAuthentication {
  User login(const std::string &email, const std::string &password);
  bool registerUser(const std::string &email, const std::string &name, const std::string &surname, const std::string &password);
};

struct BookSystem {
  static bool addBook();
  static bool updateBook();
  static bool deleteBook();
  static bool viewCatalog();
};

struct LoanManagment {
  static bool lendBook();
  static bool borrowBook();
  static bool viewLoans();
};

struct WishList {
  static bool wishList();
  static bool addToWishList();
  static bool removeFromWishList();
};


struct ReadingTracker {
  static bool logProgress();
  static bool markAsRead();
  static bool viewHistory();
};

struct dataBase {

};

#endif
