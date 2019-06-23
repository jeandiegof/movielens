#pragma once
#include <string>
#include <vector>

namespace entry {
class rating {
   public:
    void set_key(uint32_t key) { _key = key; }
    void set_rating(float rating) { _rating = rating; }
    uint32_t key() const { return _key; }
    float get_rating() const { return _rating; }

    void print();

   private:
    uint32_t _key;
    float _rating;
};
}  // namespace entry