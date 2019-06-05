#include <fstream>
#include <iostream>
#include <string>
#include "csv/row.hpp"
#include "entry/movie.hpp"
#include "hash_table/quadratic_probing.hpp"

std::istream& operator>>(std::istream& str, csv::row& data) {
    data.read_row(str);
    return str;
}

int main() {
    csv::row row;
    std::ifstream file("dataset/minirating.csv");

    while (file >> row) {
        std::cout << row[3] << std::endl;
    }

    hash_table::quadratic_probing<uint32_t, entry::movie> hash_table;
    entry::movie some_entry;
    some_entry.set_key(1000);
    some_entry.set_average_rating(4.7);
    some_entry.set_rating_count(124);
    some_entry.set_genres("Action|Fiction");
    some_entry.print();

    return 0;
}