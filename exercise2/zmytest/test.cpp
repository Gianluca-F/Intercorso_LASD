
#include "./exercise/fulltest.hpp"

/* ************************************************************************** */

#include <iostream>

using namespace std;

/* ************************************************************************** */

void mytest() {
  cout << endl << "~*~#~*~ Welcome to the MY Test Suite ~*~#~*~ " << endl;
  
  uint loctestnum, loctesterr;
  uint ftestnum = 0, ftesterr = 0;

  loctestnum = 0; loctesterr = 0;
  testFullExercise(loctestnum, loctesterr);
  ftestnum += loctestnum; ftesterr += loctesterr;

  cout << endl << "Exercise (Full Test) (Errors/Tests: " << ftesterr << "/" << ftestnum << ")" << endl;
  cout << endl << "Goodbye!" << endl;
}

/* ************************************************************************** */

