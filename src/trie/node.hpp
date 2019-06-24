#pragma once
#include <map>

namespace trie {
class node {
   private:
    bool _last_char;
    uint32_t movie_id;
    std::map<char, node> _alphabet;

   public:
    node() : _last_char{false} {}
    bool is_last_char() const { return _last_char; }
    void set_last_char(bool is_last_char) { _last_char = is_last_char; }

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