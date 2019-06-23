#pragma once
#include <fstream>
#include <map>

#include "csv/row.hpp"
#include "entry/movie.hpp"
#include "entry/rating.hpp"
#include "entry/user.hpp"
#include "hash_table/quadratic_probing.hpp"

namespace inserter {
class inserter {
   public:
    using movie_table = hash_table::quadratic_probing<uint32_t, entry::movie>;
    using user_table = hash_table::quadratic_probing<uint32_t, entry::user>;

    inserter(std::ifstream& movies, std::ifstream& ratings,
             movie_table& movie_table, user_table& user_table);
    void load();

   private:
    void from_movies();
    void from_ratings();
    void average_rating(std::vector<entry::rating>& entries);
    void sort_rating(std::vector<entry::rating>& entries);

    std::ifstream& _movies;
    std::ifstream& _ratings;
    movie_table& _movie_table;
    user_table& _user_table;
    std::map<uint32_t, std::pair<float, uint32_t>> _rating_map;
};  // namespace movie_table
}  // namespace inserter