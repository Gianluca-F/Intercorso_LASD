
namespace lasd {

/* ************************************************************************** */

// Specific constructors (Vector)

template<typename Data>
Vector<Data>::Vector(const ulong newSize) {
  size = newSize;
  Elements = new Data[size] {};
}

template<typename Data>
Vector<Data>::Vector(const TraversableContainer<Data> & con) : Vector(con.Size()){
  ulong i = 0;
  con.Traverse(
    [this, &i](const Data& data){
      Elements[i++] = data;
    }
  );
}

template<typename Data>
Vector<Data>::Vector(MappableContainer<Data> && con) : Vector(con.Size()){
  ulong i = 0;
  con.Map(
    [this, &i](Data& data){
      Elements[i++] = std::move(data);
    }
  );
}

/* ************************************************************************** */

// Copy constructor (Vector)
template<typename Data>
Vector<Data>::Vector(const Vector<Data> & vec) : Vector(vec.size) {
  std::copy(vec.Elements, vec.Elements + vec.size, Elements);
}

// Move constructor (Vector)
template<typename Data>
Vector<Data>::Vector(Vector<Data> && vec) noexcept {
  std::swap(size, vec.size);
  std::swap(Elements, vec.Elements);
}

/* ************************************************************************** */

// Destructor (Vector)
template<typename Data>
Vector<Data>::~Vector() {
  delete[] Elements;
}

/* ************************************************************************** */

// Copy assignment (Vector)
template<typename Data>
Vector<Data> & Vector<Data>::operator=(const Vector<Data> & vec) {
  Vector<Data> * tmpvec = new Vector<Data>(vec);
  std::swap(*tmpvec, *this);
  delete tmpvec;
  return *this;
}

// Move assignment (Vector)
template<typename Data>
Vector<Data> & Vector<Data>::operator=(Vector<Data> && vec) noexcept {
  std::swap(size, vec.size);
  std::swap(Elements, vec.Elements);
  return *this;
}

/* ************************************************************************** */

// Comparison operators (Vector)

template<typename Data>
bool Vector<Data>::operator==(const Vector<Data> & vec) const noexcept {
  if(size != vec.size){
    return false;
  }
  for(ulong i = 0; i < size; ++i){
    if(Elements[i] != vec.Elements[i]){
      return false;
    }
  }
  return true;
}

template<typename Data>
inline bool Vector<Data>::operator!=(const Vector<Data> & vec) const noexcept {
  return !(*this == vec);
}

/* ************************************************************************** */

// Specific member functions (Vector) (inherited from ClearableContainer)

template<typename Data>
void Vector<Data>::Clear() {
  delete[] Elements;
  Elements = nullptr;
  size = 0;
}

/* ************************************************************************** */

// Specific member functions (Vector) (inherited from ResizableContainer)

template<typename Data>
void Vector<Data>::Resize(const ulong newSize) {
  if(newSize == 0) {
    Clear();
  } else if(newSize != size) {
    Data * tmpElements = new Data[newSize] {};
    ulong minSize = std::min(size, newSize);

    for (ulong i = 0; i < minSize; ++i) {
      std::swap(Elements[i], tmpElements[i]);
    }

    std::swap(Elements, tmpElements);
    size = newSize;
    delete[] tmpElements;
  }
}

/* ************************************************************************** */

// Specific member functions (Vector) (inherited from LinearContainer)

template<typename Data>
const Data & Vector<Data>::operator[](const ulong i) const {
  if(i < size){
    return Elements[i];
  }
  throw std::out_of_range("Access at index " + std::to_string(i) + "; vector size is " + std::to_string(size) + "!");
}

template<typename Data>
Data & Vector<Data>::operator[](const ulong i) {
  if(i < size){
    return Elements[i];
  }
  throw std::out_of_range("Access at index " + std::to_string(i) + "; vector size is " + std::to_string(size) + "!");
}

template<typename Data>
const Data & Vector<Data>::Front() const {
  if(size != 0){
    return Elements[0];
  }
  throw std::length_error("Access to front element of an empty vector!");
}

template<typename Data>
Data & Vector<Data>::Front() {
  if(size != 0){
    return Elements[0];
  }
  throw std::length_error("Access to front element of an empty vector!");
}

template<typename Data>
const Data & Vector<Data>::Back() const {
  if(size != 0){
    return Elements[size - 1];
  }
  throw std::length_error("Access to back element of an empty vector!");
}

template<typename Data>
Data & Vector<Data>::Back() {
  if(size != 0){
    return Elements[size - 1];
  }
  throw std::length_error("Access to back element of an empty vector!");
}

/* ************************************************************************** */

// Specific constructors (SortableVector)

template<typename Data>
SortableVector<Data>::SortableVector(const ulong newSize) : Vector<Data>(newSize) {}

template<typename Data>
SortableVector<Data>::SortableVector(const TraversableContainer<Data> & con) : Vector<Data>(con) {}

template<typename Data>
SortableVector<Data>::SortableVector(MappableContainer<Data> && con) : Vector<Data>(std::move(con)) {}

/* ************************************************************************** */

// Copy constructor (SortableVector)
template<typename Data>
SortableVector<Data>::SortableVector(const SortableVector<Data> & vec) : Vector<Data>(vec) {}

// Move constructor (SortableVector)
template<typename Data>
SortableVector<Data>::SortableVector(SortableVector<Data> && vec) noexcept : Vector<Data>(std::move(vec)) {}

/* ************************************************************************** */

// Copy assignment (SortableVector)
template<typename Data>
SortableVector<Data> & SortableVector<Data>::operator=(const SortableVector<Data> & vec) {
  Vector<Data>::operator=(vec);
  return *this;
}

// Move assignment (SortableVector)
template<typename Data>
SortableVector<Data> & SortableVector<Data>::operator=(SortableVector<Data> && vec) noexcept {
  Vector<Data>::operator=(std::move(vec));
  return *this;
}

/* ************************************************************************** */

}