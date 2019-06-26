#include "trie/node.hpp"
#include <iostream>

namespace trie {
void node::get_subwords(std::vector<uint32_t>& movie_ids) const {
    for (auto const& x : _alphabet) {
        auto movie_id = x.second.is_last_char();
        if (movie_id != 0) movie_ids.push_back(movie_id);
        auto next = &x.second;
        next->get_subwords(movie_ids);
    }
}
}  // namespace trie
