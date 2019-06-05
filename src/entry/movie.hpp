#pragma once
#include <string>
#include <vector>

namespace entry {
class movie {
   public:
    void set_key(uint32_t key) { _key = key; }
    void set_average_rating(float rating) { _rating = rating; }
    void set_rating_count(uint32_t count) { _rating_count = count; }
    void set_genres(std::string const& genres);
    uint32_t key() const { return _key; }

    void print();

   private:
    uint32_t _key;
    float _rating;
    uint32_t _rating_count;
    std::string _genres;
};
}  // namespace entry