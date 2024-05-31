
#ifndef HTCLSADR_HPP
#define HTCLSADR_HPP

/* ************************************************************************** */

#include "../hashtable.hpp"
#include "../../vector/vector.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HashTableClsAdr : virtual public HashTable<Data> {

private:

protected:

  using HashTable<Data>::size;
  using HashTable<Data>::tablesize;
  using HashTable<Data>::HashKey;

  Vector<List<Data>> table{tablesize};

public:

  // Default constructor
  HashTableClsAdr() = default;

  /* ************************************************************************ */

  // Specific constructors
  HashTableClsAdr(const ulong); // A hash table of a given size
  HashTableClsAdr(const TraversableContainer<Data> &); // A hash table obtained from a TraversableContainer
  HashTableClsAdr(const ulong, const TraversableContainer<Data> &);  // A hash table of a given size obtained from a TraversableContainer
  HashTableClsAdr(MappableContainer<Data> &&); // A hash table obtained from a MappableContainer
  HashTableClsAdr(const ulong, MappableContainer<Data> &&); // A hash table of a given size obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  HashTableClsAdr(const HashTableClsAdr<Data> &);

  // Move constructor
  HashTableClsAdr(HashTableClsAdr<Data> &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~HashTableClsAdr() = default;

  /* ************************************************************************ */

  // Copy assignment
  HashTableClsAdr & operator=(const HashTableClsAdr<Data> &);

  // Move assignment
  HashTableClsAdr & operator=(HashTableClsAdr<Data> &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HashTableClsAdr<Data> &) const noexcept;
  inline bool operator!=(const HashTableClsAdr<Data> &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  bool Insert(const Data &) override; // Copy of the value
  bool Insert(Data &&) override; // Move of the value
  bool Remove(const Data &) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)

  inline bool Exists(const Data &) const noexcept override;

  /* ************************************************************************ */

  // Specific member functions (inherited from ResizableContainer)

  void Resize(const ulong) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from ClearableContainer)

  void Clear() override;

};

/* ************************************************************************** */

}

#include "htclsadr.cpp"

#endif
