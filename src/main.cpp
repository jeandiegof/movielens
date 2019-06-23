#include <fstream>
#include <iostream>
#include <string>
#include "inserter/inserter.hpp"

#include "entry/user.hpp"

int main() {
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