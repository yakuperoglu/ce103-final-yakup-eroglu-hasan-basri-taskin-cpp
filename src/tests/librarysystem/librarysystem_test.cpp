#include "LibrarySystem.h"
#include <gtest/gtest.h>

class UserAuthenticationTest : public ::testing::Test {
 protected:
  UserAuthentication auth;
};

TEST_F(UserAuthenticationTest, LoginWithValidCredentials) {
  // Örnek geçerli kimlik bilgileri
  std::string email = "test@example.com";
  std::string password = "password123";
  // Geçerli kimlik bilgileri ile giriþ yapma testi
  User user = auth.login(email, password);
  // Beklenen sonucun kontrolü
  EXPECT_EQ(user.email, email);
}

TEST_F(UserAuthenticationTest, LoginWithInvalidCredentials) {
  // Örnek geçersiz kimlik bilgileri
  std::string email = "wrong@example.com";
  std::string password = "wrongpassword";
  // Geçersiz kimlik bilgileri ile giriþ yapma testi
  User user = auth.login(email, password);
  // Beklenen sonucun kontrolü
  EXPECT_EQ(user.email, "");
}

TEST_F(UserAuthenticationTest, RegisterUser) {
  // Yeni kullanýcý kaydý için bilgiler
  std::string email = "newuser@example.com";
  std::string name = "New";
  std::string surname = "User";
  std::string password = "newpassword";
  // Kullanýcý kaydý testi
  bool result = auth.registerUser(email, name, surname, password);
  // Beklenen sonucun kontrolü
  EXPECT_TRUE(result);
}


int main(int argc, char **argv) {
#ifdef ENABLE_LIBRARYSYSTEM_TEST
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
#else
  return 0;
#endif
}
