
#include "./exercise1a/fulltest.hpp"
#include "./exercise1b/fulltest.hpp"
#include "./exercise2a/fulltest.hpp"
#include "./exercise2b/fulltest.hpp"

/* ************************************************************************** */

#include <iostream>

/* ************************************************************************** */

using namespace std;

/* ************************************************************************** */

namespace mytest {

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

void myTestExc1(uint & testnum, uint & testerr) {
  cout << endl << "~~~~~~~~~~~~~~~ Start of TestExc1 ~~~~~~~~~~~~~~~" << endl;

  uint loctestnum, loctesterr;

  loctestnum = 0; loctesterr = 0;
  myTestFullExercise1A(loctestnum, loctesterr);
  testnum += loctestnum; testerr += loctesterr;

  loctestnum = 0; loctesterr = 0;
  myTestFullExercise1B(loctestnum, loctesterr);
  testnum += loctestnum; testerr += loctesterr;

  cout << endl << "~~~~~~~~~~~~~~~ End of TestExc1 ~~~~~~~~~~~~~~~" << endl;
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

void myTestExc2(uint & testnum, uint & testerr) {
  cout << endl << "~~~~~~~~~~~~~~~ Start of TestExc2 ~~~~~~~~~~~~~~~" << endl;

  uint loctestnum, loctesterr;

  loctestnum = 0; loctesterr = 0;
  myTestFullExercise2A(loctestnum, loctesterr);
  testnum += loctestnum; testerr += loctesterr;

  loctestnum = 0; loctesterr = 0;
  myTestFullExercise2B(loctestnum, loctesterr);
  testnum += loctestnum; testerr += loctesterr;

  cout << endl << "~~~~~~~~~~~~~~~ End of TestExc2 ~~~~~~~~~~~~~~~" << endl;
}

/* ************************************************************************** */

void myFullTest() {
  cout << endl << "~*~#~*~ Welcome to the MY Full Test Suite ~*~#~*~ " << endl << endl;

  uint testnumExc1 = 0, testerrExc1 = 0;
  uint testnumExc2 = 0, testerrExc2 = 0;

  myTestExc1();
  myTestExc2();

  myTestExc1(testnumExc1, testerrExc1);
  myTestExc2(testnumExc2, testerrExc2);

  cout << endl << "~*~#~*~ End of the MY Full Test Suite ~*~#~*~ " << endl;

  cout << endl;
  cout << endl << "****** Recap of the MY Full Test Suite ******" << endl;
  cout << endl << "* Exercise 1 (My Test) (Errors/Tests: " << testerrExc1 << "/" << testnumExc1 << ") *" << endl;
  cout << endl << "* Exercise 2 (My Test) (Errors/Tests: " << testerrExc2 << "/" << testnumExc2 << ") *" << endl;
  cout << endl << "*********************************************" << endl;

  cout << endl << "Goodbye!" << endl;
}

/* ************************************************************************** */

}
