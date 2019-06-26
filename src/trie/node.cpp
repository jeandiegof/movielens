#include "trie/node.hpp"
#include <iostream>

namespace trie {
void node::get_subwords() const {
    for (auto const& x : _alphabet) {
        std::cout << x.first << " : " << x.second.is_last_char() << std::endl;
        auto next = &x.second;
        next->get_subwords();
    }
}
}  // namespace trie
