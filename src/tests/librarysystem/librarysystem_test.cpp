#include "LibrarySystem.h"
#include <gtest/gtest.h>

class UserAuthenticationTest : public ::testing::Test {
 protected:
  UserAuthentication auth;
};

TEST_F(UserAuthenticationTest, LoginWithValidCredentials) {
  // �rnek ge�erli kimlik bilgileri
  std::string email = "test@example.com";
  std::string password = "password123";
  // Ge�erli kimlik bilgileri ile giri� yapma testi
  User user = auth.login(email, password);
  // Beklenen sonucun kontrol�
  EXPECT_EQ(user.email, email);
}

TEST_F(UserAuthenticationTest, LoginWithInvalidCredentials) {
  // �rnek ge�ersiz kimlik bilgileri
  std::string email = "wrong@example.com";
  std::string password = "wrongpassword";
  // Ge�ersiz kimlik bilgileri ile giri� yapma testi
  User user = auth.login(email, password);
  // Beklenen sonucun kontrol�
  EXPECT_EQ(user.email, "");
}

TEST_F(UserAuthenticationTest, RegisterUser) {
  // Yeni kullan�c� kayd� i�in bilgiler
  std::string email = "newuser@example.com";
  std::string name = "New";
  std::string surname = "User";
  std::string password = "newpassword";
  // Kullan�c� kayd� testi
  bool result = auth.registerUser(email, name, surname, password);
  // Beklenen sonucun kontrol�
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
