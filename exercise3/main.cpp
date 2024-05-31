
#include "zlasdtest/test.hpp"

#include "zmytest/test.hpp"

/* ************************************************************************** */

#include <iostream>

/* ************************************************************************** */

int main() {
  char test_number;

  std::cout << "Lasd Libraries 2024" << std::endl << std::endl;

  std::cout << " ************************************** " << std::endl;
  std::cout << " *                                    * " << std::endl;
  std::cout << " *   Runnable Test:                   * " << std::endl;
  std::cout << " *                                    * " << std::endl;
  std::cout << " *     (1) zmytest (only exercise1)   * " << std::endl;
  std::cout << " *     (2) zmytest (only exercise2)   * " << std::endl;
  std::cout << " *     (3) zmytest (only exercise3)   * " << std::endl;
  std::cout << " *     (4) zmytest (full)             * " << std::endl;
  std::cout << " *     (5) zlasdtest                  * " << std::endl;
  std::cout << " *                                    * " << std::endl;
  std::cout << " ************************************** " << std::endl << std::endl;
  
  std::cout << "Please enter the number of the test you want to run: ";
  std::cin >> test_number;

  switch (test_number)
  {
    case '1':
      mytest::myTestExc1();
      break;
    case '2':
      mytest::myTestExc2();
      break;
    case '3':
      mytest::myTestExc3();
      break;
    case '4':
      mytest::myFullTest();
      break;
    case '5':
      lasdtest();
      break;
    default:
      std::cout << "Invalid test number" << std::endl;
  }
  
  return 0;
}
