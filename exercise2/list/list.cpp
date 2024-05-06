
namespace lasd {

/* ************************************************************************** */

// Comparison operators (Node)

template <typename Data>
inline bool List<Data>::Node::operator==(const Node & node) const noexcept {
  return (element == node.element);
}

template <typename Data>
inline bool List<Data>::Node::operator!=(const Node & node) const noexcept {
  return !(*this == node);
}

/* ************************************************************************** */

// Specific constructors (List)

template <typename Data>
List<Data>::List(const TraversableContainer<Data> & con) {
  con.Traverse(
    [this](const Data & dat) {
      InsertAtBack(dat);
    }
  );
}

template <typename Data>
List<Data>::List(MappableContainer<Data> && con) {
  con.Map(
    [this](Data & dat) {
      InsertAtBack(std::move(dat));
    }
  );

}

/* ************************************************************************** */

// Copy constructor (List)
template <typename Data>
List<Data>::List(const List<Data> & lst) {
  if(lst.size != 0) {
    size = lst.size;
    head = new Node(*lst.head);
    tail = head;

    Node * tmp = lst.head->next;
    while (tmp) {
      tail->next = new Node(*tmp);
      tail = tail->next;
      tmp = tmp->next;
    }
  }
}

// Move constructor (List)
template <typename Data>
List<Data>::List(List<Data> && lst) noexcept {
  std::swap(head, lst.head);
  std::swap(tail, lst.tail);
  std::swap(size, lst.size);
}

/* ************************************************************************** */

// Copy assignment (List)
template <typename Data>
List<Data>& List<Data>::operator=(const List<Data> & lst) {
  if(this != &lst) {
    Clear();
    if(lst.size != 0) {
      size = lst.size;
      head = new Node(*lst.head);
      tail = head;

      Node * tmp = lst.head->next;
      while (tmp) {
        tail->next = new Node(*tmp);
        tail = tail->next;
        tmp = tmp->next;
      }
    }
  }
  return *this;
}

// Move assignment (List)
template <typename Data>
List<Data>& List<Data>::operator=(List<Data> && lst) noexcept {
  std::swap(head, lst.head);
  std::swap(tail, lst.tail);
  std::swap(size, lst.size);
  return *this;
}

/* ************************************************************************** */

// Comparison operators (List)
template <typename Data>
bool List<Data>::operator==(const List<Data> & lst) const noexcept {
  if(size != lst.size) return false;
  Node * tmp1 = head;
  Node * tmp2 = lst.head;

  while(tmp1 != nullptr) {
    if(tmp1->element != tmp2->element) return false;
    tmp1 = tmp1->next;
    tmp2 = tmp2->next;
  }
  return true;
}

template <typename Data>
inline bool List<Data>::operator!=(const List<Data> & lst) const noexcept {
  return !(*this == lst);
}

/* ************************************************************************** */

// Specific member functions (List)

template <typename Data>
void List<Data>::InsertAtFront(const Data & dat) {
  Node * tmp = new Node(dat);
  tmp->next = head;
  head = tmp;
  if(size == 0) tail = head;
  size++;
}

template <typename Data>
void List<Data>::InsertAtFront(Data && dat) {
  Node * tmp = new Node(std::move(dat));
  tmp->next = head;
  head = tmp;
  if(size == 0) tail = head;
  size++;
}

template <typename Data>
void List<Data>::RemoveFromFront() {
  if(size == 0) throw std::length_error("Access to an empty list");
  Node * tmp = head;
  if(size == 1) {
    head = tail = nullptr;
  } else {
    head = head->next;
  }
  tmp->next = nullptr;
  delete tmp;
  size--;
}

template <typename Data>
Data List<Data>::FrontNRemove() {
  if(size == 0) throw std::length_error("Access to an empty list");
  Data tmp = std::move(head->element);
  RemoveFromFront();
  return tmp;
}

template <typename Data>
void List<Data>::InsertAtBack(const Data & dat) {
  Node * tmp = new Node(dat);
  if(size == 0) {
    head = tail = tmp;
  } else {
    tail->next = tmp;
    tail = tmp;
  }
  size++;
}

template <typename Data>
void List<Data>::InsertAtBack(Data && dat) {
  Node * tmp = new Node(std::move(dat));
  if(size == 0) {
    head = tail = tmp;
  } else {
    tail->next = tmp;
    tail = tmp;
  }
  size++;
}

/* ************************************************************************** */

// Specific member functions (List) (inherited from ClearableContainer)

template <typename Data>
void List<Data>::Clear() {
  delete head;
  head = tail = nullptr;
  size = 0;
}

/* ************************************************************************** */

// Specific member functions (List) (inherited from DictionaryContainer)

template <typename Data>
bool List<Data>::Insert(const Data & dat) {
  if(Exists(dat)) return false;
  InsertAtBack(dat);
  return true;
}

template <typename Data>
bool List<Data>::Insert(Data && dat) {
  if(Exists(dat)) return false;
  InsertAtBack(std::move(dat));
  return true;
}

template <typename Data>
bool List<Data>::Remove(const Data & dat) {
  if(size == 0) return false;
  if(head->element == dat) {
    RemoveFromFront();
    return true;
  }

  Node * tmp1 = head->next;
  Node * tmp2 = head;
  while(tmp1) {
    if(tmp1->element == dat) {
      tmp2->next = tmp1->next;
      if(tail == tmp1) tail = tmp2;
      tmp1->next = nullptr;
      delete tmp1;
      size--;
      return true;
    }
    tmp2 = tmp1;
    tmp1 = tmp1->next;
  }
  return false;
}

/* ************************************************************************** */

// Specific member functions (List) (inherited from LinearContainer)

template <typename Data>
const Data & List<Data>::operator[](const ulong i) const {
  if(i >= size) throw std::out_of_range("Access at index" + std::to_string(i) + "; list size " + std::to_string(size) + "!");
  Node * tmp = head;
  for(ulong j = 0; j < i; j++) {
    tmp = tmp->next;
  }
  return tmp->element;
}

template <typename Data>
Data & List<Data>::operator[](const ulong i) {
  if(i >= size) throw std::out_of_range("Access at index" + std::to_string(i) + "; list size " + std::to_string(size) + "!");
  Node * tmp = head;
  for(ulong j = 0; j < i; j++) {
    tmp = tmp->next;
  }
  return tmp->element;
}

template <typename Data>
inline const Data & List<Data>::Front() const {
  if(size == 0) throw std::length_error("Access to an empty list");
  return head->element;
}

template <typename Data>
inline Data & List<Data>::Front() {
  if(size == 0) throw std::length_error("Access to an empty list");
  return head->element;
}

template <typename Data>
inline const Data & List<Data>::Back() const {
  if(size == 0) throw std::length_error("Access to an empty list");
  return tail->element;
}

template <typename Data>
inline Data & List<Data>::Back() {
  if(size == 0) throw std::length_error("Access to an empty list");
  return tail->element;
}

/* ************************************************************************** */

// Specific member functions (List) (inherited from TraversableContainer)

template <typename Data>
inline void List<Data>::Traverse(TraverseFun fun) const {
  PreOrderTraverse(fun, head);
}

/* ************************************************************************** */

// Specific member functions (List) (inherited from PreOrderTraversableContainer)

template <typename Data>
inline void List<Data>::PreOrderTraverse(TraverseFun fun) const {
  PreOrderTraverse(fun, head);
}

/* ************************************************************************** */

// Specific member functions (List) (inherited from PostOrderTraversableContainer)

template <typename Data>
inline void List<Data>::PostOrderTraverse(TraverseFun fun) const {
  PostOrderTraverse(fun, head);
}

/* ************************************************************************** */

// Specific member functions (List) (inherited from MappableContainer)

template <typename Data>
inline void List<Data>::Map(MapFun fun) {
  PreOrderMap(fun, head);
}

/* ************************************************************************** */

// Specific member functions (List) (inherited from PreOrderMappableContainer)

template <typename Data>
inline void List<Data>::PreOrderMap(MapFun fun) {
  PreOrderMap(fun, head);
}

/* ************************************************************************** */

// Specific member functions (List) (inherited from PostOrderMappableContainer)

template <typename Data>
inline void List<Data>::PostOrderMap(MapFun fun) {
  PostOrderMap(fun, head);
}

/* ************************************************************************** */

// Auxiliary member functions (List) (for TraversableContainer)

template <typename Data>
void List<Data>::PreOrderTraverse(TraverseFun fun, const Node * cur) const {
  if(cur) {
    fun(cur->element);
    PreOrderTraverse(fun, cur->next);
  }
}

template <typename Data>
void List<Data>::PostOrderTraverse(TraverseFun fun, const Node * cur) const {
  if(cur) {
    PostOrderTraverse(fun, cur->next);
    fun(cur->element);
  }
}

/* ************************************************************************** */

// Auxiliary member functions (List) (for MappableContainer)

template <typename Data>
void List<Data>::PreOrderMap(MapFun fun, Node * cur) {
  if(cur) {
    fun(cur->element);
    PreOrderMap(fun, cur->next);
  }
}

template <typename Data>
void List<Data>::PostOrderMap(MapFun fun, Node * cur) {
  if(cur) {
    PostOrderMap(fun, cur->next);
    fun(cur->element);
  }
}

/* ************************************************************************** */

}