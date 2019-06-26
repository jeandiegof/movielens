#pragma once
#include "trie/node.hpp"
// heavily based on
// https://codereview.stackexchange.com/questions/202464/c-trie-implementation

namespace trie {
class trie {
   private:
    node root;

   public:
    void insert(std::string const&, uint32_t mark);
    uint32_t contains(std::string const&) const;
    std::vector<uint32_t> contains_prefix(std::string const& string) const;
};
}  // namespace trie