#include <fstream>
#include <iostream>
#include <string>
//#include "csv/row.hpp"
//#include "entry/movie.hpp"
//#include "hash_table/quadratic_probing.hpp"
#include "inserter/movie_table.hpp"

int main() {
    hash_table::quadratic_probing<uint32_t, entry::movie> hash_table;
    hash_table.set_size(50957);
    std::ifstream file("dataset/movie.csv");
    inserter::movie_table(file, hash_table);

    auto result = hash_table.find(5816);
    result.print();
    std::cout << "Done." << std::endl;
    return 0;
}