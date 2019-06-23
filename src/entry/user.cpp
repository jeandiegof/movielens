#include "entry/user.hpp"
#include <iostream>

namespace entry {
void user::add_rating(std::pair<uint32_t, float> rating) {
    _ratings.push_back(rating);
}
void user::print() const {
    std::cout << "userId " << _user_id << std::endl;
    for (const auto& rating : _ratings) {
        std::cout << "\tmovieId: " << rating.first << std::endl;
        std::cout << "\t\trating: " << rating.second << std::endl;
    }
}

void user::clear() {
    set_key(0);
    _ratings.clear();
}
}  // namespace entry