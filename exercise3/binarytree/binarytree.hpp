
#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/mappable.hpp"

#include "../iterator/iterator.hpp"

#include "../stack/vec/stackvec.hpp"
// #include "../stack/lst/stacklst.hpp"
#include "../queue/vec/queuevec.hpp"
// #include "../queue/lst/queuelst.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTree : virtual public PreOrderTraversableContainer<Data>,
                   virtual public PostOrderTraversableContainer<Data>,
                   virtual public InOrderTraversableContainer<Data>,
                   virtual public BreadthTraversableContainer<Data> {

private:

protected:

  using Container::size;

public:

  struct Node {

  protected:

    // Comparison operators
    bool operator==(const Node &) const noexcept;
    inline bool operator!=(const Node &) const noexcept;

  public:

    friend class BinaryTree<Data>;

    /* ********************************************************************** */

    // Destructor
    virtual ~Node() = default;

    /* ********************************************************************** */

    // Copy assignment
    Node & operator=(const Node &) = delete;

    // Move assignment
    Node & operator=(Node &&) = delete;

    /* ********************************************************************** */

    // Specific member functions

    virtual inline const Data & Element() const noexcept = 0; // Immutable access to the element

    inline bool IsLeaf() const noexcept;
    virtual inline bool HasLeftChild() const noexcept = 0; 
    virtual inline bool HasRightChild() const noexcept = 0;

    virtual const Node & LeftChild() const = 0; // (concrete function must throw std::out_of_range when not existent)
    virtual const Node & RightChild() const = 0; // (concrete function must throw std::out_of_range when not existent)
    
  };

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTree() = default;

  /* ************************************************************************ */

  // Copy assignment
  BinaryTree & operator=(const BinaryTree<Data> &) = delete;

  // Move assignment
  BinaryTree & operator=(BinaryTree<Data> &&) = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTree<Data> &) const noexcept;
  inline bool operator!=(const BinaryTree<Data> &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

  virtual const Node & Root() const = 0; // (concrete function must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  using typename TraversableContainer<Data>::TraverseFun;

  inline void Traverse(TraverseFun) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)

  inline void PreOrderTraverse(TraverseFun) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)
  
  inline void PostOrderTraverse(TraverseFun) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from InOrderTraversableContainer)

  inline void InOrderTraverse(TraverseFun) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthTraversableContainer)

  inline void BreadthTraverse(TraverseFun) const override;

protected:

  // Auxiliary member functions (for TraversableContainer)

  void PreOrderTraverse(TraverseFun, const Node &) const;
  void PostOrderTraverse(TraverseFun, const Node &) const;
  void InOrderTraverse(TraverseFun, const Node &) const;
  void BreadthTraverse(TraverseFun, const Node &) const;

};

/* ************************************************************************** */

template <typename Data>
class MutableBinaryTree : virtual public ClearableContainer,
                          virtual public BinaryTree<Data>,
                          virtual public PreOrderMappableContainer<Data>,
                          virtual public PostOrderMappableContainer<Data>,
                          virtual public InOrderMappableContainer<Data>,
                          virtual public BreadthMappableContainer<Data> {

private:

protected:

public:

  struct MutableNode : virtual public BinaryTree<Data>::Node {

    friend class MutableBinaryTree<Data>;

    /* ********************************************************************** */

    // Destructor
    virtual ~MutableNode() = default;

    /* ********************************************************************** */

    // Copy assignment
    MutableNode & operator=(const MutableNode &) = delete;

    // Move assignment
    MutableNode & operator=(MutableNode &&) = delete;

    /* ********************************************************************** */

    // Specific member functions

    using BinaryTree<Data>::Node::Element;
    virtual inline Data & Element() noexcept = 0; // Mutable access to the element

    using BinaryTree<Data>::Node::LeftChild;
    virtual MutableNode & LeftChild() = 0; // (concrete function must throw std::out_of_range when not existent)
    using BinaryTree<Data>::Node::RightChild;
    virtual MutableNode & RightChild() = 0; // (concrete function must throw std::out_of_range when not existent)

  };

  /* ************************************************************************ */

  // Destructor
  virtual ~MutableBinaryTree() = default;

  /* ************************************************************************ */

  // Copy assignment
  MutableBinaryTree & operator=(const MutableBinaryTree<Data> &) = delete;

  // Move assignment
  MutableBinaryTree & operator=(MutableBinaryTree<Data> &&) = delete;

  /* ************************************************************************ */

  // Specific member functions

  using BinaryTree<Data>::Root;
  virtual MutableNode & Root() = 0; // (concrete function must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFun;

  inline void Map(MapFun) override;

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)

  inline void PreOrderMap(MapFun) override;

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)

  inline void PostOrderMap(MapFun) override;

  /* ************************************************************************ */

  // Specific member function (inherited from InOrderMappableContainer)

  inline void InOrderMap(MapFun) override;

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthMappableContainer)

  inline void BreadthMap(MapFun) override;

protected:

  // Auxiliary member functions (for MappableContainer)

  void PreOrderMap(MapFun, MutableNode &);
  void PostOrderMap(MapFun, MutableNode &);
  void InOrderMap(MapFun, MutableNode &);
  void BreadthMap(MapFun, MutableNode &);

};

/* ************************************************************************** */

template <typename Data>
class BTPreOrderIterator : virtual public ForwardIterator<Data>,
                           virtual public ResettableIterator<Data> {

private:

protected:

  const typename BinaryTree<Data>::Node * root = nullptr;
  StackVec<const typename BinaryTree<Data>::Node *> stack;

public:

  // Specific constructors
  BTPreOrderIterator(const BinaryTree<Data> &); // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTPreOrderIterator(const BTPreOrderIterator<Data> &);

  // Move constructor
  BTPreOrderIterator(BTPreOrderIterator<Data> &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BTPreOrderIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTPreOrderIterator & operator=(const BTPreOrderIterator<Data> &);

  // Move assignment
  BTPreOrderIterator & operator=(BTPreOrderIterator<Data> &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const BTPreOrderIterator<Data> &) const noexcept;
  inline bool operator!=(const BTPreOrderIterator<Data> &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  const Data & operator*() const override; // (throw std::out_of_range when terminated)

  inline bool Terminated() const noexcept override;

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  ForwardIterator<Data> & operator++() override; // (throw std::out_of_range when terminated)

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  void Reset() noexcept override;

};

/* ************************************************************************** */

template <typename Data>
class BTPreOrderMutableIterator : virtual public MutableIterator<Data>,
                                  virtual public BTPreOrderIterator<Data> {

private:

protected:

  using BTPreOrderIterator<Data>::stack;

public:

  // Specific constructors
  BTPreOrderMutableIterator(MutableBinaryTree<Data> & tree) : BTPreOrderIterator<Data>(tree) {}; // An iterator over a given mutable binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTPreOrderMutableIterator(const BTPreOrderMutableIterator<Data> & iterator) : BTPreOrderIterator<Data>(iterator) {};

  // Move constructor
  BTPreOrderMutableIterator(BTPreOrderMutableIterator<Data> && iterator) noexcept : BTPreOrderIterator<Data>(std::move(iterator)) {};

  /* ************************************************************************ */

  // Destructor
  virtual ~BTPreOrderMutableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTPreOrderMutableIterator & operator=(const BTPreOrderMutableIterator<Data> & iterator) {
    BTPreOrderIterator<Data>::operator=(iterator);
  }

  // Move assignment
  BTPreOrderMutableIterator & operator=(BTPreOrderMutableIterator<Data> && iterator) noexcept {
    BTPreOrderIterator<Data>::operator=(std::move(iterator));
  }

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const BTPreOrderMutableIterator<Data> & iterator) const noexcept {
    return BTPreOrderIterator<Data>::operator==(iterator);
  }

  inline bool operator!=(const BTPreOrderMutableIterator<Data> & iterator) const noexcept {
    return BTPreOrderIterator<Data>::operator!=(iterator);
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)

  Data & operator*() override; // (throw std::out_of_range when terminated)

};

/* ************************************************************************** */

template <typename Data>
class BTPostOrderIterator : virtual public ForwardIterator<Data>,
                            virtual public ResettableIterator<Data> {

private:

protected:

  const typename BinaryTree<Data>::Node * root = nullptr;
  StackVec<const typename BinaryTree<Data>::Node *> stack;

public:

  // Specific constructors
  BTPostOrderIterator(const BinaryTree<Data> &); // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTPostOrderIterator(const BTPostOrderIterator<Data> &);

  // Move constructor
  BTPostOrderIterator(BTPostOrderIterator<Data> &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BTPostOrderIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTPostOrderIterator & operator=(const BTPostOrderIterator<Data> &);

  // Move assignment
  BTPostOrderIterator & operator=(BTPostOrderIterator<Data> &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const BTPostOrderIterator<Data> &) const noexcept;
  inline bool operator!=(const BTPostOrderIterator<Data> &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  const Data & operator*() const override; // (throw std::out_of_range when terminated)

  inline bool Terminated() const noexcept override;

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  ForwardIterator<Data> & operator++() override; // (throw std::out_of_range when terminated)

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  void Reset() noexcept override;

  protected:

  // Auxiliary member functions (for ForwardIterator)

  void PushLeftLeaf(const typename BinaryTree<Data>::Node *);

};

/* ************************************************************************** */

template <typename Data>
class BTPostOrderMutableIterator : virtual public MutableIterator<Data>,
                                   virtual public BTPostOrderIterator<Data> {

private:

protected:

  using BTPostOrderIterator<Data>::stack;

public:

  // Specific constructors
  BTPostOrderMutableIterator(MutableBinaryTree<Data> & tree) : BTPostOrderIterator<Data>(tree) {}; // An iterator over a given mutable binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTPostOrderMutableIterator(const BTPostOrderMutableIterator<Data> & iterator) : BTPostOrderIterator<Data>(iterator) {};

  // Move constructor
  BTPostOrderMutableIterator(BTPostOrderMutableIterator<Data> && iterator) noexcept : BTPostOrderIterator<Data>(std::move(iterator)) {};

  /* ************************************************************************ */

  // Destructor
  virtual ~BTPostOrderMutableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTPostOrderMutableIterator & operator=(const BTPostOrderMutableIterator<Data> & iterator) {
    BTPostOrderIterator<Data>::operator=(iterator);
  }

  // Move assignment
  BTPostOrderMutableIterator & operator=(BTPostOrderMutableIterator<Data> && iterator) noexcept {
    BTPostOrderIterator<Data>::operator=(std::move(iterator));
  }

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const BTPostOrderMutableIterator<Data> & iterator) const noexcept {
    return BTPostOrderIterator<Data>::operator==(iterator);
  }

  inline bool operator!=(const BTPostOrderMutableIterator<Data> & iterator) const noexcept {
    return BTPostOrderIterator<Data>::operator!=(iterator);
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)

  Data & operator*() override; // (throw std::out_of_range when terminated)

};

/* ************************************************************************** */

template <typename Data>
class BTInOrderIterator : virtual public ForwardIterator<Data>,
                          virtual public ResettableIterator<Data> {

private:

protected:

  const typename BinaryTree<Data>::Node * root = nullptr;
  StackVec<const typename BinaryTree<Data>::Node *> stack;

public:

  // Specific constructors
  BTInOrderIterator(const BinaryTree<Data> &); // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTInOrderIterator(const BTInOrderIterator<Data> &);

  // Move constructor
  BTInOrderIterator(BTInOrderIterator<Data> &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BTInOrderIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTInOrderIterator & operator=(const BTInOrderIterator<Data> &);

  // Move assignment
  BTInOrderIterator & operator=(BTInOrderIterator<Data> &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const BTInOrderIterator<Data> &) const noexcept;
  inline bool operator!=(const BTInOrderIterator<Data> &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  const Data & operator*() const override; // (throw std::out_of_range when terminated)

  inline bool Terminated() const noexcept override;

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  ForwardIterator<Data> & operator++() override; // (throw std::out_of_range when terminated)

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  void Reset() noexcept override;

  protected:

  // Auxiliary member functions

  void PushLeftNode(const typename BinaryTree<Data>::Node *);

};

/* ************************************************************************** */

template <typename Data>
class BTInOrderMutableIterator : virtual public MutableIterator<Data>,
                                 virtual public BTInOrderIterator<Data> {

private:

protected:

  using BTInOrderIterator<Data>::stack;

public:

  // Specific constructors
  BTInOrderMutableIterator(MutableBinaryTree<Data> & tree) : BTInOrderIterator<Data>(tree) {}; // An iterator over a given mutable binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTInOrderMutableIterator(const BTInOrderMutableIterator<Data> & iterator) : BTInOrderIterator<Data>(iterator) {};

  // Move constructor
  BTInOrderMutableIterator(BTInOrderMutableIterator<Data> && iterator) noexcept : BTInOrderIterator<Data>(std::move(iterator)) {};

  /* ************************************************************************ */

  // Destructor
  virtual ~BTInOrderMutableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTInOrderMutableIterator & operator=(const BTInOrderMutableIterator<Data> & iterator) {
    BTInOrderIterator<Data>::operator=(iterator);
  }

  // Move assignment
  BTInOrderMutableIterator & operator=(BTInOrderMutableIterator<Data> && iterator) noexcept {
    BTInOrderIterator<Data>::operator=(std::move(iterator));
  }

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const BTInOrderMutableIterator<Data> & iterator) const noexcept {
    return BTInOrderIterator<Data>::operator==(iterator);
  }
  
  inline bool operator!=(const BTInOrderMutableIterator<Data> & iterator) const noexcept {
    return BTInOrderIterator<Data>::operator!=(iterator);
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)
  
  Data & operator*() override; // (throw std::out_of_range when terminated)

};

/* ************************************************************************** */

template <typename Data>
class BTBreadthIterator : virtual public ForwardIterator<Data>,
                          virtual public ResettableIterator<Data> {

private:

protected:

  const typename BinaryTree<Data>::Node * root = nullptr;
  QueueVec<const typename BinaryTree<Data>::Node *> queue;

public:

  // Specific constructors
  BTBreadthIterator(const BinaryTree<Data> &); // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTBreadthIterator(const BTBreadthIterator<Data> &);

  // Move constructor
  BTBreadthIterator(BTBreadthIterator<Data> &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BTBreadthIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTBreadthIterator & operator=(const BTBreadthIterator<Data> &);

  // Move assignment
  BTBreadthIterator & operator=(BTBreadthIterator<Data> &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const BTBreadthIterator<Data> &) const noexcept;
  inline bool operator!=(const BTBreadthIterator<Data> &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  const Data & operator*() const override; // (throw std::out_of_range when terminated)

  inline bool Terminated() const noexcept override;

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  ForwardIterator<Data> & operator++() override; // (throw std::out_of_range when terminated)

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  void Reset() noexcept override;

};

/* ************************************************************************** */

template <typename Data>
class BTBreadthMutableIterator : virtual public MutableIterator<Data>,
                                 virtual public BTBreadthIterator<Data> {

private:

protected:
  
  using BTBreadthIterator<Data>::queue;

public:

  // Specific constructors
  BTBreadthMutableIterator(MutableBinaryTree<Data> & tree) : BTBreadthIterator<Data>(tree) {}; // An iterator over a given mutable binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTBreadthMutableIterator(const BTBreadthMutableIterator<Data> & iterator) : BTBreadthIterator<Data>(iterator) {};

  // Move constructor
  BTBreadthMutableIterator(BTBreadthMutableIterator<Data> && iterator) noexcept : BTBreadthIterator<Data>(std::move(iterator)) {};

  /* ************************************************************************ */

  // Destructor
  virtual ~BTBreadthMutableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTBreadthMutableIterator & operator=(const BTBreadthMutableIterator<Data> & iterator) {
    BTBreadthIterator<Data>::operator=(iterator);
  }

  // Move assignment
  BTBreadthMutableIterator & operator=(BTBreadthMutableIterator<Data> && iterator) noexcept {
    BTBreadthIterator<Data>::operator=(std::move(iterator));
  }

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const BTBreadthMutableIterator<Data> & iterator) const noexcept {
    return BTBreadthIterator<Data>::operator==(iterator);
  }

  inline bool operator!=(const BTBreadthMutableIterator<Data> & iterator) const noexcept {
    return BTBreadthIterator<Data>::operator!=(iterator);
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)

  Data & operator*() override; // (throw std::out_of_range when terminated)

};

/* ************************************************************************** */

}

#include "binarytree.cpp"

#endif
