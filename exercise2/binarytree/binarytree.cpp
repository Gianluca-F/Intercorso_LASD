
namespace lasd {

/* ************************************************************************** */

// Comparison operators (Node)

template <typename Data>
bool BinaryTree<Data>::Node::operator==(const Node & node) const noexcept {
  if(Element() != node.Element()) { return false; }
  if(HasLeftChild() != node.HasLeftChild())  { return false; }
  if(HasRightChild() != node.HasRightChild()) { return false; }
  if(HasLeftChild() && LeftChild().operator!=(node.LeftChild()))   { return false; }
  if(HasRightChild() && RightChild().operator!=(node.RightChild())) { return false; }
  
  return true;
}

template <typename Data>
inline bool BinaryTree<Data>::Node::operator!=(const Node & node) const noexcept {
  return !(*this == node);
}

/* ************************************************************************** */

// Specific member functions (Node)

template <typename Data>
inline bool BinaryTree<Data>::Node::IsLeaf() const noexcept {
  return !(HasLeftChild() || HasRightChild());
}

/* ************************************************************************** */

// Comparison operators (BinaryTree)

template <typename Data>
bool BinaryTree<Data>::operator==(const BinaryTree<Data> & tree) const noexcept {
  if(size != tree.size) { return false; }
  if(size == 0) { return true; }
  return (Root().operator==(tree.Root()));
}

template <typename Data>
inline bool BinaryTree<Data>::operator!=(const BinaryTree<Data> & tree) const noexcept {
  return !(*this == tree);
}

/* ************************************************************************** */

// Specific member functions (BinaryTree) (inherited from TraversableContainer)

template <typename Data>
inline void BinaryTree<Data>::Traverse(TraverseFun fun) const {
  BreadthTraverse(fun, Root());
}

/* ************************************************************************** */

// Specific member functions (BinaryTree) (inherited from PreOrderTraversableContainer)

template <typename Data>
inline void BinaryTree<Data>::PreOrderTraverse(TraverseFun fun) const {
  if(size) { PreOrderTraverse(fun, Root()); }
}

/* ************************************************************************** */

// Specific member functions (BinaryTree) (inherited from PostOrderTraversableContainer)

template <typename Data>
inline void BinaryTree<Data>::PostOrderTraverse(TraverseFun fun) const {
  if(size) { PostOrderTraverse(fun, Root()); }
}

/* ************************************************************************** */

// Specific member functions (BinaryTree) (inherited from InOrderTraversableContainer)

template <typename Data>
inline void BinaryTree<Data>::InOrderTraverse(TraverseFun fun) const {
  if(size) { InOrderTraverse(fun, Root()); }
}

/* ************************************************************************** */

// Specific member functions (BinaryTree) (inherited from BreadthTraversableContainer)

template <typename Data>
inline void BinaryTree<Data>::BreadthTraverse(TraverseFun fun) const {
  if(size) { BreadthTraverse(fun, Root()); }
}

/* ************************************************************************** */

// Auxiliary member functions (BinaryTree) (for TraversableContainer)

template <typename Data>
void BinaryTree<Data>::PreOrderTraverse(TraverseFun fun, const Node & node) const {
  fun(node.Element());
  if(node.HasLeftChild())  { PreOrderTraverse(fun, node.LeftChild()); }
  if(node.HasRightChild()) { PreOrderTraverse(fun, node.RightChild()); }
}

template <typename Data>
void BinaryTree<Data>::PostOrderTraverse(TraverseFun fun, const Node & node) const {
  if(node.HasLeftChild())  { PostOrderTraverse(fun, node.LeftChild()); }
  if(node.HasRightChild()) { PostOrderTraverse(fun, node.RightChild()); }
  fun(node.Element());
}

template <typename Data>
void BinaryTree<Data>::InOrderTraverse(TraverseFun fun, const Node & node) const {
  if(node.HasLeftChild())  { InOrderTraverse(fun, node.LeftChild()); }
  fun(node.Element());
  if(node.HasRightChild()) { InOrderTraverse(fun, node.RightChild()); }
}

template <typename Data>
void BinaryTree<Data>::BreadthTraverse(TraverseFun fun, const Node & node) const {
  QueueVec<const Node *> queue;
  queue.Enqueue(&node);

  while(!queue.Empty()) {
    const Node & current = *queue.HeadNDequeue();
    fun(current.Element());
    if(current.HasLeftChild())  { queue.Enqueue(&current.LeftChild()); }
    if(current.HasRightChild()) { queue.Enqueue(&current.RightChild()); }
  }
}

/* ************************************************************************** */

// Specific member functions (MutableBinaryTree) (inherited from MappableContainer)

template <typename Data>
inline void MutableBinaryTree<Data>::Map(MapFun fun) {
  BreadthMap(fun, Root());
}

/* ************************************************************************** */

// Specific member functions (MutableBinaryTree) (inherited from PreOrderMappableContainer)

template <typename Data>
inline void MutableBinaryTree<Data>::PreOrderMap(MapFun fun) {
  if(size) { PreOrderMap(fun, Root()); }
}

/* ************************************************************************** */

// Specific member functions (MutableBinaryTree) (inherited from PostOrderMappableContainer)

template <typename Data>
inline void MutableBinaryTree<Data>::PostOrderMap(MapFun fun) {
  if(size) { PostOrderMap(fun, Root()); }
}

/* ************************************************************************** */

// Specific member functions (MutableBinaryTree) (inherited from InOrderMappableContainer)

template <typename Data>
inline void MutableBinaryTree<Data>::InOrderMap(MapFun fun) {
  if(size) { InOrderMap(fun, Root()); }
}

/* ************************************************************************** */

// Specific member functions (MutableBinaryTree) (inherited from BreadthMappableContainer)

template <typename Data>
inline void MutableBinaryTree<Data>::BreadthMap(MapFun fun) {
  if(size) { BreadthMap(fun, Root()); }
}

/* ************************************************************************** */

// Auxiliary member functions (MutableBinaryTree) (for MappableContainer)

template <typename Data>
void MutableBinaryTree<Data>::PreOrderMap(MapFun fun, MutableNode & node) {
  fun(node.Element());
  if(node.HasLeftChild())  { PreOrderMap(fun, node.LeftChild()); }
  if(node.HasRightChild()) { PreOrderMap(fun, node.RightChild()); }
}

template <typename Data>
void MutableBinaryTree<Data>::PostOrderMap(MapFun fun, MutableNode & node) {
  if(node.HasLeftChild())  { PostOrderMap(fun, node.LeftChild()); }
  if(node.HasRightChild()) { PostOrderMap(fun, node.RightChild()); }
  fun(node.Element());
}

template <typename Data>
void MutableBinaryTree<Data>::InOrderMap(MapFun fun, MutableNode & node) {
  if(node.HasLeftChild())  { InOrderMap(fun, node.LeftChild()); }
  fun(node.Element());
  if(node.HasRightChild()) { InOrderMap(fun, node.RightChild()); }
}

template <typename Data>
void MutableBinaryTree<Data>::BreadthMap(MapFun fun, MutableNode & node) {
  QueueVec<MutableNode *> queue;
  queue.Enqueue(&node);

  while(!queue.Empty()) {
    MutableNode & current = *queue.HeadNDequeue();
    fun(current.Element());
    if(current.HasLeftChild())  { queue.Enqueue(&current.LeftChild()); }
    if(current.HasRightChild()) { queue.Enqueue(&current.RightChild()); }
  }
}

/* ************************************************************************** */

// Specific constructors (BTPreOrderIterator)

template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(const BinaryTree<Data> & tree) {
  if(tree.Size() != 0) {
    root = &tree.Root();
    stack.Push(root);
  }
}

/* ************************************************************************** */

// Copy constructor (BTPreOrderIterator)
template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(const BTPreOrderIterator<Data> & iterator) {
  root = iterator.root;
  stack = iterator.stack;
}

// Move constructor (BTPreOrderIterator)
template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(BTPreOrderIterator<Data> && iterator) noexcept {
  std::swap(root, iterator.root);
  std::swap(stack, iterator.stack);
}

/* ************************************************************************** */

// Copy assignment (BTPreOrderIterator)
template <typename Data>
BTPreOrderIterator<Data> & BTPreOrderIterator<Data>::operator=(const BTPreOrderIterator<Data> & iterator) {
  if(this != &iterator) {
    root = iterator.root;
    stack = iterator.stack;
  }
  return *this;
}

// Move assignment (BTPreOrderIterator)
template <typename Data>
BTPreOrderIterator<Data> & BTPreOrderIterator<Data>::operator=(BTPreOrderIterator<Data> && iterator) noexcept {
  if(this != &iterator) {
    std::swap(root, iterator.root);
    std::swap(stack, iterator.stack);
  }
  return *this;
}

/* ************************************************************************** */

// Comparison operators (BTPreOrderIterator)

template <typename Data>
inline bool BTPreOrderIterator<Data>::operator==(const BTPreOrderIterator<Data> & iterator) const noexcept {
  return ((root == iterator.root) && (stack == iterator.stack));
}

template <typename Data>
inline bool BTPreOrderIterator<Data>::operator!=(const BTPreOrderIterator<Data> & iterator) const noexcept {
  return !(*this == iterator);
}

/* ************************************************************************** */

// Specific member functions (BTPreOrderIterator) (inherited from Iterator)

template <typename Data>
const Data & BTPreOrderIterator<Data>::operator*() const {
  if(Terminated()) { throw std::out_of_range("Iterator out of range"); }
  return stack.Top()->Element();
}

template <typename Data>
inline bool BTPreOrderIterator<Data>::Terminated() const noexcept {
  return stack.Empty();
}

/* ************************************************************************** */

// Specific member functions (BTPreOrderIterator) (inherited from ForwardIterator)

template <typename Data>
ForwardIterator<Data> & BTPreOrderIterator<Data>::operator++() {
  if(Terminated()) { throw std::out_of_range("Iterator out of range"); }
  
  const typename BinaryTree<Data>::Node & current = *stack.TopNPop();
  if(current.HasRightChild()) { stack.Push(&current.RightChild()); }
  if(current.HasLeftChild()) { stack.Push(&current.LeftChild()); }
  return *this;
}

/* ************************************************************************** */

// Specific member functions (BTPreOrderIterator) (inherited from ResettableIterator)

template <typename Data>
void BTPreOrderIterator<Data>::Reset() noexcept {
  if(root != nullptr) {
    stack.Clear();
    stack.Push(root);
  }
}

/* ************************************************************************** */

// Specific member functions (BTPreOrderMutableIterator) (inherited from MutableIterator)

template <typename Data>
Data & BTPreOrderMutableIterator<Data>::operator*() {
  if(Terminated()) { throw std::out_of_range("Iterator out of range"); }
  return const_cast<Data &>(stack.Top()->Element());
}

/* ************************************************************************** */

// Specific constructors (BTPostOrderIterator)

template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(const BinaryTree<Data> & tree) {
  if(tree.Size() != 0) {
    root = &tree.Root();
    PushLeftLeaf(root);
  }
}

/* ************************************************************************** */

// Copy constructor (BTPostOrderIterator)
template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(const BTPostOrderIterator<Data> & iterator) {
  root = iterator.root;
  stack = iterator.stack;
}

// Move constructor (BTPostOrderIterator)
template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(BTPostOrderIterator<Data> && iterator) noexcept {
  std::swap(root, iterator.root);
  std::swap(stack, iterator.stack);
}

/* ************************************************************************** */

// Copy assignment (BTPostOrderIterator)
template <typename Data>
BTPostOrderIterator<Data> & BTPostOrderIterator<Data>::operator=(const BTPostOrderIterator<Data> & iterator) {
  if(this != &iterator) {
    root = iterator.root;
    stack = iterator.stack;
  }
  return *this;
}

// Move assignment (BTPostOrderIterator)
template <typename Data>
BTPostOrderIterator<Data> & BTPostOrderIterator<Data>::operator=(BTPostOrderIterator<Data> && iterator) noexcept {
  if(this != &iterator) {
    std::swap(root, iterator.root);
    std::swap(stack, iterator.stack);
  }
  return *this;
}

/* ************************************************************************** */

// Comparison operators (BTPostOrderIterator)

template <typename Data>
inline bool BTPostOrderIterator<Data>::operator==(const BTPostOrderIterator<Data> & iterator) const noexcept {
  return ((root == iterator.root) && (stack == iterator.stack));
}

template <typename Data>
inline bool BTPostOrderIterator<Data>::operator!=(const BTPostOrderIterator<Data> & iterator) const noexcept {
  return !(*this == iterator);
}

/* ************************************************************************** */

// Specific member functions (BTPostOrderIterator) (inherited from Iterator)

template <typename Data>
const Data & BTPostOrderIterator<Data>::operator*() const {
  if(Terminated()) { throw std::out_of_range("Iterator out of range"); }
  return stack.Top()->Element();
}

template <typename Data>
inline bool BTPostOrderIterator<Data>::Terminated() const noexcept {
  return stack.Empty();
}

/* ************************************************************************** */

// Specific member functions (BTPostOrderIterator) (inherited from ForwardIterator)

template <typename Data>
ForwardIterator<Data> & BTPostOrderIterator<Data>::operator++() {
  if(Terminated()) { throw std::out_of_range("Iterator out of range"); }

  const typename BinaryTree<Data>::Node & current = *stack.TopNPop();
  if(stack.Empty()) { return *this; }
  
  const typename BinaryTree<Data>::Node & parent = *stack.Top();
  if((parent.HasRightChild()) && (&parent.RightChild() != &current)) { 
    PushLeftLeaf(&parent.RightChild());
  } 
  return *this;
}

/* ************************************************************************** */

// Specific member functions (BTPostOrderIterator) (inherited from ResettableIterator)

template <typename Data>
void BTPostOrderIterator<Data>::Reset() noexcept {
  if(root != nullptr) {
    stack.Clear();
    PushLeftLeaf(root);
  }
}

/* ************************************************************************** */

// Auxiliary member functions (BTPostOrderIterator)

template <typename Data>
void BTPostOrderIterator<Data>::PushLeftLeaf(const typename BinaryTree<Data>::Node * node) {
  stack.Push(node);
  do {
    while(node->HasLeftChild()) {
      node = &node->LeftChild();
      stack.Push(node);
    }
    if(node->HasRightChild()) {
      node = &node->RightChild();
      stack.Push(node);
    }
  } while(!node->IsLeaf());
}

/* ************************************************************************** */

// Specific member functions (BTPostOrderMutableIterator) (inherited from MutableIterator)

template <typename Data>
Data & BTPostOrderMutableIterator<Data>::operator*() {
  if(Terminated()) { throw std::out_of_range("Iterator out of range"); }
  return const_cast<Data &>(stack.Top()->Element());
}

/* ************************************************************************** */

// Specific constructors (BTInOrderIterator)

template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(const BinaryTree<Data> & tree) {
  if(tree.Size() != 0) {
    root = &tree.Root();
    PushLeftNode(root);
  }
}

/* ************************************************************************** */

// Copy constructor (BTInOrderIterator)
template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(const BTInOrderIterator<Data> & iterator) {
  root = iterator.root;
  stack = iterator.stack;
}

// Move constructor (BTInOrderIterator)
template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(BTInOrderIterator<Data> && iterator) noexcept {
  std::swap(root, iterator.root);
  std::swap(stack, iterator.stack);
}

/* ************************************************************************** */

// Copy assignment (BTInOrderIterator)
template <typename Data>
BTInOrderIterator<Data> & BTInOrderIterator<Data>::operator=(const BTInOrderIterator<Data> & iterator) {
  if(this != &iterator) {
    root = iterator.root;
    stack = iterator.stack;
  }
  return *this;
}

// Move assignment (BTInOrderIterator)
template <typename Data>
BTInOrderIterator<Data> & BTInOrderIterator<Data>::operator=(BTInOrderIterator<Data> && iterator) noexcept {
  if(this != &iterator) {
    std::swap(root, iterator.root);
    std::swap(stack, iterator.stack);
  }
  return *this;
}

/* ************************************************************************** */

// Comparison operators (BTInOrderIterator)

template <typename Data>
inline bool BTInOrderIterator<Data>::operator==(const BTInOrderIterator<Data> & iterator) const noexcept {
  return ((root == iterator.root) && (stack == iterator.stack));
}

template <typename Data>
inline bool BTInOrderIterator<Data>::operator!=(const BTInOrderIterator<Data> & iterator) const noexcept {
  return !(*this == iterator);
}

/* ************************************************************************** */

// Specific member functions (BTInOrderIterator) (inherited from Iterator)

template <typename Data>
const Data & BTInOrderIterator<Data>::operator*() const {
  if(Terminated()) { throw std::out_of_range("Iterator out of range"); }
  return stack.Top()->Element();
}

template <typename Data>
inline bool BTInOrderIterator<Data>::Terminated() const noexcept {
  return stack.Empty();
}

/* ************************************************************************** */

// Specific member functions (BTInOrderIterator) (inherited from ForwardIterator)

template <typename Data>
ForwardIterator<Data> & BTInOrderIterator<Data>::operator++() {
  if(Terminated()) { throw std::out_of_range("Iterator out of range"); }

  const typename BinaryTree<Data>::Node & current = *stack.TopNPop();
  if(current.HasRightChild()) { PushLeftNode(&current.RightChild()); }
  return *this;
}

/* ************************************************************************** */

// Specific member functions (BTInOrderIterator) (inherited from ResettableIterator)

template <typename Data>
void BTInOrderIterator<Data>::Reset() noexcept {
  if(root != nullptr) {
    stack.Clear();
    PushLeftNode(root);
  }
}

/* ************************************************************************** */

// Auxiliary member functions (BTInOrderIterator)

template <typename Data>
void BTInOrderIterator<Data>::PushLeftNode(const typename BinaryTree<Data>::Node * node) {
  stack.Push(node);
  while(node->HasLeftChild()) {
    node = &node->LeftChild();
    stack.Push(node);
  }
}

/* ************************************************************************** */

// Specific member functions (BTInOrderMutableIterator) (inherited from MutableIterator)

template <typename Data>
Data & BTInOrderMutableIterator<Data>::operator*() {
  if(Terminated()) { throw std::out_of_range("Iterator out of range"); }
  return const_cast<Data &>(stack.Top()->Element());
}

/* ************************************************************************** */

// Specific constructors (BTBreadthIterator)

template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(const BinaryTree<Data> & tree) {
  if(tree.Size() != 0) {
    root = &tree.Root();
    queue.Enqueue(root);
  }
}

/* ************************************************************************** */

// Copy constructor (BTBreadthIterator)
template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(const BTBreadthIterator<Data> & iterator) {
  root = iterator.root;
  queue = iterator.queue;
}

// Move constructor (BTBreadthIterator)
template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(BTBreadthIterator<Data> && iterator) noexcept {
  std::swap(root, iterator.root);
  std::swap(queue, iterator.queue);
}

/* ************************************************************************** */

// Copy assignment (BTBreadthIterator)
template <typename Data>
BTBreadthIterator<Data> & BTBreadthIterator<Data>::operator=(const BTBreadthIterator<Data> & iterator) {
  if(this != &iterator) {
    root = iterator.root;
    queue = iterator.queue;
  }
  return *this;
}

// Move assignment (BTBreadthIterator)
template <typename Data>
BTBreadthIterator<Data> & BTBreadthIterator<Data>::operator=(BTBreadthIterator<Data> && iterator) noexcept {
  if(this != &iterator) {
    std::swap(root, iterator.root);
    std::swap(queue, iterator.queue);
  }
  return *this;
}

/* ************************************************************************** */

// Comparison operators (BTBreadthIterator)

template <typename Data>
inline bool BTBreadthIterator<Data>::operator==(const BTBreadthIterator<Data> & iterator) const noexcept {
  return ((root == iterator.root) && (queue == iterator.queue));
}

template <typename Data>
inline bool BTBreadthIterator<Data>::operator!=(const BTBreadthIterator<Data> & iterator) const noexcept {
  return !(*this == iterator);
}

/* ************************************************************************** */

// Specific member functions (BTBreadthIterator) (inherited from Iterator)

template <typename Data>
const Data & BTBreadthIterator<Data>::operator*() const {
  if(Terminated()) { throw std::out_of_range("Iterator out of range"); }
  return queue.Head()->Element();
}

template <typename Data>
inline bool BTBreadthIterator<Data>::Terminated() const noexcept {
  return queue.Empty();
}

/* ************************************************************************** */

// Specific member functions (BTBreadthIterator) (inherited from ForwardIterator)

template <typename Data>
ForwardIterator<Data> & BTBreadthIterator<Data>::operator++() {
  if(Terminated()) { throw std::out_of_range("Iterator out of range"); }

  const typename BinaryTree<Data>::Node & current = *queue.HeadNDequeue();
  if(current.HasLeftChild()) { queue.Enqueue(&current.LeftChild()); }
  if(current.HasRightChild()) { queue.Enqueue(&current.RightChild()); }
  return *this;
}

/* ************************************************************************** */

// Specific member functions (BTBreadthIterator) (inherited from ResettableIterator)

template <typename Data>
void BTBreadthIterator<Data>::Reset() noexcept {
  if(root != nullptr) {
    queue.Clear();
    queue.Enqueue(root);
  }
}

/* ************************************************************************** */

// Specific member functions (BTBreadthMutableIterator) (inherited from MutableIterator)

template <typename Data>
Data & BTBreadthMutableIterator<Data>::operator*() {
  if(Terminated()) { throw std::out_of_range("Iterator out of range"); }
  return const_cast<Data &>(queue.Head()->Element());
}

/* ************************************************************************** */

}
