
#ifndef QUEUEVEC_HPP
#define QUEUEVEC_HPP

/* ************************************************************************** */

#include "../queue.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

#ifndef DEFAULT_QUEUE_DIM
#define DEFAULT_QUEUE_DIM 10
#endif

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class QueueVec : virtual public Queue<Data>, 
                 virtual protected Vector<Data> {

private:

protected:

  ulong head = 0;
  ulong tail = 0;
  ulong numElmts = 0;

  using Vector<Data>::size;
  using Vector<Data>::Elements;

public:

  // Default constructor
  QueueVec() : Vector<Data>(DEFAULT_QUEUE_DIM) {};

  /* ************************************************************************ */

  // Specific constructor
  QueueVec(const TraversableContainer<Data> &);
  QueueVec(MappableContainer<Data> &&);

  /* ************************************************************************ */

  // Copy constructor
  QueueVec(const QueueVec<Data> &);

  // Move constructor
  QueueVec(QueueVec<Data> &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~QueueVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  QueueVec & operator=(const QueueVec<Data> &);

  // Move assignment
  QueueVec & operator=(QueueVec<Data> &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const QueueVec<Data> &) const noexcept;
  inline bool operator!=(const QueueVec<Data> &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Queue)

  const Data & Head() const override; // (must throw std::length_error when empty)
  Data & Head() override; // (must throw std::length_error when empty)
  void Dequeue() override; // (must throw std::length_error when empty)
  Data HeadNDequeue() override; // (must throw std::length_error when empty)
  void Enqueue(const Data &) override;
  void Enqueue(Data &&) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  inline bool Empty() const noexcept override;
  inline ulong Size() const noexcept override;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() override;

protected:

  // Auxiliary member functions

  inline void Expand();
  inline void Reduce();

  void Resize(ulong, ulong);

};

/* ************************************************************************** */

}

#include "queuevec.cpp"

#endif
