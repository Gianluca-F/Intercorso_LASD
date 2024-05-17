
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

// #include "../../zlasdtest/stack/stack.hpp"
// #include "../../stack/vec/stackvec.hpp"
// #include "../../stack/lst/stacklst.hpp"

// #include "../../zlasdtest/queue/queue.hpp"
// #include "../../queue/vec/queuevec.hpp"
// #include "../../queue/lst/queuelst.hpp"

#include "../../zlasdtest/binarytree/binarytree.hpp"
#include "../../zlasdtest/iterator/iterator.hpp"

#include "../../binarytree/binarytree.hpp"
#include "../../binarytree/lnk/binarytreelnk.hpp"
#include "../../binarytree/vec/binarytreevec.hpp"

#include "../../zlasdtest/bst/bst.hpp"

/* ************************************************************************** */

#include <random>
#include <cstring>

/* ************************************************************************** */

#define NUM_BST 20 // Number of elements in the binary search tree
#define MAX_BST 100 // Maximum value of the elements in the binary search tree 
                    // (MAX_BST MUST BE >> NUM_BST)

/* ************************************************************************** */

using namespace std;

/* ************************************************************************** */

namespace mytest {

/* ************************************************************************** */

void myTestBSTint(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of BST<int> Test:" << endl;

  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<int> dis(-1*MAX_BST, MAX_BST);

  try {
    // empty trees
    cout << "\n~~~ BST empty tests ~~~\n" << endl;
    lasd::BST<int> bst;
    lasd::BinaryTreeLnk<int> btl_empty;
    lasd::BinaryTreeVec<int> btv_empty;

    Empty(loctestnum, loctesterr, bst, true);
    Size(loctestnum, loctesterr, bst, true, 0);
    Exists<int>(loctestnum, loctesterr, bst, false, 0);

    Min<int>(loctestnum, loctesterr, bst, false, 0);
    RemoveMin<int>(loctestnum, loctesterr, bst, false);
    MinNRemove<int>(loctestnum, loctesterr, bst, false, 0);
    Max<int>(loctestnum, loctesterr, bst, false, 0);
    RemoveMax<int>(loctestnum, loctesterr, bst, false);
    MaxNRemove<int>(loctestnum, loctesterr, bst, false, 0);

    Predecessor<int>(loctestnum, loctesterr, bst, false, 1, 0);
    RemovePredecessor<int>(loctestnum, loctesterr, bst, false, 1);
    PredecessorNRemove<int>(loctestnum, loctesterr, bst, false, 1, 0);
    Successor<int>(loctestnum, loctesterr, bst, false, 0, 1);
    RemoveSuccessor<int>(loctestnum, loctesterr, bst, false, 0);
    SuccessorNRemove<int>(loctestnum, loctesterr, bst, false, 0, 1);

    Root<int>(loctestnum, loctesterr, bst, false, 0);

    EqualBT<int>(loctestnum, loctesterr, bst, btl_empty);
    EqualBT<int>(loctestnum, loctesterr, bst, btl_empty);
    EqualBT<int>(loctestnum, loctesterr, bst, btv_empty);
    EqualBST<int>(loctestnum, loctesterr, bst, bst);

    bst.Clear();

    /* ************************************************************* */

    // trees with one element
    cout << "\n~~~ BST with one element tests ~~~\n" << endl;
    lasd::Vector<int> v(1); v[0] = 0;
    lasd::BinaryTreeVec<int> btv(v);
    lasd::BinaryTreeLnk<int> btl(v);
    InsertC<int>(loctestnum, loctesterr, bst, true, 0);

    Empty(loctestnum, loctesterr, bst, false);
    Size(loctestnum, loctesterr, bst, true, 1);

    Exists<int>(loctestnum, loctesterr, bst, true, 0);
    Exists<int>(loctestnum, loctesterr, bst, false, 1);

    Min<int>(loctestnum, loctesterr, bst, true, 0);
    Max<int>(loctestnum, loctesterr, bst, true, 0);

    Root<int>(loctestnum, loctesterr, bst, true, 0);

    EqualBT<int>(loctestnum, loctesterr, btv, bst);
    EqualBT<int>(loctestnum, loctesterr, bst, btl);
    EqualBST<int>(loctestnum, loctesterr, bst, bst);

    RemoveMin<int>(loctestnum, loctesterr, bst, true);
    Size(loctestnum, loctesterr, bst, true, 0);

    InsertC<int>(loctestnum, loctesterr, bst, true, 1);
    MinNRemove<int>(loctestnum, loctesterr, bst, true, 1);
    Size(loctestnum, loctesterr, bst, true, 0);

    InsertC<int>(loctestnum, loctesterr, bst, true, 1);
    MaxNRemove<int>(loctestnum, loctesterr, bst, true, 1);
    Size(loctestnum, loctesterr, bst, true, 0);

    InsertC<int>(loctestnum, loctesterr, bst, true, -1);
    Predecessor<int>(loctestnum, loctesterr, bst, true, 0, -1);
    Successor(loctestnum, loctesterr, bst, true, -2, -1);

    Predecessor<int>(loctestnum, loctesterr, bst, false, -1, -2);
    Successor<int>(loctestnum, loctesterr, bst, false, -1, 0);

    NonEqualBT<int>(loctestnum, loctesterr, bst, btv);
    NonEqualBT<int>(loctestnum, loctesterr, bst, btl);

    bst.Clear();
    Empty(loctestnum, loctesterr, bst, true);
    Size(loctestnum, loctesterr, bst, true, 0);

    /* ************************************************************* */

    // trees with many elements
    cout << "\n~~~ BST with many elements tests ~~~\n" << endl;
    int min = MAX_BST, max = -1*MAX_BST;

    lasd::Vector<int> v2(NUM_BST);
    for (uint i = 0; i < NUM_BST; i++) {
      int val = dis(gen);
      while(v2.Exists(val)) { val = dis(gen); } // No duplicates
      v2[i] = val; 
      if(val < min) { min = val; }
      if(val > max) { max = val; }
    }
    lasd::List<int> l(v2);
    lasd::BinaryTreeVec<int> btv2(v2);
    lasd::BinaryTreeLnk<int> btl2(l);
    InsertAllC(loctestnum, loctesterr, bst, true, v2);

    Empty(loctestnum, loctesterr, bst, false);
    Size(loctestnum, loctesterr, bst, true, NUM_BST);

    for(uint i = 0; i < NUM_BST; i++) {
      Exists(loctestnum, loctesterr, bst, true, v2[i]);
    }

    Root(loctestnum, loctesterr, bst, true, v2[0]);
    Min(loctestnum, loctesterr, bst, true, min);
    Max(loctestnum, loctesterr, bst, true, max);
    EqualBST(loctestnum, loctesterr, bst, bst);

    TraverseInOrder(loctestnum, loctesterr, bst, true, &TraversePrint<int>);

    lasd::BST<int> bst2(bst);
    EqualBST(loctestnum, loctesterr, bst, bst2);

    MinNRemove(loctestnum, loctesterr, bst2, true, min);
    MaxNRemove(loctestnum, loctesterr, bst2, true, max);
    Size(loctestnum, loctesterr, bst2, true, NUM_BST-2);
    NonEqualBST(loctestnum, loctesterr, bst, bst2);

    RemoveMin(loctestnum, loctesterr, bst2, true);
    Size(loctestnum, loctesterr, bst2, true, NUM_BST-3);

    RemoveMax(loctestnum, loctesterr, bst2, true);
    Size(loctestnum, loctesterr, bst2, true, NUM_BST-4);

    TraverseInOrder(loctestnum, loctesterr, bst2, true, &TraversePrint<int>);

    lasd::BST<int> bst3(move(bst2));
    bst2.Clear();
    Size(loctestnum, loctesterr, bst3, true, NUM_BST-4);

    RemoveAll(loctestnum, loctesterr, bst3, false, l);
    Size(loctestnum, loctesterr, bst3, true, 0);

    RemoveSome(loctestnum, loctesterr, bst3, false, v2);
    Size(loctestnum, loctesterr, bst3, true, 0);

    InsertAllM(loctestnum, loctesterr, bst3, true, move(l));
    Size(loctestnum, loctesterr, bst3, true, NUM_BST);
    EqualBST(loctestnum, loctesterr, bst, bst3);

    bst3.Clear();

    v2[1] = MAX_BST+1;
    InsertAllM(loctestnum, loctesterr, bst3, true, move(v2));
    Min(loctestnum, loctesterr, bst3, true, min);
    Max(loctestnum, loctesterr, bst3, true, MAX_BST+1);
    Size(loctestnum, loctesterr, bst3, true, NUM_BST);

    TraverseInOrder(loctestnum, loctesterr, bst3, true, &TraversePrint<int>);
    NonEqualBST(loctestnum, loctesterr, bst, bst3);

    bst2 = move(bst3);
    Size(loctestnum, loctesterr, bst2, true, NUM_BST);
    Exists(loctestnum, loctesterr, bst2, true, MAX_BST+1);
    NonEqualBST(loctestnum, loctesterr, bst, bst2);
    TraverseInOrder(loctestnum, loctesterr, bst2, true, &TraversePrint<int>);

    bst2 = bst;
    Size(loctestnum, loctesterr, bst2, true, NUM_BST);
    EqualBST(loctestnum, loctesterr, bst, bst2);
    TraverseInOrder(loctestnum, loctesterr, bst2, true, &TraversePrint<int>);

    /* ************************************************************* */


  } catch (exception & exc) {
    cout << "Caught exception: " << exc.what() << endl;
    loctestnum++;
    loctesterr++;
  }

  testnum += loctestnum;
  testerr += loctesterr;
  cout << endl << "BST<int> (Error/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}

/* ************************************************************************** */

void myTestBSTdouble(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of BST<double> Test:" << endl;
  try {
    lasd::BST<double> bst;

  } catch (exception & exc) {
    cout << "Caught exception: " << exc.what() << endl;
    loctestnum++;
    loctesterr++;
  }

  testnum += loctestnum;
  testerr += loctesterr;
  cout << endl << "BST<double> (Error/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}

/* ************************************************************************** */

void myTestBSTstring(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of BST<string> Test:" << endl;
  try {
    lasd::BST<string> bst;

  } catch (exception & exc) {
    cout << "Caught exception: " << exc.what() << endl;
    loctestnum++;
    loctesterr++;
  }

  testnum += loctestnum;
  testerr += loctesterr;
  cout << endl << "BST<string> (Error/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}

/* ************************************************************************** */

void myTestFullExercise2B(uint & testnum, uint & testerr) {
  cout << endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  myTestBSTint(testnum, testerr);
  // myTestBSTdouble(testnum, testerr);
  // myTestBSTstring(testnum, testerr);
}

/* ************************************************************************** */

}