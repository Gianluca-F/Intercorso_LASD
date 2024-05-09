
namespace lasd {

/* ************************************************************************** */

// Specific constructors (NodeVec)

template <typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec(const Data & data, const ulong ind, BinaryTreeVec<Data> * tree) {
  exists = true;
  element = data;
  index = ind;
  treeVec = tree;
}

template <typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec(Data && data, const ulong ind, BinaryTreeVec<Data> * tree) {
  exists = true;
  element = std::move(data);
  index = ind;
  treeVec = tree;
}

/* ************************************************************************** */

// Copy constructor (NodeVec)
template <typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec(const NodeVec & node) {
  exists = node.exists;
  element = node.element;
  index = node.index;
  treeVec = node.treeVec;
}

// Move constructor (NodeVec)
template <typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec(NodeVec && node) noexcept {
  std::swap(exists, node.exists);  
  std::swap(element, node.element);
  std::swap(index, node.index);
  std::swap(treeVec, node.treeVec);
}

/* ************************************************************************** */

// Destructor (NodeVec)
template <typename Data>
BinaryTreeVec<Data>::NodeVec::~NodeVec() {
  exists = false;
}

/* ************************************************************************** */

// Copy assignment (NodeVec)
template <typename Data>
typename BinaryTreeVec<Data>::NodeVec & BinaryTreeVec<Data>::NodeVec::operator=(const NodeVec & node) {
  if(this != &node) {
    exists = node.exists;    
    element = node.element;
  }
  return *this;
}

// Move assignment (NodeVec)
template <typename Data>
typename BinaryTreeVec<Data>::NodeVec & BinaryTreeVec<Data>::NodeVec::operator=(NodeVec && node) noexcept {
  std::swap(exists, node.exists);
  std::swap(element, node.element);
  return *this;
}

/* ************************************************************************** */

// Comparison operators (NodeVec)

template <typename Data>
inline bool BinaryTreeVec<Data>::NodeVec::operator==(const NodeVec & node) const noexcept {
  return ((exists == node.exists) && (BinaryTree<Data>::Node::operator==(node))); 
}

template <typename Data>
inline bool BinaryTreeVec<Data>::NodeVec::operator!=(const NodeVec & node) const noexcept {
  return !(*this == node);
}

/* ************************************************************************** */

// Specific member functions (NodeVec) (inherited from Node)

template <typename Data>
inline const Data & BinaryTreeVec<Data>::NodeVec::Element() const noexcept {
  return element;
}

template <typename Data>
inline bool BinaryTreeVec<Data>::NodeVec::HasLeftChild() const noexcept {
  return ((2*index+1 < treeVec->size) && (treeVec->tree[2*index+1])->exists);
}

template <typename Data>
inline bool BinaryTreeVec<Data>::NodeVec::HasRightChild() const noexcept {
  return ((2*index+2 < treeVec->size) && (treeVec->tree[2*index+2])->exists);
}

template <typename Data>
const BinaryTree<Data>::Node & BinaryTreeVec<Data>::NodeVec::LeftChild() const {
  if(!HasLeftChild()) { throw std::out_of_range("No left child"); }
  return *(treeVec->tree[2*index+1]);
 }
  
template <typename Data>
const BinaryTree<Data>::Node & BinaryTreeVec<Data>::NodeVec::RightChild() const {
  if(!HasRightChild()) { throw std::out_of_range("No right child"); }
  return *(treeVec->tree[2*index+2]);
}

/* ************************************************************************** */

// Specific member functions (NodeVec) (inherited from MutableNode)

template <typename Data>
inline Data & BinaryTreeVec<Data>::NodeVec::Element() noexcept {
  return element;
}

template <typename Data>
MutableBinaryTree<Data>::MutableNode & BinaryTreeVec<Data>::NodeVec::LeftChild() {
  if(!HasLeftChild()) { throw std::out_of_range("No left child"); }
  return *(treeVec->tree[2*index+1]);
}

template <typename Data>
MutableBinaryTree<Data>::MutableNode & BinaryTreeVec<Data>::NodeVec::RightChild() {
  if(!HasRightChild()) { throw std::out_of_range("No right child"); }
  return *(treeVec->tree[2*index+2]);
}

/* ************************************************************************** */

// Specific constructors (BinaryTreeVec)

template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const TraversableContainer<Data> & con) {
  size = con.Size();
  tree = Vector<NodeVec*>(size);
  ulong i = 0;
  con.Traverse([this, &i](const Data & data) {
    tree[i] = new NodeVec(data, i, this);
    i++;
  });
}

template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(MappableContainer<Data> && con) {
  size = con.Size();
  tree = Vector<NodeVec*>(size);
  ulong i = 0;
  con.Map([this, &i](Data && data) {
    tree[i] = new NodeVec(std::move(data), i, this);
    i++;
  });
}

/* ************************************************************************** */

// Copy constructor (BinaryTreeVec)
template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec<Data> & bt) {
  size = bt.size;
  tree = Vector<NodeVec*>(size);
  for(ulong i = 0; i < size; i++) {
    tree[i] = new NodeVec((bt.tree[i])->element, i, this);
  }
}

// Move constructor (BinaryTreeVec)
template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec<Data> && bt) noexcept {
  std::swap(size, bt.size);
  std::swap(tree, bt.tree);
}

/* ************************************************************************** */

// Destructor (BinaryTreeVec)

template <typename Data>
BinaryTreeVec<Data>::~BinaryTreeVec() {
  for(ulong i = 0; i < size; i++) {
    delete tree[i];
  }
}

/* ************************************************************************** */

// Copy assignment (BinaryTreeVec)
template <typename Data>
BinaryTreeVec<Data> & BinaryTreeVec<Data>::operator=(const BinaryTreeVec<Data> & bt) {
  if(this != &bt) {
    Clear();
    size = bt.size;
    tree = Vector<NodeVec*>(size);
    for(ulong i = 0; i < size; i++) {
      tree[i] = new NodeVec((bt.tree[i])->element, i, this);
    }
  }
  return *this;
}

// Move assignment (BinaryTreeVec)
template <typename Data>
BinaryTreeVec<Data> & BinaryTreeVec<Data>::operator=(BinaryTreeVec<Data> && bt) noexcept {
  std::swap(size, bt.size);
  std::swap(tree, bt.tree);
  return *this;
}

/* ************************************************************************** */

// Comparison operators (BinaryTreeVec)

template <typename Data>
bool BinaryTreeVec<Data>::operator==(const BinaryTreeVec<Data> & bt) const noexcept {
  if(size != bt.size) { return false; }
  for(ulong i = 0; i < size; i++) {
    if(*tree[i] != *bt.tree[i]) { return false; }
  }
  return true;
}

template <typename Data>
inline bool BinaryTreeVec<Data>::operator!=(const BinaryTreeVec<Data> & bt) const noexcept {
  return !(*this == bt);
}

/* ************************************************************************** */

// Specific member functions (BinaryTreeVec) (inherited from BinaryTree)

template <typename Data>
const BinaryTree<Data>::Node & BinaryTreeVec<Data>::Root() const {
  if(size == 0) { throw std::length_error("Empty tree"); }
  return *tree[0];
}

/* ************************************************************************** */

// Specific member function (BinaryTreeVec) (inherited from MutableBinaryTree)

template <typename Data>
MutableBinaryTree<Data>::MutableNode & BinaryTreeVec<Data>::Root() {
  if(size == 0) { throw std::length_error("Empty tree"); }
  return *tree[0];
}

/* ************************************************************************** */

// Specific member function (BinaryTreeVec) (inherited from ClearableContainer)

template <typename Data>
void BinaryTreeVec<Data>::Clear() {
  for(ulong i = 0; i < size; i++) {
    delete tree[i];
    tree[i] = nullptr;
  }
  tree = Vector<NodeVec*>();
  size = 0;
}

/* ************************************************************************** */

// Specific member functions (BinaryTreeVec) (inherited from BreadthTraversableContainer)

template <typename Data>
void BinaryTreeVec<Data>::BreadthTraverse(TraverseFun fun) const {
  for(ulong i = 0; i < size; i++) {
    if(tree[i]->exists) {
      fun(tree[i]->element);
    }
  }
}

/* ************************************************************************** */

// Specific member functions (BinaryTreeVec) (inherited from BreadthMappableContainer)

template <typename Data>
void BinaryTreeVec<Data>::BreadthMap(MapFun fun) {
  for(ulong i = 0; i < size; i++) {
    if(tree[i]->exists) {
      fun(tree[i]->element);
    }
  }
}

/* ************************************************************************** */

}
