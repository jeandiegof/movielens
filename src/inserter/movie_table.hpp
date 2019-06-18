#pragma once
#include <fstream>
#include "csv/row.hpp"
#include "entry/movie.hpp"
#include "entry/movie_rating.hpp"
#include "hash_table/quadratic_probing.hpp"

namespace inserter {
void movie_table(std::ifstream& file, hash_table::quadratic_probing<uint32_t, entry::movie>& table);
void movie_table(std::ifstream& file, std::vector<entry::movie_rating>& table);
}