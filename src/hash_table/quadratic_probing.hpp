#pragma once
#include <numeric>
#include "hash_table.hpp"

namespace hash_table {
template <typename K, typename T>
class quadratic_probing : public hash_table<K, T> {
   public:
    using base = hash_table<K, T>;
    quadratic_probing() {}
    ~quadratic_probing() {}
    bool insert(const K& key, const T& d) override;
    const T find(const K& key) override;

   private:
    virtual uint32_t hash(const K& d) override;
};

template <typename K, typename T>
uint32_t quadratic_probing<K, T>::hash(const K& key) {
    return 1 + (key % (base::table.size() - 1));
}

template <typename K, typename T>
bool quadratic_probing<K, T>::insert(const K& key, const T& d) {
    if (hash_table<K, T>::_is_full) {
        std::cout << "Error inserting data. The table is full" << std::endl;
        return false;
    }

    K hash_value = hash(key);
    while (hash_table<K, T>::table[hash_value].key() != 0 &&
           hash_table<K, T>::table[hash_value].key() != key) {
        hash_value = hash(hash_value + 1);
    }

    if (base::table[hash_value].key() != 0) {
        std::cout << "The table is full!" << std::endl;
        std::cout << std::flush;
        abort();  // for tests only
        return false;
    }
    base::table[hash_value] = d;
    return true;
}

// it's linear...
template <typename K, typename T>
const T quadratic_probing<K, T>::find(const K& key) {
    K hash_value = hash(key);

    while (base::table[hash_value].key() != 0 &&
           base::table[hash_value].key() != key) {
        hash_value = hash(hash_value + 1);
    }

    if (base::table[hash_value].key() == 0) {
        std::cout << "Error: " << key << " not found" << std::endl;
        return {};
    } else {
        return base::table[hash_value];
    }
}
}  // namespace hash_table