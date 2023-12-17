#ifndef LIBRARYSYSTEM_H
#define LIBRARYSYSTEM_H

#include <string>

#include "../../utility/header/commonTypes.h"
using namespace std;
namespace Coruh {
namespace Librarysystem {

struct Deneme {

  int adminUserMenu();

};
struct User {
  string email;
  string name;
  string surname;

};
struct UserAuthentication {
  User login(const string &email, const string &password);
  bool registerUser(const string &email, const string &name, const string &surname, const string &password);

};

struct BookSystem {

};
struct LoanManagment {

};

struct WishList {

};

struct ReadingTracker {


};
}
}
#endif
