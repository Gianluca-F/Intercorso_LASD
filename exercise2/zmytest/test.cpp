
#include "./exercise1a/fulltest.hpp"
#include "./exercise1b/fulltest.hpp"
#include "./exercise2a/fulltest.hpp"
#include "./exercise2b/fulltest.hpp"

/* ************************************************************************** */

#include <iostream>

using namespace std;

/* ************************************************************************** */

void myTestExc1() {
  cout << endl << "~*~#~*~ Welcome to the MY Test Ex1 Suite ~*~#~*~ " << endl;
  
  uint loctestnum, loctesterr;
  uint testnum = 0, testerr = 0;

  loctestnum = 0; loctesterr = 0;
  myTestFullExercise1A(loctestnum, loctesterr);
  testnum += loctestnum; testerr += loctesterr;

  loctestnum = 0; loctesterr = 0;
  myTestFullExercise1B(loctestnum, loctesterr);
  testnum += loctestnum; testerr += loctesterr;

  cout << endl << "Exercise 1 (My Test) (Errors/Tests: " << testerr << "/" << testnum << ")" << endl;
  cout << endl << "~*~#~*~ End of the MY Test Ex1 Suite ~*~#~*~ " << endl << endl;
}

/* ************************************************************************** */

void myTestExc2() {
  cout << endl << "~*~#~*~ Welcome to the MY Test Ex2 Suite ~*~#~*~ " << endl;
  
  uint loctestnum, loctesterr;
  uint testnum = 0, testerr = 0;

  loctestnum = 0; loctesterr = 0;
  myTestFullExercise2A(loctestnum, loctesterr);
  testnum += loctestnum; testerr += loctesterr;

  loctestnum = 0; loctesterr = 0;
  myTestFullExercise2B(loctestnum, loctesterr);
  testnum += loctestnum; testerr += loctesterr;

  cout << endl << "Exercise 2 (My Test) (Errors/Tests: " << testerr << "/" << testnum << ")" << endl;
  cout << endl << "~*~#~*~ End of the MY Test Ex2 Suite ~*~#~*~ " << endl << endl;
}

/* ************************************************************************** */

void myFullTest() {
  cout << endl << "~*~#~*~ Welcome to the MY Full Test Suite ~*~#~*~ " << endl << endl;

  myTestExc1();
  myTestExc2();

  cout << endl << "~*~#~*~ End of the MY Full Test Suite ~*~#~*~ " << endl;
  cout << endl << "Goodbye!" << endl;
}

/* ************************************************************************** */

