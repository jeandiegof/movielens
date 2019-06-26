#include <fstream>
#include <iostream>
#include <string>
#include "console/console.hpp"
#include "entry/user.hpp"
#include "inserter/inserter.hpp"
#include "trie/trie.hpp"

int main() {
    hash_table::quadratic_probing<uint32_t, entry::movie> movie_table;
    movie_table.set_size(50957);

    hash_table::quadratic_probing<uint32_t, entry::user> user_table;
    user_table.set_size(173137);

    std::ifstream movies_file("dataset/movie.csv");
    std::ifstream ratings_file("dataset/rating.csv");
    trie::trie trie;

    inserter::inserter database(movies_file, ratings_file,
                                movie_table, user_table, trie);
    database.load();

    console::console console(movie_table, user_table, trie);
    console.start();

    return 0;

    std::cout << "Searching..." << std::endl;
    std::cout << std::flush;
    auto k = user_table.find(5518);
    k.print();

    k = user_table.find(138490);
    k.print();

    k = user_table.find(138493);
    k.print();

    return 0;
}