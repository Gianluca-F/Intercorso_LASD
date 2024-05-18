
namespace lasd {

/* ************************************************************************** */

// Copy assignment (QueueLst)
template <typename Data>
inline QueueLst<Data> & QueueLst<Data>::operator=(const QueueLst<Data> & queue) {
  List<Data>::operator=(queue);
  return *this;
}

// Move assignment (QueueLst)
template <typename Data>
inline QueueLst<Data> & QueueLst<Data>::operator=(QueueLst<Data> && queue) noexcept {
  List<Data>::operator=(std::move(queue));
  return *this;
}

/* ************************************************************************** */

// Comparison operators (QueueLst)

template <typename Data>
inline bool QueueLst<Data>::operator==(const QueueLst<Data> & queue) const noexcept {
  return List<Data>::operator==(queue);
}

template <typename Data>
inline bool QueueLst<Data>::operator!=(const QueueLst<Data> & queue) const noexcept {
  return !(*this == queue);
}

/* ************************************************************************** */

// Specific member functions (QueueLst) (inherited from Queue)

template <typename Data>
inline const Data & QueueLst<Data>::Head() const {
  if(size == 0)
    throw std::length_error("Queue is empty");
  return List<Data>::Front();
}

template <typename Data>
inline Data & QueueLst<Data>::Head() {
  if(size == 0)
    throw std::length_error("Queue is empty");
  return List<Data>::Front();
}

template <typename Data>
inline void QueueLst<Data>::Dequeue() {
  if(size == 0)
    throw std::length_error("Queue is empty");
  return List<Data>::RemoveFromFront();
}

template <typename Data>
inline Data QueueLst<Data>::HeadNDequeue() {
  if(size == 0)
    throw std::length_error("Queue is empty");
  return List<Data>::FrontNRemove();
}

template <typename Data>
inline void QueueLst<Data>::Enqueue(const Data & dat) {
  return List<Data>::InsertAtBack(dat);
}

template <typename Data>
inline void QueueLst<Data>::Enqueue(Data && dat) {
  return List<Data>::InsertAtBack(std::move(dat));
}


/* ************************************************************************** */

}
