#pragma once
#include <fstream>
#include <map>

#include "csv/row.hpp"
#include "entry/movie.hpp"
#include "entry/rating.hpp"
#include "entry/user.hpp"
#include "hash_table/quadratic_probing.hpp"
#include "trie/tags_trie.hpp"
#include "trie/trie.hpp"

namespace inserter {
class inserter {
   public:
    using movie_table = hash_table::quadratic_probing<uint32_t, entry::movie>;
    using user_table = hash_table::quadratic_probing<uint32_t, entry::user>;
    using rating_map = std::map<uint32_t, std::pair<float, uint32_t>>;

    inserter(std::ifstream& movies, std::ifstream& ratings, std::ifstream& tags,
             movie_table& movie_table, user_table& user_table,
             trie::trie& trie, trie::tags_trie& tags_trie);
    void load();

   private:
    void from_tags();
    void from_movies();
    void from_ratings();
    void average_rating(rating_map& map);

    std::ifstream& _movies;
    std::ifstream& _ratings;
    std::ifstream& _tags;
    movie_table& _movie_table;
    user_table& _user_table;
    trie::trie& _trie;
    trie::tags_trie& _tags_trie;
    std::map<uint32_t, std::pair<float, uint32_t>> _rating_map;
};  // namespace movie_table
}  // namespace inserter