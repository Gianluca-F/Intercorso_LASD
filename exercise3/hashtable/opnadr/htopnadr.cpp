
namespace lasd {

/* ************************************************************************** */

// Specific constructors

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const ulong size) : HashTable<Data>::HashTable() {
  ulong newtablesize = MIN_TABLESIZE;
  while(newtablesize < size) {
    newtablesize *= 2;
  }
  tablesize = newtablesize;
  table.Resize(tablesize);
  states.Resize(tablesize);
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const TraversableContainer<Data> & con) : HashTableOpnAdr(con.Size()) {
  con.Traverse(
    [this](const Data & dat) {
      Insert(dat);
    }
  );
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const ulong size, const TraversableContainer<Data> & con) : HashTableOpnAdr(size) {
  con.Traverse(
    [this](const Data & dat) {
      Insert(dat);
    }
  );
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(MappableContainer<Data> && con) : HashTableOpnAdr(con.Size()) {
  con.Map(
    [this](Data & dat) {
      Insert(std::move(dat));
    }
  );
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const ulong size, MappableContainer<Data> && con) : HashTableOpnAdr(size) {
  con.Map(
    [this](Data & dat) {
      Insert(std::move(dat));
    }
  );
}

/* ************************************************************************** */

// Copy constructor
template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const HashTableOpnAdr<Data> & ht) : HashTable<Data>(ht) {
  table = ht.table;
  states = ht.states;
}

// Move constructor
template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(HashTableOpnAdr<Data> && ht) noexcept : HashTable<Data>(std::move(ht)) {
  std::swap(table, ht.table);
  std::swap(states, ht.states);
}

/* ************************************************************************** */

// Copy assignment
template <typename Data>
HashTableOpnAdr<Data> & HashTableOpnAdr<Data>::operator=(const HashTableOpnAdr<Data> & ht) {
  HashTable<Data>::operator=(ht);
  table = ht.table;
  states = ht.states;
  return *this;
}

// Move assignment
template <typename Data>
HashTableOpnAdr<Data> & HashTableOpnAdr<Data>::operator=(HashTableOpnAdr<Data> && ht) noexcept {
  HashTable<Data>::operator=(std::move(ht));
  std::swap(table, ht.table);
  std::swap(states, ht.states);
  return *this;
}

/* ************************************************************************** */

// Comparison operators

template <typename Data>
bool HashTableOpnAdr<Data>::operator==(const HashTableOpnAdr<Data> & ht) const noexcept {
  if(size != ht.size) { return false; }

  for(ulong i = 0; i < tablesize; ++i) {
    if(states[i] == state::FULL) {
      if(!ht.Exists(table[i])) {
        return false;
      }
    }
  }
  return true;
}

template <typename Data>
inline bool HashTableOpnAdr<Data>::operator!=(const HashTableOpnAdr<Data> & ht) const noexcept {
  return !(*this == ht);
}

/* ************************************************************************** */

// Specific member functions (inherited from DictionaryContainer)

template <typename Data>
bool HashTableOpnAdr<Data>::Insert(const Data & dat) {
  if(size >= tablesize / 2) {
    Expand();
  }

  ulong index = 0;
  ulong key = FindEmpty(dat, index);

  /* ~~ Case 1: Cella piena => dato presente ~~~ */
  if(states[key] == state::FULL) {
    return false;
  }

  /* ~~~ Case 2: cella logicamente vuota => il dato potrebbe essere altrove ~~~ */
  if(states[key] == state::DELETED) {
    if(Remove(dat, ++index)) {
      table[key] = dat;
      states[key] = state::FULL;
      return false;
    }
  }

  /* ~~~ Case 3: cella fisicamente vuota => il dato non è presente ~~~ */
  ++size;
  table[key] = dat;
  states[key] = state::FULL;
  return true;
}

template <typename Data>
bool HashTableOpnAdr<Data>::Insert(Data && dat) {
  if(size >= tablesize / 2) {
    Expand();
  }

  ulong index = 0;
  ulong key = FindEmpty(dat, index);

  /* ~~ Case 1: Cella piena => dato presente ~~~ */
  if(states[key] == state::FULL) {
    return false;
  }

  /* ~~~ Case 2: cella logicamente vuota => il dato potrebbe essere altrove ~~~ */
  if(states[key] == state::DELETED) {
    if(Remove(dat, ++index)) {
      table[key] = std::move(dat);
      states[key] = state::FULL;
      return false;
    }
  }

  /* ~~~ Case 3: cella fisicamente vuota => il dato non è presente ~~~ */
  ++size;
  table[key] = std::move(dat);
  states[key] = state::FULL;
  return true;
}

template <typename Data>
bool HashTableOpnAdr<Data>::Remove(const Data & dat) {
  if(size <= tablesize / 8) {
    Reduce();
  }

  ulong index = 0;
  if(Remove(dat, index)) {
    --size;
    return true;
  }
  return false;
}

/* ************************************************************************** */

// Specific member functions (inherited from TestableContainer)

template <typename Data>
bool HashTableOpnAdr<Data>::Exists(const Data & dat) const noexcept {
  ulong index = 0;
  ulong key = Find(dat, index);
  return ((states[key] == state::FULL) && (table[key] == dat));
}

/* ************************************************************************** */

// Specific member functions (inherited from ResizableContainer)

template <typename Data>
void HashTableOpnAdr<Data>::Resize(const ulong INtablesize) {
  ulong newtablesize = MIN_TABLESIZE;
  while(newtablesize < INtablesize) {
    newtablesize *= 2;
  }
  HashTableOpnAdr<Data> newht(newtablesize);
  for(ulong i = 0; i < tablesize; ++i) {
    if(states[i] == state::FULL) {
      newht.Insert(table[i]);
    }
  }
  std::swap(*this, newht);
}

/* ************************************************************************** */

// Specific member functions (inherited from ClearableContainer)

template <typename Data>
void HashTableOpnAdr<Data>::Clear() {
  HashTableOpnAdr<Data> newht(MIN_TABLESIZE);
  std::swap(*this, newht);
}

/* ************************************************************************** */

// Auxiliary member functions

template <typename Data>
inline ulong HashTableOpnAdr<Data>::HashKey(const ulong key, const ulong i) const noexcept {
  return (key + (i*(i+1)) / 2) % tablesize;
}

template <typename Data>
ulong HashTableOpnAdr<Data>::Find(const Data & dat, ulong & i) const noexcept {
  ulong hash = HashKey(dat);
  ulong key = hash;
  while(i<tablesize) {
    key = HashKey(hash, i);
    if(states[key] == state::EMPTY) {
      return key;
    }
    if(states[key] == state::FULL && table[key] == dat) {
      return key;
    }
    ++i;
  }
  return key;
}

template <typename Data>
ulong HashTableOpnAdr<Data>::FindEmpty(const Data & dat, ulong & i) const noexcept {
  ulong hash = HashKey(dat);
  ulong key = hash;
  while(i<tablesize) {
    key = HashKey(hash, i);
    if(states[key] == state::EMPTY || states[key] == state::DELETED) {
      return key;
    }
    if(states[key] == state::FULL && table[key] == dat) {
      return key;
    }
    ++i;
  }
  return key;
}

template <typename Data>
bool HashTableOpnAdr<Data>::Remove(const Data & dat, ulong & i) noexcept {
  ulong hash = HashKey(dat);
  ulong key = hash;
  while(i<tablesize) {
    key = HashKey(hash, i);
    if(states[key] == state::EMPTY) {
      return false;
    }
    if(states[key] == state::FULL && table[key] == dat) {
      states[key] = state::DELETED;
      return true;
    }
    ++i;
  }
  return false;
}

template <typename Data>
void HashTableOpnAdr<Data>::Expand() {
  Resize(tablesize * 2);
}

template <typename Data>
void HashTableOpnAdr<Data>::Reduce() {
  Resize(tablesize / 2);
}

/* ************************************************************************** */

}
