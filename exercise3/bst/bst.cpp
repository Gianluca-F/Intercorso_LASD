
namespace lasd {

/* ************************************************************************** */

// Specific constructors

template <typename Data>
BST<Data>::BST(const TraversableContainer<Data> & con) {
  if(con.Size() != 0) {
    con.Traverse(
      [this](const Data & dat) {
        Insert(dat);
      }
    );
  }
}

template <typename Data>
BST<Data>::BST(MappableContainer<Data> && con) {
  if(con.Size() != 0) {
    con.Map(
      [this](Data & dat) {
        Insert(std::move(dat));
      }
    );
  }
}

/* ************************************************************************** */

// Copy constructor
template <typename Data>
BST<Data>::BST(const BST<Data> & tree) {
  if(tree.root != nullptr) {
    size = tree.size;
    root = new NodeLnk(*tree.root);
  }
}

// Move constructor
template <typename Data>
BST<Data>::BST(BST<Data> && tree) noexcept {
  std::swap(size, tree.size);
  std::swap(root, tree.root);
}

/* ************************************************************************** */

// Copy assignment
template <typename Data>
BST<Data> & BST<Data>::operator=(const BST<Data> & tree) {
  if(this != &tree) {
    Clear();
    if(tree.root != nullptr) {
      size = tree.size;
      root = new NodeLnk(*tree.root);
    }
  }
  return *this;
}

// Move assignment
template <typename Data>
BST<Data> & BST<Data>::operator=(BST<Data> && tree) noexcept {
  std::swap(size, tree.size);
  std::swap(root, tree.root);
  return *this;
}

/* ************************************************************************** */

// Comparison operators

template <typename Data>
bool BST<Data>::operator==(const BST<Data> & tree) const noexcept {
  if(size != tree.size) { return false; }

  BTInOrderIterator<Data> bst1(*this);
  BTInOrderIterator<Data> bst2(tree);

  while(!bst1.Terminated())
  {
    if(*bst1 != *bst2) { return false; }
    ++bst1;
    ++bst2;
  }

  return true;
}

template <typename Data>
inline bool BST<Data>::operator!=(const BST<Data> & tree) const noexcept {
  return !(*this == tree);
}

/* ************************************************************************** */

// Specific member functions

template <typename Data>
const Data & BST<Data>::Min() const {
  if(root == nullptr) { throw std::length_error("The tree is empty"); }
  return FindPointerToMin(root)->element;
}

template <typename Data>
Data BST<Data>::MinNRemove() {
  if(root == nullptr) { throw std::length_error("The tree is empty"); }
  return DataNDelete(DetachMin(root));
}

template <typename Data>
void BST<Data>::RemoveMin() {
  if(root == nullptr) { throw std::length_error("The tree is empty"); }
  delete DetachMin(root);
}

template <typename Data>
const Data & BST<Data>::Max() const {
  if(root == nullptr) { throw std::length_error("The tree is empty"); }
  return FindPointerToMax(root)->element;
}

template <typename Data>
Data BST<Data>::MaxNRemove() {
  if(root == nullptr) { throw std::length_error("The tree is empty"); }
  return DataNDelete(DetachMax(root));
}

template <typename Data>
void BST<Data>::RemoveMax() {
  if(root == nullptr) { throw std::length_error("The tree is empty"); }
  delete DetachMax(root);
}

template <typename Data>
const Data & BST<Data>::Predecessor(const Data & dat) const {
  const NodeLnk * const * node = FindPointerToPredecessor(root, dat);
  if(node == nullptr) { throw std::length_error("The element has no predecessor"); }
  return (*node)->element;
}

template <typename Data>
Data BST<Data>::PredecessorNRemove(const Data & dat) {
  NodeLnk ** node = FindPointerToPredecessor(root, dat);
  if(node == nullptr) { throw std::length_error("The element has no predecessor"); }
  NodeLnk * tmp = Detach(*node);
  Data pred = std::move(tmp->element);
  delete tmp;
  return pred;
}

template <typename Data>
void BST<Data>::RemovePredecessor(const Data & dat) {
  NodeLnk ** node = FindPointerToPredecessor(root, dat);
  if(node == nullptr) { throw std::length_error("The element has no predecessor"); }
  delete Detach(*node);
}

template <typename Data>
const Data & BST<Data>::Successor(const Data & dat) const {
  const NodeLnk * const * node = FindPointerToSuccessor(root, dat);
  if(node == nullptr) { throw std::length_error("The element has no successor"); }
  return (*node)->element;
}

template <typename Data>
Data BST<Data>::SuccessorNRemove(const Data & dat) {
  NodeLnk ** node = FindPointerToSuccessor(root, dat);
  if(node == nullptr) { throw std::length_error("The element has no successor"); }
  NodeLnk * tmp = Detach(*node);
  Data succ = std::move(tmp->element);
  delete tmp;
  return succ;
}

template <typename Data>
void BST<Data>::RemoveSuccessor(const Data & dat) {
  NodeLnk ** node = FindPointerToSuccessor(root, dat);
  if(node == nullptr) { throw std::length_error("The element has no successor"); }
  delete Detach(*node);
}

/* ************************************************************************** */

// Specific member functions (inherited from DictionaryContainer)

template <typename Data>
bool BST<Data>::Insert(const Data & dat) {
  if(root == nullptr) {
    root = new NodeLnk(dat);
  } else {
    NodeLnk *& node = FindPointerTo(root, dat);
    if(node != nullptr) {
      return false;
    }
    node = new NodeLnk(dat);
  }
  ++size;
  return true;
}

template <typename Data>
bool BST<Data>::Insert(Data && dat) {
  if(root == nullptr) {
    root = new NodeLnk(std::move(dat));
  } else {
    NodeLnk *& node = FindPointerTo(root, dat);
    if(node != nullptr) {
      return false;
    }
    node = new NodeLnk(std::move(dat));
  }
  ++size;
  return true;
}

template <typename Data>
bool BST<Data>::Remove(const Data & dat) {
  NodeLnk *& node = FindPointerTo(root, dat);
  if(node == nullptr) { return false; }
  delete Detach(node);
  return true;
}

/* ************************************************************************** */

// Specific member functions (inherited from TestableContainer)

template <typename Data>
bool BST<Data>::Exists(const Data & dat) const noexcept {
  return FindPointerTo(root, dat) != nullptr;
}

/* ************************************************************************** */

// Auxiliary member functions

template <typename Data>
Data BST<Data>::DataNDelete(NodeLnk * node) noexcept {
  Data dat = std::move(node->element);
  delete node;
  return dat;
}

template <typename Data>
typename BST<Data>::NodeLnk * BST<Data>::Detach(NodeLnk *& node) noexcept {
  NodeLnk * tmp = nullptr;
  if(node->left == nullptr) { 
    std::swap(tmp, node->right);
    std::swap(tmp, node);
  }
  else if(node->right == nullptr) { 
    std::swap(tmp, node->left);
    std::swap(tmp, node); 
  } 
  else {
    NodeLnk *& min = FindPointerToMin(node->right);
    std::swap(tmp, min->right);
    std::swap(tmp, min);
    std::swap(tmp->element, node->element);
  }
  --size;
  return tmp;
}

template <typename Data>
typename BST<Data>::NodeLnk * BST<Data>::DetachMin(NodeLnk *& node) noexcept {
  NodeLnk *& min = FindPointerToMin(node);
  NodeLnk * tmp = nullptr;
  std::swap(tmp, min->right);
  std::swap(tmp, min);
  --size;
  return tmp;
}

template <typename Data>
typename BST<Data>::NodeLnk * BST<Data>::DetachMax(NodeLnk *& node) noexcept {
  NodeLnk *& max = FindPointerToMax(node);
  NodeLnk * tmp = nullptr;
  std::swap(tmp, max->left);
  std::swap(tmp, max);
  --size;
  return tmp;
}

template <typename Data>
const typename BST<Data>::NodeLnk * const & BST<Data>::FindPointerToMin(const NodeLnk * const & node) const noexcept {
  if(node->left == nullptr) { return node; }
  return FindPointerToMin(node->left);
}

template <typename Data>
inline typename BST<Data>::NodeLnk *& BST<Data>::FindPointerToMin(NodeLnk *& node) noexcept {
  return const_cast<NodeLnk *&>(static_cast<const BST<Data> *>(this)->FindPointerToMin(node));
}

template <typename Data>
const typename BST<Data>::NodeLnk * const & BST<Data>::FindPointerToMax(const NodeLnk * const & node) const noexcept {
  if(node->right == nullptr) { return node; }
  return FindPointerToMax(node->right);
}

template <typename Data>
inline typename BST<Data>::NodeLnk *& BST<Data>::FindPointerToMax(NodeLnk *& node) noexcept {
  return const_cast<NodeLnk *&>(static_cast<const BST<Data> *>(this)->FindPointerToMax(node));
}

template <typename Data>
const typename BST<Data>::NodeLnk * const & BST<Data>::FindPointerTo(const NodeLnk * const & node, const Data & dat) const noexcept {
  if(node == nullptr) { return node; } 
  if(dat < node->element) { return FindPointerTo(node->left, dat); } 
  if(dat > node->element) { return FindPointerTo(node->right, dat); }
  return node;
}

template <typename Data>
inline typename BST<Data>::NodeLnk *& BST<Data>::FindPointerTo(NodeLnk *& node, const Data & dat) noexcept {
  return const_cast<NodeLnk *&>(static_cast<const BST<Data> *>(this)->FindPointerTo(node, dat));
}

template <typename Data>
const typename BST<Data>::NodeLnk * const * BST<Data>::FindPointerToPredecessor(const NodeLnk * const & node, const Data & dat) const noexcept {
  if(node == nullptr) { return nullptr; }
  if(dat < node->element) { return FindPointerToPredecessor(node->left, dat); }
  if(dat > node->element) {
    const NodeLnk * const * pred = FindPointerToPredecessor(node->right, dat);
    if(pred == nullptr) { return &node; }
    return pred;
  }
  if(node->left != nullptr) { return &FindPointerToMax(node->left); }
  return nullptr;
}

template <typename Data>
inline typename BST<Data>::NodeLnk ** BST<Data>::FindPointerToPredecessor(NodeLnk *& node, const Data & dat) noexcept {
  return const_cast<NodeLnk **>(static_cast<const BST<Data> *>(this)->FindPointerToPredecessor(node, dat));
}

template <typename Data>
const typename BST<Data>::NodeLnk * const * BST<Data>::FindPointerToSuccessor(const NodeLnk * const & node, const Data & dat) const noexcept {
  if(node == nullptr) { return nullptr; }
  if(dat < node->element) {
    const NodeLnk * const * succ = FindPointerToSuccessor(node->left, dat);
    if(succ == nullptr) { return &node; }
    return succ;
  }
  if(dat > node->element) { return FindPointerToSuccessor(node->right, dat); }
  if(node->right != nullptr) { return &FindPointerToMin(node->right); }
  return nullptr;
}

template <typename Data>
inline typename BST<Data>::NodeLnk ** BST<Data>::FindPointerToSuccessor(NodeLnk *& node, const Data & dat) noexcept {
  return const_cast<NodeLnk **>(static_cast<const BST<Data> *>(this)->FindPointerToSuccessor(node, dat));
}

/* ************************************************************************** */

}
