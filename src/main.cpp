#include <fstream>
#include <iostream>
#include <string>
#include "entry/user.hpp"
#include "inserter/inserter.hpp"
#include "trie/trie.hpp"

int main() {
    trie::trie trie;
    trie.insert("jean");
    trie.insert("jea");

    std::cout << "jean" << trie.contains("jean") << std::endl;
    std::cout << "j" << trie.contains("j") << std::endl;
    std::cout << "jea" << trie.contains("jea") << std::endl;
    std::cout << "jea" << trie.contains("je") << std::endl;
    return 0;  // testing trie implementation

    hash_table::quadratic_probing<uint32_t, entry::movie> movie_table;
    movie_table.set_size(50957);

    hash_table::quadratic_probing<uint32_t, entry::user> user_table;
    user_table.set_size(173137);

    std::ifstream movies_file("dataset/movie.csv");
    std::ifstream ratings_file("dataset/rating.csv");
    inserter::inserter movies(movies_file, ratings_file,
                              movie_table, user_table);
    movies.load();

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