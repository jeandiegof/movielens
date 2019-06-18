#include "entry/movie_rating.hpp"
#include <iostream>

namespace entry {

void movie_rating::print() {
    std::cout << "movieId " << _key << std::endl;
    std::cout << "\trating: " << _rating << std::endl;
}
}  // namespace entry