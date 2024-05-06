
#ifndef VECTOR_HPP
#define VECTOR_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Vector : virtual public ResizableContainer, 
               virtual public LinearContainer<Data>{

private:

protected:

  using Container::size;

  Data * Elements = nullptr;

public:

  // Default constructor
  Vector() = default;

  /* ************************************************************************ */

  // Specific constructors
  Vector(const ulong); // A vector with a given initial dimension
  Vector(const TraversableContainer<Data> &); // A vector obtained from a TraversableContainer
  Vector(MappableContainer<Data> &&); // A vector obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  Vector(const Vector<Data> &);

  // Move constructor
  Vector(Vector<Data> &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~Vector();

  /* ************************************************************************ */

  // Copy assignment
  Vector & operator=(const Vector<Data> &);

  // Move assignment
  Vector & operator=(Vector<Data> &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Vector<Data> &) const noexcept;
  bool operator!=(const Vector<Data> &) const noexcept;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() override;

  /* ************************************************************************ */

  // Specific member function (inherited from ResizableContainer)

  void Resize(const ulong) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  // Override (NonMutable) LinearContainer member (must throw std::out_of_range when out of range)
  const Data & operator[](const ulong) const override;
  // Override (Mutable) LinearContainer member (must throw std::out_of_range when out of range)
  Data & operator[](const ulong) override;

  // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  const Data & Front() const override;
  // Override (Mutable) LinearContainer member (must throw std::length_error when empty)
  Data & Front() override; 

  // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  const Data & Back() const override;
  // Override (Mutable) LinearContainer member (must throw std::length_error when empty)
  Data & Back() override; 

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

template <typename Data>
class SortableVector : virtual public Vector<Data>, 
                       virtual public SortableLinearContainer<Data> {

private:

protected:

  // using Container::???;

public:

  // Default constructor
  SortableVector() = default;

  /* ************************************************************************ */

  // Specific constructors
  SortableVector(const ulong); // A vector with a given initial dimension
  
  SortableVector(const TraversableContainer<Data> &); // A vector obtained from a TraversableContainer
  SortableVector(MappableContainer<Data> &&); // A vector obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  SortableVector(const SortableVector<Data> &);

  // Move constructor
  SortableVector(SortableVector<Data> &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~SortableVector() = default;

  /* ************************************************************************ */

  // Copy assignment
  SortableVector & operator=(const SortableVector<Data> &);

  // Move assignment
  SortableVector & operator=(SortableVector<Data> &&) noexcept;

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "vector.cpp"

#endif
