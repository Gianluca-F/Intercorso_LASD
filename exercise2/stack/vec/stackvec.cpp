
namespace lasd {

/* ************************************************************************** */

// Specific Constructors (StackVec)

template <typename Data>
StackVec<Data>::StackVec(const TraversableContainer<Data> & con) : Vector<Data>(con) {
  index = con.Size();
}

template <typename Data>
StackVec<Data>::StackVec(MappableContainer<Data> && con) : Vector<Data>(std::move(con)) {
  index = con.Size();
}

/* ************************************************************************** */

// Copy Constructor (StackVec)
template <typename Data>
StackVec<Data>::StackVec(const StackVec<Data> & stack) : Vector<Data>(stack), index(stack.index) {};

// Move Constructor (StackVec)
template <typename Data>
StackVec<Data>::StackVec(StackVec<Data> && stack) noexcept : Vector<Data>(std::move(stack)) {
  std::swap(index, stack.index);
}

/* ************************************************************************** */

// Copy Assignment (StackVec)
template <typename Data>
StackVec<Data> & StackVec<Data>::operator=(const StackVec<Data> & stack) {
  Vector<Data>::operator=(stack);
  index = stack.index;
  return *this;
}

// Move Assignment (StackVec)
template <typename Data>
StackVec<Data> & StackVec<Data>::operator=(StackVec<Data> && stack) noexcept {
  Vector<Data>::operator=(std::move(stack));
  std::swap(index, stack.index);
  return *this;
}

/* ************************************************************************** */

// Comparison operators (StackVec)
template <typename Data>
bool StackVec<Data>::operator==(const StackVec<Data> & stack) const noexcept {
  if (index != stack.index) {
    return false;
  }
  for (ulong i = 0; i < index; ++i) {
    if (Elements[i] != stack.Elements[i]) {
      return false;
    }
  }
  return true;
}

template <typename Data>
inline bool StackVec<Data>::operator!=(const StackVec<Data> & stack) const noexcept {
  return !(*this == stack);
}

/* ************************************************************************** */

// Specific member functions (StackVec) (inherited from Stack)

template <typename Data>
const Data & StackVec<Data>::Top() const {
  if (index == 0) {
    throw std::length_error("Stack is empty");
  }
  return Elements[index - 1];
}

template <typename Data>
Data & StackVec<Data>::Top() {
  if (index == 0) {
    throw std::length_error("Stack is empty");
  }
  return Elements[index - 1];
}

template <typename Data>
void StackVec<Data>::Pop() {
  if (index == 0) {
    throw std::length_error("Stack is empty");
  }
  Reduce();
  --index;
}

template <typename Data>
Data StackVec<Data>::TopNPop() {
  if (index == 0) {
    throw std::length_error("Stack is empty");
  }
  Reduce();
  return std::move(Elements[--index]);
}

template <typename Data>
void StackVec<Data>::Push(const Data & val) {
  Expand();
  Elements[index++] = val;
}

template <typename Data>
void StackVec<Data>::Push(Data && val) {
  Expand();
  Elements[index++] = std::move(val);
}

/* ************************************************************************** */

// Specific member functions (StackVec) (inherited from Container)

template <typename Data>
inline bool StackVec<Data>::Empty() const noexcept {
  return (index == 0);
}

template <typename Data>
inline ulong StackVec<Data>::Size() const noexcept {
  return index;
}

/* ************************************************************************** */

// Specific member functions (StackVec) (inherited from ClearableContainer)

template <typename Data>
void StackVec<Data>::Clear() {
  index = 0;
  Vector<Data>::Resize(DEFAULT_STACK_DIM);
}

/* ************************************************************************** */

// Auxiliary member functions

template <typename Data>
void StackVec<Data>::Expand() {
  if (index == size) {
    Vector<Data>::Resize(size * 1.5);
  }
}

template <typename Data>
void StackVec<Data>::Reduce() {
  if (index <= size / 4 && size > DEFAULT_STACK_DIM) {
    Vector<Data>::Resize(size / 1.5);
  }
}

/* ************************************************************************** */

}
