#pragma once
#include "entry/movie.hpp"
#include "entry/rating.hpp"

namespace sort {
void quicksort(std::vector<entry::rating>& list, int32_t begin, int32_t end);
void sort(std::vector<uint32_t>& list);
void sort(std::vector<entry::movie>& list);
void sort(std::vector<entry::rating>& list);
}  // namespace sort