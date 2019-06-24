#pragma once
#include "trie/node.hpp"
// heavily based on
// https://codereview.stackexchange.com/questions/202464/c-trie-implementation

namespace trie {
class trie {
   private:
    node root;

   public:
    void insert(std::string const&);
    bool contains(std::string const&) const;
};
}  // namespace trie