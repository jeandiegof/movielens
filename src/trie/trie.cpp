#include "trie/trie.hpp"
#include <iostream>
#include <vector>

namespace trie {
void trie::insert(std::string const& string, uint32_t mark) {
    auto node = &root;

    for (auto ch : string) {
        auto child = node->get_child(ch);

        if (child == nullptr) {
            node->add_child({}, ch);
            child = node->get_child(ch);
        }
        node = child;
    }
    node->set_last_char(mark);
}

uint32_t trie::contains(std::string const& string) const {
    auto node = &root;

    for (auto ch : string) {
        node = node->get_child(ch);
        if (node == nullptr) {
            return false;
        }
    }
    return node->is_last_char();
}

std::vector<uint32_t> trie::contains_prefix(std::string const& prefix) const {
    auto node = &root;

    for (auto ch : prefix) {
        node = node->get_child(ch);
        if (node == nullptr) {
            std::cout << "Prefix " << prefix << " not found." << std::endl;
            return {};
        }
    }

    std::vector<uint32_t> movie_ids;
    if (node->is_last_char()) {
        movie_ids.push_back(node->is_last_char());
    }
    node->get_subwords(movie_ids);

    return movie_ids;
}

std::vector<uint32_t> trie::subwords() {
    auto node = &root;
    std::vector<uint32_t> movie_ids;
    node->get_subwords(movie_ids);

    return movie_ids;
}
}  // namespace trie
