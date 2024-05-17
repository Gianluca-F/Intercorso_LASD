#include <iostream>

/* ************************************************************************** */

#include "../../zlasdtest/container/container.hpp"
#include "../../zlasdtest/container/testable.hpp"
#include "../../zlasdtest/container/dictionary.hpp"
#include "../../zlasdtest/container/traversable.hpp"
#include "../../zlasdtest/container/mappable.hpp"
#include "../../zlasdtest/container/linear.hpp"

#include "../../zlasdtest/vector/vector.hpp"

#include "../../zlasdtest/list/list.hpp"

/* ************************************************************************** */

#include <random>
#include <cstring>

/* ************************************************************************** */

#define NUM 200
#define MAX 50      // FOR SOME TESTS, 2*MAX MUST BE < NUM

/* ************************************************************************** */

using namespace std;

/* ************************************************************************** */

namespace mytest {

/* ************************************************************************** */

void myTestVectorInt(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of Vector<int> Test:" << endl;

  try {
    lasd::Vector<int> v;
    Empty(loctestnum, loctesterr, v, true);
    GetAt(loctestnum, loctesterr, v, false, 0, 1);

    v.Resize(5);

    SetAt(loctestnum, loctesterr, v, true, 0, 1);
    SetAt(loctestnum, loctesterr, v, true, 1, 0);
    SetAt(loctestnum, loctesterr, v, true, 2, 0);
    SetAt(loctestnum, loctesterr, v, true, 3, 0);
    SetAt(loctestnum, loctesterr, v, true, 4, 2);

    GetFront(loctestnum, loctesterr, v, true, 1);
    GetBack(loctestnum, loctesterr, v, true, 2);

    lasd::Vector<int> v1(std::move(v));

    EqualLinear(loctestnum, loctesterr, v1, v, false);

    TraversePreOrder(loctestnum, loctesterr, v1, true, &TraversePrint<int>);

    MapPreOrder(loctestnum, loctesterr, v1, true, &MapDouble<int>);
    TraversePreOrder(loctestnum, loctesterr, v1, true, &TraversePrint<int>);
    GetFront(loctestnum, loctesterr, v1, true, 2);
    GetBack(loctestnum, loctesterr, v1, true, 4);

    lasd::SortableVector<int> v2(v1);
    v2.Sort();

    SetFront(loctestnum, loctesterr, v2, true, 0);
    SetBack(loctestnum, loctesterr, v2, true, NUM-2);

    FoldPreOrder(loctestnum, loctesterr, v2, true, &FoldAdd<int>, 0, 200);

    EqualVector(loctestnum, loctesterr, v1, v2, false);

    v1.Clear();
    Empty(loctestnum, loctesterr, v1, true);

  } catch (exception& exc) {
    cout << "Caught exception: " << exc.what() << endl;
    loctestnum++;
    loctesterr++;
  }

  testerr += loctesterr;
  testnum += loctestnum;
  cout << "Vector<int> Test (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}

/* ************************************************************************** */

void myTestVectorDouble(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of Vector<double> Test:" << endl;

  try {
    lasd::Vector<double> v;
    Empty(loctestnum, loctesterr, v, true);

    v.Resize(5);

    SetAt(loctestnum, loctesterr, v, true, 0, 1.1);
    SetAt(loctestnum, loctesterr, v, true, 1, 0.0);
    SetAt(loctestnum, loctesterr, v, true, 2, 0.0);
    SetAt(loctestnum, loctesterr, v, true, 3, 0.0);
    SetAt(loctestnum, loctesterr, v, true, 4, 2.2);

    GetFront(loctestnum, loctesterr, v, true, 1.1);
    GetBack(loctestnum, loctesterr, v, true, 2.2);

    lasd::Vector<double> v1(std::move(v));

    EqualLinear(loctestnum, loctesterr, v1, v, false);

    TraversePreOrder(loctestnum, loctesterr, v1, true, &TraversePrint<double>);

    MapPostOrder(loctestnum, loctesterr, v1, true, &MapDouble<double>);
    TraversePreOrder(loctestnum, loctesterr, v1, true, &TraversePrint<double>);
    GetFront(loctestnum, loctesterr, v1, true, 2.2);
    GetBack(loctestnum, loctesterr, v1, true, 4.4);

    lasd::SortableVector<double> v2(v1);
    v2.Sort();
    TraversePreOrder(loctestnum, loctesterr, v2, true, &TraversePrint<double>);

    SetFront(loctestnum, loctesterr, v2, true, 0.0);
    SetBack(loctestnum, loctesterr, v2, true, 9.9);

    double tmp = 2.2 + 9.9;
    FoldPostOrder(loctestnum, loctesterr, v2, true, &FoldAdd<double>, 0.0, tmp);

    EqualVector(loctestnum, loctesterr, v1, v2, false);

    v1.Clear();
    Empty(loctestnum, loctesterr, v1, true);

  } catch (exception& exc) {
    cout << "Caught exception: " << exc.what() << endl;
    loctestnum++;
    loctesterr++;
  }

  testerr += loctesterr;
  testnum += loctestnum;
  cout << "Vector<double> Test (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}

/* ************************************************************************** */

void myTestVectorString(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of Vector<string> Test:" << endl;

  try {
    lasd::Vector<string> v;
    Empty(loctestnum, loctesterr, v, true);

    v.Resize(5);

    SetAt(loctestnum, loctesterr, v, true, 0, string("A"));
    SetAt(loctestnum, loctesterr, v, true, 1, string("B"));
    SetAt(loctestnum, loctesterr, v, true, 2, string("C"));
    SetAt(loctestnum, loctesterr, v, true, 3, string("D"));
    SetAt(loctestnum, loctesterr, v, true, 4, string("E"));

    GetFront(loctestnum, loctesterr, v, true, string("A"));
    GetBack(loctestnum, loctesterr, v, true, string("E"));

    lasd::Vector<string> v1(std::move(v));

    EqualLinear(loctestnum, loctesterr, v1, v, false);

    TraversePreOrder(loctestnum, loctesterr, v1, true, &TraversePrint<string>);

    MapPostOrder(loctestnum, loctesterr, v1, true, [](string & s) { s = s + s; });
    TraversePreOrder(loctestnum, loctesterr, v1, true, &TraversePrint<string>);
    GetFront(loctestnum, loctesterr, v1, true, string("AA"));
    GetBack(loctestnum, loctesterr, v1, true, string("EE"));

    lasd::SortableVector<string> v2(v1);
    v2.Sort();
    TraversePostOrder(loctestnum, loctesterr, v2, true, &TraversePrint<string>);

    SetFront(loctestnum, loctesterr, v2, true, string("Z"));
    SetBack(loctestnum, loctesterr, v2, true, string("X"));

    FoldPostOrder(loctestnum, loctesterr, v2, true, &FoldStringConcatenate, string(""), string("XDDCCBBZ"));

    EqualVector(loctestnum, loctesterr, v1, v2, false);

    v1.Clear();
    Empty(loctestnum, loctesterr, v1, true);

  } catch (exception& exc) {
    cout << "Caught exception: " << exc.what() << endl;
    loctestnum++;
    loctesterr++;
  }

  testerr += loctesterr;
  testnum += loctestnum;
  cout << "Vector<string> Test (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}

/* ************************************************************************** */

void testListInt(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of List<int> Test:" << endl;

  try {
    lasd::List<int> l;
    Empty(loctestnum, loctesterr, l, true);
    Size(loctestnum, loctesterr, l, true, 0);

    InsertM(loctestnum, loctesterr, l, true, 1);
    InsertM(loctestnum, loctesterr, l, true, 2);
    InsertM(loctestnum, loctesterr, l, true, 3);

    GetFront(loctestnum, loctesterr, l, true, 1);
    GetBack(loctestnum, loctesterr, l, false, 2);
    Size(loctestnum, loctesterr, l, true, 3);

    RemoveFromFront(loctestnum, loctesterr, l, true);
    GetFront(loctestnum, loctesterr, l, true, 2);
    Size(loctestnum, loctesterr, l, false, 3);

    FrontNRemove(loctestnum, loctesterr, l, true, 2);
    Size(loctestnum, loctesterr, l, true, 1);

    lasd::Vector<int> v(NUM);
    for (int i = 0; i < NUM; i++) {
      v[i] = i;
    }

    InsertAllM(loctestnum, loctesterr, l, false, std::move(v));
    Size(loctestnum, loctesterr, l, true, NUM);

    InsertSomeC(loctestnum, loctesterr, l, false, v);
    Size(loctestnum, loctesterr, l, true, NUM);

    GetFront(loctestnum, loctesterr, l, true, 3);
    GetBack(loctestnum, loctesterr, l, true, NUM-1);

    lasd::List<int> l1(l);

    EqualList(loctestnum, loctesterr, l, l1, true);
    MapPreOrder(loctestnum, loctesterr, l, true, &MapDouble<int>);
    NonEqualList(loctestnum, loctesterr, l, l1, true);
    MapPostOrder(loctestnum, loctesterr, l, true, &MapHalf<int>);
    EqualList(loctestnum, loctesterr, l, l1, true);

    MapPreOrder(loctestnum, loctesterr, l, true, &MapParityInvert<int>);
    InsertSomeM(loctestnum, loctesterr, l, true, std::move(v));
    Size(loctestnum, loctesterr, l, true, NUM*1.5);

    l1 = l;
    EqualList(loctestnum, loctesterr, l, l1, true);
    RemoveAll(loctestnum, loctesterr, l, true, v);
    Size(loctestnum, loctesterr, l, true, NUM/2);

    lasd::Vector<int> v1(NUM);
    for (int i = -NUM; i < 0; i++) {
      v1[i+NUM] = i;
    }
    Exists(loctestnum, loctesterr, l, true, -1);
  
    RemoveSome(loctestnum, loctesterr, l, true, v1);
    Empty(loctestnum, loctesterr, l, true);

    Remove(loctestnum, loctesterr, l, false, 0);

  } catch (exception& exc) {
    cout << "Caught exception: " << exc.what() << endl;
    loctestnum++;
    loctesterr++;
  }

  testerr += loctesterr;
  testnum += loctestnum;
  cout << "List<int> Test (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}

/* ************************************************************************** */

 void testListDouble(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of List<double> Test:" << endl;

  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<int> distrib(-1*MAX, MAX);

  try {
    lasd::List<double> l;
    Empty(loctestnum, loctesterr, l, true);
    Size(loctestnum, loctesterr, l, true, 0);

    InsertM(loctestnum, loctesterr, l, true, 1.1);
    
    lasd::Vector<double> v(NUM);
    for(int i = 0; i < NUM; i++) {
      int r = distrib(gen);
      v[i] = r;
    }
    InsertAllM(loctestnum, loctesterr, l, false, std::move(v));
    Size(loctestnum, loctesterr, l, false, NUM);

    InsertM(loctestnum, loctesterr, l, true, 2.2);
    MapPostOrder(loctestnum, loctesterr, l, true, &MapHalf<double>);

    GetFront(loctestnum, loctesterr, l, true, 1.1/2);
    GetBack(loctestnum, loctesterr, l, true, 2.2/2);

    l.Clear();
    
    InsertC(loctestnum, loctesterr, l, true, 1.1);
    InsertC(loctestnum, loctesterr, l, true, 2.2);
    InsertC(loctestnum, loctesterr, l, true, 3.3);
    InsertC(loctestnum, loctesterr, l, true, 4.4);
    InsertC(loctestnum, loctesterr, l, true, 5.5);
    InsertC(loctestnum, loctesterr, l, true, 6.6);
    InsertC(loctestnum, loctesterr, l, true, 0.0);
    FoldPreOrder(loctestnum, loctesterr, l, true, &FoldMultiply<double>, 1.0, 0.0);
    Size(loctestnum, loctesterr, l, true, 7);
    Exists(loctestnum, loctesterr, l, true, 5.5);

    lasd::List<double> l1(l);
    EqualList(loctestnum, loctesterr, l, l1, true);

  } catch (exception& exc) {
    cout << "Caught exception: " << exc.what() << endl;
    loctestnum++;
    loctesterr++;
  }

  testerr += loctesterr;
  testnum += loctestnum;
  cout << "List<double> Test (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}

/* ************************************************************************** */

void testListString(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of List<string> Test:" << endl;

  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<int> distrib(-1*MAX, MAX);

  try {
    lasd::List<string> l;
    Empty(loctestnum, loctesterr, l, true);
    Size(loctestnum, loctesterr, l, true, 0);

    InsertAtBack(loctestnum, loctesterr, l, true, string("A"));
    InsertAtFront(loctestnum, loctesterr, l, true, string("B"));

    GetFront(loctestnum, loctesterr, l, true, string("B"));
    GetBack(loctestnum, loctesterr, l, true, string("A"));

    lasd::Vector<string> v(NUM);
    for(int i = 0; i < NUM; i++) {
      v[i] = to_string(i);
    }
    InsertAllC(loctestnum, loctesterr, l, true, v);
    Size(loctestnum, loctesterr, l, false, NUM);

    v.Resize(NUM-3);

    RemoveAll(loctestnum, loctesterr, l, true, v);
    GetFront(loctestnum, loctesterr, l, true, string("B"));
    GetBack(loctestnum, loctesterr, l, true, to_string(NUM-1));
    Size(loctestnum, loctesterr, l, true, 5);

    lasd::List<string> l1(l);

    EqualList(loctestnum, loctesterr, l, l1, true);
    MapPreOrder(loctestnum, loctesterr, l, true, [](string & s) { s = s + s; });
    GetBack(loctestnum, loctesterr, l, true, to_string(NUM-1) + to_string(NUM-1));
    NonEqualList(loctestnum, loctesterr, l, l1, true);

  } catch (exception& exc) {
    cout << "Caught exception: " << exc.what() << endl;
    loctestnum++;
    loctesterr++;
  }

  testerr += loctesterr;
  testnum += loctestnum;
  cout << "List<string> Test (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
} 

/* ************************************************************************** */

void myTestVector(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  myTestVectorInt(loctestnum, loctesterr);
  myTestVectorDouble(loctestnum, loctesterr);
  myTestVectorString(loctestnum, loctesterr);
  testnum += loctestnum; 
  testerr += loctesterr;
  cout << "Vector (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}

/* ************************************************************************** */

void myTestList(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  testListInt(loctestnum, loctesterr);
  testListDouble(loctestnum, loctesterr);
  testListString(loctestnum, loctesterr);
  testnum += loctestnum;
  testerr += loctesterr;
  cout << "List (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}

/* ************************************************************************** */

void myTestFullExercise1A(uint & testnum, uint & testerr) {
  myTestVector(testnum, testerr);
  myTestList(testnum, testerr);
}

/* ************************************************************************** */

}
