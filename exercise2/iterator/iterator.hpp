
#ifndef ITERATOR_HPP
#define ITERATOR_HPP

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Iterator {

private:

protected:

public:

  // Destructor
  virtual ~Iterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  Iterator & operator=(const Iterator &) = delete;

  // Move assignment
  Iterator & operator=(Iterator &&) = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Iterator &) const noexcept = delete;
  bool operator!=(const Iterator &) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions

  virtual const Data & operator*() const = 0; // (non-mutable version; concrete function must throw std::out_of_range when terminated)

  virtual bool Terminated() const noexcept = 0;

};

/* ************************************************************************** */

template <typename Data>
class MutableIterator : virtual public Iterator<Data> {

private:

protected:

public:

  // Destructor
  virtual ~MutableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  MutableIterator & operator=(const MutableIterator &) = delete;

  // Move assignment
  MutableIterator & operator=(MutableIterator &&) = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const MutableIterator &) const noexcept = delete;
  bool operator!=(const MutableIterator &) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions

  using Iterator<Data>::operator*;
  virtual Data & operator*() = 0; // (mutable version; concrete function must throw std::out_of_range when terminated)

};

/* ************************************************************************** */

template <typename Data>
class ForwardIterator : virtual public Iterator<Data> {

private:

protected:

public:

  // Destructor
  virtual ~ForwardIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  ForwardIterator & operator=(const ForwardIterator &) = delete;

  // Move assignment 
  ForwardIterator & operator=(ForwardIterator &&) = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const ForwardIterator &) const noexcept = delete;
  bool operator!=(const ForwardIterator &) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions

  virtual ForwardIterator & operator++() = 0; // (concrete function must throw std::out_of_range when terminated)

};

/* ************************************************************************** */

template <typename Data>
class ResettableIterator : virtual public Iterator<Data> {

private:

protected:

public:

  // Destructor
  virtual ~ResettableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  ResettableIterator & operator=(const ResettableIterator &) = delete;

  // Move assignment
  ResettableIterator & operator=(ResettableIterator &&) = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const ResettableIterator &) const noexcept = delete;
  bool operator!=(const ResettableIterator &) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions

  virtual void Reset() noexcept = 0;

};

/* ************************************************************************** */

}

#endif
