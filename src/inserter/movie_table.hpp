#pragma once
#include <fstream>
#include <map>

#include "csv/row.hpp"
#include "entry/movie.hpp"
#include "entry/rating.hpp"
#include "hash_table/quadratic_probing.hpp"

namespace inserter {
class movie_table {
   public:
    using table_type = hash_table::quadratic_probing<uint32_t, entry::movie>;
    movie_table(std::ifstream& movies, std::ifstream& ratings, table_type& table);
    void load();

   private:
    void from_movies();
    void from_ratings();
    void average_rating(std::vector<entry::rating>& entries);
    void sort_rating(std::vector<entry::rating>& entries);

    std::ifstream& _movies;
    std::ifstream& _ratings;
    table_type& _table;
    std::map<uint32_t, std::pair<float, uint32_t>> _rating_map;
};  // namespace movie_table
}  // namespace inserter