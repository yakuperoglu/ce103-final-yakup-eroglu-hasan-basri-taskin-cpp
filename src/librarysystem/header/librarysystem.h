#ifndef LIBRARYSYSTEM_H
#define LIBRARYSYSTEM_H

#include <string>

int mainMenu();

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

};

struct LoanManagment {

};

struct WishList {

};

struct ReadingTracker {

};

#endif
