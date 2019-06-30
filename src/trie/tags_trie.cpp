#include "trie/tags_trie.hpp"
#include <iostream>
#include <vector>

namespace trie {
void tags_trie::insert(std::string const& string, uint32_t mark) {
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

std::vector<uint32_t> tags_trie::contains(std::string const& string) const {
    auto node = &root;

    for (auto ch : string) {
        node = node->get_child(ch);
        if (node == nullptr) {
            return {};
        }
    }
    return node->is_last_char();
}
}  // namespace trie
