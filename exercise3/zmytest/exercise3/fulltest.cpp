
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

#define NUM_HT 1000 // Number of elements in the hash table
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
    lasd::HashTableClsAdr<int> htopnadr_empty;
    lasd::HashTableClsAdr<int> htopnadr2_empty;
    lasd::HashTableClsAdr<int> htopnadrcopy_empty{htopnadr_empty};
    lasd::HashTableClsAdr<int> htopnadrmove_empty{std::move(htopnadr_empty)};
    Empty(loctestnum, loctesterr, htopnadrcopy_empty, true);
    Size(loctestnum, loctesterr, htopnadr2_empty, true, 0);
    Exists(loctestnum, loctesterr, htopnadrmove_empty, false, 0);

    EqualHT(loctestnum, loctesterr, htopnadr2_empty, htopnadrcopy_empty);
    EqualHT(loctestnum, loctesterr, htopnadr2_empty, htopnadrmove_empty);
    EqualHT(loctestnum, loctesterr, htopnadrcopy_empty, htopnadrmove_empty);

    htopnadr_empty.Clear(); htopnadr2_empty.Clear(); htopnadrcopy_empty.Clear(); htopnadrmove_empty.Clear();

    /* ************************************************************************************************* */

    // HashTableOpnAdr with elements
    cout << endl << "\n~~~ HashTableOpnAdr with elements ~~~\n" << endl;
    lasd::Vector<int> vec2{NUM_HT};
    for (uint i = 0; i < NUM_HT; ++i) {
      vec2[i] = pow(-2, ((i % 15) + (i % 24)) % 30) + i; 
    }
    lasd::List<int> list2{vec2};

    lasd::HashTableOpnAdr<int> htopnadr{};
    for(uint i = 0; i < NUM_HT; ++i) {
      InsertC<int>(loctestnum, loctesterr, htopnadr, i);
      Exists<int>(loctestnum, loctesterr, htopnadr, true, i);
      Remove<int>(loctestnum, loctesterr, htopnadr, true, i);
      Exists<int>(loctestnum, loctesterr, htopnadr, false, i);
    }

    InsertC(loctestnum, loctesterr, htopnadr, vec2);
    myTestHTint(htopnadr, vec2, loctestnum, loctesterr);
    EqualHT(loctestnum, loctesterr, htopnadr, htopnadr);

    lasd::HashTableOpnAdr<int> htopnadr2{31};
    InsertM(loctestnum, loctesterr, htopnadr2, move(list2));
    list2 = vec2;

    lasd::HashTableOpnAdr<int> htopnadr3{vec2};
    EqualHT(loctestnum, loctesterr, htopnadr2, htopnadr3);

    lasd::HashTableOpnAdr<int> htopnadr4{static_cast<ulong>(pow(2, 2) - 1), list2};
    EqualHT(loctestnum, loctesterr, htopnadr2, htopnadr4);
    htopnadr4.Clear();

    lasd::HashTableOpnAdr<int> htopnadr5{move(vec2)};
    EqualHT(loctestnum, loctesterr, htopnadr3, htopnadr5);

    lasd::HashTableOpnAdr<int> htopnadr6{0, move(list2)};
    EqualHT(loctestnum, loctesterr, htopnadr6, htopnadr5);
    htopnadr6.Clear();

    lasd::HashTableOpnAdr<int> htopnadr_copy{htopnadr};
    NonEqualHT(loctestnum, loctesterr, htopnadr_copy, htopnadr3);
    Size(loctestnum, loctesterr, htopnadr_copy, true, htopnadr.Size());

    lasd::HashTableOpnAdr<int> htopnadr2_move{move(htopnadr2)};
    EqualHT(loctestnum, loctesterr, htopnadr2_move, htopnadr3);

    NonEqualHT(loctestnum, loctesterr, htopnadr2, htopnadr2_move);
    htopnadr2 = htopnadr5;
    EqualHT(loctestnum, loctesterr, htopnadr2, htopnadr2_move);

    htopnadr5.Resize(0);
    Exists(loctestnum, loctesterr, htopnadr5, false, 4);
    InsertC(loctestnum, loctesterr, htopnadr5, 4);
    NonEqualHT(loctestnum, loctesterr, htopnadr5, htopnadr3);
    htopnadr3 = move(htopnadr5);
    NonEqualHT(loctestnum, loctesterr, htopnadr2, htopnadr3); 

    /* ************************************************************************************************* */

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

void myTestHTdouble(lasd::HashTable<double> & ht, const lasd::LinearContainer<double> & con, uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;

  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<int> dis(5, 23);

  uint rand = dis(gen);

  try {
    Size(loctestnum, loctesterr, ht, true, con.Size());
    for(uint i = 0; i < con.Size(); ++i) {
      Exists(loctestnum, loctesterr, ht, true, con[i]);
    }
    for(uint i = 0; i < con.Size(); i += rand) {
      Remove(loctestnum, loctesterr, ht, true, con[i]);
    }
    Size(loctestnum, loctesterr, ht, true, con.Size() * (rand - 1) / rand);
    for(uint i = 0; i < con.Size(); ++i) {
      if(i % rand == 0) {
        Exists(loctestnum, loctesterr, ht, false, con[i]);
      } else {
        Exists(loctestnum, loctesterr, ht, true, con[i]);
      }
    }
    InsertSomeC(loctestnum, loctesterr, ht, true, con);
    Size(loctestnum, loctesterr, ht, true, con.Size());
    ht.Resize(0);
    Size(loctestnum, loctesterr, ht, true, con.Size());
    ht.Resize(1002);
    Size(loctestnum, loctesterr, ht, true, con.Size());
    RemoveAll(loctestnum, loctesterr, ht, true, con);
  } catch (exception & exc) {
    cout << exc.what() << endl;
    loctestnum++; 
    loctesterr++;
  }
  cout << "End of HashTable<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void myTestHTdouble(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of HashTable<double> Test:" << endl;

  try {
    cout << endl << "~ Begin of HashTable Close Addressing Test:" << endl;

    lasd::List<double> list;
    for (uint i = 0; i < 295; ++i) {
      list.InsertAtFront(pow(-2.12, (i * 2 % 30)) + i); 
    }
    lasd::Vector<double> vec{list};

    lasd::HashTableClsAdr<double> htclsadr{};
    InsertC(loctestnum, loctesterr, htclsadr, vec);
    myTestHTdouble(htclsadr, vec, loctestnum, loctesterr);
    EqualHT(loctestnum, loctesterr, htclsadr, htclsadr);

    lasd::HashTableClsAdr<double> htclsadr2{31};
    InsertM(loctestnum, loctesterr, htclsadr2, move(list));
    list = vec;

    lasd::HashTableClsAdr<double> htclsadr3{vec};
    EqualHT(loctestnum, loctesterr, htclsadr2, htclsadr3);

    lasd::HashTableClsAdr<double> htclsadr4{static_cast<ulong>(pow(2, 2) - 1), list};
    EqualHT(loctestnum, loctesterr, htclsadr2, htclsadr4);
    htclsadr4.Clear();

    lasd::HashTableClsAdr<double> htclsadr5{move(vec)};
    EqualHT(loctestnum, loctesterr, htclsadr3, htclsadr5);

    lasd::HashTableClsAdr<double> htclsadr6{0, move(list)};
    EqualHT(loctestnum, loctesterr, htclsadr6, htclsadr5);
    htclsadr6.Clear();

    lasd::HashTableClsAdr<double> htclsadr_copy{htclsadr};
    NonEqualHT(loctestnum, loctesterr, htclsadr_copy, htclsadr3);
    Size(loctestnum, loctesterr, htclsadr_copy, true, htclsadr.Size());

    lasd::HashTableClsAdr<double> htclsadr2_move{move(htclsadr2)};
    EqualHT(loctestnum, loctesterr, htclsadr2_move, htclsadr3);

    NonEqualHT(loctestnum, loctesterr, htclsadr2, htclsadr2_move);
    htclsadr2 = htclsadr5;
    EqualHT(loctestnum, loctesterr, htclsadr2, htclsadr2_move);

    htclsadr5.Resize(0);
    Exists(loctestnum, loctesterr, htclsadr5, false, 4.0);
    InsertC(loctestnum, loctesterr, htclsadr5, 4.0);
    NonEqualHT(loctestnum, loctesterr, htclsadr5, htclsadr3);
    htclsadr3 = move(htclsadr5);
    NonEqualHT(loctestnum, loctesterr, htclsadr2, htclsadr3); 

    vec.Clear(); list.Clear(); htclsadr_copy.Clear(); htclsadr2_move.Clear();
    htclsadr.Clear(); htclsadr2.Clear(); htclsadr3.Clear(); htclsadr4.Clear(); htclsadr5.Clear(); htclsadr6.Clear();

    /* ************************************************************************************************* */

    // HashTableOpnAdr Tests
    cout << endl << "~ Begin of HashTableOpmAdr<double> Test:" << endl;
    
    lasd::List<double> list2;
    for (uint i = 0; i < 295; ++i) {
      list2.InsertAtFront(pow(-2.12, (i * 2 % 30)) + i); 
    }
    lasd::Vector<double> vec2{list2};

    lasd::HashTableOpnAdr<double> htopnadr{};
    for(uint i = 0; i < NUM_HT; ++i) {
      InsertC<double>(loctestnum, loctesterr, htopnadr, i);
      Exists<double>(loctestnum, loctesterr, htopnadr, true, i);
      Remove<double>(loctestnum, loctesterr, htopnadr, true, i);
      Exists<double>(loctestnum, loctesterr, htopnadr, false, i);
    }

    InsertC(loctestnum, loctesterr, htopnadr, vec2);
    myTestHTdouble(htopnadr, vec2, loctestnum, loctesterr);
    EqualHT(loctestnum, loctesterr, htopnadr, htopnadr);

    lasd::HashTableOpnAdr<double> htopnadr2{31};
    InsertM(loctestnum, loctesterr, htopnadr2, move(list2));
    list2 = vec2;

    lasd::HashTableOpnAdr<double> htopnadr3{vec2};
    EqualHT(loctestnum, loctesterr, htopnadr2, htopnadr3);

    lasd::HashTableOpnAdr<double> htopnadr4{static_cast<ulong>(pow(2, 2) - 1), list2};
    EqualHT(loctestnum, loctesterr, htopnadr2, htopnadr4);
    htopnadr4.Clear();

    lasd::HashTableOpnAdr<double> htopnadr5{move(vec2)};
    EqualHT(loctestnum, loctesterr, htopnadr3, htopnadr5);

    lasd::HashTableOpnAdr<double> htopnadr6{0, move(list2)};
    EqualHT(loctestnum, loctesterr, htopnadr6, htopnadr5);
    htopnadr6.Clear();

    lasd::HashTableOpnAdr<double> htopnadr_copy{htopnadr};
    NonEqualHT(loctestnum, loctesterr, htopnadr_copy, htopnadr3);
    Size(loctestnum, loctesterr, htopnadr_copy, true, htopnadr.Size());

    lasd::HashTableOpnAdr<double> htopnadr2_move{move(htopnadr2)};
    EqualHT(loctestnum, loctesterr, htopnadr2_move, htopnadr3);

    NonEqualHT(loctestnum, loctesterr, htopnadr2, htopnadr2_move);
    htopnadr2 = htopnadr5;
    EqualHT(loctestnum, loctesterr, htopnadr2, htopnadr2_move);

    htopnadr5.Resize(0);
    Exists(loctestnum, loctesterr, htopnadr5, false, 0.0);
    InsertC(loctestnum, loctesterr, htopnadr5, 0.0);
    NonEqualHT(loctestnum, loctesterr, htopnadr5, htopnadr3);
    htopnadr3 = move(htopnadr5);
    NonEqualHT(loctestnum, loctesterr, htopnadr2, htopnadr3); 

    /* ************************************************************************************************* */

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

void myTestHTstring(lasd::HashTable<string> & ht, const lasd::LinearContainer<string> & con, uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;

  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<int> dis(5, 23);

  uint rand = dis(gen);

  try {
    Size(loctestnum, loctesterr, ht, true, con.Size());
    for(uint i = 0; i < con.Size(); ++i) {
      Exists(loctestnum, loctesterr, ht, true, con[i]);
    }
    for(uint i = 0; i < con.Size(); i+= rand) {
      Remove(loctestnum, loctesterr, ht, true, con[i]);
    }
    Size(loctestnum, loctesterr, ht, true, con.Size() * (rand - 1) / rand);
    for(uint i = 0; i < con.Size(); ++i) {
      if(i % rand == 0) {
        Exists(loctestnum, loctesterr, ht, false, con[i]);
      } else {
        Exists(loctestnum, loctesterr, ht, true, con[i]);
      }
    }
    InsertSomeC(loctestnum, loctesterr, ht, true, con);
    Size(loctestnum, loctesterr, ht, true, con.Size());
    ht.Resize(0);
    Size(loctestnum, loctesterr, ht, true, con.Size());
    ht.Resize(1002);
    Size(loctestnum, loctesterr, ht, true, con.Size());
    RemoveAll(loctestnum, loctesterr, ht, true, con);
  } catch (exception & exc) {
    cout << exc.what() << endl;
    loctestnum++; 
    loctesterr++;
  }
  cout << "End of HashTable<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

void myTestHTstring(uint & testnum, uint & testerr) {
  uint loctestnum = 0, loctesterr = 0;
  cout << endl << "Begin of HashTable<string> Test:" << endl;

  try {
    cout << endl << "~ Begin of HashTable Close Addressing Test:" << endl;

    lasd::Vector<string> vec{306};
    for (uint i = 2; i < 303; ++i) {
      vec[i] = "String" + to_string(i);
    }
    vec[0] = "£"; vec[1] = "€"; vec[303] = "¥"; vec[304] = "₩"; vec[305] = "₱";
    lasd::List<string> list{vec};

    lasd::HashTableClsAdr<string> htclsadr{};
    InsertAllC(loctestnum, loctesterr, htclsadr, true, list);
    myTestHTstring(htclsadr, vec, loctestnum, loctesterr);
    EqualHT(loctestnum, loctesterr, htclsadr, htclsadr);

    lasd::HashTableClsAdr<string> htclsadr2{31};
    InsertM(loctestnum, loctesterr, htclsadr2, move(list));
    list = vec;

    lasd::HashTableClsAdr<string> htclsadr3{vec};
    EqualHT(loctestnum, loctesterr, htclsadr2, htclsadr3);

    lasd::HashTableClsAdr<string> htclsadr4{static_cast<ulong>(pow(2, 2) - 1), list};
    EqualHT(loctestnum, loctesterr, htclsadr2, htclsadr4);
    htclsadr4.Clear();

    lasd::HashTableClsAdr<string> htclsadr5{move(vec)};
    EqualHT(loctestnum, loctesterr, htclsadr3, htclsadr5);

    lasd::HashTableClsAdr<string> htclsadr6{0, move(list)};
    EqualHT(loctestnum, loctesterr, htclsadr6, htclsadr5);
    htclsadr6.Clear();

    lasd::HashTableClsAdr<string> htclsadr_copy{htclsadr};
    NonEqualHT(loctestnum, loctesterr, htclsadr_copy, htclsadr3);
    Size(loctestnum, loctesterr, htclsadr_copy, true, htclsadr.Size());

    lasd::HashTableClsAdr<string> htclsadr2_move{move(htclsadr2)};
    EqualHT(loctestnum, loctesterr, htclsadr2_move, htclsadr3);

    NonEqualHT(loctestnum, loctesterr, htclsadr2, htclsadr2_move);
    htclsadr2 = htclsadr5;
    EqualHT(loctestnum, loctesterr, htclsadr2, htclsadr2_move);

    htclsadr5.Resize(0);
    Exists(loctestnum, loctesterr, htclsadr5, false, string("4.0"));
    InsertC(loctestnum, loctesterr, htclsadr5, string("4.0"));
    NonEqualHT(loctestnum, loctesterr, htclsadr5, htclsadr3);
    htclsadr3 = move(htclsadr5);
    NonEqualHT(loctestnum, loctesterr, htclsadr2, htclsadr3); 

    vec.Clear(); list.Clear(); htclsadr_copy.Clear(); htclsadr2_move.Clear();
    htclsadr.Clear(); htclsadr2.Clear(); htclsadr3.Clear(); htclsadr4.Clear(); htclsadr5.Clear(); htclsadr6.Clear();

    /* ************************************************************************************************* */

    // HashTableOpnAdr Tests
    cout << endl << "~ Begin of HashTableOpmAdr<double> Test:" << endl;

    lasd::Vector<string> vec2{306};
    for (uint i = 2; i < 303; ++i) {
      vec2[i] = "String" + to_string(i);
    }
    vec2[0] = "£"; vec2[1] = "€"; vec2[303] = "¥"; vec2[304] = "₩"; vec2[305] = "₱";
    lasd::List<string> list2{vec2}, list3{list2};

    lasd::HashTableOpnAdr<string> htopnadr{};
    for(uint i = 0; i < 306; ++i) {
      InsertC<string>(loctestnum, loctesterr, htopnadr, to_string(i));
      Exists<string>(loctestnum, loctesterr, htopnadr, true, to_string(i));
      Remove<string>(loctestnum, loctesterr, htopnadr, true, to_string(i));
      Exists<string>(loctestnum, loctesterr, htopnadr, false, to_string(i));
    }
    InsertAllM(loctestnum, loctesterr, htopnadr, true, move(list3));
    myTestHTstring(htopnadr, vec2, loctestnum, loctesterr);
    EqualHT(loctestnum, loctesterr, htopnadr, htopnadr);

    lasd::HashTableOpnAdr<string> htopnadr2{31};
    InsertM(loctestnum, loctesterr, htopnadr2, move(list2));
    list2 = vec2;

    lasd::HashTableOpnAdr<string> htopnadr3{vec2};
    EqualHT(loctestnum, loctesterr, htopnadr2, htopnadr3);

    lasd::HashTableOpnAdr<string> htopnadr4{static_cast<ulong>(pow(2, 2) - 1), list2};
    EqualHT(loctestnum, loctesterr, htopnadr2, htopnadr4);
    htopnadr4.Clear();

    lasd::HashTableOpnAdr<string> htopnadr5{move(vec2)};
    EqualHT(loctestnum, loctesterr, htopnadr3, htopnadr5);

    lasd::HashTableOpnAdr<string> htopnadr6{0, move(list2)};
    EqualHT(loctestnum, loctesterr, htopnadr6, htopnadr5);
    htopnadr6.Clear();

    lasd::HashTableOpnAdr<string> htopnadr_copy{htopnadr};
    NonEqualHT(loctestnum, loctesterr, htopnadr_copy, htopnadr3);
    Size(loctestnum, loctesterr, htopnadr_copy, true, htopnadr.Size());

    lasd::HashTableOpnAdr<string> htopnadr2_move{move(htopnadr2)};
    EqualHT(loctestnum, loctesterr, htopnadr2_move, htopnadr3);

    NonEqualHT(loctestnum, loctesterr, htopnadr2, htopnadr2_move);
    htopnadr2 = htopnadr5;
    EqualHT(loctestnum, loctesterr, htopnadr2, htopnadr2_move);

    htopnadr5.Resize(0);
    Exists(loctestnum, loctesterr, htopnadr5, false, string("4.0"));
    InsertC(loctestnum, loctesterr, htopnadr5, string("4.0"));
    NonEqualHT(loctestnum, loctesterr, htopnadr5, htopnadr3);
    htopnadr3 = move(htopnadr5);
    NonEqualHT(loctestnum, loctesterr, htopnadr2, htopnadr3); 

    vec2.Clear(); list2.Clear(); htopnadr_copy.Clear(); htopnadr2_move.Clear();
    htopnadr.Clear(); htopnadr2.Clear(); htopnadr3.Clear(); htopnadr4.Clear(); htopnadr5.Clear(); htopnadr6.Clear();

    /* ************************************************************************************************* */

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
  myTestHTdouble(testnum, testerr);
  myTestHTstring(testnum, testerr);
}

/* ************************************************************************** */

}