#include "entry/movie.hpp"
#include <iomanip>
#include <iostream>

namespace entry {

void movie::set_genres(std::string const& genres) {
    _genres = genres;
}

void movie::print() const {
    std::cout << std::setw(65) << std::setfill(' ')
              << std::right
              << std::setw(8)
              << _key << "  "
              << std::left
              << std::setw(65) << std::setfill(' ')
              << ((_title.size() > 55) ? _title.substr(0, 55) + "..." : _title)
              << std::setw(45) << std::setfill(' ')
              << _genres
              << std::setw(8) << std::setfill(' ')
              << _rating << "  "
              << std::setw(8) << std::setfill(' ')
              << _rating_count
              << std::endl;
    std::cout << std::flush;
}
}  // namespace entry