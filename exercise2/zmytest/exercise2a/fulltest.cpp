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

#define NUM 20
#define MAX 50      

/* ************************************************************************** */

using namespace std;

/* ************************************************************************** */

namespace mytest {

/* ************************************************************************** */

template <typename Data>
void myTestBT(lasd::BinaryTree<Data> & bt, uint & testnum, uint & testerr, Data expc_res_add, Data expc_res_mul) {
  try {
    Traverse(testnum, testerr, bt, true, &TraversePrint<int>);
    TraversePreOrder(testnum, testerr, bt, true, &TraversePrint<int>);
    TraversePostOrder(testnum, testerr, bt, true, &TraversePrint<int>);
    TraverseInOrder(testnum, testerr, bt, true, &TraversePrint<int>);
    TraverseBreadth(testnum, testerr, bt, true, &TraversePrint<int>);

    Fold(testnum, testerr, bt, true, &FoldAdd<int>, 0, expc_res_add);
    FoldPreOrder(testnum, testerr, bt, true, &FoldAdd<int>, 0, expc_res_add);
    FoldPostOrder(testnum, testerr, bt, true, &FoldAdd<int>, 0, expc_res_add);
    FoldInOrder(testnum, testerr, bt, true, &FoldAdd<int>, 0, expc_res_add);
    FoldBreadth(testnum, testerr, bt, true, &FoldAdd<int>, 0, expc_res_add);

    Fold(testnum, testerr, bt, true, &FoldMultiply<int>, 1, expc_res_mul);
    FoldPreOrder(testnum, testerr, bt, true, &FoldMultiply<int>, 1, expc_res_mul);
    FoldPostOrder(testnum, testerr, bt, true, &FoldMultiply<int>, 1, expc_res_mul);
    FoldInOrder(testnum, testerr, bt, true, &FoldMultiply<int>, 1, expc_res_mul);
    FoldBreadth(testnum, testerr, bt, true, &FoldMultiply<int>, 1, expc_res_mul);
  }
  catch (...) {
    testnum++; testerr++;
    cout << endl << "Unmanaged error! " << endl;
  }
}

/* ************************************************************************** */

void myTestBTint(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of BinaryTree<int> Test:" << endl;

  try {
    cout << endl << "~ BinaryTreeVec<int> Test:" << endl;
   
    // BinaryTreeVec empty
    cout << "\n~~~ BinaryTreeVec empty ~~~\n" << endl;
    lasd::BinaryTreeVec<int> btv_empty;
    Root<int>(loctestnum, loctesterr, btv_empty, false, 10);

    // BinaryTreeVec with one element
    cout << "\n~~~ BinaryTreeVec with one element (created using a vector) ~~~\n" << endl;
    lasd::Vector<int> v1(1);  v1[0] = -5;
    lasd::BinaryTreeVec<int> btv_one(v1);

    GetElement<int>(loctestnum, loctesterr, btv_one.Root(), true, -5);
    HasLeftChild<int>(loctestnum, loctesterr, btv_one.Root(), false);
    HasRightChild<int>(loctestnum, loctesterr, btv_one.Root(), false);
    IsLeaf<int>(loctestnum, loctesterr, btv_one.Root(), true);

    cout << "\n~~~ BinaryTreeVec with one element (created using a list) ~~~\n" << endl;
    lasd::List<int> l1;  l1.InsertAtBack(-5);
    lasd::BinaryTreeVec<int> btv_one2(l1);

    GetElement<int>(loctestnum, loctesterr, btv_one2.Root(), true, -5);
    HasLeftChild<int>(loctestnum, loctesterr, btv_one2.Root(), false);
    HasRightChild<int>(loctestnum, loctesterr, btv_one2.Root(), false);
    IsLeaf<int>(loctestnum, loctesterr, btv_one2.Root(), true);

    EqualBT<int>(loctestnum, loctesterr, btv_one, btv_one2);

    lasd::BinaryTreeVec<int> btv_one_copy(btv_one);
    lasd::BinaryTreeVec<int> btv_one2_move(move(btv_one2));

    EqualBT<int>(loctestnum, loctesterr, btv_one, btv_one_copy);
    EqualBT<int>(loctestnum, loctesterr, btv_one_copy, btv_one2_move);

    SetElement<int>(loctestnum, loctesterr, btv_one.Root(), true, 10);
    NonEqualBT<int>(loctestnum, loctesterr, btv_one, btv_one_copy);

    // BinaryTreeVec with many elements
    cout << "\n~~~ BinaryTreeVec with many elements (created using a vector) ~~~\n" << endl;
    lasd::Vector<int> v2(NUM);
    uint i;
    for (i = 0; i < NUM; i++) {
      v2[i] = i;
    }
    lasd::BinaryTreeVec<int> btv_many(v2);

    GetElement<int>(loctestnum, loctesterr, btv_many.Root(), true, 0);
    HasLeftChild<int>(loctestnum, loctesterr, btv_many.Root(), true);
    HasRightChild<int>(loctestnum, loctesterr, btv_many.Root(), true);
    IsLeaf<int>(loctestnum, loctesterr, btv_many.Root(), false);
    HasLeftChild<int>(loctestnum, loctesterr, btv_many.Root().RightChild().LeftChild().RightChild(), false);
    IsLeaf<int>(loctestnum, loctesterr, btv_many.Root().RightChild().LeftChild().RightChild(), true);

    int expc_res_add = (i-1)*i/2;
    int expc_res_mul = 0;
    myTestBT<int>(btv_many, loctestnum, loctesterr, expc_res_add, expc_res_mul);

    cout << "\n~~~ BinaryTreeVec with many elements (created using a list) ~~~\n" << endl;
    lasd::List<int> l2(v2);
    lasd::BinaryTreeVec<int> btv_many2(l2);

    EqualBT<int>(loctestnum, loctesterr, btv_many, btv_many2);
    myTestBT<int>(btv_many2, loctestnum, loctesterr, expc_res_add, expc_res_mul);

    lasd::BinaryTreeVec<int> btv_many_copy(btv_many);
    lasd::BinaryTreeVec<int> btv_many2_move(move(btv_many2));

    EqualBT<int>(loctestnum, loctesterr, btv_many, btv_many_copy);
    EqualBT<int>(loctestnum, loctesterr, btv_many_copy, btv_many2_move);

    GetElement<int>(loctestnum, loctesterr, btv_many.Root().RightChild().LeftChild().RightChild(), true, 12);
    SetElement<int>(loctestnum, loctesterr, btv_many.Root().RightChild().LeftChild().RightChild(), true, 10);
    NonEqualBT<int>(loctestnum, loctesterr, btv_many, btv_many_copy);

    /* ************************************************************************************************* */

    cout << endl << "\n~ BinaryTreeLnk<int> Test:" << endl;

    // BinaryTreeLnk empty
    cout << "\n~~~ BinaryTreeLnk empty ~~~\n" << endl;
    lasd::BinaryTreeLnk<int> btl_empty;
    Root<int>(loctestnum, loctesterr, btl_empty, false, 0);

    // BinaryTreeLnk with one element
    cout << "\n~~~ BinaryTreeLnk with one element (created using a vector) ~~~\n" << endl;
    lasd::BinaryTreeLnk<int> btl_one(v1);

    GetElement<int>(loctestnum, loctesterr, btl_one.Root(), true, -5);
    HasLeftChild<int>(loctestnum, loctesterr, btl_one.Root(), false);
    HasRightChild<int>(loctestnum, loctesterr, btl_one.Root(), false);
    IsLeaf<int>(loctestnum, loctesterr, btl_one.Root(), true);

    cout << "\n~~~ BinaryTreeLnk with one element (created using a list) ~~~\n" << endl;
    lasd::BinaryTreeLnk<int> btl_one2(l1);

    GetElement<int>(loctestnum, loctesterr, btl_one2.Root(), true, -5);
    HasLeftChild<int>(loctestnum, loctesterr, btl_one2.Root(), false);
    HasRightChild<int>(loctestnum, loctesterr, btl_one2.Root(), false);
    IsLeaf<int>(loctestnum, loctesterr, btl_one2.Root(), true);

    EqualBT<int>(loctestnum, loctesterr, btl_one, btl_one2);

    lasd::BinaryTreeLnk<int> btl_one_copy(btl_one);
    lasd::BinaryTreeLnk<int> btl_one2_move(move(btl_one2));

    EqualBT<int>(loctestnum, loctesterr, btl_one, btl_one_copy);
    EqualBT<int>(loctestnum, loctesterr, btl_one_copy, btl_one2_move);

    SetElement<int>(loctestnum, loctesterr, btl_one.Root(), true, 10);
    NonEqualBT<int>(loctestnum, loctesterr, btl_one, btl_one_copy);

    // BinaryTreeLnk with many elements
    cout << "\n~~~ BinaryTreeLnk with many elements (created using a vector) ~~~\n" << endl;
    lasd::BinaryTreeLnk<int> btl_many(v2);

    GetElement<int>(loctestnum, loctesterr, btl_many.Root(), true, 0);
    HasLeftChild<int>(loctestnum, loctesterr, btl_many.Root(), true);
    HasRightChild<int>(loctestnum, loctesterr, btl_many.Root(), true);
    IsLeaf<int>(loctestnum, loctesterr, btl_many.Root(), false);
    HasLeftChild<int>(loctestnum, loctesterr, btl_many.Root().RightChild().LeftChild().RightChild(), false);
    IsLeaf<int>(loctestnum, loctesterr, btl_many.Root().RightChild().LeftChild().RightChild(), true);

    myTestBT<int>(btl_many, loctestnum, loctesterr, expc_res_add, expc_res_mul);

    cout << "\n~~~ BinaryTreeLnk with many elements (created using a list) ~~~\n" << endl;
    lasd::BinaryTreeLnk<int> btl_many2(l2);

    EqualBT<int>(loctestnum, loctesterr, btl_many, btl_many2);
    myTestBT<int>(btl_many2, loctestnum, loctesterr, expc_res_add, expc_res_mul);    

    lasd::BinaryTreeLnk<int> btl_many_copy(btl_many);
    lasd::BinaryTreeLnk<int> btl_many2_move(move(btl_many2));

    EqualBT<int>(loctestnum, loctesterr, btl_many, btl_many_copy);
    EqualBT<int>(loctestnum, loctesterr, btl_many_copy, btl_many2_move);

    GetElement<int>(loctestnum, loctesterr, btl_many.Root().RightChild().LeftChild().RightChild(), true, 12);
    SetElement<int>(loctestnum, loctesterr, btl_many.Root().RightChild().LeftChild().RightChild(), true, 10);
    NonEqualBT<int>(loctestnum, loctesterr, btl_many, btl_many_copy);

    /* ************************************************************************************************* */

    cout << endl << "~ BinaryTreeVec/Lnk<int> Comparison Tests:" << endl;
    EqualBT<int>(loctestnum, loctesterr, btv_empty, btl_empty);
    NonEqualBT<int>(loctestnum, loctesterr, btv_empty, btl_one);
    NonEqualBT<int>(loctestnum, loctesterr, btv_one, btl_empty);
    EqualBT<int>(loctestnum, loctesterr, btv_one, btl_one);
    EqualBT<int>(loctestnum, loctesterr, btv_many, btl_many);
    NonEqualBT<int>(loctestnum, loctesterr, btv_many, btl_many_copy);
    NonEqualBT<int>(loctestnum, loctesterr, btv_many_copy, btl_many);

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