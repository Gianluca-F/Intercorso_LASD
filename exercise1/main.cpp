
#include "zlasdtest/test.hpp"

#include "zmytest/test.hpp"

/* ************************************************************************** */

#include <iostream>

/* ************************************************************************** */

int main() {
  short test_number;

  std::cout << "Lasd Libraries 2024" << std::endl << std::endl;

  std::cout << " **************************** " << std::endl;
  std::cout << " *                          * " << std::endl;
  std::cout << " *   Runnable Test:         * " << std::endl;
  std::cout << " *                          * " << std::endl;
  std::cout << " *     (1) zmytest          * " << std::endl;
  std::cout << " *     (2) zlasdtest        * " << std::endl;
  std::cout << " *                          * " << std::endl;
  std::cout << " **************************** " << std::endl << std::endl;
  
  std::cout << "Please enter the number of the test you want to run: ";
  std::cin >> test_number;

  switch (test_number)
  {
    case 1:
      mytest();
      break;
    case 2:
      lasdtest();
      break;
    default:
      std::cout << "Invalid test number" << std::endl;
  }
  
  return 0;
}
