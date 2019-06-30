#pragma once
#include <string>
#include "inserter/inserter.hpp"

namespace console {
class console {
   public:
    console(hash_table::quadratic_probing<uint32_t, entry::movie>& movie_table,
            hash_table::quadratic_probing<uint32_t, entry::user>& user_table,
            trie::trie& trie, trie::tags_trie& tags_trie);
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
    void handle_top_n(std::string query);
    void handle_tags(std::string query);

    bool check_genre(entry::movie& movie, std::string genre);
    bool is_by_id(std::string const& query);
    void find_movie_id(std::string query);
    void find_movie_string(std::string query);

    query_class parse_query(std::string query);

    hash_table::quadratic_probing<uint32_t, entry::movie>& _movie_table;
    hash_table::quadratic_probing<uint32_t, entry::user>& _user_table;
    trie::trie& _trie;
    trie::tags_trie& _tags_trie;
};
}  // namespace console
