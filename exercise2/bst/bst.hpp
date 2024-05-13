
#ifndef BST_HPP
#define BST_HPP

/* ************************************************************************** */

#include "../binarytree/lnk/binarytreelnk.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BST : virtual public ClearableContainer,
            virtual public DictionaryContainer<Data>,
            virtual public BinaryTree<Data>,
            virtual protected BinaryTreeLnk<Data> {

private:

protected:

  using typename BinaryTreeLnk<Data>::NodeLnk;

  using BinaryTreeLnk<Data>::size;
  using BinaryTreeLnk<Data>::root;

public:

  // Default constructor
  BST() = default;

  /* ************************************************************************ */

  // Specific constructors
  BST(const TraversableContainer<Data> &);
  BST(MappableContainer<Data> &&);

  /* ************************************************************************ */

  // Copy constructor
  BST(const BST<Data> &);

  // Move constructor
  BST(BST<Data> &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BST() = default;

  /* ************************************************************************ */

  // Copy assignment
  BST & operator=(const BST<Data> &);

  // Move assignment
  BST & operator=(BST<Data> &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  using BinaryTreeLnk<Data>::InOrderTraverse;
  bool operator==(const BST<Data> &) const noexcept;
  inline bool operator!=(const BST<Data> &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

  const Data & Min() const; // (concrete function must throw std::length_error when empty)
  Data MinNRemove(); // (concrete function must throw std::length_error when empty)
  void RemoveMin(); // (concrete function must throw std::length_error when empty)

  const Data & Max() const; // (concrete function must throw std::length_error when empty)
  Data MaxNRemove(); // (concrete function must throw std::length_error when empty)
  void RemoveMax(); // (concrete function must throw std::length_error when empty)

  const Data & Predecessor(const Data &) const; // (concrete function must throw std::length_error when not found)
  Data PredecessorNRemove(const Data &); // (concrete function must throw std::length_error when not found)
  void RemovePredecessor(const Data &); // (concrete function must throw std::length_error when not found)

  const Data & Successor(const Data &) const; // (concrete function must throw std::length_error when not found)
  Data SuccessorNRemove(const Data &); // (concrete function must throw std::length_error when not found)
  void RemoveSuccessor(const Data &); // (concrete function must throw std::length_error when not found)

  /* ************************************************************************ */

  // Specific member function (inherited from BinaryTree)

  using BinaryTreeLnk<Data>::Root;

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  bool Insert(const Data &) override; // Copy of the value
  bool Insert(Data &&) override; // Move of the value
  bool Remove(const Data &) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)

  bool Exists(const Data &) const noexcept override;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  using BinaryTreeLnk<Data>::Clear;

protected:

  // Auxiliary functions, if necessary!

  Data DataNDelete(NodeLnk *) noexcept;
  
  NodeLnk * Detach(NodeLnk *&) noexcept;

  NodeLnk * DetachMin(NodeLnk *&) noexcept;
  NodeLnk * DetachMax(NodeLnk *&) noexcept;

  const NodeLnk * const & FindPointerToMin(const NodeLnk * const &) const noexcept;
  inline NodeLnk *& FindPointerToMin(NodeLnk *&) noexcept;

  const NodeLnk * const & FindPointerToMax(const NodeLnk * const &) const noexcept;
  inline NodeLnk *& FindPointerToMax(NodeLnk *&) noexcept;

  const NodeLnk * const & FindPointerTo(const NodeLnk * const &, const Data &) const noexcept;
  inline NodeLnk *& FindPointerTo(NodeLnk *&, const Data &) noexcept;

  const NodeLnk * const * FindPointerToPredecessor(const NodeLnk * const &, const Data &) const noexcept;
  inline NodeLnk ** FindPointerToPredecessor(NodeLnk *&, const Data &) noexcept;
  
  const NodeLnk * const * FindPointerToSuccessor(const NodeLnk * const &, const Data &) const noexcept;
  inline NodeLnk ** FindPointerToSuccessor(NodeLnk *&, const Data &) noexcept;

};

/* ************************************************************************** */

}

#include "bst.cpp"

#endif
