
#ifndef QUEUELST_HPP
#define QUEUELST_HPP

/* ************************************************************************** */

#include "../queue.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class QueueLst : virtual public Queue<Data>, 
                 virtual protected List<Data> {

private:

protected:

  using List<Data>::size;

public:

  // Default constructor
  QueueLst() = default;

  /* ************************************************************************ */

  // Specific constructor
  QueueLst(const TraversableContainer<Data> & con) : List<Data>(con) {};
  QueueLst(MappableContainer<Data> && con) : List<Data>(std::move(con)) {};

  /* ************************************************************************ */

  // Copy constructor
  inline QueueLst(const QueueLst<Data> & queue) : List<Data>(queue) {};

  // Move constructor
  inline QueueLst(QueueLst<Data> && queue) noexcept : List<Data>(std::move(queue)) {};

  /* ************************************************************************ */

  // Destructor
  virtual ~QueueLst() = default;

  /* ************************************************************************ */

  // Copy assignment
  inline QueueLst & operator=(const QueueLst<Data> &);

  // Move assignment
  inline QueueLst & operator=(QueueLst<Data> &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const QueueLst<Data> &) const noexcept;
  inline bool operator!=(const QueueLst<Data> &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Queue)

  inline const Data& Head() const override; // (must throw std::length_error when empty)
  inline Data& Head() override; // (must throw std::length_error when empty)
  inline void Dequeue() override; // (must throw std::length_error when empty)
  inline Data HeadNDequeue() override; // (must throw std::length_error when empty)
  inline void Enqueue(const Data &) override;
  inline void Enqueue(Data &&) override;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  using List<Data>::Clear;

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "queuelst.cpp"

#endif
