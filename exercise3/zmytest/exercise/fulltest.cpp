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

#include "../../zlasdtest/stack/stack.hpp"
#include "../../stack/vec/stackvec.hpp"
#include "../../stack/lst/stacklst.hpp"

#include "../../zlasdtest/queue/queue.hpp"
#include "../../queue/vec/queuevec.hpp"
#include "../../queue/lst/queuelst.hpp"

#include "../../zlasdtest/binarytree/binarytree.hpp"
#include "../../binarytree/lnk/binarytreelnk.hpp"
#include "../../binarytree/vec/binarytreevec.hpp"

#include "../../zlasdtest/iterator/iterator.hpp"

#include "../../zlasdtest/bst/bst.hpp"
#include "../../bst/bst.hpp"



/* ************************************************************************** */

#include <random>
#include <cstring>

/* ************************************************************************** */

#define NUM 200
#define MAX 50      // FOR SOME TESTS, 2*MAX MUST BE < NUM

/* ************************************************************************** */

using namespace std;

/* ************************************************************************** */

void testVectorInt(uint & testnum, uint & testerr) {
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

void testVectorDouble(uint & testnum, uint & testerr) {
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

void testVectorString(uint & testnum, uint & testerr) {
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
      uint r = distrib(gen);
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

template <typename Stk>
void testStackInt(Stk & stk, uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;  

  try {
    Empty(loctestnum, loctesterr, stk, true);
    Top(loctestnum, loctesterr, stk, false, 0);

    PushC(loctestnum, loctesterr, stk, 1);
    PushC(loctestnum, loctesterr, stk, 2);
    PushC(loctestnum, loctesterr, stk, 3);
    Top(loctestnum, loctesterr, stk, true, 3);

    Pop(loctestnum, loctesterr, stk, true);
    Top(loctestnum, loctesterr, stk, true, 2);

    Size(loctestnum, loctesterr, stk, true, 2);

    PushC(loctestnum, loctesterr, stk, 4);
    PushC(loctestnum, loctesterr, stk, 5);

    Size(loctestnum, loctesterr, stk, true, 4);

    Top(loctestnum, loctesterr, stk, true, 5);

    TopNPop(loctestnum, loctesterr, stk, true, 5);

    Size(loctestnum, loctesterr, stk, true, 3);

    Stk stk1(stk);

    EqualStack(loctestnum, loctesterr, stk, stk1, true);

    stk1.Clear();
    Empty(loctestnum, loctesterr, stk1, true);

    Stk stk2(std::move(stk));

    EqualStack(loctestnum, loctesterr, stk, stk2, false);

    stk2.Clear();
    Empty(loctestnum, loctesterr, stk2, true);

    for(int i = 0; i < NUM; i++) {
      stk2.Push(i);
    }

    Size(loctestnum, loctesterr, stk2, true, NUM);

  } catch (exception& exc) {
    cout << "Caught exception: " << exc.what() << endl;
    loctestnum++;
    loctesterr++;
  }
  
  testnum += loctestnum;
  testerr += loctesterr;
  cout << endl << "End of Stack<Int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}
void testStackInt(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  lasd::StackLst<int> s;
  cout << endl << "Begin of StackLst<Int> Test:" << endl;
  testStackInt(s, loctestnum, loctesterr);
  lasd::StackVec<int> s1;
  cout << endl << "Begin of StackVec<Int> Test:" << endl;
  testStackInt(s1, loctestnum, loctesterr);
  testerr += loctesterr;
  testnum += loctestnum;
}

/* ************************************************************************** */

template <typename Stk>
void testStackDouble(Stk & stk, uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;  

  try {
    Empty(loctestnum, loctesterr, stk, true);
    Pop(loctestnum, loctesterr, stk, false);

    PushC(loctestnum, loctesterr, stk, 1.1);
    PushC(loctestnum, loctesterr, stk, 2.2);
    PushC(loctestnum, loctesterr, stk, 3.3);
    Top(loctestnum, loctesterr, stk, true, 3.3);

    Pop(loctestnum, loctesterr, stk, true);
    Top(loctestnum, loctesterr, stk, true, 2.2);

    Size(loctestnum, loctesterr, stk, true, 2);

    PushC(loctestnum, loctesterr, stk, 4.4);
    PushC(loctestnum, loctesterr, stk, 5.5);

    Size(loctestnum, loctesterr, stk, true, 4);

    Top(loctestnum, loctesterr, stk, true, 5.5);

    TopNPop(loctestnum, loctesterr, stk, true, 5.5);

    Size(loctestnum, loctesterr, stk, true, 3);

    Stk stk1(stk);

    EqualStack(loctestnum, loctesterr, stk, stk1, true);

    stk1.Clear();
    Empty(loctestnum, loctesterr, stk1, true);

    Stk stk2(std::move(stk));

    EqualStack(loctestnum, loctesterr, stk, stk2, false);

    stk2.Clear();
    Empty(loctestnum, loctesterr, stk2, true);

  } catch (exception& exc) {
    cout << "Caught exception: " << exc.what() << endl;
    loctestnum++;
    loctesterr++;
  }

  testnum += loctestnum;
  testerr += loctesterr;
  cout << endl << "End of Stack<Float> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}
void testStackDouble(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  lasd::StackVec<double> s;
  cout << endl << "Begin of StackVec<double> Test:" << endl;
  testStackDouble(s, loctestnum, loctesterr);
  lasd::StackLst<double> s1;
  cout << endl << "Begin of StackLst<double> Test:" << endl;
  testStackDouble(s1, loctestnum, loctesterr);
  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */

template <typename Stk>
void testStackString(Stk & stk, uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;  

  try {
    Empty(loctestnum, loctesterr, stk, true);
    Pop(loctestnum, loctesterr, stk, false);

    PushC(loctestnum, loctesterr, stk, string("A"));
    PushC(loctestnum, loctesterr, stk, string("B"));
    PushC(loctestnum, loctesterr, stk, string("C"));
    Top(loctestnum, loctesterr, stk, true, string("C"));

    Pop(loctestnum, loctesterr, stk, true);
    Top(loctestnum, loctesterr, stk, true, string("B"));

    Size(loctestnum, loctesterr, stk, true, 2);

    PushC(loctestnum, loctesterr, stk, string("D"));
    PushC(loctestnum, loctesterr, stk, string("E"));

    Size(loctestnum, loctesterr, stk, true, 4);

    Top(loctestnum, loctesterr, stk, true, string("E"));

    TopNPop(loctestnum, loctesterr, stk, true, string("E"));

    Size(loctestnum, loctesterr, stk, true, 3);

    Stk stk1(stk);

    EqualStack(loctestnum, loctesterr, stk, stk1, true);

    stk1.Clear();
    Empty(loctestnum, loctesterr, stk1, true);

    Stk stk2(std::move(stk));

    EqualStack(loctestnum, loctesterr, stk, stk2, false);

    stk2.Clear();
    Empty(loctestnum, loctesterr, stk2, true);

    for(int i = 0; i < NUM; i++) {
      stk2.Push(to_string(i));
    }

    TopNPop(loctestnum, loctesterr, stk2, true, to_string(NUM-1));

  } catch (exception& exc) {
    cout << "Caught exception: " << exc.what() << endl;
    loctestnum++;
    loctesterr++;
  }

  testnum += loctestnum;
  testerr += loctesterr;
  cout << endl << "End of Stack<String> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}
void testStackString(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  lasd::StackVec<string> s;
  cout << endl << "Begin of StackVec<string> Test:" << endl;
  testStackString(s, loctestnum, loctesterr);
  lasd::StackLst<string> s1;
  cout << endl << "Begin of StackLst<string> Test:" << endl;
  testStackString(s1, loctestnum, loctesterr);
  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */

template <typename Queue>
void testQueueInt(Queue & q, uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;

  try {
    Empty(loctestnum, loctesterr, q, true);
    Head(loctestnum, loctesterr, q, false, 0);

    EnqueueM(loctestnum, loctesterr, q, 1);
    EnqueueM(loctestnum, loctesterr, q, 2);
    EnqueueM(loctestnum, loctesterr, q, 3);
    Head(loctestnum, loctesterr, q, true, 1);

    Dequeue(loctestnum, loctesterr, q, true);
    Head(loctestnum, loctesterr, q, true, 2);

    Size(loctestnum, loctesterr, q, true, 2);

    EnqueueC(loctestnum, loctesterr, q, 4);
    EnqueueC(loctestnum, loctesterr, q, 5);

    Size(loctestnum, loctesterr, q, true, 4);

    Head(loctestnum, loctesterr, q, true, 2);

    HeadNDequeue(loctestnum, loctesterr, q, true, 2);

    Size(loctestnum, loctesterr, q, true, 3);

    Queue q1(q);

    EqualQueue(loctestnum, loctesterr, q, q1, true);

    q1.Clear();
    Empty(loctestnum, loctesterr, q1, true);

    Queue q2(std::move(q));

    EqualQueue(loctestnum, loctesterr, q, q2, false);

    q2.Clear();
    Empty(loctestnum, loctesterr, q2, true);

    for(int i = 0; i < NUM; i++) {
      q2.Enqueue(i);
    }

    Size(loctestnum, loctesterr, q2, true, NUM);

  } catch (exception& exc) {
    cout << "Caught exception: " << exc.what() << endl;
    loctestnum++;
    loctesterr++;
  }

  testnum += loctestnum;
  testerr += loctesterr;
  cout << endl << "End of Queue<Int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}
void testQueueInt(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  lasd::QueueVec<int> q;
  cout << endl << "Begin of QueueVec<int> Test:" << endl;
  testQueueInt(q, loctestnum, loctesterr);
  lasd::QueueLst<int> q1;
  cout << endl << "Begin of QueueLst<int> Test:" << endl;
  testQueueInt(q1, loctestnum, loctesterr);
  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */

template <typename Queue>
void testQueueDouble(Queue & q, uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;

  try {
    Empty(loctestnum, loctesterr, q, true);
    Head(loctestnum, loctesterr, q, false, 0.0);

    EnqueueM(loctestnum, loctesterr, q, 1.1);
    EnqueueM(loctestnum, loctesterr, q, 2.2);
    EnqueueM(loctestnum, loctesterr, q, 3.3);
    Head(loctestnum, loctesterr, q, true, 1.1);

    Dequeue(loctestnum, loctesterr, q, true);
    Head(loctestnum, loctesterr, q, true, 2.2);

    Size(loctestnum, loctesterr, q, true, 2);

    EnqueueC(loctestnum, loctesterr, q, 4.4);
    EnqueueC(loctestnum, loctesterr, q, 5.5);

    Size(loctestnum, loctesterr, q, true, 4);

    Head(loctestnum, loctesterr, q, true, 2.2);

    HeadNDequeue(loctestnum, loctesterr, q, true, 2.2);

    Size(loctestnum, loctesterr, q, true, 3);

    Queue q1(q);

    EqualQueue(loctestnum, loctesterr, q, q1, true);

    q.Clear();
    Empty(loctestnum, loctesterr, q, true);

    Queue q2(std::move(q));

    EqualQueue(loctestnum, loctesterr, q1, q2, false);
    Size(loctestnum, loctesterr, q2, true, 0);

    q2.Clear();
    Empty(loctestnum, loctesterr, q2, true);

    for(int i = 0; i < NUM; i++) {
      q2.Enqueue(i);
    }

    Size(loctestnum, loctesterr, q2, true, NUM);

  } catch (exception& exc) {
    cout << "Caught exception: " << exc.what() << endl;
    loctestnum++;
    loctesterr++;
  }

  testnum += loctestnum;
  testerr += loctesterr;
  cout << endl << "End of Queue<Float> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}
void testQueueDouble(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  lasd::QueueVec<double> q;
  cout << endl << "Begin of QueueVec<double> Test:" << endl;
  testQueueDouble(q, loctestnum, loctesterr);
  lasd::QueueLst<double> q1;
  cout << endl << "Begin of QueueLst<double> Test:" << endl;
  testQueueDouble(q1, loctestnum, loctesterr);
  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */

template <typename Queue>
void testQueueString(Queue & q, uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;

  try {
    Empty(loctestnum, loctesterr, q, true);
    Head(loctestnum, loctesterr, q, false, string("A"));

    EnqueueM(loctestnum, loctesterr, q, string("A"));
    EnqueueM(loctestnum, loctesterr, q, string("B"));
    EnqueueM(loctestnum, loctesterr, q, string("C"));
    Head(loctestnum, loctesterr, q, true, string("A"));

    Dequeue(loctestnum, loctesterr, q, true);
    Head(loctestnum, loctesterr, q, true, string("B"));

    Size(loctestnum, loctesterr, q, true, 2);

    EnqueueC(loctestnum, loctesterr, q, string("D"));
    EnqueueC(loctestnum, loctesterr, q, string("E"));

    Size(loctestnum, loctesterr, q, true, 4);

    Head(loctestnum, loctesterr, q, true, string("B"));

    HeadNDequeue(loctestnum, loctesterr, q, true, string("B"));

    Size(loctestnum, loctesterr, q, true, 3);

    Queue q1(q);

    EqualQueue(loctestnum, loctesterr, q, q1, true);

    q1.Clear();
    Empty(loctestnum, loctesterr, q1, true);

    Queue q2(std::move(q));

    EqualQueue(loctestnum, loctesterr, q, q2, false);

    q2.Clear();
    Empty(loctestnum, loctesterr, q2, true);

    for(int i = 0; i < NUM; i++) {
      q2.Enqueue(to_string(i));
    }

    Size(loctestnum, loctesterr, q2, true, NUM);

  } catch (exception& exc) {
    cout << "Caught exception: " << exc.what() << endl;
    loctestnum++;
    loctesterr++;
  }

  testnum += loctestnum;
  testerr += loctesterr;
  cout << endl << "End of Queue<String> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}
void testQueueString(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  lasd::QueueVec<string> q;
  cout << endl << "Begin of QueueVec<string> Test:" << endl;
  testQueueString(q, loctestnum, loctesterr);
  lasd::QueueLst<string> q1;
  cout << endl << "Begin of QueueLst<string> Test:" << endl;
  testQueueString(q1, loctestnum, loctesterr);
  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */

void testBinaryTreeInt(lasd::BinaryTree<int> & bt, uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  try {
    Traverse(loctestnum, loctesterr, bt, true, &TraversePrint<int>);

    Root(loctestnum, loctesterr, bt, true, 3);
    GetElement(loctestnum, loctesterr, bt.Root(), true, 3);

    Traverse(loctestnum, loctesterr, bt, true, &TraversePrint<int>);

    IsLeaf<int>(loctestnum, loctesterr, bt.Root().RightChild(), true);
    IsLeaf<int>(loctestnum, loctesterr, bt.Root().LeftChild(), false);
    HasLeftChild<int>(loctestnum, loctesterr, bt.Root().LeftChild(), true);
    HasRightChild<int>(loctestnum, loctesterr, bt.Root().LeftChild(), false);

    lasd::BinaryTreeVec<int> bt1(std::move(bt));

    Traverse(loctestnum, loctesterr, bt, true, &TraversePrint<int>);
    Traverse(loctestnum, loctesterr, bt1, true, &TraversePrint<int>);

    EqualBT(loctestnum, loctesterr, bt, bt1);
    Empty(loctestnum, loctesterr, bt, false);
    Exists(loctestnum, loctesterr, bt, true, 3);

    lasd::BinaryTreeLnk<int> bt2(bt1);

    EqualBT(loctestnum, loctesterr, bt1, bt2);
    
    GetElement(loctestnum, loctesterr, bt2.Root().LeftChild().LeftChild(), false, 0);

    TraverseBreadth(loctestnum, loctesterr, bt2, true, &TraversePrint<int>);

    Fold(loctestnum, loctesterr, bt2, true, &FoldAdd<int>, 0, 21);
    FoldPreOrder(loctestnum, loctesterr, bt2, true, &FoldMultiply<int>, 1, 576);
    FoldInOrder(loctestnum, loctesterr, bt2, false, &FoldAdd<int>, 0, 1);
    FoldBreadth(loctestnum, loctesterr, bt2, true, &FoldMultiply<int>, 2, 1152);

  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of BinaryTree<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}
void testBinaryTreeInt(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of BinaryTree<int> Test:" << endl;
  try {
    lasd::Vector<int> vec(4);
    SetAt(loctestnum, loctesterr, vec, true, 0, 3);
    SetAt(loctestnum, loctesterr, vec, true, 1, 4);
    SetAt(loctestnum, loctesterr, vec, true, 2, 6);
    SetAt(loctestnum, loctesterr, vec, true, 3, 8);

    lasd::BinaryTreeVec<int> btvec(vec);
    cout << endl << "Begin of BinaryTreeVec<int> Test:" << endl;
    testBinaryTreeInt(btvec, loctestnum, loctesterr);
    lasd::BinaryTreeLnk<int> btlnk(vec);
    cout << endl << "Begin of BinaryTreeLnk<int> Test:" << endl;
    testBinaryTreeInt(btlnk, loctestnum, loctesterr);
    cout << "\n";

    lasd::Vector<int> v(btvec);
    lasd::List<int> l(v);

    lasd::BinaryTreeVec<int> btvec1(v);
    lasd::BinaryTreeLnk<int> btlnk1(l);

    TraverseInOrder(loctestnum, loctesterr, btvec1, true, &TraversePrint<int>);

    EqualBT(loctestnum, loctesterr, btvec, btvec1);
    EqualBT(loctestnum, loctesterr, btlnk, btlnk1);

    lasd::BinaryTreeVec<int> btvec2(std::move(btvec));

    Empty(loctestnum, loctesterr, btvec, true);
    Traverse(loctestnum, loctesterr, btvec, true, &TraversePrint<int>);
    Traverse(loctestnum, loctesterr, btvec2, true, &TraversePrint<int>);

    NonEqualBT(loctestnum, loctesterr, btvec, btvec2);

    Map(loctestnum, loctesterr, btvec, true, &MapDouble<int>);
  } 
  catch (...) {
    loctesterr++; loctestnum++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of BinaryTree<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */

void testBinaryTreeDouble(lasd::MutableBinaryTree<double> & bt, uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  try {
    lasd::BTPostOrderMutableIterator<double> it(bt);
    Terminated(loctestnum, loctesterr, it, false);

    ++it;

    Traverse(loctestnum, loctesterr, bt, true, &TraversePrint<double>);

    GetItrValue(loctestnum, loctesterr, it, false, 3.0);
    SetItrValue(loctestnum, loctesterr, it, true, 4.0);

    Traverse(loctestnum, loctesterr, bt, true, &TraversePrint<double>);

    lasd::BTInOrderMutableIterator<double> it1(bt);

    GetItrValue(loctestnum, loctesterr, it1, false, 1.2);
    SetItrValue(loctestnum, loctesterr, it1, true, 3.0);

    ++it1;
    Traverse(loctestnum, loctesterr, bt, true, &TraversePrint<double>);
    it1.Reset();

    SetItrValue(loctestnum, loctesterr, it1, true, 1.2);

    Traverse(loctestnum, loctesterr, bt, true, &TraversePrint<double>);
    
    ++it1;
    GetItrValue(loctestnum, loctesterr, it1, true, 4.0);
    GetItrValue(loctestnum, loctesterr, it1, false, 0.8);
    ++it1;
    ++it1;
    ++it1;
    
    GetItrValue(loctestnum, loctesterr, it1, false, 3.0);

    Terminated(loctestnum, loctesterr, it1, true);

    lasd::BTBreadthMutableIterator<double> it2(bt);

    GetItrValue(loctestnum, loctesterr, it2, true, 1.2);
    SetItrValue(loctestnum, loctesterr, it2, true, 2.1);

    Map(loctestnum, loctesterr, bt, true, &MapDouble<double>);

    GetItrValue(loctestnum, loctesterr, it2, true, 4.2);
    
    Traverse(loctestnum, loctesterr, bt, true, &TraversePrint<double>);

    lasd::BTInOrderMutableIterator<double> it3(it1);

    Terminated(loctestnum, loctesterr, it3, true);

    GetItrValue(loctestnum, loctesterr, it3, false, 0.1);
    it3.Reset();

    lasd::BTInOrderIterator<double> it4(it3);

    Traverse(loctestnum, loctesterr, bt, true, &TraversePrint<double>);

    GetItrValue(loctestnum, loctesterr, it4, true, 2.4);
    ++it4;
    GetItrValue(loctestnum, loctesterr, it4, true, 8.0);
    it4.Reset(); 

    TraverseInOrder(loctestnum, loctesterr, bt, true, &TraversePrint<double>);

    GetItrValue(loctestnum, loctesterr, it4, true, *it4);
    GetItrValue(loctestnum, loctesterr, it4, false, *it4-1);
    GetItrValue(loctestnum, loctesterr, ++it4, false, *it4+1);

    SetElement(loctestnum, loctesterr, bt.Root().LeftChild().LeftChild(), true, 0.3);
    SetElement(loctestnum, loctesterr, bt.Root().RightChild(), true, 0.6);

    lasd::BinaryTreeVec<double> bt1(bt);

    EqualBT(loctestnum, loctesterr, bt, bt1);

    Traverse(loctestnum, loctesterr, bt, true, &TraversePrint<double>);
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of BinaryTree<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}
void testBinaryTreeDouble(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of BinaryTree<double> Test:" << endl;
  try {
    lasd::List<double> lst;
    InsertAtFront(loctestnum, loctesterr, lst, true, 0.3);
    InsertAtBack(loctestnum, loctesterr, lst, true, 3.0);
    InsertAtFront(loctestnum, loctesterr, lst, true, 1.2);
    InsertAtBack(loctestnum, loctesterr, lst, true, 2.1);

    lasd::BinaryTreeVec<double> btvec(lst);
    cout << endl << "Begin of BinaryTreeVec<double> Test:" << endl;
    testBinaryTreeDouble(btvec, loctestnum, loctesterr);
    lasd::BinaryTreeLnk<double> btlnk(lst);
    cout << endl << "Begin of BinaryTreeLnk<double> Test:" << endl;
    testBinaryTreeDouble(btlnk, loctestnum, loctesterr);
    cout << "\n";

    Root(loctestnum, loctesterr, btvec, true, 4.2);
    Root(loctestnum, loctesterr, btlnk, true, 4.2);

    EqualBT(loctestnum, loctesterr, btvec, btlnk);

    GetElement(loctestnum, loctesterr, btvec.Root().LeftChild(), false, 4.2);

    EqualBT(loctestnum, loctesterr, btvec, btlnk);
  } 
  catch (...) {
    loctesterr++; loctestnum++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of BinaryTree<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */

void testBinaryTreeString(lasd::BinaryTree<string> & bt, uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  try {
    Traverse(loctestnum, loctesterr, bt, true, &TraversePrint<string>);

    Root(loctestnum, loctesterr, bt, true, string("A"));
    GetElement(loctestnum, loctesterr, bt.Root(), true, string("A"));

    Traverse(loctestnum, loctesterr, bt, true, &TraversePrint<string>);

    IsLeaf<string>(loctestnum, loctesterr, bt.Root().RightChild(), true);
    IsLeaf<string>(loctestnum, loctesterr, bt.Root().LeftChild(), false);
    HasLeftChild<string>(loctestnum, loctesterr, bt.Root().LeftChild(), true);
    HasRightChild<string>(loctestnum, loctesterr, bt.Root().LeftChild(), false);

    lasd::BinaryTreeVec<string> bt1(std::move(bt));

    Traverse(loctestnum, loctesterr, bt, true, &TraversePrint<string>);
    Traverse(loctestnum, loctesterr, bt1, true, &TraversePrint<string>);

    EqualBT(loctestnum, loctesterr, bt, bt1);
    Empty(loctestnum, loctesterr, bt, false);
    Exists(loctestnum, loctesterr, bt, true, string("D"));

    lasd::BinaryTreeLnk<string> bt2(bt1);

    EqualBT(loctestnum, loctesterr, bt1, bt2);
    
    GetElement(loctestnum, loctesterr, bt2.Root().LeftChild().LeftChild(), false, string("A"));

    Fold(loctestnum, loctesterr, bt2, true, &FoldStringConcatenate, string("?"), string("?ABCD"));
    FoldPreOrder(loctestnum, loctesterr, bt2, true, &FoldStringConcatenate, string("?"), string("?ABDC"));
    FoldInOrder(loctestnum, loctesterr, bt2, false, &FoldStringConcatenate, string("?"), string("?ABDC"));
    FoldBreadth(loctestnum, loctesterr, bt2, true, &FoldStringConcatenate, string("?"), string("?ABCD"));

    SetElement(loctestnum, loctesterr, bt2.Root().LeftChild().LeftChild(), true, string("B"));
    SetElement(loctestnum, loctesterr, bt2.Root().RightChild(), true, string("C"));
    SetElement(loctestnum, loctesterr, bt2.Root().LeftChild(), true, string("D"));

    TraverseBreadth(loctestnum, loctesterr, bt2, true, &TraversePrint<string>);

  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of BinaryTree<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}
void testBinaryTreeString(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of BinaryTree<string> Test:" << endl;
  try {
    lasd::Vector<string> vec(4);
    SetAt(loctestnum, loctesterr, vec, true, 0, string("A"));
    SetAt(loctestnum, loctesterr, vec, true, 1, string("B"));
    SetAt(loctestnum, loctesterr, vec, true, 2, string("C"));
    SetAt(loctestnum, loctesterr, vec, true, 3, string("D"));

    lasd::BinaryTreeVec<string> btvec(vec);
    cout << endl << "Begin of BinaryTreeVec<string> Test:" << endl;
    testBinaryTreeString(btvec, loctestnum, loctesterr);
    lasd::BinaryTreeLnk<string> btlnk(vec);
    cout << endl << "Begin of BinaryTreeLnk<string> Test:" << endl;
    testBinaryTreeString(btlnk, loctestnum, loctesterr);
    cout << "\n";

    
    lasd::Vector<string> v(btvec);
    SetAt(loctestnum, loctesterr, v, true, 0, string("D"));
    SetAt(loctestnum, loctesterr, v, true, 1, string("D"));
    SetAt(loctestnum, loctesterr, v, true, 2, string("D"));
    SetAt(loctestnum, loctesterr, v, true, 3, string("D"));

    lasd::BinaryTreeVec<string> btvec1(v);
    Root<string>(loctestnum, loctesterr, btvec1, true, string("D"));

    HasRightChild<string>(loctestnum, loctesterr, btvec1.Root(), true);
    HasLeftChild<string>(loctestnum, loctesterr, btvec1.Root(), true);

    NonEqualBT(loctestnum, loctesterr, btvec, btvec1);
  } 
  catch (...) {
    loctesterr++; loctestnum++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of BinaryTree<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */

void testBSTInt(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of BST<int> Test:" << endl;
  try {
    lasd::BST<int> bst;
    Empty(loctestnum, loctesterr, bst, true);
    Size(loctestnum, loctesterr, bst, true, 0);

    InsertM(loctestnum, loctesterr, bst, true, 4);
    InsertM(loctestnum, loctesterr, bst, true, 5);
    InsertM(loctestnum, loctesterr, bst, true, 6);
    InsertM(loctestnum, loctesterr, bst, true, 2);

    Size(loctestnum, loctesterr, bst, true, 4);

    Remove(loctestnum, loctesterr, bst, false, 3);
    Remove(loctestnum, loctesterr, bst, true, 4);
    Remove(loctestnum, loctesterr, bst, true, 6);
    Remove(loctestnum, loctesterr, bst, true, 2);

    Empty(loctestnum, loctesterr, bst, false);

    lasd::Vector<int> v(4);
    SetAt(loctestnum, loctesterr, v, true, 0, 4);
    SetAt(loctestnum, loctesterr, v, true, 1, 5);
    SetAt(loctestnum, loctesterr, v, true, 2, 1);
    SetAt(loctestnum, loctesterr, v, true, 3, 2);

    InsertAllC(loctestnum, loctesterr, bst, false, v);

    Empty(loctestnum, loctesterr, bst, false);
    RemoveAll(loctestnum, loctesterr, bst, true, v);
    Empty(loctestnum, loctesterr, bst, true);

    lasd::Vector<int> v1(9);

    SetAt(loctestnum, loctesterr, v1, true, 0, 0);
    SetAt(loctestnum, loctesterr, v1, true, 1, 5);
    SetAt(loctestnum, loctesterr, v1, true, 2, 1);
    SetAt(loctestnum, loctesterr, v1, true, 3, 2);
    SetAt(loctestnum, loctesterr, v1, true, 4, 3);
    SetAt(loctestnum, loctesterr, v1, true, 5, 11);
    SetAt(loctestnum, loctesterr, v1, true, 6, 10);
    SetAt(loctestnum, loctesterr, v1, true, 7, 28);
    SetAt(loctestnum, loctesterr, v1, true, 8, 29);

    InsertAllM(loctestnum, loctesterr, bst, true, std::move(v1));
        
    TraverseInOrder(loctestnum, loctesterr, bst, true, &TraversePrint<int>);

    for(int i = 1; i < 4; i++) {
      v[i] = i*100;
    }

    InsertSomeC(loctestnum, loctesterr, bst, true, v);
    Traverse(loctestnum, loctesterr, bst, true, &TraversePrint<int>);
    RemoveSome(loctestnum, loctesterr, bst, true, v);
    TraverseInOrder(loctestnum, loctesterr, bst, true, &TraversePrint<int>);
    
    lasd::BST<int> bst1(bst);

    EqualBST(loctestnum, loctesterr, bst, bst1);

    Min(loctestnum, loctesterr, bst, true, 0);
    Max(loctestnum, loctesterr, bst, true, 29);

    lasd::BST<int> bst2(std::move(bst1));

    RemoveMin(loctestnum, loctesterr, bst2, true);
    MinNRemove(loctestnum, loctesterr, bst2, true, 1);
    RemoveMax(loctestnum, loctesterr, bst2, true);
    MaxNRemove(loctestnum, loctesterr, bst2, true, 28);

    TraverseInOrder(loctestnum, loctesterr, bst2, true, &TraversePrint<int>);

    Predecessor(loctestnum, loctesterr, bst2, true, 5, 3);
    Successor(loctestnum, loctesterr, bst2, true, 5, 10);

    lasd::BST<int> bst3(bst2);

    EqualBST(loctestnum, loctesterr, bst2, bst3);
    NonEqualBST(loctestnum, loctesterr, bst, bst2);

    RemoveSuccessor(loctestnum, loctesterr, bst3, true, 5);
    RemovePredecessor(loctestnum, loctesterr, bst3, true, 5);

    TraverseInOrder(loctestnum, loctesterr, bst3, true, &TraversePrint<int>);

    FoldPreOrder(loctestnum, loctesterr, bst3, true, &FoldAdd<int>, 0, 18);
    FoldInOrder(loctestnum, loctesterr, bst3, true, &FoldAdd<int>, 0, 18);

    PredecessorNRemove(loctestnum, loctesterr, bst3, true, 10, 5);
    SuccessorNRemove(loctestnum, loctesterr, bst3, true, 10, 11);

    Exists(loctestnum, loctesterr, bst3, true, 2);

    PredecessorNRemove(loctestnum, loctesterr, bst3, true, 5, 2);

    Empty(loctestnum, loctesterr, bst3, true);

  }
  catch (...) {
    loctesterr++; loctestnum++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of BST<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */

void testBSTDouble(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of BST<double> Test:" << endl;
  try {
    
    lasd::List<double> lst;
    InsertAtFront(loctestnum, loctesterr, lst, true, 0.33);
    InsertAtBack(loctestnum, loctesterr, lst, true, 35.0);
    InsertAtFront(loctestnum, loctesterr, lst, true, 21.2);
    InsertAtBack(loctestnum, loctesterr, lst, true, 12.1);


    lasd::BinaryTreeLnk<double> btlnk(lst);
    lasd::BST<double> bst(btlnk);

    TraverseInOrder(loctestnum, loctesterr, bst, true, &TraversePrint<double>);

    NonEqualBT(loctestnum, loctesterr, btlnk, bst);

    Empty(loctestnum, loctesterr, bst, false);
    Size(loctestnum, loctesterr, bst, false, 0);

    InsertM(loctestnum, loctesterr, bst, true, 4.4);
    InsertM(loctestnum, loctesterr, bst, true, 5.5);
    InsertM(loctestnum, loctesterr, bst, true, 6.6);
    InsertM(loctestnum, loctesterr, bst, true, 2.2);

    Remove(loctestnum, loctesterr, bst, false, 3.3);

    Root(loctestnum, loctesterr, bst, true, 21.2);
    GetElement(loctestnum, loctesterr, bst.Root(), true, 21.2);
    GetElement(loctestnum, loctesterr, bst.Root().RightChild(), true, 35.0);
    GetElement(loctestnum, loctesterr, bst.Root().LeftChild(), true, 0.33);
    GetElement(loctestnum, loctesterr, bst.Root().LeftChild().RightChild(), true, 12.1);

    IsLeaf<double>(loctestnum, loctesterr, bst.Root().RightChild(), true);

    lasd::BST<double> bst1(std::move(bst));

    EqualBST(loctestnum, loctesterr, bst1, bst1);

    HasLeftChild<double>(loctestnum, loctesterr, bst1.Root(), true);
    HasRightChild<double>(loctestnum, loctesterr, bst1.Root(), true);

  }
  catch (...) {
    loctesterr++; loctestnum++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of BST<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */

void testBSTString(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of BST<string> Test:" << endl;
  try {
    lasd::BST<string> bst;
    Empty(loctestnum, loctesterr, bst, true);
    Size(loctestnum, loctesterr, bst, true, 0);
    
    lasd::Vector<string> v(4);
    SetAt(loctestnum, loctesterr, v, true, 0, string("A"));
    SetAt(loctestnum, loctesterr, v, true, 1, string("B"));
    SetAt(loctestnum, loctesterr, v, true, 2, string("C"));
    SetAt(loctestnum, loctesterr, v, true, 3, string("D"));

    lasd::BinaryTreeVec<string> btvec(v);

    lasd::BST<string> bst1(btvec);

    NonEqualBST(loctestnum, loctesterr, bst, bst1);

    InsertM(loctestnum, loctesterr, bst1, true, string("E"));
    InsertM(loctestnum, loctesterr, bst1, true, string("F"));
    InsertM(loctestnum, loctesterr, bst1, true, string("G"));
    InsertM(loctestnum, loctesterr, bst1, true, string("H"));

    Remove(loctestnum, loctesterr, bst1, false, string("I"));
    Remove(loctestnum, loctesterr, bst1, true, string("E"));

    lasd::BTPostOrderIterator<string> it(bst1);

    GetItrValue(loctestnum, loctesterr, it, true, string("H"));
    ++it;
    ++it;
    GetItrValue(loctestnum, loctesterr, it, true, string("F"));
    ++it;
    ++it;
    GetItrValue(loctestnum, loctesterr, it, true, string("C"));
    ++it;
    ++it;
    GetItrValue(loctestnum, loctesterr, it, true, string("A"));
    ++it;

    Terminated(loctestnum, loctesterr, it, true);

    TraverseInOrder(loctestnum, loctesterr, bst1, true, &TraversePrint<string>);
  }
  catch (...) {
    loctesterr++; loctestnum++;
    cout << endl << "Unmanaged error! " << endl;
  }
  cout << "End of BST<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */

void fulltestVector(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  testVectorInt(loctestnum, loctesterr);
  testVectorDouble(loctestnum, loctesterr);
  testVectorString(loctestnum, loctesterr);
  testnum += loctestnum; 
  testerr += loctesterr;
  cout << "Vector (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}

/* ************************************************************************** */

void fulltestList(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  testListInt(loctestnum, loctesterr);
  testListDouble(loctestnum, loctesterr);
  testListString(loctestnum, loctesterr);
  testnum += loctestnum;
  testerr += loctesterr;
  cout << "List (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}

/* ************************************************************************** */

void fulltestStack(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  testStackInt(loctestnum, loctesterr);
  testStackDouble(loctestnum, loctesterr);
  testStackString(loctestnum, loctesterr);
  testnum += loctestnum;
  testerr += loctesterr;
  cout << "Stack (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}


/* ************************************************************************** */

void fulltestQueue(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  testQueueInt(loctestnum, loctesterr);
  testQueueDouble(loctestnum, loctesterr);
  testQueueString(loctestnum, loctesterr);
  testnum += loctestnum;
  testerr += loctesterr;
  cout << "Queue (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}

/* ************************************************************************** */

void fulltestBinaryTree(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  testBinaryTreeInt(loctestnum, loctesterr);
  testBinaryTreeDouble(loctestnum, loctesterr);
  testBinaryTreeString(loctestnum, loctesterr);
  testnum += loctestnum;
  testerr += loctesterr;
  cout << "BinaryTree (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}

/* ************************************************************************** */

void fulltestBST(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  testBSTInt(loctestnum, loctesterr);
  testBSTDouble(loctestnum, loctesterr);
  testBSTString(loctestnum, loctesterr);
  testnum += loctestnum;
  testerr += loctesterr;
  cout << "BST (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}

/* ************************************************************************** */

void testFullExercise(uint & testnum, uint & testerr) {
  fulltestVector(testnum, testerr);
  fulltestList(testnum, testerr);
  fulltestStack(testnum, testerr);
  fulltestQueue(testnum, testerr);
  fulltestBinaryTree(testnum, testerr);
  fulltestBST(testnum, testerr);
}

/* ************************************************************************** */