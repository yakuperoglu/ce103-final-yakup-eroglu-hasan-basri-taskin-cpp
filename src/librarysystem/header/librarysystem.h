#ifndef LIBRARYSYSTEM_H
#define LIBRARYSYSTEM_H

#include <string>

using namespace std;



struct Deneme {
  static int admin_UserMenu();
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
struct FileBinaryOperations {
  bool WriteFile();
  bool ReadFile();
  bool ConvertBinaryToText();
  bool ConvertTextToBinary();
}
#endif
