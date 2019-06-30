#include "entry/movie.hpp"
#include <iomanip>
#include <iostream>

namespace entry {

void movie::set_genres(std::string const& genres) {
    _genres = genres;
}

void movie::print() const {
    std::cout << std::right
              << std::setw(8) << _key << "  "
              << std::left
              << std::setw(65) << ((_title.size() > 45) ? _title.substr(0, 45) + "..." : _title)
              << std::setw(45)
              << _genres << std::setw(5) << _rating << "  "
              << std::setw(8) << _rating_count << std::endl;
    std::cout << std::flush;
}
}  // namespace entry