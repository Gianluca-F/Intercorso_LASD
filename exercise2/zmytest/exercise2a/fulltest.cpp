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
#include "../../zlasdtest/iterator/iterator.hpp"

#include "../../binarytree/binarytree.hpp"
#include "../../binarytree/lnk/binarytreelnk.hpp"
#include "../../binarytree/vec/binarytreevec.hpp"

/* ************************************************************************** */

#include <random>
#include <cstring>

/* ************************************************************************** */

#define NUM 200
#define MAX 50      

/* ************************************************************************** */

using namespace std;

/* ************************************************************************** */

namespace mytest {

/* ************************************************************************** */

void myTestBTint(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of BinaryTree<int> Test:" << endl;

  try {
    cout << endl << "~ BinaryTreeVec<int> Test:" << endl;
   
    // BinaryTreeVec empty
    lasd::BinaryTreeVec<int> btv_empty;
    Root<int>(loctestnum, loctesterr, btv_empty, false, 10);

    // BinaryTreeVec with one element
    lasd::Vector<int> v1(1);  v1[0] = -5;
    lasd::BinaryTreeVec<int> btv_one(v1);

    GetElement<int>(loctestnum, loctesterr, btv_one.Root(), true, -5);
    HasLeftChild<int>(loctestnum, loctesterr, btv_one.Root(), false);
    HasRightChild<int>(loctestnum, loctesterr, btv_one.Root(), false);
    IsLeaf<int>(loctestnum, loctesterr, btv_one.Root(), true);

    // BinaryTreeVec with many elements
    lasd::Vector<int> v2(NUM);
    for (uint i = 0; i < NUM; i++) {
      v2[i] = i*i;
    }
    lasd::BinaryTreeVec<int> btv_many(v2);





    cout << endl << "~ BinaryTreeLnk<int> Test:" << endl;

    // BinaryTreeLnk empty
    lasd::BinaryTreeLnk<int> btl_empty;
    Root<int>(loctestnum, loctesterr, btl_empty, false, 0);

    // BinaryTreeLnk with one element
    lasd::List<int> l1;  l1.InsertAtBack(0);
    lasd::BinaryTreeLnk<int> btl_one(l1);

    GetElement<int>(loctestnum, loctesterr, btl_one.Root(), true, 0);
    HasLeftChild<int>(loctestnum, loctesterr, btl_one.Root(), false);
    HasRightChild<int>(loctestnum, loctesterr, btl_one.Root(), false);
    IsLeaf<int>(loctestnum, loctesterr, btl_one.Root(), true);

    cout << endl << "Begin of BinaryTreeVec/Lnk<int> Test:" << endl;
    EqualBT<int>(loctestnum, loctesterr, btv_empty, btl_empty);
    NonEqualBT<int>(loctestnum, loctesterr, btv_empty, btl_one);

  } catch (exception& exc) {
    cout << "Caught exception: " << exc.what() << endl;
    loctestnum++;
    loctesterr++;
  }

  testerr += loctesterr;
  testnum += loctestnum;
  cout << endl << "BinaryTree<int> (Error/Tests: " << loctesterr << "/" << loctestnum << ")" << endl; 
}

/* ************************************************************************** */

void myTestBTdouble(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of BinaryTree<double> Test:" << endl;

  try {

  } catch (exception& exc) {
    cout << "Caught exception: " << exc.what() << endl;
    loctestnum++;
    loctesterr++;
  }

  testerr += loctesterr;
  testnum += loctestnum;
  cout << "BinaryTree<double> (Error/Tests: " << loctesterr << "/" << loctestnum << ")" << endl; 
}

/* ************************************************************************** */

void myTestBTstring(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of BinaryTree<string> Test:" << endl;

  try {

  } catch (exception& exc) {
    cout << "Caught exception: " << exc.what() << endl;
    loctestnum++;
    loctesterr++;
  }

  testerr += loctesterr;
  testnum += loctestnum;
  cout << "BinaryTree<string> (Error/Tests: " << loctesterr << "/" << loctestnum << ")" << endl; 
}

/* ************************************************************************** */

void myTestBinaryTree(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  myTestBTint(testnum, testerr);
  myTestBTdouble(testnum, testerr);
  myTestBTstring(testnum, testerr);
  testnum += loctestnum;
  testerr += loctesterr;
  cout << "BinaryTree (Error/Tests: " << loctesterr << "/" << loctestnum << ")" << endl; 
}

/* ************************************************************************** */

void myTestFullExercise2A(uint & testnum, uint & testerr) {
  myTestBinaryTree(testnum, testerr);
  // cout << endl << "~*~#~*~ Welcome to the MY Full Test Suite for Exercise 2A ~*~#~*~ " << endl << endl;

  // lasd::BinaryTreeVec<int> btv;
  // lasd::BinaryTreeLnk<int> btl;

  // lasd::BinaryTree<int> & bt = btv;

  // cout << "Creating a binary tree with the following structure:" << endl;
  // cout << "       1" << endl;
  // cout << "      / \\" << endl;
  // cout << "     2   3" << endl;
  // cout << "    / \\   \\" << endl;
  // cout << "   4   5   6" << endl;
  // cout << "  / \\" << endl;
  // cout << " 7   8" << endl;

  // btv.Root().Element() = 1;
  // btv.Root().LeftChild().Element() = 2;
  // btv.Root().RightChild().Element() = 3;
  // btv.Root().LeftChild().LeftChild().Element() = 4;
  // btv.Root().LeftChild().RightChild().Element() = 5;
  // btv.Root().RightChild().RightChild().Element() = 6;
  // btv.Root().LeftChild().LeftChild().LeftChild().Element() = 7;
  // btv.Root().LeftChild().LeftChild().RightChild().Element() = 8;

  // cout << "The tree has been created." << endl;

  // cout << "Testing the tree:" << endl;

  // GetElement(testnum, testerr, bt.Root(), true, 1);
  // GetElement(testnum, testerr, bt.Root().LeftChild(), true, 2);
  // GetElement(testnum, testerr, bt.Root().RightChild(), true, 3);
  // GetElement(testnum, testerr, bt.Root().LeftChild().LeftChild(), true, 4);
  // GetElement(testnum, testerr, bt.Root().LeftChild().RightChild(), true, 5);
  // GetElement(testnum, testerr, bt.Root().RightChild().RightChild(), true, 6);
  // GetElement(testnum, testerr, bt.Root().LeftChild().LeftChild().LeftChild(), true, 7);
  // GetElement(testnum, testerr, bt.Root
}

/* ************************************************************************** */

}