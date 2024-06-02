
#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

/* ************************************************************************** */

#include <random>

/* ************************************************************************** */

#include "../container/dictionary.hpp"

/* ************************************************************************** */

#ifndef MIN_TABLESIZE
#define MIN_TABLESIZE 128
#endif

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Hashable {

public:
  
  ulong operator()(const Data &) const noexcept = 0;

};

/* ************************************************************************** */

template <typename Data>
class HashTable : virtual public ResizableContainer, 
                  virtual public DictionaryContainer<Data> {

private:

protected:

  using DictionaryContainer<Data>::size;

  ulong acoeff = 1;
  ulong bcoeff = 0;
  static const ulong prime = 4294967291; // Largest prime number that fits in 32 bits (2^32 - 5) (otherwise 1000000016531)

  std::default_random_engine gen = std::default_random_engine(std::random_device {}());
  std::uniform_int_distribution<ulong> dista = std::uniform_int_distribution<ulong>(1, prime - 1);
  std::uniform_int_distribution<ulong> distb = std::uniform_int_distribution<ulong>(0, prime - 1);

  static const Hashable<Data> constexpr enchash{};

  ulong tablesize = MIN_TABLESIZE;

  /* ************************************************************************ */

  // Default constructor
  HashTable();

  /* ************************************************************************ */

  // Copy constructor
  HashTable(const HashTable<Data> &);

  // Move constructor
  HashTable(HashTable<Data> &&) noexcept;

  /* ************************************************************************ */

  // Copy assignment
  HashTable & operator=(const HashTable<Data> &) noexcept;

  // Move assignment
  HashTable & operator=(HashTable<Data> &&) noexcept;

public:

  // Destructor
  virtual ~HashTable() = default;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HashTable &) const noexcept = delete;
  bool operator!=(const HashTable &) const noexcept = delete;

protected:

  // Auxiliary member functions

  virtual inline ulong HashKey(const Data &) const noexcept;

  virtual inline ulong HashKey(ulong) const noexcept;

};

/* ************************************************************************** */

}

#include "hashtable.cpp"

#endif
