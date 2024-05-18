
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

    btl_empty.Clear(); btv_empty.Clear(); bst.Clear();

    /* ************************************************************************************************* */

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

    v.Clear(); btv.Clear(); btl.Clear();

    /* ************************************************************************************************* */

    // trees with many (random) elements
    cout << "\n~~~ BST with many (random) elements tests ~~~\n" << endl;
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
    InsertAllC<int>(loctestnum, loctesterr, bst, true, v2);

    Empty(loctestnum, loctesterr, bst, false);
    Size(loctestnum, loctesterr, bst, true, NUM_BST);

    for(uint i = 0; i < NUM_BST; i++) {
      Exists<int>(loctestnum, loctesterr, bst, true, v2[i]);
    }

    Root<int>(loctestnum, loctesterr, bst, true, v2[0]);
    Min<int>(loctestnum, loctesterr, bst, true, min);
    Max<int>(loctestnum, loctesterr, bst, true, max);
    EqualBST<int>(loctestnum, loctesterr, bst, bst);

    TraverseInOrder<int>(loctestnum, loctesterr, bst, true, &TraversePrint<int>);

    lasd::BST<int> bst2(bst);
    EqualBST<int>(loctestnum, loctesterr, bst, bst2);

    MinNRemove<int>(loctestnum, loctesterr, bst2, true, min);
    MaxNRemove<int>(loctestnum, loctesterr, bst2, true, max);
    Size(loctestnum, loctesterr, bst2, true, NUM_BST-2);
    NonEqualBST<int>(loctestnum, loctesterr, bst, bst2);

    RemoveMin<int>(loctestnum, loctesterr, bst2, true);
    Size(loctestnum, loctesterr, bst2, true, NUM_BST-3);

    RemoveMax<int>(loctestnum, loctesterr, bst2, true);
    Size(loctestnum, loctesterr, bst2, true, NUM_BST-4);

    TraverseInOrder<int>(loctestnum, loctesterr, bst2, true, &TraversePrint<int>);

    lasd::BST<int> bst3(move(bst2));
    bst2.Clear();
    Size(loctestnum, loctesterr, bst3, true, NUM_BST-4);

    RemoveAll<int>(loctestnum, loctesterr, bst3, false, l);
    Size(loctestnum, loctesterr, bst3, true, 0);

    RemoveSome<int>(loctestnum, loctesterr, bst3, false, v2);
    Size(loctestnum, loctesterr, bst3, true, 0);

    InsertAllM<int>(loctestnum, loctesterr, bst3, true, move(l));
    Size(loctestnum, loctesterr, bst3, true, NUM_BST);
    EqualBST<int>(loctestnum, loctesterr, bst, bst3);

    bst3.Clear();

    if(v2[1] != min) { v2[1] = MAX_BST+1; }
    else { v2[2] = MAX_BST+1; }

    InsertAllM<int>(loctestnum, loctesterr, bst3, true, move(v2));
    Min<int>(loctestnum, loctesterr, bst3, true, min);
    Max<int>(loctestnum, loctesterr, bst3, true, MAX_BST+1);
    Size(loctestnum, loctesterr, bst3, true, NUM_BST);

    TraverseInOrder<int>(loctestnum, loctesterr, bst3, true, &TraversePrint<int>);
    NonEqualBST<int>(loctestnum, loctesterr, bst, bst3);

    bst2 = move(bst3);
    Size(loctestnum, loctesterr, bst2, true, NUM_BST);
    Exists<int>(loctestnum, loctesterr, bst2, true, MAX_BST+1);
    NonEqualBST<int>(loctestnum, loctesterr, bst, bst2);
    TraverseInOrder<int>(loctestnum, loctesterr, bst2, true, &TraversePrint<int>);

    bst2 = bst;
    Size(loctestnum, loctesterr, bst2, true, NUM_BST);
    EqualBST<int>(loctestnum, loctesterr, bst, bst2);
    TraverseInOrder<int>(loctestnum, loctesterr, bst2, true, &TraversePrint<int>);

    v2.Clear(); l.Clear(); btv2.Clear(); btl2.Clear(); bst.Clear(); bst2.Clear(); bst3.Clear();

    /* ************************************************************************************************* */

    // trees with many (decided) elements

    cout << "\n~~~ BST with many (decided) elements tests ~~~\n" << endl;

    lasd::Vector<int> v4(10);
                                                  v4[0] = 10;
    //                                          /              \  .
                          v4[1] = 5;                                       v4[2] = 15; 
    //                  /           \                                    /           \  .
            v4[3] = 3;                v4[4] = 7;            v4[5] = 12;                v4[6] = 17;
    //       /    \                   /
    v4[7] = 1;  v4[8] = 4;    v4[9] = 6;

    lasd::List<int> l4;
    for(uint i = 0; i < 10; i++) { l4.InsertAtFront(v4[i]); }

    lasd::BinaryTreeVec<int> btv_v4(v4);
    lasd::BinaryTreeLnk<int> btl_v4(v4);
    lasd::BinaryTreeVec<int> btv_l4(l4);
    lasd::BinaryTreeLnk<int> btl_l4(l4);
    lasd::BST<int> bst_v4(v4);
    lasd::BST<int> bst_l4(l4);

    TraverseInOrder<int>(loctestnum, loctesterr, btv_v4, true, &TraversePrint<int>);
    TraverseInOrder<int>(loctestnum, loctesterr, btl_v4, true, &TraversePrint<int>);
    TraverseInOrder<int>(loctestnum, loctesterr, btv_l4, true, &TraversePrint<int>);
    TraverseInOrder<int>(loctestnum, loctesterr, btl_l4, true, &TraversePrint<int>);

    TraverseInOrder<int>(loctestnum, loctesterr, bst_v4, true, &TraversePrint<int>);


    // Comparison tests
    cout << "\n~~~ BST Comparison tests ~~~\n" << endl;

    EqualBT<int>(loctestnum, loctesterr, bst_v4, btv_v4);
    EqualBT<int>(loctestnum, loctesterr, bst_v4, btl_v4);

    NonEqualBT<int>(loctestnum, loctesterr, btv_v4, btv_l4);
    NonEqualBT<int>(loctestnum, loctesterr, btl_v4, btl_l4);
    NonEqualBT<int>(loctestnum, loctesterr, bst_v4, btv_l4);
    NonEqualBT<int>(loctestnum, loctesterr, bst_l4, btl_l4);

    EqualBST<int>(loctestnum, loctesterr, bst_v4, bst_l4);

    btv_v4.Clear(); btl_v4.Clear(); btv_l4.Clear(); btl_l4.Clear(); 

    /* ************************************************************************ */

    // Pred and Succ tests
    cout << "\n~~~ BST Predecessor and Successor tests ~~~\n" << endl;

    // Case 1: value exists in the tree
    Predecessor<int>(loctestnum, loctesterr, bst_v4, true, 10, 7);
    Predecessor<int>(loctestnum, loctesterr, bst_v4, true, 5, 4);
    Predecessor<int>(loctestnum, loctesterr, bst_v4, true, 15, 12);
    Predecessor<int>(loctestnum, loctesterr, bst_v4, true, 17, 15);
    Predecessor<int>(loctestnum, loctesterr, bst_v4, true, 12, 10);
    Predecessor<int>(loctestnum, loctesterr, bst_v4, false, 1, 0);

    Successor<int>(loctestnum, loctesterr, bst_v4, true, 10, 12);
    Successor<int>(loctestnum, loctesterr, bst_v4, true, 5, 6);
    Successor<int>(loctestnum, loctesterr, bst_v4, true, 1, 3);
    Successor<int>(loctestnum, loctesterr, bst_v4, true, 7, 10);
    Successor<int>(loctestnum, loctesterr, bst_v4, true, 12, 15);
    Successor<int>(loctestnum, loctesterr, bst_v4, false, 17, 19);

    // Case 2: value does not exist in the tree
    Predecessor<int>(loctestnum, loctesterr, bst_v4, true, 11, 10);
    Predecessor<int>(loctestnum, loctesterr, bst_v4, true, 8, 7);
    Predecessor<int>(loctestnum, loctesterr, bst_v4, true, 13, 12);
    Predecessor<int>(loctestnum, loctesterr, bst_v4, true, 19, 17);
    Predecessor<int>(loctestnum, loctesterr, bst_v4, false, 0, -1);

    Successor<int>(loctestnum, loctesterr, bst_v4, true, 8, 10);
    Successor<int>(loctestnum, loctesterr, bst_v4, true, 11, 12);
    Successor<int>(loctestnum, loctesterr, bst_v4, true, 13, 15);
    Successor<int>(loctestnum, loctesterr, bst_v4, true, 0, 1);
    Successor<int>(loctestnum, loctesterr, bst_v4, false, 19, 20);

    // with remove  
    PredecessorNRemove<int>(loctestnum, loctesterr, bst_v4, true, 10, 7);
    RemovePredecessor<int>(loctestnum, loctesterr, bst_v4, true, 10);
    Predecessor<int>(loctestnum, loctesterr, bst_v4, true, 10, 5);
    TraverseInOrder<int>(loctestnum, loctesterr, bst_v4, true, &TraversePrint<int>);

    SuccessorNRemove<int>(loctestnum, loctesterr, bst_v4, true, 12, 15);
    RemoveSuccessor<int>(loctestnum, loctesterr, bst_v4, true, 12);
    Successor<int>(loctestnum, loctesterr, bst_v4, false, 12, 15);
    TraverseInOrder<int>(loctestnum, loctesterr, bst_v4, true, &TraversePrint<int>);

    Size(loctestnum, loctesterr, bst_v4, true, 6);

    bst_v4 = bst_l4;
    Size(loctestnum, loctesterr, bst_v4, true, 10);

    bst_v4.Clear(); bst_l4.Clear();

    /* ************************************************************************************************* */

    // a degenerate BST 

    cout << "\n~~~ BST degenerate tests ~~~\n" << endl;

    lasd::Vector<int> v5(NUM_BST);
    for (uint i = 0; i < NUM_BST; i++) { 
      v5[i] = i; 
    }
    lasd::BinaryTreeVec<int> btv5(v5);
    lasd::BST<int> bst5(btv5);
    lasd::BinaryTreeLnk<int> btl5((lasd::TraversableContainer<int>&)bst5); // otherwise it would be considered as a BinaryTreeLnk (that is protected)

    EqualBT<int>(loctestnum, loctesterr, btv5, btl5);
    NonEqualBT<int>(loctestnum, loctesterr, btv5, bst5);
    NonEqualBT<int>(loctestnum, loctesterr, bst5, btv5);

    lasd::BST<int> bst5_copy(bst5);

    PredecessorNRemove<int>(loctestnum, loctesterr, bst5, false, 0, -1);
    SuccessorNRemove<int>(loctestnum, loctesterr, bst5, false, NUM_BST-1, NUM_BST);

    FoldPreOrder<int, int>(loctestnum, loctesterr, bst5, true, &FoldAdd<int>, 0, NUM_BST*(NUM_BST-1)/2);

    Remove<int>(loctestnum, loctesterr, bst5, true, 8);
    FoldInOrder<int, int>(loctestnum, loctesterr, bst5, true, &FoldAdd<int>, 0, NUM_BST*(NUM_BST-1)/2 - 8);

    Remove<int>(loctestnum, loctesterr, bst5, true, 10);
    FoldPostOrder<int, int>(loctestnum, loctesterr, bst5, true, &FoldAdd<int>, 0, NUM_BST*(NUM_BST-1)/2 - 18);

    Remove<int>(loctestnum, loctesterr, bst5, true, 0);
    Root(loctestnum, loctesterr, bst5, true, 1);
    TraverseInOrder<int>(loctestnum, loctesterr, bst5, true, &TraversePrint<int>);
    TraverseInOrder<int>(loctestnum, loctesterr, bst5_copy, true, &TraversePrint<int>);
    FoldBreadth<int, int>(loctestnum, loctesterr, bst5, true, &FoldAdd<int>, 0, NUM_BST*(NUM_BST-1)/2 - 18);

    InsertSomeC<int>(loctestnum, loctesterr, bst5, true, v5);
    FoldPreOrder<int, int>(loctestnum, loctesterr, bst5, true, &FoldMultiply<int>, 1, 0);
    FoldInOrder<int, int>(loctestnum, loctesterr, bst5, true, &FoldMultiply<int>, 1, 0);
    FoldPostOrder<int, int>(loctestnum, loctesterr, bst5, true, &FoldMultiply<int>, 1, 0);
    FoldBreadth<int, int>(loctestnum, loctesterr, bst5, true, &FoldMultiply<int>, 1, 0);

    Size(loctestnum, loctesterr, bst5, true, NUM_BST);
    Size(loctestnum, loctesterr, bst5_copy, true, NUM_BST);
    EqualBST<int>(loctestnum, loctesterr, bst5, bst5_copy);
    NonEqualBT<int>(loctestnum, loctesterr, bst5, btv5);

    bst5.Clear(); bst5_copy.Clear(); 
    EqualBST<int>(loctestnum, loctesterr, bst5, bst5_copy);
    EqualBT<int>(loctestnum, loctesterr, bst5, bst5_copy);
    
    btv5.Clear(); btl5.Clear();

    /* ************************************************************************************************* */

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

template <typename Data>
void myTestiterator(lasd::ForwardIterator<Data> & it, uint & testnum, uint & testerr,lasd::Vector<Data> vec) {
  for(uint i = 0; vec.Size() && !it.Terminated(); i++) {
    GetItrValue<Data>(testnum, testerr, it, true, vec[i]);
    ++it;
  }
}

void myTestBSTdouble(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of BST<double> Test:" << endl;
  try {
    // trees with many (decided) elements
    cout << "\n~~~ BST and iterators tests ~~~\n" << endl;

    lasd::Vector<double> v(11);
                                v[0] = 10.6;
    //                        /              \  .
                      v[2] = 9.5;            v[1] = 15.2; 
    //              /           \                      \  .
        v[3] = 3.0;               v[4] = 10.1;         v[6] = 17.0;
    //      /    \                   /                      \   .
      v[7] = 1.12; v[5] = 4.8;  v[8] = 9.6;              v[9] = 25.77;
    //                                                          \  .
                                                              v[10] = 30.0;

    lasd::Vector<double> v_breadth(11);
    v_breadth[0] = 10.6; 
    v_breadth[1] = 9.5; v_breadth[2] = 15.2; 
    v_breadth[3] = 3.0; v_breadth[4] = 10.1; v_breadth[5] = 17.0; 
    v_breadth[6] = 1.12; v_breadth[7] = 4.8; v_breadth[8] = 9.6; v_breadth[9] = 25.77; 
    v_breadth[10] = 30.0;

    lasd::Vector<double> v_pre(11);
    v_pre[0] = 10.6;
    v_pre[1] = 9.5; v_pre[2] = 3.0; v_pre[3] = 1.12; v_pre[4] = 4.8; v_pre[5] = 10.1; v_pre[6] = 9.6; 
    v_pre[7] = 15.2; v_pre[8] = 17.0; v_pre[9] = 25.77; v_pre[10] = 30.0;

    lasd::Vector<double> v_in(11);
    v_in[0] = 1.12; v_in[1] = 3.0; v_in[2] = 4.8; v_in[3] = 9.5; v_in[4] = 9.6; v_in[5] = 10.1;
    v_in[6] = 10.6; 
    v_in[7] = 15.2; v_in[8] = 17.0; v_in[9] = 25.77; v_in[10] = 30.0;

    lasd::Vector<double> v_post(11);
    v_post[0] = 1.12; v_post[1] = 4.8; v_post[2] = 3.0; v_post[3] = 9.6; v_post[4] = 10.1; v_post[5] = 9.5;
    v_post[6] = 30.0; v_post[7] = 25.77; v_post[8] = 17.0; v_post[9] = 15.2; 
    v_post[10] = 10.6;

    lasd::BST<double> bst;
    InsertAllC<double>(loctestnum, loctesterr, bst, true, v);

    lasd::BST<double> bst_copy(bst);
    lasd::BST<double> bst_move(move(bst_copy));

    SuccessorNRemove<double>(loctestnum, loctesterr, bst, true, 10.5, 10.6); 
    Root(loctestnum, loctesterr, bst, true, 15.2);

    PredecessorNRemove<double>(loctestnum, loctesterr, bst, true, 15.2, 10.1);
    InsertSomeC<double>(loctestnum, loctesterr, bst, true, v);
    TraversePreOrder<double>(loctestnum, loctesterr, bst, true, &TraversePrint<double>);

    Root(loctestnum, loctesterr, bst, true, 15.2);
    TraverseInOrder<double>(loctestnum, loctesterr, bst, true, &TraversePrint<double>);

    bst = bst_move;

    // iterators
    lasd::BTPreOrderIterator<double> it_pre(bst);
    Terminated<double>(loctestnum, loctesterr, it_pre, false);
    myTestiterator<double>(it_pre, loctestnum, loctesterr, v_pre);
    Terminated<double>(loctestnum, loctesterr, it_pre, true);
    it_pre.Reset();
    myTestiterator<double>(it_pre, loctestnum, loctesterr, v_pre);

    lasd::BTInOrderIterator<double> it_in(bst);
    Terminated<double>(loctestnum, loctesterr, it_in, false);
    myTestiterator<double>(it_in, loctestnum, loctesterr, v_in);
    Terminated<double>(loctestnum, loctesterr, it_in, true);
    it_in.Reset();
    myTestiterator<double>(it_in, loctestnum, loctesterr, v_in);

    lasd::BTPostOrderIterator<double> it_post(bst);
    Terminated<double>(loctestnum, loctesterr, it_post, false);
    myTestiterator<double>(it_post, loctestnum, loctesterr, v_post);
    Terminated<double>(loctestnum, loctesterr, it_post, true);
    it_post.Reset();
    myTestiterator<double>(it_post, loctestnum, loctesterr, v_post);

    lasd::BTBreadthIterator<double> it_breadth(bst);
    Terminated<double>(loctestnum, loctesterr, it_breadth, false);
    myTestiterator<double>(it_breadth, loctestnum, loctesterr, v_breadth);
    Terminated<double>(loctestnum, loctesterr, it_breadth, true);
    it_breadth.Reset();
    myTestiterator<double>(it_breadth, loctestnum, loctesterr, v_breadth);

    bst.Clear();
    Empty(loctestnum, loctesterr, bst, true);

    lasd::BTPreOrderIterator<double> it_pre2(bst);
    Terminated<double>(loctestnum, loctesterr, it_pre2, true);

    lasd::BTInOrderIterator<double> it_in2(bst);
    Terminated<double>(loctestnum, loctesterr, it_in2, true);

    lasd::BTPostOrderIterator<double> it_post2(bst);
    Terminated<double>(loctestnum, loctesterr, it_post2, true);

    lasd::BTBreadthIterator<double> it_breadth2(bst);
    Terminated<double>(loctestnum, loctesterr, it_breadth2, true);

    /* ************************************************************************************************* */

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
    lasd::List<string> l;
    InsertAtBack(loctestnum, loctesterr, l, true, string("A"));
    InsertAtBack(loctestnum, loctesterr, l, true, string("B"));
    InsertAtFront(loctestnum, loctesterr, l, true, string("C"));
    InsertAtFront(loctestnum, loctesterr, l, true, string("D"));
    InsertAtBack(loctestnum, loctesterr, l, true, string("E"));
    InsertAtBack(loctestnum, loctesterr, l, true, string("F"));

    lasd::Vector<string> v(l);
    lasd::BST<string> bst(move(v));
    lasd::BST<string> bst2(move(l));

    EqualBT<string>(loctestnum, loctesterr, bst, bst2);
    EqualBST<string>(loctestnum, loctesterr, bst, bst2);
    
    TraverseInOrder<string>(loctestnum, loctesterr, bst, true, &TraversePrint<string>);

    RemovePredecessor<string>(loctestnum, loctesterr, bst, true, string("E"));
    InsertC<string>(loctestnum, loctesterr, bst, true, string("D"));

    NonEqualBT<string>(loctestnum, loctesterr, bst, bst2);
    EqualBST<string>(loctestnum, loctesterr, bst, bst2);

    lasd::BTInOrderIterator<string> it_in(bst);
    Terminated<string>(loctestnum, loctesterr, it_in, false);
    GetItrValue<string>(loctestnum, loctesterr, it_in, true, string("A"));
    ++it_in;
    GetItrValue<string>(loctestnum, loctesterr, it_in, true, string("B"));
    ++it_in;
    GetItrValue<string>(loctestnum, loctesterr, it_in, true, string("C"));
    ++it_in;
    GetItrValue<string>(loctestnum, loctesterr, it_in, true, string("D"));
    ++it_in;
    GetItrValue<string>(loctestnum, loctesterr, it_in, true, string("E"));
    ++it_in;
    GetItrValue<string>(loctestnum, loctesterr, it_in, true, string("F"));
    Terminated<string>(loctestnum, loctesterr, it_in, false);
    ++it_in;
    Terminated<string>(loctestnum, loctesterr, it_in, true);

    FoldInOrder<string, string>(loctestnum, loctesterr, bst, true, &FoldStringConcatenate, string(""), string("ABCDEF"));

    /* ************************************************************************************************* */

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
  myTestBSTdouble(testnum, testerr);
  myTestBSTstring(testnum, testerr);
}

/* ************************************************************************** */

}