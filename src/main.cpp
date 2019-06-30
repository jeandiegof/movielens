#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include "console/console.hpp"
#include "entry/user.hpp"
#include "inserter/inserter.hpp"
#include "sort/sort.hpp"
#include "trie/tags_trie.hpp"
#include "trie/trie.hpp"

int main() {
    hash_table::quadratic_probing<uint32_t, entry::movie> movie_table;
    movie_table.set_size(50957);

    hash_table::quadratic_probing<uint32_t, entry::user> user_table;
    user_table.set_size(173137);

    std::ifstream movies_file("dataset/movie.csv");
    std::ifstream ratings_file("dataset/rating.csv");
    std::ifstream tags_file("dataset/tag.csv");

    trie::trie trie;
    trie::tags_trie tags_trie;

    inserter::inserter database(movies_file, ratings_file, tags_file,
                                movie_table, user_table,
                                trie, tags_trie);
    database.load();

    movies_file.close();
    ratings_file.close();
    tags_file.close();

    console::console console(movie_table, user_table, trie, tags_trie);
    console.start();

    return 0;
}