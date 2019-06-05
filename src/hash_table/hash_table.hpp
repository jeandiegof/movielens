#pragma once
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

namespace hash_table {
template <typename K, typename T>
class hash_table {
   public:
    hash_table();
    virtual ~hash_table() { std::cout << "~hash_table()" << std::endl; };
    virtual bool insert(const K& key, const T& data) = 0;
    virtual const T& find(const K& key) = 0;

    void set_size(uint32_t size);
    uint32_t size();
    uint32_t collisions();
    void print();
    float load_factor();

   protected:
    virtual uint32_t hash(const K& key) = 0;
    std::vector<T> table;
    bool _is_full;
    uint16_t _insertions;
    uint32_t _collisions;
};

template <typename K, typename T>
hash_table<K, T>::hash_table()
    : table(0),
      _is_full(false),
      _insertions(0),
      _collisions(0) {
    std::cout << "hash_table()" << std::endl;
}

template <typename K, typename T>
void hash_table<K, T>::set_size(uint32_t size) {
    table.resize(size);
}

template <typename K, typename T>
uint32_t hash_table<K, T>::size() {
    return table.size();
}

template <typename K, typename T>
void hash_table<K, T>::print() {
    for (uint16_t i = 0; i < table.size(); i++) {
        std::cout << (uint16_t)i << "\t\t" << table[i] << std::endl;
    }
}

template <typename K, typename T>
float hash_table<K, T>::load_factor() {
    return (100.0 * _insertions) / table.size();
}

template <typename K, typename T>
uint32_t hash_table<K, T>::collisions() {
    return _collisions;
}
}  // namespace hash_table