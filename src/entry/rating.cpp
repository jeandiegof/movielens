#include "entry/rating.hpp"
#include <iostream>

namespace entry {
void rating::print() {
    std::cout << "movieId " << _key << std::endl;
    std::cout << "\trating: " << _rating << std::endl;
}
}  // namespace entry