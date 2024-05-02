
#ifndef STACKVEC_HPP
#define STACKVEC_HPP 

/* ************************************************************************** */

#include "../stack.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

#ifndef DEFAULT_STACK_DIM
#define DEFAULT_STACK_DIM 10
#endif

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class StackVec : virtual public Stack<Data>, 
                 virtual protected Vector<Data> {

private:

protected:

  ulong index = 0;

  using Vector<Data>::size;
  using Vector<Data>::Elements;

public:

  // Default constructor
  StackVec() : Vector<Data>(DEFAULT_STACK_DIM) {};

  /* ************************************************************************ */

  // Specific constructor
  StackVec(const TraversableContainer<Data> & con);
  StackVec(MappableContainer<Data> && con);

  /* ************************************************************************ */

  // Copy constructor
  StackVec(const StackVec<Data> & stack);

  // Move constructor
  StackVec(StackVec<Data> && stack) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~StackVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  StackVec & operator=(const StackVec<Data> &);

  // Move assignment
  StackVec & operator=(StackVec<Data> &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const StackVec<Data> &) const noexcept;
  inline bool operator!=(const StackVec<Data> &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Stack)

  const Data & Top() const override; // (must throw std::length_error when empty)
  Data & Top() override; // (must throw std::length_error when empty)
  void Pop() override; // (must throw std::length_error when empty)
  Data TopNPop() override; // (must throw std::length_error when empty)
  void Push(const Data &) override;
  void Push(Data &&) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  inline bool Empty() const noexcept override;
  inline ulong Size() const noexcept override;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() override;

protected:

  // Auxiliary member functions

  void Expand();
  void Reduce();

};

/* ************************************************************************** */

}

#include "stackvec.cpp"

#endif
