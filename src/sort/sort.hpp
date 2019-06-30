#pragma once
#include "entry/movie.hpp"
#include "entry/rating.hpp"

namespace sort {
void sort(std::vector<uint32_t>& list);
void sort(std::vector<entry::movie>& list);
void sort(std::vector<entry::rating>& list);
}  // namespace sort