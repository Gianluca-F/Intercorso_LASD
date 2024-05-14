
namespace lasd {

/* ************************************************************************** */

// Specific member functions(LinearContainer)

template <typename Data>
inline const Data& LinearContainer<Data>::Front() const {
  return operator[](0);
}

template <typename Data>
inline Data& LinearContainer<Data>::Front() {
  return operator[](0);
}

template <typename Data>
inline const Data& LinearContainer<Data>::Back() const {
  return operator[](size - 1);
}

template <typename Data>
inline Data& LinearContainer<Data>::Back() {
  return operator[](size - 1);
}

/* ************************************************************************** */

// Specific member functions (LinearContainer) (inherited from TraversableContainer)

template <typename Data>
inline void LinearContainer<Data>::Traverse(TraverseFun fun) const {
    PreOrderTraverse(fun);
}

/* ************************************************************************** */

// Specific member functions (LinearContainer) (inherited from PreOrderTraversableContainer)

template <typename Data>
inline void LinearContainer<Data>::PreOrderTraverse(TraverseFun fun) const {
  for(ulong i = 0; i < size; ++i){
    fun(operator[](i));
  }
}

/* ************************************************************************** */

// Specific member functions (LinearContainer) (inherited from PostOrderTraversableContainer)

template <typename Data>
inline void LinearContainer<Data>::PostOrderTraverse(TraverseFun fun) const {
  for(ulong i = size; i > 0; ){
    fun(operator[](--i));
  }
}

/* ************************************************************************** */

// Specific member functions (LinearContainer) (inherited from MappableContainer)

template <typename Data>
inline void LinearContainer<Data>::Map(MapFun fun) {
  PreOrderMap(fun);
}

/* ************************************************************************** */

// Specific member functions (LinearContainer) (inherited from PreOrderMappableContainer)

template <typename Data>
inline void LinearContainer<Data>::PreOrderMap(MapFun fun) {
  for(ulong i = 0; i < size; ++i){
    fun(operator[](i));
  }
}

/* ************************************************************************** */

// Specific member functions (LinearContainer) (inherited from PostOrderMappableContainer)

template <typename Data>
inline void LinearContainer<Data>::PostOrderMap(MapFun fun) {
  for(ulong i = size; i > 0; ){
    fun(operator[](--i));
  }
}

/* ************************************************************************** */

// Comparison operators (LinearContainer)

template <typename Data>
bool LinearContainer<Data>::operator==(const LinearContainer<Data>& linearContainer) const noexcept {
  if(size != linearContainer.size) { return false; }

  for(ulong i = 0; i < size; ++i){
    if(operator[](i) != linearContainer[i]) { return false; }
  }

  return true;
}

template <typename Data>
bool LinearContainer<Data>::operator!=(const LinearContainer<Data>& linearContainer) const noexcept {
 return !(*this == linearContainer);
}

/* ************************************************************************** */

// Specific member functions (SortableLinearContainer)

template <typename Data>
inline void SortableLinearContainer<Data>::Sort() noexcept {
  QuickSort(0, size - 1);
}

template <typename Data>
void SortableLinearContainer<Data>::QuickSort(ulong left, ulong right) noexcept {
  if(left < right){
    ulong q = Partition(left, right);
    QuickSort(left, q);
    QuickSort(q + 1, right);
  }
}

template <typename Data>
ulong SortableLinearContainer<Data>::Partition(ulong left, ulong right) noexcept {
  Data x = operator[](left);
  ulong i = left - 1;
  ulong j = right + 1;

  do{
    do{ ++i; } while(operator[](i) < x);
    do{ --j; } while(operator[](j) > x);

    if(i < j) { std::swap(operator[](i), operator[](j)); }
  }while(i < j);

  return j;
}

/* ************************************************************************** */

}