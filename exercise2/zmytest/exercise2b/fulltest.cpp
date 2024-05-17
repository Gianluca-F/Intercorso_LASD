
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

/* ************************************************************************** */

using namespace std;

/* ************************************************************************** */

namespace mytest {

/* ************************************************************************** */

void myTestBSTint(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of BST<int> Test:" << endl;
  try {
    lasd::BST<int> bst_empty;
    lasd::BinaryTreeLnk<int> btl_empty;
    lasd::BinaryTreeVec<int> btv_empty;

    Empty(loctestnum, loctesterr, bst_empty, true);
    Size(loctestnum, loctesterr, bst_empty, true, 0);

    EqualBT(loctestnum, loctesterr, bst_empty, btl_empty);
    EqualBT(loctestnum, loctesterr, bst_empty, btl_empty);
    EqualBT(loctestnum, loctesterr, bst_empty, btv_empty);
    EqualBST(loctestnum, loctesterr, bst_empty, bst_empty);


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