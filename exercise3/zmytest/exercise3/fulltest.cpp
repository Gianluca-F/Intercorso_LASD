
#include <iostream>

// /* ************************************************************************** */

#include "../../zlasdtest/container/container.hpp"
#include "../../zlasdtest/container/testable.hpp"
#include "../../zlasdtest/container/dictionary.hpp"
#include "../../zlasdtest/container/traversable.hpp"
#include "../../zlasdtest/container/mappable.hpp"
#include "../../zlasdtest/container/linear.hpp"

#include "../../zlasdtest/vector/vector.hpp"

#include "../../zlasdtest/list/list.hpp"

#include "../../zlasdtest/hashtable/hashtable.hpp"
#include "../../hashtable/clsadr/htclsadr.hpp"
#include "../../hashtable/opnadr/htopnadr.hpp"

/* ************************************************************************** */

#include <random>
#include <unordered_map>
#include <cmath>
#include <cstring>

/* ************************************************************************** */

#define NUM_HT 300 // Number of elements in the hash table
                    // (if it would not be a dictionary container)

/* ************************************************************************** */

using namespace std;

/* ************************************************************************** */

namespace mytest {

/* ************************************************************************** */

void myTestHTint(lasd::HashTable<int> & ht, const lasd::LinearContainer<int> & con, uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;

  uint removedCount = 0;
  uint duplicateCount = 0;
  std::unordered_map<int, int> frequencyMap; 

  // Mappa per tenere traccia delle frequenze dei valori
  for(uint i = 0; i < NUM_HT; ++i) {
      ++frequencyMap[con[i]];
  }

  // Conta quanti valori sono duplicati
  for(const auto & entry : frequencyMap) {
      if(entry.second > 1) {
          duplicateCount += (entry.second - 1);
      }
  }
  lasd::Vector<int> removedNums{duplicateCount};

  try {
    Size(loctestnum, loctesterr, ht, true, NUM_HT - duplicateCount);
    CountHT(loctestnum, loctesterr, ht, con, NUM_HT);

    for(uint i = 0; i < NUM_HT; ++i) {
      Exists(loctestnum, loctesterr, ht, true, con[i]);
    }

    for(uint i = 0; i < NUM_HT; ++i) {
      if(frequencyMap[con[i]] > 1) {
        Remove(loctestnum, loctesterr, ht, true, con[i]);
        frequencyMap[con[i]] = 0;
        removedNums[removedCount] = con[i];
        ++removedCount;
      }
    }

    Size(loctestnum, loctesterr, ht, true, NUM_HT - duplicateCount - removedCount);
    
    for(uint i = 0; i < NUM_HT; ++i) {
      if(frequencyMap[con[i]] == 0) {
        Exists(loctestnum, loctesterr, ht, false, con[i]);
      } else {
        Exists(loctestnum, loctesterr, ht, true, con[i]);
      }
    }

    for(uint i = 0; i < removedCount;) {
      InsertC(loctestnum, loctesterr, ht, removedNums[--removedCount]);
    }

    Size(loctestnum, loctesterr, ht, true, NUM_HT - duplicateCount);
    ht.Resize(12);
    Size(loctestnum, loctesterr, ht, true, NUM_HT - duplicateCount);
    ht.Resize(2004);
    Size(loctestnum, loctesterr, ht, true, NUM_HT - duplicateCount);
    ht.Resize(187);
    Size(loctestnum, loctesterr, ht, true, NUM_HT - duplicateCount);
    CountHT(loctestnum, loctesterr, ht, con, NUM_HT);

    const uint dimVec = 20;
    lasd::Vector<int> vec(dimVec);
    for (uint i = 0; i < dimVec/2; ++i) {
      vec[i] = vec[i + dimVec/2] = pow(-2, ((i % 15) + (i % 24)) % 30) + i; 
    }
    CountHT(loctestnum, loctesterr, ht, vec, dimVec);

    for(uint i = 0; i < dimVec/4; ++i) {
      Remove(loctestnum, loctesterr, ht, true, vec[i]);
      Remove(loctestnum, loctesterr, ht, false, vec[i + dimVec/2]);
    }

    ht.Resize(0);
    CountHT(loctestnum, loctesterr, ht, vec, dimVec/2);
    Size(loctestnum, loctesterr, ht, true, NUM_HT - duplicateCount - dimVec/4);
    ht.Clear();
    CountHT(loctestnum, loctesterr, ht, vec, 0);
    Size(loctestnum, loctesterr, ht, true, 0);
    Empty(loctestnum, loctesterr, ht, true);
    InsertM(loctestnum, loctesterr, ht, move(vec)); vec.Clear();
    Size(loctestnum, loctesterr, ht, true, dimVec/2);
    CountHT(loctestnum, loctesterr, ht, vec, 0);

  } catch (exception & exc) {
    cout << exc.what() << endl;
    loctestnum++;
    loctesterr++;
  }
  cout << "End of HashTable<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */

void myTestHTint(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of HashTable<int> Test:" << endl;

  try {
    // HashTableClsAdr Tests
    cout << endl << "~ Begin of HashTableClsAdr<int> Test:" << endl;

    // HashTableClsAdr empty
    cout << endl << "\n~~~ HashTableClsAdr empty ~~~\n" << endl;
    lasd::HashTableClsAdr<int> htclsadr_empty;
    lasd::HashTableClsAdr<int> htclsadr2_empty;
    lasd::HashTableClsAdr<int> htclsadrcopy_empty{htclsadr_empty};
    lasd::HashTableClsAdr<int> htclsadrmove_empty{std::move(htclsadr_empty)};
    Empty(loctestnum, loctesterr, htclsadrcopy_empty, true);
    Size(loctestnum, loctesterr, htclsadr2_empty, true, 0);
    Exists(loctestnum, loctesterr, htclsadrmove_empty, false, 0);

    EqualHT(loctestnum, loctesterr, htclsadr2_empty, htclsadrcopy_empty);
    EqualHT(loctestnum, loctesterr, htclsadr2_empty, htclsadrmove_empty);
    EqualHT(loctestnum, loctesterr, htclsadrcopy_empty, htclsadrmove_empty);

    htclsadr_empty.Clear(); htclsadr2_empty.Clear(); htclsadrcopy_empty.Clear(); htclsadrmove_empty.Clear();

    /* ************************************************************************************************* */
    
    // HashTableClsAdr with elements
    cout << endl << "\n~~~ HashTableClsAdr with elements ~~~\n" << endl;
    lasd::Vector<int> vec{NUM_HT};
    for (uint i = 0; i < NUM_HT; ++i) {
      vec[i] = pow(-2, ((i % 15) + (i % 24)) % 30) + i; 
    }
    lasd::List<int> list{vec};

    lasd::HashTableClsAdr<int> htclsadr{};
    InsertC(loctestnum, loctesterr, htclsadr, vec);
    myTestHTint(htclsadr, vec, loctestnum, loctesterr);
    EqualHT(loctestnum, loctesterr, htclsadr, htclsadr);

    lasd::HashTableClsAdr<int> htclsadr2{31};
    InsertM(loctestnum, loctesterr, htclsadr2, move(list));
    list = vec;

    lasd::HashTableClsAdr<int> htclsadr3{vec};
    EqualHT(loctestnum, loctesterr, htclsadr2, htclsadr3);

    lasd::HashTableClsAdr<int> htclsadr4{static_cast<ulong>(pow(2, 2) - 1), list};
    EqualHT(loctestnum, loctesterr, htclsadr2, htclsadr4);
    htclsadr4.Clear();

    lasd::HashTableClsAdr<int> htclsadr5{move(vec)};
    EqualHT(loctestnum, loctesterr, htclsadr3, htclsadr5);

    lasd::HashTableClsAdr<int> htclsadr6{0, move(list)};
    EqualHT(loctestnum, loctesterr, htclsadr6, htclsadr5);
    htclsadr6.Clear();

    lasd::HashTableClsAdr<int> htclsadr_copy{htclsadr};
    NonEqualHT(loctestnum, loctesterr, htclsadr_copy, htclsadr3);
    Size(loctestnum, loctesterr, htclsadr_copy, true, htclsadr.Size());

    lasd::HashTableClsAdr<int> htclsadr2_move{move(htclsadr2)};
    EqualHT(loctestnum, loctesterr, htclsadr2_move, htclsadr3);

    NonEqualHT(loctestnum, loctesterr, htclsadr2, htclsadr2_move);
    htclsadr2 = htclsadr5;
    EqualHT(loctestnum, loctesterr, htclsadr2, htclsadr2_move);

    htclsadr5.Resize(0);
    Exists(loctestnum, loctesterr, htclsadr5, false, 4);
    InsertC(loctestnum, loctesterr, htclsadr5, 4);
    NonEqualHT(loctestnum, loctesterr, htclsadr5, htclsadr3);
    htclsadr3 = move(htclsadr5);
    NonEqualHT(loctestnum, loctesterr, htclsadr2, htclsadr3); 

    vec.Clear(); list.Clear(); htclsadr_copy.Clear(); htclsadr2_move.Clear();
    htclsadr.Clear(); htclsadr2.Clear(); htclsadr3.Clear(); htclsadr4.Clear(); htclsadr5.Clear(); htclsadr6.Clear();

    /* ************************************************************************************************* */

    // HashTableOpnAdr Tests
    cout << endl << "~ Begin of HashTableOpmAdr<int> Test:" << endl;

    // HashTableOpnAdr empty
    cout << endl << "\n~~~ HashTableOpnAdr empty ~~~\n" << endl;


  } catch (exception & exc) {
    cout << exc.what() << endl;
    loctestnum++;
    loctesterr++;
  }

  testerr += loctesterr;
  testnum += loctestnum;
  cout << endl << "HashTable<int> (Error/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}

/* ************************************************************************** */

void myTestHTdouble(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of HashTable<double> Test:" << endl;

  try {
    cout << endl << "~ Begin of HashTable Close Addressing Test:" << endl;

  } catch (exception & exc) {
    cout << exc.what() << endl;
    loctestnum++;
    loctesterr++;
  }

  testerr += loctesterr;
  testnum += loctestnum;
  cout << endl << "HashTable<double> (Error/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}

/* ************************************************************************** */

void myTestHTstring(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of HashTable<string> Test:" << endl;

  try {
    cout << endl << "~ Begin of HashTable Close Addressing Test:" << endl;

  } catch (exception & exc) {
    cout << exc.what() << endl;
    loctestnum++;
    loctesterr++;
  }

  testerr += loctesterr;
  testnum += loctestnum;
  cout << endl << "HashTable<string> (Error/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}

/* ************************************************************************** */

void myTestFullExercise3(uint & testnum, uint & testerr) {
  myTestHTint(testnum, testerr);
  // myTestHTdouble(testnum, testerr);
  // myTestHTstring(testnum, testerr);
}

/* ************************************************************************** */

}