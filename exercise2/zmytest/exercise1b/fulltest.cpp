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

template <typename Stk>
void myTestStackInt(Stk & stk, uint & testnum, uint & testerr) {
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
void myTestStackInt(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  lasd::StackLst<int> s;
  cout << endl << "Begin of StackLst<Int> Test:" << endl;
  myTestStackInt(s, loctestnum, loctesterr);
  lasd::StackVec<int> s1;
  cout << endl << "Begin of StackVec<Int> Test:" << endl;
  myTestStackInt(s1, loctestnum, loctesterr);
  testerr += loctesterr;
  testnum += loctestnum;
}

/* ************************************************************************** */

template <typename Stk>
void myTestStackDouble(Stk & stk, uint & testnum, uint & testerr) {
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
void myTestStackDouble(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  lasd::StackVec<double> s;
  cout << endl << "Begin of StackVec<double> Test:" << endl;
  myTestStackDouble(s, loctestnum, loctesterr);
  lasd::StackLst<double> s1;
  cout << endl << "Begin of StackLst<double> Test:" << endl;
  myTestStackDouble(s1, loctestnum, loctesterr);
  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */

template <typename Stk>
void myTestStackString(Stk & stk, uint & testnum, uint & testerr) {
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
void myTestStackString(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  lasd::StackVec<string> s;
  cout << endl << "Begin of StackVec<string> Test:" << endl;
  myTestStackString(s, loctestnum, loctesterr);
  lasd::StackLst<string> s1;
  cout << endl << "Begin of StackLst<string> Test:" << endl;
  myTestStackString(s1, loctestnum, loctesterr);
  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */

template <typename Queue>
void myTestQueueInt(Queue & q, uint & testnum, uint & testerr) {
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
void myTestQueueInt(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  lasd::QueueVec<int> q;
  cout << endl << "Begin of QueueVec<int> Test:" << endl;
  myTestQueueInt(q, loctestnum, loctesterr);
  lasd::QueueLst<int> q1;
  cout << endl << "Begin of QueueLst<int> Test:" << endl;
  myTestQueueInt(q1, loctestnum, loctesterr);
  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */

template <typename Queue>
void myTestQueueDouble(Queue & q, uint & testnum, uint & testerr) {
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
void myTestQueueDouble(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  lasd::QueueVec<double> q;
  cout << endl << "Begin of QueueVec<double> Test:" << endl;
  myTestQueueDouble(q, loctestnum, loctesterr);
  lasd::QueueLst<double> q1;
  cout << endl << "Begin of QueueLst<double> Test:" << endl;
  myTestQueueDouble(q1, loctestnum, loctesterr);
  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */

template <typename Queue>
void myTestQueueString(Queue & q, uint & testnum, uint & testerr) {
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
void myTestQueueString(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  lasd::QueueVec<string> q;
  cout << endl << "Begin of QueueVec<string> Test:" << endl;
  myTestQueueString(q, loctestnum, loctesterr);
  lasd::QueueLst<string> q1;
  cout << endl << "Begin of QueueLst<string> Test:" << endl;
  myTestQueueString(q1, loctestnum, loctesterr);
  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */

void myTestStack(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  myTestStackInt(loctestnum, loctesterr);
  myTestStackDouble(loctestnum, loctesterr);
  myTestStackString(loctestnum, loctesterr);
  testnum += loctestnum;
  testerr += loctesterr;
  cout << "Stack (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}

/* ************************************************************************** */

void myTestQueue(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  myTestQueueInt(loctestnum, loctesterr);
  myTestQueueDouble(loctestnum, loctesterr);
  myTestQueueString(loctestnum, loctesterr);
  testnum += loctestnum;
  testerr += loctesterr;
  cout << "Queue (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}

/* ************************************************************************** */

void myTestFullExercise1B(uint & testnum, uint & testerr) {
  myTestStack(testnum, testerr);
  myTestQueue(testnum, testerr);
}

/* ************************************************************************** */

}
