
namespace lasd {

/* ************************************************************************** */

#include <string>

/* ************************************************************************** */

// Specific function (Hashable<int>)
template <>
class Hashable<int> {

public:

  virtual ulong operator()(const int & dat) const noexcept {
    return dat * dat;
  }

};

// Specific function (Hashable<double>)
template <>
class Hashable<double> {

public:

  virtual ulong operator()(const double & dat) const noexcept {
    long intgpart = floor(dat);
    long fracpart = pow(2, 24) * (dat - intgpart);
    return intgpart * fracpart;
  }

};

// Specific function (Hashable<string>)
template <>
class Hashable<std::string> {

public:

  virtual ulong operator()(const std::string & dat) const noexcept {
    ulong hash = 5381; // Magic number
    for(ulong i = 0; i < dat.length(); ++i) {
      hash = ((hash << 5) + hash) + dat[i];
    }
    return hash;
  }

};

/* ************************************************************************** */

// Default constructor (HashTable)
template <typename Data>
HashTable<Data>::HashTable() {
  acoeff = dista(gen) * 2 + 1;
  bcoeff = distb(gen); 
}

/* ************************************************************************** */

// Copy constructor (HashTable)
template <typename Data>
HashTable<Data>::HashTable(const HashTable<Data> & ht) {
  size = ht.size;
  acoeff = ht.acoeff;
  bcoeff = ht.bcoeff;
  tablesize = ht.tablesize;
}

// Move constructor (HashTable)
template <typename Data>
HashTable<Data>::HashTable(HashTable<Data> && ht) noexcept {
  std::swap(size, ht.size);
  std::swap(acoeff, ht.acoeff);
  std::swap(bcoeff, ht.bcoeff);
  std::swap(tablesize, ht.tablesize);
}

/* ************************************************************************** */

// Copy assignment (HashTable)
template <typename Data>
HashTable<Data> & HashTable<Data>::operator=(const HashTable<Data> & ht) noexcept {
  size = ht.size;
  acoeff = ht.acoeff;
  bcoeff = ht.bcoeff;
  tablesize = ht.tablesize;
  return *this;
}

// Move assignment (HashTable)
template <typename Data>
HashTable<Data> & HashTable<Data>::operator=(HashTable<Data> && ht) noexcept {
  std::swap(size, ht.size);
  std::swap(acoeff, ht.acoeff);
  std::swap(bcoeff, ht.bcoeff);
  std::swap(tablesize, ht.tablesize);
  return *this;
}

/* ************************************************************************** */

// Auxiliary member functions (HashTable)

template <typename Data>
inline ulong HashTable<Data>::HashKey(const Data & dat) const noexcept {
  return HashKey(enchash(dat));
}

template <typename Data>
inline ulong HashTable<Data>::HashKey(ulong key) const noexcept {
  return ((acoeff * key + bcoeff) % prime) % tablesize;
}

/* ************************************************************************** */

}
