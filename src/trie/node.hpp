#pragma once
#include <map>
#include <vector>

namespace trie {
class node {
   private:
    uint32_t _last_char;
    uint32_t movie_id;
    std::map<char, node> _alphabet;

   public:
    node() : _last_char{0} {}
    uint32_t is_last_char() const { return _last_char; }
    void set_last_char(uint32_t is_last_char) { _last_char = is_last_char; }
    void get_subwords(std::vector<uint32_t>& movie_ids) const;

    void add_child(node node, char index) {
        _alphabet.insert({index, std::move(node)});
    }

    node* get_child(char index) {
        auto child = _alphabet.find(index);
        if (child != _alphabet.end()) {
            return &child->second;
        }
        return nullptr;
    }

    node const* get_child(char index) const {
        auto child = _alphabet.find(index);
        if (child != _alphabet.end()) {
            return &child->second;
        }
        return nullptr;
    }
};
}  // namespace trie