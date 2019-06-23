#include "entry/movie.hpp"
#include <iostream>

namespace entry {

void movie::set_genres(std::string const& genres) {
    _genres = genres;
}

void movie::print() const {
    std::cout << "movieId " << _key << std::endl;
    std::cout << "\taverage rating: " << _rating << std::endl;
    std::cout << "\trating count: " << _rating_count << std::endl;
    std::cout << "\tgenres: " << _genres << std::endl;
}
}  // namespace entry