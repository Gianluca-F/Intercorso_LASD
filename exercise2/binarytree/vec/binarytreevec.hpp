
#ifndef BINARYTREEVEC_HPP
#define BINARYTREEVEC_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeVec : virtual public MutableBinaryTree<Data> {

private:

protected:

  using ClearableContainer::size;

public:

  using typename BinaryTree<Data>::Node;
  using typename MutableBinaryTree<Data>::MutableNode;

protected:

  struct NodeVec : virtual public MutableNode {

    friend class BinaryTreeVec<Data>;

    /* ************************************************************************ */

    bool exists = false;
    Data element;

    ulong index;
    BinaryTreeVec<Data> * treeVec = nullptr;

    /* ************************************************************************ */

    // Specific constructors

    NodeVec(const Data &, const ulong, BinaryTreeVec<Data> *);
    NodeVec(Data &&, const ulong, BinaryTreeVec<Data> *);

    /* ************************************************************************ */

    // Copy constructor
    NodeVec(const NodeVec &);

    // Move constructor
    NodeVec(NodeVec &&) noexcept;

    /* ************************************************************************ */

    // Destructor
    virtual ~NodeVec();

    /* ************************************************************************ */

    // Copy assignment
    NodeVec & operator=(const NodeVec &);

    // Move assignment
    NodeVec & operator=(NodeVec &&) noexcept;

    /* ************************************************************************ */

    // Comparison operators
    inline bool operator==(const NodeVec &) const noexcept;
    inline bool operator!=(const NodeVec &) const noexcept;

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

  Vector<NodeVec *> tree {};

public:

  // Default constructor
  BinaryTreeVec() = default;

  /* ************************************************************************ */

  // Specific constructors
  BinaryTreeVec(const TraversableContainer<Data> &);
  BinaryTreeVec(MappableContainer<Data> &&);

  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeVec(const BinaryTreeVec<Data> &);

  // Move constructor
  BinaryTreeVec(BinaryTreeVec<Data> &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTreeVec();

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeVec & operator=(const BinaryTreeVec<Data> &);

  // Move assignment
  BinaryTreeVec & operator=(BinaryTreeVec<Data> &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTreeVec<Data> &) const noexcept;
  inline bool operator!=(const BinaryTreeVec<Data> &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  const Node & Root() const override; // (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from MutableBinaryTree)

  MutableNode & Root() override; // (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() override;

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthTraversableContainer)

  using typename TraversableContainer<Data>::TraverseFun;

  void BreadthTraverse(TraverseFun) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthMappableContainer)

  using typename MappableContainer<Data>::MapFun;

  void BreadthMap(MapFun) override;
  
protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "binarytreevec.cpp"

#endif
