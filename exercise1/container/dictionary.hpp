
#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

/* ************************************************************************** */
#include "testable.hpp"
#include "traversable.hpp"
#include "mappable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class DictionaryContainer : virtual public TestableContainer<Data> {

private:

protected:

public:

  // Destructor
  virtual ~DictionaryContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  DictionaryContainer& operator=(const DictionaryContainer&) = delete;
  
  // Move assignment
  DictionaryContainer& operator=(DictionaryContainer &&) = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const DictionaryContainer &) const noexcept = delete;
  bool operator!=(const DictionaryContainer &) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions
 
  virtual bool Insert(const Data &) = 0; // Copy of the value
  virtual bool Insert(Data &&) = 0; // Move of the value
  virtual bool Remove(const Data &) = 0;

  // Copy of the value; From TraversableContainer; True if all are inserted
  inline virtual bool InsertAll(const TraversableContainer<Data> &);
  // Move of the value; From MappableContainer; True if all are inserted
  inline virtual bool InsertAll(MappableContainer<Data> &&);
  // From TraversableContainer; True if all are removed
  inline virtual bool RemoveAll(const TraversableContainer<Data> &);

  // Copy of the value; From TraversableContainer; True if some is inserted
  inline virtual bool InsertSome(const TraversableContainer<Data> &);
  // Move of the value; From MappableContainer; True if some is inserted
  inline virtual bool InsertSome(MappableContainer<Data> &&);
  // From TraversableContainer; True if some is removed
  inline virtual bool RemoveSome(const TraversableContainer<Data> &);

};

/* ************************************************************************** */

}

#include "dictionary.cpp"

#endif
