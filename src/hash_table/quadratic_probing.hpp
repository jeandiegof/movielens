#pragma once
#include <numeric>
#include "hash_table.hpp"

namespace hash_table {
template <typename K, typename T>
class quadratic_probing : public hash_table<K, T> {
   public:
    quadratic_probing() { std::cout << "quadractic_probing()" << std::endl; }
    ~quadratic_probing() { std::cout << "~quadractic_probing()" << std::endl; }
    bool insert(const K& key, const T& d) override;
    const T& find(const K& key) override;

   private:
    virtual uint32_t hash(const K& d) override;
};

template <typename K, typename T>
uint32_t quadratic_probing<K, T>::hash(const K& key) {
    // TODO remove this hash function
    return key % hash_table<K, T>::table.size();
}

template <typename K, typename T>
bool quadratic_probing<K, T>::insert(const K& key, const T& d) {
    if (hash_table<K, T>::_is_full) {
        return false;
    }

    K hash_value = hash(key);
    for (uint32_t i = 0; i < hash_table<K, T>::table.size(); i++) {
        const uint32_t target_index = static_cast<uint32_t>((hash_value + std::pow(i, 2))) % hash_table<K, T>::table.size();
        if (hash_table<K, T>::table[target_index].key() != 0) {
            hash_table<K, T>::table[target_index] = d;
            hash_table<K, T>::_insertions++;
            return true;
        }
        if (hash_value == target_index) {
            hash_table<K, T>::_collisions++;
        }
    }
    hash_table<K, T>::_is_full = true;
    return false;
}

template <typename K, typename T>
const T& quadratic_probing<K, T>::find(const K& key) {
    uint16_t count = 0;
    K hash_value = hash(key);

    for (uint16_t i = 0; i < hash_table<K, T>::table.size(); i++) {
        count++;
        const uint32_t target_index = static_cast<uint32_t>((hash_value + std::pow(i, 2))) % hash_table<K, T>::table.size();
        if (hash_table<K, T>::table[target_index].key() == key) {
            return hash_table<K, T>::table[target_index];
        }
    }
    // Returns a reference to the first element if the target
    // element was not found. Why???
    return hash_table<K, T>::table[0];
}
}