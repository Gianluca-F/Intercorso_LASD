
namespace lasd {

/* ************************************************************************** */

// Specific constructors (NodeLnk)

template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(const Data & data) : element(data) {};

template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(Data && data) : element(std::move(data)) {};

/* ************************************************************************** */

// Copy constructor (NodeLnk)
template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(const NodeLnk & node) {
  element = node.element;
  if(node.left != nullptr) {
    left = new NodeLnk(*node.left);
  }
  if(node.right != nullptr) {
    right = new NodeLnk(*node.right);
  }
}

// Move constructor (NodeLnk)
template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(NodeLnk && node) noexcept {
  std::swap(element, node.element);
  std::swap(left, node.left);
  std::swap(right, node.right);
}

/* ************************************************************************** */

// Destructor (NodeLnk)
template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::~NodeLnk() {
  delete left;
  delete right;
}

/* ************************************************************************** */

// Copy assignment (NodeLnk)
template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk & BinaryTreeLnk<Data>::NodeLnk::operator=(const NodeLnk & node) {
  if(this != &node) {
    element = node.element;
    if(node.left != nullptr) {
      left = new NodeLnk(*node.left);
    }
    if(node.right != nullptr) {
      right = new NodeLnk(*node.right);
    }
  }
  return *this;
}

// Move assignment (NodeLnk)
template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk & BinaryTreeLnk<Data>::NodeLnk::operator=(NodeLnk && node) noexcept {
  std::swap(element, node.element);
  std::swap(left, node.left);
  std::swap(right, node.right);
  return *this;
}

/* ************************************************************************** */

// Comparison operators (NodeLnk)

template <typename Data>
inline bool BinaryTreeLnk<Data>::NodeLnk::operator==(const NodeLnk & node) const noexcept {
  return BinaryTree<Data>::Node::operator==(node);
}

template <typename Data>
inline bool BinaryTreeLnk<Data>::NodeLnk::operator!=(const NodeLnk & node) const noexcept {
  return !(*this == node);
}

/* ************************************************************************** */

// Specific member functions (NodeLnk) (inherited from Node)

template <typename Data>
inline const Data & BinaryTreeLnk<Data>::NodeLnk::Element() const noexcept {
  return element;
}

template <typename Data>
inline bool BinaryTreeLnk<Data>::NodeLnk::HasLeftChild() const noexcept {
  return left != nullptr;
}

template <typename Data>
inline bool BinaryTreeLnk<Data>::NodeLnk::HasRightChild() const noexcept {
  return right != nullptr;
}

template <typename Data>
const typename BinaryTree<Data>::Node & BinaryTreeLnk<Data>::NodeLnk::LeftChild() const {
  if(!HasLeftChild()) { throw std::out_of_range("No left child"); } 
  return *left;
}

template <typename Data>
const typename BinaryTree<Data>::Node & BinaryTreeLnk<Data>::NodeLnk::RightChild() const {
  if(!HasRightChild()) { throw std::out_of_range("No right child"); } 
  return *right;
}

/* ************************************************************************** */

// Specific member functions (NodeLnk) (inherited from MutableNode)

template <typename Data>
inline Data & BinaryTreeLnk<Data>::NodeLnk::Element() noexcept {
  return element;
}

template <typename Data>
typename MutableBinaryTree<Data>::MutableNode & BinaryTreeLnk<Data>::NodeLnk::LeftChild() {
  if(!HasLeftChild()) { throw std::out_of_range("No left child"); } 
  return *left;
}

template <typename Data>
typename MutableBinaryTree<Data>::MutableNode & BinaryTreeLnk<Data>::NodeLnk::RightChild() {
  if(!HasRightChild()) { throw std::out_of_range("No right child"); } 
  return *right;
}

/* ************************************************************************** */

// Specific constructors (BinaryTreeLnk)

template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const TraversableContainer<Data> & con) {
  if(con.Size() != 0) {
    size = con.Size();
    QueueVec<NodeLnk **> queue;
    queue.Enqueue(&root);
    con.Traverse(
      [&queue](const Data & dat) {
        NodeLnk *& current = *queue.HeadNDequeue();
        current = new NodeLnk(dat);
        queue.Enqueue(&current->left);
        queue.Enqueue(&current->right);
      }
    );  
  }
}

template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(MappableContainer<Data> && con) {
  if(con.Size() != 0) {
    size = con.Size();
    QueueVec<NodeLnk **> queue;
    queue.Enqueue(&root);
    con.Map(
      [&queue](Data & dat) {
        NodeLnk *& current = *queue.HeadNDequeue();
        current = new NodeLnk(std::move(dat));
        queue.Enqueue(&current->left);
        queue.Enqueue(&current->right);
      }
    );
  }
}

/* ************************************************************************** */

// Copy constructor (BinaryTreeLnk)
template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const BinaryTreeLnk<Data> & tree) {
  if(tree.root != nullptr) {
    size = tree.size;
    root = new NodeLnk(*tree.root);
  }
}

// Move constructor (BinaryTreeLnk)
template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(BinaryTreeLnk<Data> && tree) noexcept {
  std::swap(size, tree.size);
  std::swap(root, tree.root);
}

/* ************************************************************************** */

// Destructor (BinaryTreeLnk)
template <typename Data>
BinaryTreeLnk<Data>::~BinaryTreeLnk() {
  delete root;
}

/* ************************************************************************** */

// Copy assignment (BinaryTreeLnk)
template <typename Data>
BinaryTreeLnk<Data> & BinaryTreeLnk<Data>::operator=(const BinaryTreeLnk<Data> & tree) {
  if(this != &tree) {
    Clear();
    if(tree.root != nullptr) {
      size = tree.size;
      root = new NodeLnk(*tree.root);
    }
  }
  return *this;
}

// Move assignment (BinaryTreeLnk)
template <typename Data>
BinaryTreeLnk<Data> & BinaryTreeLnk<Data>::operator=(BinaryTreeLnk<Data> && tree) noexcept {
  std::swap(size, tree.size);
  std::swap(root, tree.root);
  return *this;
}

/* ************************************************************************** */

// Comparison operators (BinaryTreeLnk)

template <typename Data>
inline bool BinaryTreeLnk<Data>::operator==(const BinaryTreeLnk<Data> & tree) const noexcept {
  return BinaryTree<Data>::operator==(tree);
}

template <typename Data>
inline bool BinaryTreeLnk<Data>::operator!=(const BinaryTreeLnk<Data> & tree) const noexcept {
  return !(*this == tree);
}

/* ************************************************************************** */

// Specific member functions (inherited from BinaryTree)

template <typename Data>
const typename BinaryTree<Data>::Node & BinaryTreeLnk<Data>::Root() const {
  if(size == 0) { throw std::length_error("Empty tree"); }
  return *root;
}

/* ************************************************************************** */

// Specific member functions (inherited from MutableBinaryTree)

template <typename Data>
typename MutableBinaryTree<Data>::MutableNode & BinaryTreeLnk<Data>::Root() {
  if(size == 0) { throw std::length_error("Empty tree"); }
  return *root;
}

/* ************************************************************************** */

// Specific member functions (inherited from ClearableContainer)

template <typename Data>
void BinaryTreeLnk<Data>::Clear() {
  delete root;
  root = nullptr;
  size = 0;
}

/* ************************************************************************** */

}
