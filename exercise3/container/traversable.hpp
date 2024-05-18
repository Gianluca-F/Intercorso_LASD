
#ifndef TRAVERSABLE_HPP
#define TRAVERSABLE_HPP

/* ************************************************************************** */

#include <functional>

/* ************************************************************************** */

#include "testable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class TraversableContainer : virtual public TestableContainer<Data> {

private:

protected:

public:

  // Destructor
  virtual ~TraversableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  TraversableContainer & operator=(const TraversableContainer &) = delete;

  // Move assignment
  TraversableContainer & operator=(TraversableContainer &&) = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const TraversableContainer &) const noexcept = delete;
  bool operator!=(const TraversableContainer &) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member function

  using TraverseFun = std::function<void(const Data &)>;

  virtual void Traverse(TraverseFun) const = 0;

  template <typename Accumulator>
  using FoldFun = std::function<Accumulator(const Data &, const Accumulator &)>;

  template <typename Accumulator>
  Accumulator Fold(FoldFun<Accumulator>, Accumulator) const;

  /* ************************************************************************ */

  // Specific member function (inherited from TestableContainer)

  inline bool Exists(const Data &) const noexcept override;

};

/* ************************************************************************** */

template <typename Data>
class PreOrderTraversableContainer : virtual public TraversableContainer<Data> {

private:

protected:

public:

  // Destructor
  virtual ~PreOrderTraversableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  PreOrderTraversableContainer & operator=(const PreOrderTraversableContainer &) = delete;

  // Move assignment
  PreOrderTraversableContainer & operator=(PreOrderTraversableContainer &&) = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const PreOrderTraversableContainer &) const = delete;
  bool operator!=(const PreOrderTraversableContainer &) const = delete;

  /* ************************************************************************ */
  
  // Specific member function

  using typename TraversableContainer<Data>::TraverseFun;

  virtual void PreOrderTraverse(TraverseFun) const = 0;

  template <typename Accumulator>
  using FoldFun = typename TraversableContainer<Data>::FoldFun<Accumulator>;

  template <typename Accumulator>
  Accumulator PreOrderFold(FoldFun<Accumulator>, Accumulator) const;

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  virtual void Traverse(TraverseFun) const override;

};

/* ************************************************************************** */

template <typename Data>
class PostOrderTraversableContainer : virtual public TraversableContainer<Data> {

private:

protected:

public:

  // Destructor
  virtual ~PostOrderTraversableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  PostOrderTraversableContainer & operator=(const PostOrderTraversableContainer &) = delete;

  // Move assignment
  PostOrderTraversableContainer & operator=(PostOrderTraversableContainer &&) = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const PostOrderTraversableContainer &) const = delete;
  bool operator!=(const PostOrderTraversableContainer &) const = delete;

  /* ************************************************************************ */

  // Specific member function

  using typename TraversableContainer<Data>::TraverseFun;

  virtual void PostOrderTraverse(TraverseFun) const = 0;

  template <typename Accumulator>
  using FoldFun = typename TraversableContainer<Data>::FoldFun<Accumulator>;

  template <typename Accumulator>
  Accumulator PostOrderFold(FoldFun<Accumulator>, Accumulator) const;

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  virtual void Traverse(TraverseFun) const override;

};

/* ************************************************************************** */

template <typename Data>
class InOrderTraversableContainer : virtual public TraversableContainer<Data> {

private:

protected:

public:

  // Destructor
  virtual ~InOrderTraversableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  InOrderTraversableContainer & operator=(const InOrderTraversableContainer &) = delete;

  // Move assignment
  InOrderTraversableContainer & operator=(InOrderTraversableContainer &&) = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const InOrderTraversableContainer &) const = delete;
  bool operator!=(const InOrderTraversableContainer &) const = delete;

  /* ************************************************************************ */

  // Specific member function

  using typename TraversableContainer<Data>::TraverseFun;

  virtual void InOrderTraverse(TraverseFun) const = 0;

  template <typename Accumulator>
  using FoldFun = typename TraversableContainer<Data>::FoldFun<Accumulator>;

  template <typename Accumulator>
  Accumulator InOrderFold(FoldFun<Accumulator>, Accumulator) const;

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  virtual void Traverse(TraverseFun) const override;

};

/* ************************************************************************** */

template <typename Data>
class BreadthTraversableContainer : virtual public TraversableContainer<Data> {

private:

protected:

public:

  // Destructor
  virtual ~BreadthTraversableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  BreadthTraversableContainer & operator=(const BreadthTraversableContainer &) = delete;

  // Move assignment
  BreadthTraversableContainer & operator=(BreadthTraversableContainer &&) = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BreadthTraversableContainer &) const = delete;
  bool operator!=(const BreadthTraversableContainer &) const = delete;

  /* ************************************************************************ */

  // Specific member function

  using typename TraversableContainer<Data>::TraverseFun;

  virtual void BreadthTraverse(TraverseFun) const = 0;

  template <typename Accumulator>
  using FoldFun = typename TraversableContainer<Data>::FoldFun<Accumulator>;

  template <typename Accumulator>
  Accumulator BreadthFold(FoldFun<Accumulator>, Accumulator) const;

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  virtual void Traverse(TraverseFun) const override;

};

/* ************************************************************************** */

}

#include "traversable.cpp"

#endif
