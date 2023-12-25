#ifndef LIBRARYSYSTEM_H
#define LIBRARYSYSTEM_H

using namespace std;

const int maxStringSize = 100;
struct User {
  char email[maxStringSize];
  char name[maxStringSize];
  char surname[maxStringSize];
  char password[maxStringSize];
};

struct UserAuthentication {
  User login(const char &email, const char &password);
  bool registerUser(const char &email, const char &name, const char &surname, const char &password);
  static bool writeUser(const User &user);
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

//struct FileBinaryOperations {
//  bool WriteFile(const char* fileName);
//  bool ReadFile();
//  bool ConvertBinaryToText();
//  bool ConvertTextToBinary();
//};
#endif
