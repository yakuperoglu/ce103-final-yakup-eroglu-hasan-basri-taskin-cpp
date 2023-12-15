#include "../header/librarysystem.h"
#include <stdexcept>

using namespace Coruh::Librarysystem;

double Librarysystem::add(double a, double b) {
  return a + b;
}

double Librarysystem::subtract(double a, double b) {
  return a - b;
}

double Librarysystem::multiply(double a, double b) {
  return a * b;
}

double Librarysystem::divide(double a, double b) {
  if (b == 0) {
    throw std::invalid_argument("Division by zero is not allowed.");
  }

  return a / b;
}
