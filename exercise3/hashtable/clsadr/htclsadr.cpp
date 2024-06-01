
namespace lasd {

/* ************************************************************************** */

// Specific constructors

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const ulong size) {
  while (tablesize < size) { tablesize *= 2; }
  table.Resize(tablesize);
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const TraversableContainer<Data> & con) : HashTableClsAdr(con.Size()) {
  con.Traverse(
    [this](const Data & dat) {
      Insert(dat);
    }
  );
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const ulong size, const TraversableContainer<Data> & con) : HashTableClsAdr(size) {
  con.Traverse(
    [this](const Data & dat) {
      Insert(dat);
    }
  );
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(MappableContainer<Data> && con) : HashTableClsAdr(con.Size()) {
  con.Map(
    [this](Data & dat) {
      Insert(std::move(dat));
    }
  );
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const ulong size, MappableContainer<Data> && con) : HashTableClsAdr(size) {
  con.Map(
    [this](Data & dat) {
      Insert(std::move(dat));
    }
  );
}

/* ************************************************************************** */

// Copy constructor
template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const HashTableClsAdr<Data> & ht) : HashTable<Data>(ht) {
  table = ht.table;
}

// Move constructor
template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(HashTableClsAdr<Data> && ht) noexcept : HashTable<Data>(std::move(ht)) {
  std::swap(table, ht.table);
}

/* ************************************************************************** */

// Copy assignment
template <typename Data>
HashTableClsAdr<Data> & HashTableClsAdr<Data>::operator=(const HashTableClsAdr<Data> & ht) {
  HashTable<Data>::operator=(ht);
  table = ht.table;
  return *this;
}

// Move assignment
template <typename Data>
HashTableClsAdr<Data> & HashTableClsAdr<Data>::operator=(HashTableClsAdr<Data> && ht) noexcept {
  HashTable<Data>::operator=(std::move(ht));
  std::swap(table, ht.table);
  return *this;
}

/* ************************************************************************** */

// Comparison operators

template <typename Data>
bool HashTableClsAdr<Data>::operator==(const HashTableClsAdr<Data> & ht) const noexcept {
  if(size != ht.size) { return false; }

  bool check = true;

  for(ulong i=0; i<tablesize; ++i) {
    table[i].Traverse(
      [ht, &check](const Data & dat) {
        check &= ht.Exists(dat);
      }
    );
    if(!check) { return false; }
  }

  return true;
}

template <typename Data>
inline bool HashTableClsAdr<Data>::operator!=(const HashTableClsAdr<Data> & ht) const noexcept {
  return !(*this == ht);
}

/* ************************************************************************** */

// Specific member functions (inherited from DictionaryContainer)

template <typename Data>
bool HashTableClsAdr<Data>::Insert(const Data & dat) {
  if(Exists(dat)) { return false; }
  table[HashKey(dat)].InsertAtFront(dat);
  ++size;
  return true;
}

template <typename Data>
bool HashTableClsAdr<Data>::Insert(Data && dat) {
  if(Exists(dat)) { return false; }
  table[HashKey(dat)].InsertAtFront(std::move(dat));
  ++size;
  return true;
}

template <typename Data>
bool HashTableClsAdr<Data>::Remove(const Data & dat) {
  if(table[HashKey(dat)].Remove(dat)) {
    --size;
    return true;
  }
  return false;
}

/* ************************************************************************** */

// Specific member functions (inherited from TestableContainer)

template <typename Data>
inline bool HashTableClsAdr<Data>::Exists(const Data & dat) const noexcept {
  return table[HashKey(dat)].Exists(dat);
}

/* ************************************************************************** */

// Specific member functions (inherited from ResizableContainer)

template <typename Data>
void HashTableClsAdr<Data>::Resize(const ulong INtablesize) {
  if(tablesize == INtablesize) { return; }

  ulong newtablesize = MIN_TABLESIZE;
  while(newtablesize < INtablesize) {
    newtablesize *= 2;
  }

  HashTableClsAdr<Data> newht(newtablesize);
  for(ulong i = 0; i < tablesize; ++i) {
    table[i].Traverse(
      [&newht](const Data & dat) {
        newht.Insert(dat);
      }
    );
  }
  std::swap(*this, newht);
}

/* ************************************************************************** */

// Specific member functions (inherited from ClearableContainer)

template <typename Data>
void HashTableClsAdr<Data>::Clear() {
  HashTableClsAdr<Data> newht(MIN_TABLESIZE);
  std::swap(*this, newht);
}

/* ************************************************************************** */

}
