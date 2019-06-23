#pragma once
#include <cstdint>
#include <vector>

namespace entry {
class user {
   public:
    void set_key(uint32_t key) { _user_id = key; }
    inline uint32_t key() const { return _user_id; }
    void add_rating(std::pair<uint32_t, float> rating);
    void print() const;
    void clear();

   private:
    uint32_t _user_id;
    std::vector<std::pair<uint32_t, float>> _ratings;
};
}  // namespace entry