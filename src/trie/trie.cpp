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

void trie::contains_prefix(std::string const& prefix) const {
    auto node = &root;

    for (auto ch : prefix) {
        node = node->get_child(ch);
        if (node == nullptr) {
            std::cout << "Prefix " << prefix << " not found." << std::endl;
            return;
        }
    }
    std::cout << "Found prefix " << prefix << std::endl;
    std::cout << "Printing all subwords..." << std::endl;
    std::cout << node->is_last_char() << " " << std::endl;
    node->get_subwords(node);
}
}  // namespace trie
