/**
 * @file main.cpp
 * @brief Main program file for the Personal Library System.
 *
 * This file contains the main function that initializes the library system
 * and invokes the main menu to interact with users. It includes necessary
 * headers and uses the librarysystem.h functions to manage the library operations.
 */

#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <stdexcept>
#include "librarysystem.h"

using namespace std;

/**
 * @brief Main function to run the Personal Library System.
 *
 * The main function initializes the library system and invokes the main menu,
 * allowing users to interact with the library operations. It uses functions
 * from the librarysystem.h header to handle various functionalities.
 *
 * @return 0 on successful execution.
 */
int main() {
  mainMenu(std::cin, std::cout);
  return 0;
}
