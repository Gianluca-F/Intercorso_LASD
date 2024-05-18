
#ifndef LIST_HPP
#define LIST_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/linear.hpp"
#include "../container/dictionary.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class List : virtual public ClearableContainer, 
             virtual public LinearContainer<Data>, 
             virtual public DictionaryContainer<Data> {

private:

protected:

  using Container::size;
  using TestableContainer<Data>::Exists;

  struct Node {

    Data element;
    Node * next = nullptr;

     /* ********************************************************************** */

    // Default constructor
    inline Node() = default;

    /* ********************************************************************** */

    // Specific constructors
    inline Node(const Data & dat) : element(dat) {};
    inline Node(Data && dat) noexcept : element(std::move(dat)) {};


    /* ********************************************************************** */

    // Copy constructor
    inline Node(const Node & nod) : element(nod.element) {};

    // Move constructor
    inline Node(Node && nod) noexcept : element(std::move(nod.element)) {};

    /* ********************************************************************** */

    // Destructor
    virtual ~Node() { delete next; };

    /* ********************************************************************** */

    // Comparison operators
    inline bool operator==(const Node &) const noexcept;
    inline bool operator!=(const Node &) const noexcept;

  };

  Node * head = nullptr;
  Node * tail = nullptr;

public:

  // Default constructor
  List() = default;

  /* ************************************************************************ */

  // Specific constructor
  List(const TraversableContainer<Data> &);
  List(MappableContainer<Data> &&);

  /* ************************************************************************ */

  // Copy constructor
  List(const List<Data> &);

  // Move constructor
  List(List<Data> &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~List() { delete head; };

  /* ************************************************************************ */

  // Copy assignment
  List & operator=(const List<Data> &);

  // Move assignment
  List & operator=(List<Data> &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const List<Data> &) const noexcept;
  inline bool operator!=(const List<Data> &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

  void InsertAtFront(const Data &);
  void InsertAtFront(Data &&);

  void RemoveFromFront(); // (must throw std::length_error when empty)
  Data FrontNRemove(); // (must throw std::length_error when empty)

  void InsertAtBack(const Data &);
  void InsertAtBack(Data &&);

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() override;

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  bool Insert(const Data &) override;
  bool Insert(Data &&) override;
  bool Remove(const Data &) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  const Data & operator[](const ulong) const override; // (must throw std::out_of_range when out of range)
  Data & operator[](const ulong) override; // (must throw std::out_of_range when out of range)
  
  inline const Data & Front() const override; // (must throw std::length_error when empty)
  inline Data & Front() override; // (must throw std::length_error when empty)
  
  inline const Data & Back() const override; // (must throw std::length_error when empty)
  inline Data & Back() override; // (must throw std::length_error when empty)

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

  // Specific member function (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFun;

  inline void Map(MapFun) override;

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)

  inline void PreOrderMap(MapFun) override;

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)

  inline void PostOrderMap(MapFun) override;

protected:

  // Auxiliary member functions (for TraversableContainer)

  void PreOrderTraverse(TraverseFun, const Node *) const;
  void PostOrderTraverse(TraverseFun, const Node *) const;

  /* ************************************************************************ */

  // Auxiliary member functions (for MappableContainer)

  void PreOrderMap(MapFun, Node *);
  void PostOrderMap(MapFun, Node *);

};

/* ************************************************************************** */

}

#include "list.cpp"

#endif
