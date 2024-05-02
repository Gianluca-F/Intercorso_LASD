
#ifndef STACKLST_HPP
#define STACKLST_HPP

/* ************************************************************************** */

#include "../stack.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class StackLst : virtual public Stack<Data>, 
                 virtual protected List<Data> {

private:

protected:

  using List<Data>::size;

public:

  // Default constructor
  StackLst() = default;

  /* ************************************************************************ */

  // Specific constructor
  StackLst(const TraversableContainer<Data> & con) : List<Data>(con) {};
  StackLst(MappableContainer<Data> && con) : List<Data>(std::move(con)) {};

  /* ************************************************************************ */

  // Copy constructor
  inline StackLst(const StackLst<Data> & stack) : List<Data>(stack) {};

  // Move constructor
  inline StackLst(StackLst<Data> && stack) noexcept : List<Data>(std::move(stack)) {};

  /* ************************************************************************ */

  // Destructor
  virtual ~StackLst() = default;

  /* ************************************************************************ */

  // Copy assignment
  inline StackLst & operator=(const StackLst &);

  // Move assignment
  inline StackLst & operator=(StackLst &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const StackLst<Data> &) const noexcept;
  inline bool operator!=(const StackLst<Data> &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Stack)

  inline const Data & Top() const override; // (must throw std::length_error when empty)
  inline Data & Top() override; // (must throw std::length_error when empty)
  inline void Pop() override; // (must throw std::length_error when empty)
  inline Data TopNPop() override; // (must throw std::length_error when empty)
  inline void Push(const Data &) override;
  inline void Push(Data &&) override;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  using List<Data>::Clear;

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "stacklst.cpp"

#endif
