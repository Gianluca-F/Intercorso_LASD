
#ifndef BINARYTREELNK_HPP
#define BINARYTREELNK_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeLnk : virtual public MutableBinaryTree<Data> {

private:

protected:

  using ClearableContainer::size;

public:

  using typename BinaryTree<Data>::Node;
  using typename MutableBinaryTree<Data>::MutableNode;

protected:

  struct NodeLnk : virtual public MutableNode { 
    
    NodeLnk * left = nullptr;
    NodeLnk * right = nullptr;
    Data element;

    /* ************************************************************************ */

    // Specific constructors

    NodeLnk(const Data &);
    NodeLnk(Data &&);

    /* ************************************************************************ */

    // Copy constructor
    NodeLnk(const NodeLnk &);

    // Move constructor
    NodeLnk(NodeLnk &&) noexcept;

    /* ************************************************************************ */

    // Destructor
    virtual ~NodeLnk();

    /* ************************************************************************ */

    // Copy assignment
    NodeLnk & operator=(const NodeLnk &);
    
    // Move assignment
    NodeLnk & operator=(NodeLnk &&) noexcept;

    /* ************************************************************************ */

    // Comparison operators
    inline bool operator==(const NodeLnk &) const noexcept;
    inline bool operator!=(const NodeLnk &) const noexcept;

    /* ************************************************************************ */

    // Specific member functions (inherited from Node)

    inline const Data & Element() const noexcept override;
    
    inline bool HasLeftChild() const noexcept override;
    inline bool HasRightChild() const noexcept override;

    virtual const Node & LeftChild() const override; // (throw std::out_of_range when not existent)
    virtual const Node & RightChild() const override; // (throw std::out_of_range when not existent)

    /* ************************************************************************ */

    // Specific member functions (inherited from MutableNode)

    inline Data & Element() noexcept override;

    virtual MutableNode & LeftChild() override; // (throw std::out_of_range when not existent)
    virtual MutableNode & RightChild() override; // (throw std::out_of_range when not existent)
    
  };

  /* ************************************************************************ */

  NodeLnk * root = nullptr;

public:

  // Default constructor
  BinaryTreeLnk() = default;

  /* ************************************************************************ */

  // Specific constructors
  BinaryTreeLnk(const TraversableContainer<Data> &);
  BinaryTreeLnk(MappableContainer<Data> &&);

  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeLnk(const BinaryTreeLnk<Data> &);

  // Move constructor
  BinaryTreeLnk(BinaryTreeLnk<Data> &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTreeLnk();

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeLnk & operator=(const BinaryTreeLnk<Data> &);

  // Move assignment
  BinaryTreeLnk & operator=(BinaryTreeLnk<Data> &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const BinaryTreeLnk<Data> &) const noexcept;
  inline bool operator!=(const BinaryTreeLnk<Data> &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  const Node & Root() const override; // (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from MutableBinaryTree)

  MutableNode & Root() override; // (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() override;

};

/* ************************************************************************** */

}

#include "binarytreelnk.cpp"

#endif
