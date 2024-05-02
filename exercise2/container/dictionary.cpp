
namespace lasd {

/* ************************************************************************** */

// Specific member functions(DictionaryContainer)

template <typename Data>
inline bool DictionaryContainer<Data>::InsertAll(const TraversableContainer<Data>& con) {
  bool inserted = true;
  con.Traverse(
    [this, &inserted](const Data& data) {
      inserted &= Insert(data);
    }
  );
  return inserted;
}

template <typename Data>
inline bool DictionaryContainer<Data>::InsertAll(MappableContainer<Data>&& con) {
  bool inserted = true;
  con.Map(
    [this, &inserted](Data& data) {
      inserted &= Insert(std::move(data));
    }
  );
  return inserted;
}

template <typename Data>
inline bool DictionaryContainer<Data>::RemoveAll(const TraversableContainer<Data>& con) {
  bool removed = true;
  con.Traverse(
    [this, &removed](const Data& data) {
      removed &= Remove(data);
    }
  );
  return removed;
}

template <typename Data>
inline bool DictionaryContainer<Data>::InsertSome(const TraversableContainer<Data>& con) {
  bool inserted = false;
  con.Traverse(
    [this, &inserted](const Data& data) {
      inserted |= Insert(data);
    }
  );
  return inserted;
}

template <typename Data>
inline bool DictionaryContainer<Data>::InsertSome(MappableContainer<Data>&& con) {
  bool inserted = false;
  con.Map(
    [this, &inserted](Data& data) {
      inserted |= Insert(std::move(data));
    }
  );
  return inserted;
}

template <typename Data>
inline bool DictionaryContainer<Data>::RemoveSome(const TraversableContainer<Data>& con) {
  bool removed = false;
  con.Traverse(
    [this, &removed](const Data& data) {
      removed |= Remove(data);
    }
  );
  return removed;
}

/* ************************************************************************** */

}