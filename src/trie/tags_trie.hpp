#pragma once
#include "trie/tags_node.hpp"
// heavily based on
// https://codereview.stackexchange.com/questions/202464/c-trie-implementation

namespace trie {
class tags_trie {
   private:
    tags_node root;

   public:
    void insert(std::string const&, uint32_t mark);
    std::vector<uint32_t> contains(std::string const&) const;
};
}  // namespace trie