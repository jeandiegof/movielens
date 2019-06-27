#pragma once
#include <string>
#include <vector>

namespace entry {
class movie {
   public:
    void set_key(uint32_t key) { _key = key; }
    void set_title(std::string const title) { _title = title; };
    void set_average_rating(float rating) { _rating = rating; }
    void set_rating_count(uint32_t count) { _rating_count = count; }
    void set_genres(std::string const& genres);

    uint32_t key() const { return _key; }
    std::string const& title() const { return _title; }
    float rating() const { return _rating; }
    uint32_t count() const { return _rating_count; }
    std::string genres() const { return _genres; }

    void print() const;

   private:
    uint32_t _key;
    float _rating;
    uint32_t _rating_count;
    std::string _genres;
    std::string _title;
};
}  // namespace entry