#pragma once
#include <map>
#include <vector>

namespace trie {
class tags_node {
   private:
    std::vector<uint32_t> _movie_ids;
    std::map<char, tags_node> _alphabet;

   public:
    tags_node() {}
    std::vector<uint32_t> is_last_char() const { return _movie_ids; }
    void set_last_char(uint32_t movie_id) { _movie_ids.push_back(movie_id); }

    void add_child(tags_node node, char index) {
        _alphabet.insert({index, std::move(node)});
    }

    tags_node* get_child(char index) {
        auto child = _alphabet.find(index);
        if (child != _alphabet.end()) {
            return &child->second;
        }
        return nullptr;
    }

    tags_node const* get_child(char index) const {
        auto child = _alphabet.find(index);
        if (child != _alphabet.end()) {
            return &child->second;
        }
        return nullptr;
    }
};
}  // namespace trie