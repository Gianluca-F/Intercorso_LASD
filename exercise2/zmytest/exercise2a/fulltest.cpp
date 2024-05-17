#include <iostream>

/* ************************************************************************** */

#include "../../zlasdtest/container/container.hpp"
// #include "../../zlasdtest/container/testable.hpp"
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

/* ************************************************************************** */

#include <random>
#include <cstring>

/* ************************************************************************** */

#define NUM_BT 20 // Number of elements in the binary tree

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
    lasd::BinaryTreeLnk<int> btv2_empty;
    lasd::BinaryTreeVec<int> btv3_empty(btv_empty);
    Root<int>(loctestnum, loctesterr, btv_empty, false, 10);
    EqualBT<int>(loctestnum, loctesterr, btv_empty, btv2_empty);
    EqualBT<int>(loctestnum, loctesterr, btv_empty, btv3_empty);
    EqualBT<int>(loctestnum, loctesterr, btv2_empty, btv3_empty);

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
    lasd::Vector<int> v2(NUM_BT);
    uint i;
    for (i = 0; i < NUM_BT; i++) {
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
    lasd::BinaryTreeLnk<int> btl2_empty;
    Root<int>(loctestnum, loctesterr, btl_empty, false, 0);
    EqualBT<int>(loctestnum, loctesterr, btl_empty, btl2_empty);

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

    btv_many.Clear();
    EqualBT<int>(loctestnum, loctesterr, btv_many, btl_empty);
    NonEqualBT<int>(loctestnum, loctesterr, btv_many, btl_many);

    btl_many.Clear();
    EqualBT<int>(loctestnum, loctesterr, btl_empty, btv_empty);
    NonEqualBT<int>(loctestnum, loctesterr, btl_many, btv_many_copy);

    EqualBT<int>(loctestnum, loctesterr, btv_many, btl_empty);

    /* ************************************************************************************************* */

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

template <typename Data>
void EqualIt(uint & testnum, uint & testerr, const lasd::BTBreadthIterator<Data> & it1, const lasd::BTBreadthIterator<Data> & it2) {
  bool tst;
  testnum++;
  cout << " " << testnum << " (" << testerr << ") The two iterators are " << ((tst = (it1 == it2)) ? "" : "not ") << "equal: ";
  cout << (tst ? "Correct" : "Error") << "!" << std::endl;
  testerr += (1 - (uint) tst);
}

template <typename Data>
void NonEqualIt(uint & testnum, uint & testerr, const lasd::BTBreadthIterator<Data> & it1, const lasd::BTBreadthIterator<Data> & it2) {
  bool tst;
  testnum++;
  cout << " " << testnum << " (" << testerr << ") The two iterators are " << ((tst = (it1 != it2)) ? "not " : "") << "equal: ";
  cout << (tst ? "Correct" : "Error") << "!" << std::endl;
  testerr += (1 - (uint) tst);
}

template <typename Data>
void EqualIt(uint & testnum, uint & testerr, const lasd::BTPreOrderIterator<Data> & it1, const lasd::BTPreOrderIterator<Data> & it2) {
  bool tst;
  testnum++;
  cout << " " << testnum << " (" << testerr << ") The two iterators are " << ((tst = (it1 == it2)) ? "" : "not ") << "equal: ";
  cout << (tst ? "Correct" : "Error") << "!" << std::endl;
  testerr += (1 - (uint) tst);
}

template <typename Data>
void NonEqualIt(uint & testnum, uint & testerr, const lasd::BTPreOrderIterator<Data> & it1, const lasd::BTPreOrderIterator<Data> & it2) {
  bool tst;
  testnum++;
  cout << " " << testnum << " (" << testerr << ") The two iterators are " << ((tst = (it1 != it2)) ? "not " : "") << "equal: ";
  cout << (tst ? "Correct" : "Error") << "!" << std::endl;
  testerr += (1 - (uint) tst);
}

template <typename Data>
void EqualIt(uint & testnum, uint & testerr, const lasd::BTPostOrderIterator<Data> & it1, const lasd::BTPostOrderIterator<Data> & it2) {
  bool tst;
  testnum++;
  cout << " " << testnum << " (" << testerr << ") The two iterators are " << ((tst = (it1 == it2)) ? "" : "not ") << "equal: ";
  cout << (tst ? "Correct" : "Error") << "!" << std::endl;
  testerr += (1 - (uint) tst);
}

template <typename Data>
void NonEqualIt(uint & testnum, uint & testerr, const lasd::BTPostOrderIterator<Data> & it1, const lasd::BTPostOrderIterator<Data> & it2) {
  bool tst;
  testnum++;
  cout << " " << testnum << " (" << testerr << ") The two iterators are " << ((tst = (it1 != it2)) ? "not " : "") << "equal: ";
  cout << (tst ? "Correct" : "Error") << "!" << std::endl;
  testerr += (1 - (uint) tst);
}

template <typename Data>
void EqualIt(uint & testnum, uint & testerr, const lasd::BTInOrderIterator<Data> & it1, const lasd::BTInOrderIterator<Data> & it2) {
  bool tst;
  testnum++;
  cout << " " << testnum << " (" << testerr << ") The two iterators are " << ((tst = (it1 == it2)) ? "" : "not ") << "equal: ";
  cout << (tst ? "Correct" : "Error") << "!" << std::endl;
  testerr += (1 - (uint) tst);
}

template <typename Data>
void NonEqualIt(uint & testnum, uint & testerr, const lasd::BTInOrderIterator<Data> & it1, const lasd::BTInOrderIterator<Data> & it2) {
  bool tst;
  testnum++;
  cout << " " << testnum << " (" << testerr << ") The two iterators are " << ((tst = (it1 != it2)) ? "not " : "") << "equal: ";
  cout << (tst ? "Correct" : "Error") << "!" << std::endl;
  testerr += (1 - (uint) tst);
}

/* ************************************************************************** */

void myTestBTdouble(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of BinaryTree<double> Test (using iterators):" << endl;

  try {
    // BinaryTree empty
    cout << "\n~~~ BinaryTree empty ~~~\n" << endl;
    lasd::BinaryTreeVec<double> btv_empty;
    lasd::BinaryTreeLnk<double> btl_empty;

    lasd::BTBreadthMutableIterator<double> mut_it_bt_empty(btv_empty);
    Terminated<double>(loctestnum, loctesterr, mut_it_bt_empty, true);
    GetItrValue<double>(loctestnum, loctesterr, mut_it_bt_empty, false, 5.0);
    SetItrValue<double>(loctestnum, loctesterr, mut_it_bt_empty, false, 10.2);

    lasd::BTBreadthIterator<double> it_bt_empty(mut_it_bt_empty);
    Terminated<double>(loctestnum, loctesterr, it_bt_empty, true);
    GetItrValue<double>(loctestnum, loctesterr, it_bt_empty, false, 5.0);

    lasd::BTPreOrderMutableIterator<double> mut_it2_bt_empty(btv_empty);
    Terminated<double>(loctestnum, loctesterr, mut_it2_bt_empty, true);
    GetItrValue<double>(loctestnum, loctesterr, mut_it2_bt_empty, false, 5.0);
    SetItrValue<double>(loctestnum, loctesterr, mut_it2_bt_empty, false, 10.2);

    lasd::BTPreOrderIterator<double> it2_bt_empty(move(mut_it2_bt_empty));
    Terminated<double>(loctestnum, loctesterr, it2_bt_empty, true);
    GetItrValue<double>(loctestnum, loctesterr, it2_bt_empty, false, 5.0);

    lasd::BTPostOrderMutableIterator<double> mut_it3_bt_empty(btl_empty);
    Terminated<double>(loctestnum, loctesterr, mut_it3_bt_empty, true);
    GetItrValue<double>(loctestnum, loctesterr, mut_it3_bt_empty, false, 5.0);
    SetItrValue<double>(loctestnum, loctesterr, mut_it3_bt_empty, false, 10.2);

    lasd::BTPostOrderIterator<double> it3_bt_empty(mut_it3_bt_empty);
    Terminated<double>(loctestnum, loctesterr, it3_bt_empty, true);
    GetItrValue<double>(loctestnum, loctesterr, it3_bt_empty, false, 5.0);

    lasd::BTInOrderMutableIterator<double> mut_it4_bt_empty(btl_empty);
    Terminated<double>(loctestnum, loctesterr, mut_it4_bt_empty, true);
    GetItrValue<double>(loctestnum, loctesterr, mut_it4_bt_empty, false, 5.0);
    SetItrValue<double>(loctestnum, loctesterr, mut_it4_bt_empty, false, 10.2);

    lasd::BTInOrderIterator<double> it4_bt_empty(move(mut_it4_bt_empty));
    Terminated<double>(loctestnum, loctesterr, it4_bt_empty, true);
    GetItrValue<double>(loctestnum, loctesterr, it4_bt_empty, false, 5.0);

    /* ************************************************************************************************* */

    // BinaryTree with one element
    cout << "\n~~~ BinaryTree with one element ~~~\n" << endl;
    lasd::Vector<double> v1(1);  v1[0] = -5.2;
    lasd::BinaryTreeVec<double> btv_one(v1);
    lasd::List<double> l1;  l1.InsertAtBack(3.18);
    lasd::BinaryTreeLnk<double> btl_one(l1);

    lasd::BTBreadthMutableIterator<double> mut_it_bt_one(btv_one);
    Terminated<double>(loctestnum, loctesterr, mut_it_bt_one, false);
    GetItrValue<double>(loctestnum, loctesterr, mut_it_bt_one, true, -5.2);
    SetItrValue<double>(loctestnum, loctesterr, mut_it_bt_one, true, 10.2);

    lasd::BTBreadthIterator<double> it_bt_one(btv_one);
    Terminated<double>(loctestnum, loctesterr, it_bt_one, false);
    GetItrValue<double>(loctestnum, loctesterr, it_bt_one, true, 10.2);

    EqualIt<double>(loctestnum, loctesterr, mut_it_bt_one, it_bt_one);
    Terminated<double>(loctestnum, loctesterr, it_bt_one, false);
    ++it_bt_one;
    Terminated<double>(loctestnum, loctesterr, it_bt_one, true);
    NonEqualIt<double>(loctestnum, loctesterr, mut_it_bt_one, it_bt_one);
    it_bt_one.Reset();
    EqualIt<double>(loctestnum, loctesterr, mut_it_bt_one, it_bt_one);

    lasd::BTPreOrderMutableIterator<double> mut_it2_bt_one(btl_one);
    Terminated<double>(loctestnum, loctesterr, mut_it2_bt_one, false);
    GetItrValue<double>(loctestnum, loctesterr, mut_it2_bt_one, true, 3.18);
    SetItrValue<double>(loctestnum, loctesterr, mut_it2_bt_one, true, 10.2);

    lasd::BTPreOrderIterator<double> it2_bt_one(move(mut_it2_bt_one));
    Terminated<double>(loctestnum, loctesterr, it2_bt_one, false);
    GetItrValue<double>(loctestnum, loctesterr, it2_bt_one, true, 10.2);

    NonEqualIt<double>(loctestnum, loctesterr, mut_it2_bt_one, it2_bt_one);

    lasd::BTPostOrderMutableIterator<double> mut_it3_bt_one(btv_one);
    Terminated<double>(loctestnum, loctesterr, mut_it3_bt_one, false);
    GetItrValue<double>(loctestnum, loctesterr, mut_it3_bt_one, true, 10.2);
    SetItrValue<double>(loctestnum, loctesterr, mut_it3_bt_one, true, -5.2);

    lasd::BTPostOrderIterator<double> it3_bt_one(btv_one);
    Terminated<double>(loctestnum, loctesterr, it3_bt_one, false);
    GetItrValue<double>(loctestnum, loctesterr, it3_bt_one, true, -5.2);

    EqualIt<double>(loctestnum, loctesterr, mut_it3_bt_one, it3_bt_one);
    ++it3_bt_one;
    Terminated<double>(loctestnum, loctesterr, it3_bt_one, true);
    ++mut_it3_bt_one;
    Terminated<double>(loctestnum, loctesterr, mut_it3_bt_one, true);
    EqualIt<double>(loctestnum, loctesterr, mut_it3_bt_one, it3_bt_one);
    it3_bt_one.Reset();
    NonEqualIt<double>(loctestnum, loctesterr, mut_it3_bt_one, it3_bt_one);
    mut_it3_bt_one.Reset();
    EqualIt<double>(loctestnum, loctesterr, mut_it3_bt_one, it3_bt_one);

    lasd::BTInOrderMutableIterator<double> mut_it4_bt_one(btl_one);
    Terminated<double>(loctestnum, loctesterr, mut_it4_bt_one, false);
    GetItrValue<double>(loctestnum, loctesterr, mut_it4_bt_one, true, 10.2);
    SetItrValue<double>(loctestnum, loctesterr, mut_it4_bt_one, true, 3.18);

    lasd::BTInOrderIterator<double> it4_bt_one(move(mut_it4_bt_one));
    Terminated<double>(loctestnum, loctesterr, it4_bt_one, false);
    GetItrValue<double>(loctestnum, loctesterr, it4_bt_one, true, 3.18);

    NonEqualIt<double>(loctestnum, loctesterr, mut_it4_bt_one, it4_bt_one);

    /* ************************************************************************************************* */

    // BinaryTree with many elements
    cout << "\n~~~ BinaryTree with many elements ~~~\n" << endl;
    lasd::Vector<double> v2(NUM_BT);
    for(uint i = 0; i < NUM_BT; i++) {
      v2[i] = i;
    }
    lasd::List<double> l2(v2);
    lasd::BinaryTreeVec<double> btv_many(v2);
    lasd::BinaryTreeLnk<double> btl_many(l2);

    lasd::BTBreadthMutableIterator<double> mut_it_bt_many(btv_many);
    for(uint i = 0; i < NUM_BT; i++) {
      GetItrValue<double>(loctestnum, loctesterr, mut_it_bt_many, true, i);
      ++mut_it_bt_many;
    }
    Terminated<double>(loctestnum, loctesterr, mut_it_bt_many, true);
    mut_it_bt_many.Reset();
    SetItrValue<double>(loctestnum, loctesterr, mut_it_bt_many, true, 7.77);
    Root<double>(loctestnum, loctesterr, btv_many, true, 7.77);

    lasd::BTPostOrderMutableIterator<double> mut_it3_bt_many(btl_many);
    btl_many.PostOrderMap(
      [&loctestnum, &loctesterr, &mut_it3_bt_many](double & dat) { 
        GetItrValue<double>(loctestnum, loctesterr, mut_it3_bt_many, true, dat);
        ++mut_it3_bt_many;
      }
    );
    Terminated<double>(loctestnum, loctesterr, mut_it3_bt_many, true);
    mut_it3_bt_many.Reset();
    SetItrValue<double>(loctestnum, loctesterr, mut_it3_bt_many, true, 7.77);
    Root<double>(loctestnum, loctesterr, btl_many, false, 7.77);

    lasd::BTPreOrderMutableIterator<double> mut_it2_bt_many(btv_many);
    btv_many.PreOrderMap(
      [&loctestnum, &loctesterr, &mut_it2_bt_many](double & dat) { 
        GetItrValue<double>(loctestnum, loctesterr, mut_it2_bt_many, true, dat);
        ++mut_it2_bt_many;
      }
    );

    lasd::BTInOrderMutableIterator<double> mut_it4_bt_many(btl_many);
    btl_many.InOrderMap(
      [&loctestnum, &loctesterr, &mut_it4_bt_many](double & dat) { 
        GetItrValue<double>(loctestnum, loctesterr, mut_it4_bt_many, true, dat);
        ++mut_it4_bt_many;
      }
    );    

    /* ************************************************************************************************* */

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
    // BinaryTree empty
    cout << "\n~~~ BinaryTree empty ~~~\n" << endl;
    lasd::BinaryTreeVec<string> btv_empty;
    lasd::BinaryTreeLnk<string> btl_empty;
    Root<string>(loctestnum, loctesterr, btv_empty, false, "");
    EqualBT<string>(loctestnum, loctesterr, btv_empty, btl_empty);

    /* ************************************************************************************************* */

    // BinaryTree with one element
    cout << "\n~~~ BinaryTree with one element ~~~\n" << endl;
    lasd::Vector<string> v1(1);  v1[0] = string("Hello");
    lasd::BinaryTreeVec<string> btv_one(v1);
    lasd::List<string> l1;  l1.InsertAtBack(string("World"));
    lasd::BinaryTreeLnk<string> btl_one(l1);
    Root<string>(loctestnum, loctesterr, btv_one, true, string("Hello"));
    NonEqualBT<string>(loctestnum, loctesterr, btv_one, btl_one);

    SetElement<string>(loctestnum, loctesterr, btv_one.Root(), true, string("World"));
    EqualBT<string>(loctestnum, loctesterr, btv_one, btl_one);

    lasd::BinaryTreeVec<string> btv_one_copy(btv_one);
    lasd::BinaryTreeLnk<string> btl_one_copy(btl_one);
    EqualBT<string>(loctestnum, loctesterr, btl_one_copy, btv_one_copy);

    lasd::BinaryTreeVec<string> btv_one_move(move(btv_one));
    lasd::BinaryTreeLnk<string> btl_one_move(move(btl_one));
    EqualBT<string>(loctestnum, loctesterr, btl_one_move, btv_one_move);

    /* ************************************************************************************************* */

    // BinaryTree with many elements
    cout << "\n~~~ BinaryTree with many elements ~~~\n" << endl;
    lasd::Vector<string> v2(NUM_BT);
    for(uint i = 0; i < NUM_BT; i++) {
      v2[i] = to_string(i);
    }
    lasd::List<string> l2(v2);
    lasd::BinaryTreeVec<string> btv_many(v2);
    lasd::BinaryTreeLnk<string> btl_many(l2);

    Root<string>(loctestnum, loctesterr, btv_many, true, "0");
    EqualBT<string>(loctestnum, loctesterr, btv_many, btl_many);

    Traverse<string>(loctestnum, loctesterr, btv_many, true, &TraversePrint<string>);
    Traverse<string>(loctestnum, loctesterr, btl_many, true, &TraversePrint<string>);

    Fold(loctestnum, loctesterr, btv_many, true, &FoldStringConcatenate, string(""), string("012345678910111213141516171819"));
    
    /* ************************************************************************************************* */

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

void myTestFullExercise2A(uint & testnum, uint & testerr) {
  myTestBTint(testnum, testerr);
  myTestBTdouble(testnum, testerr);
  myTestBTstring(testnum, testerr);
}

/* ************************************************************************** */

}