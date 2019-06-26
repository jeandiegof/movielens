#include "entry/movie.hpp"
#include <iostream>

namespace entry {

void movie::set_genres(std::string const& genres) {
    _genres = genres;
}

void movie::print() const {
    std::cout << _key << "\t";
    std::cout << _title << "\t";
    std::cout << _genres << "\t";
    std::cout << _rating << "\t";
    std::cout << _rating_count << std::endl;
}
}  // namespace entry