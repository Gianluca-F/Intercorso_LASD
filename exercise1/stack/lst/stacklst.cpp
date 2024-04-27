
namespace lasd {

/* ************************************************************************** */

// Copy Assignment (StackLst)
template <typename Data>
inline StackLst<Data> & StackLst<Data>::operator=(const StackLst<Data> & stack) {
  List<Data>::operator=(stack);
  return *this;
}

// Move Assignment (StackLst)
template <typename Data>
inline StackLst<Data> & StackLst<Data>::operator=(StackLst<Data> && stack) noexcept {
  List<Data>::operator=(std::move(stack));
  return *this;
}

/* ************************************************************************** */

// Comparison operators (StackLst)

template <typename Data>
inline bool StackLst<Data>::operator==(const StackLst<Data> & stack) const noexcept {
  return List<Data>::operator==(stack);
}

template <typename Data>
inline bool StackLst<Data>::operator!=(const StackLst<Data> & stack) const noexcept {
  return !(*this == stack);
}

/* ************************************************************************** */

// Specific member functions (StackLst) (inherited from Stack)

template <typename Data>
inline const Data & StackLst<Data>::Top() const {
  if(size == 0)
    throw std::length_error("Stack is empty");
  return List<Data>::Front();
}

template <typename Data>
inline Data & StackLst<Data>::Top() {
  if(size == 0)
    throw std::length_error("Stack is empty");
  return List<Data>::Front();
}

template <typename Data>
inline void StackLst<Data>::Pop() {
  if(size == 0)
    throw std::length_error("Stack is empty");
  return List<Data>::RemoveFromFront();
}

template <typename Data>
inline Data StackLst<Data>::TopNPop() {
  if(size == 0)
    throw std::length_error("Stack is empty");
  return List<Data>::FrontNRemove();
}

template <typename Data>
inline void StackLst<Data>::Push(const Data & dat) {
  return List<Data>::InsertAtFront(dat);
}

template <typename Data>
inline void StackLst<Data>::Push(Data && dat) {
  return List<Data>::InsertAtFront(std::move(dat));
}

/* ************************************************************************** */

}