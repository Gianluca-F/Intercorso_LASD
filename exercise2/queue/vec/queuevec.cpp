
namespace lasd {

/* ************************************************************************** */

// Specific Constructors (QueueVec)

template <typename Data>
QueueVec<Data>::QueueVec(const TraversableContainer<Data> & con) : Vector<Data>(con) {
  tail = numElmts = con.Size();
};

template <typename Data>
QueueVec<Data>::QueueVec(MappableContainer<Data> && con) : Vector<Data>(std::move(con)) {
  tail = numElmts = con.Size();
};

/* ************************************************************************** */

// Copy Constructor (QueueVec)
template <typename Data>
QueueVec<Data>::QueueVec(const QueueVec<Data> & queue) : Vector<Data>(queue) {
  head = queue.head;
  tail = queue.tail;
  numElmts = queue.numElmts;
};

// Move Constructor (QueueVec)
template <typename Data>
QueueVec<Data>::QueueVec(QueueVec<Data> && queue) noexcept : Vector<Data>(std::move(queue)) {
  std::swap(head, queue.head);
  std::swap(tail, queue.tail);
  std::swap(numElmts, queue.numElmts);
};

/* ************************************************************************** */

// Copy Assignment (QueueVec)
template <typename Data>
QueueVec<Data> & QueueVec<Data>::operator=(const QueueVec<Data> & queue) {
  Vector<Data>::operator=(queue);
  head = queue.head;
  tail = queue.tail;
  numElmts = queue.numElmts;
  return *this;
};

// Move Assignment (QueueVec)
template <typename Data>
QueueVec<Data> & QueueVec<Data>::operator=(QueueVec<Data> && queue) noexcept {
  Vector<Data>::operator=(std::move(queue));
  std::swap(head, queue.head);
  std::swap(tail, queue.tail);
  std::swap(numElmts, queue.numElmts);
  return *this;
};

/* ************************************************************************** */

// Comparison operators (QueueVec)

template <typename Data>
bool QueueVec<Data>::operator==(const QueueVec<Data> & queue) const noexcept {
  if(numElmts != queue.numElmts) {
    return false;
  }
  for(ulong i = 0; i < numElmts; ++i) {
    if(Elements[(head + i) % size] != queue.Elements[(queue.head + i) % queue.size]) {
      return false;
    }
  }
  return true;
};

template <typename Data>
inline bool QueueVec<Data>::operator!=(const QueueVec<Data> & queue) const noexcept {
  return !(*this == queue);
};

/* ************************************************************************** */

// Specific member functions (QueueVec) (inherited from Queue)

template <typename Data>
const Data & QueueVec<Data>::Head() const {
  if(numElmts == 0) {
    throw std::length_error("Queue is empty");
  }
  return Elements[head];
};

template <typename Data>
Data & QueueVec<Data>::Head() {
  if(numElmts == 0) {
    throw std::length_error("Queue is empty");
  }
  return Elements[head];
};

template <typename Data>
void QueueVec<Data>::Dequeue() {
  if(numElmts == 0) {
    throw std::length_error("Queue is empty");
  }
  head = (head + 1) % size;
  --numElmts;
  Reduce();
};

template <typename Data>
Data QueueVec<Data>::HeadNDequeue() {
  Data dat = std::move(Head());
  Dequeue();
  return dat;
};

template <typename Data>
void QueueVec<Data>::Enqueue(const Data & dat) {
  if(numElmts == size) {
    Expand();
  }
  Elements[tail] = dat;
  tail = (tail + 1) % size;
  ++numElmts;
};

template <typename Data>
void QueueVec<Data>::Enqueue(Data && dat) {
  if(numElmts == size) {
    Expand();
  }
  Elements[tail] = std::move(dat);
  tail = (tail + 1) % size;
  ++numElmts;
};


/* ************************************************************************** */

// Specific member functions (QueueVec) (inherited from Container)

template <typename Data>
inline bool QueueVec<Data>::Empty() const noexcept {
  return numElmts == 0;
};

template <typename Data>
ulong QueueVec<Data>::Size() const noexcept {
  return numElmts;
};

/* ************************************************************************** */

// Specific member function (QueueVec) (inherited from ClearableContainer)

template <typename Data>
void QueueVec<Data>::Clear() {
  head = tail = numElmts = 0;
};

/* ************************************************************************** */

// Auxiliary member functions

template <typename Data>
inline void QueueVec<Data>::Expand() {
    Resize(size * 1.5, numElmts);
};

template <typename Data>
inline void QueueVec<Data>::Reduce() {
  if(numElmts <= size / 4 && size > DEFAULT_QUEUE_DIM) {
    Resize(size / 1.5, numElmts);
  }
};

template <typename Data>
void QueueVec<Data>::Resize(ulong newsize, ulong numElmts) {
  Data * newElements = new Data[newsize];
  for(ulong i = 0; i < numElmts; ++i) {
    newElements[i] = std::move(Elements[(head + i) % size]);
  }
  std::swap(Elements, newElements);
  delete[] newElements;
  head = 0;
  tail = numElmts - 1;
  size = newsize;
};

/* ************************************************************************** */

}
