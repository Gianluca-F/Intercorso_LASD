
namespace lasd {

/* ************************************************************************** */

// Specific constructors (NodeVec)

template <typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec(const Data & data, const ulong ind, BinaryTreeVec<Data> * tree) {
  element = data;
  index = ind;
  treeVec = tree;
}

template <typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec(Data && data, const ulong ind, BinaryTreeVec<Data> * tree) {
  element = std::move(data);
  index = ind;
  treeVec = tree;
}

/* ************************************************************************** */

// Comparison operators (NodeVec)

template <typename Data>
inline bool BinaryTreeVec<Data>::NodeVec::operator==(const NodeVec & node) const noexcept {
  return BinaryTree<Data>::Node::operator==(node); 
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
  return 2*index+1 < treeVec->size;
}

template <typename Data>
inline bool BinaryTreeVec<Data>::NodeVec::HasRightChild() const noexcept {
  return 2*index+2 < treeVec->size;
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
    ++i;
  });
}

template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(MappableContainer<Data> && con) {
  size = con.Size();
  tree = Vector<NodeVec*>(size);
  ulong i = 0;
  con.Map([this, &i](Data && data) {
    tree[i] = new NodeVec(std::move(data), i, this);
    ++i;
  });
}

/* ************************************************************************** */

// Copy constructor (BinaryTreeVec)
template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec<Data> & bt) {
  size = bt.size;
  tree = Vector<NodeVec*>(size);
  for(ulong i = 0; i < size; ++i) {
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
  for(ulong i = 0; i < size; ++i) {
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
    for(ulong i = 0; i < size; ++i) {
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
  for(ulong i = 0; i < size; ++i) {
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
  for(ulong i = 0; i < size; ++i) {
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
  for(ulong i = 0; i < size; ++i) {
    fun(tree[i]->element);
  }
}

/* ************************************************************************** */

// Specific member functions (BinaryTreeVec) (inherited from BreadthMappableContainer)

template <typename Data>
void BinaryTreeVec<Data>::BreadthMap(MapFun fun) {
  for(ulong i = 0; i < size; ++i) {
    fun(tree[i]->element);
  }
}

/* ************************************************************************** */

}
