#include <fstream>
#include <iostream>
#include <string>
#include "inserter/movie_table.hpp"

int main() {
    hash_table::quadratic_probing<uint32_t, entry::movie> hash_table;
    hash_table.set_size(50957);

    std::ifstream movies_file("dataset/movie.csv");
    std::ifstream ratings_file("dataset/minirating.csv");
    inserter::movie_table movies(movies_file, ratings_file, hash_table);
    movies.load();

    auto result = hash_table.find(5816);
    result.print();
    std::cout << "Done." << std::endl;
    return 0;
}