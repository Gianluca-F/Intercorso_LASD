
#ifndef HTOPNADR_HPP
#define HTOPNADR_HPP

/* ************************************************************************** */

#include "../hashtable.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HashTableOpnAdr : virtual public HashTable<Data> {

private:

protected:

  using HashTable<Data>::size;
  using HashTable<Data>::tablesize;
  using HashTable<Data>::HashKey;

  enum class state : char {EMPTY = 0, FULL = 'F', DELETED = 'D'};
  Vector<Data> table{tablesize};
  Vector<state> states{tablesize}; 

public:

  // Default constructor
  HashTableOpnAdr() = default;

  /* ************************************************************************ */

  // Specific constructors
  HashTableOpnAdr(const ulong); // A hash table of a given size
  HashTableOpnAdr(const TraversableContainer<Data> &); // A hash table obtained from a TraversableContainer
  HashTableOpnAdr(const ulong, const TraversableContainer<Data> &); // A hash table of a given size obtained from a TraversableContainer
  HashTableOpnAdr(MappableContainer<Data> &&); // A hash table obtained from a MappableContainer
  HashTableOpnAdr(const ulong, MappableContainer<Data> &&); // A hash table of a given size obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  HashTableOpnAdr(const HashTableOpnAdr<Data> &);

  // Move constructor
  HashTableOpnAdr(HashTableOpnAdr<Data> &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~HashTableOpnAdr() = default;

  /* ************************************************************************ */

  // Copy assignment
  HashTableOpnAdr & operator=(const HashTableOpnAdr<Data> &);

  // Move assignment
  HashTableOpnAdr & operator=(HashTableOpnAdr<Data> &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HashTableOpnAdr<Data> &) const noexcept;
  inline bool operator!=(const HashTableOpnAdr<Data> &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  bool Insert(const Data &) override; // Copy of the value
  bool Insert(Data &&) override; // Move of the value
  bool Remove(const Data &) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)

  bool Exists(const Data &) const noexcept override;

  /* ************************************************************************ */

  // Specific member functions (inherited from ResizableContainer)

  void Resize(const ulong) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from ClearableContainer)

  void Clear() override;

protected:

  // Auxiliary member functions

  inline ulong HashKey(const ulong, const ulong) const noexcept;

  ulong Find(const Data &, ulong &) const noexcept;
  ulong FindEmpty(const Data &, ulong &) const noexcept; 
  bool Remove(const Data &, ulong &) noexcept;

  void Expand();
  void Reduce();

};

/* ************************************************************************** */

}

#include "htopnadr.cpp"

#endif
