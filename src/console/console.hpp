#pragma once
#include <string>
#include "inserter/inserter.hpp"

namespace console {
class console {
   public:
    console(hash_table::quadratic_probing<uint32_t, entry::movie>& movie_table,
            hash_table::quadratic_probing<uint32_t, entry::user>& user_table,
            trie::trie& trie);
    void start();

   private:
    enum class query_class {
        movie,
        user,
        top_n,
        tags,
        unexpected,
        exit,
    };

    std::string get_query();
    bool handle_query(std::string query);
    void handle_movie(std::string query);
    void handle_user(std::string query);

    bool is_by_id(std::string const& query);
    void find_movie_id(std::string query);
    void find_movie_string(std::string query);

    query_class parse_query(std::string query);

    hash_table::quadratic_probing<uint32_t, entry::movie>& _movie_table;
    hash_table::quadratic_probing<uint32_t, entry::user>& _user_table;
    trie::trie& _trie;
};
}  // namespace console
