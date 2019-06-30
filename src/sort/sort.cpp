#include "sort/sort.hpp"

namespace sort {
void sort(std::vector<entry::movie>& list) {
    auto current_item = list[1];
    int32_t helper;

    for (uint32_t i = 1; i < list.size(); i++) {
        current_item = list[i];
        helper = i - 1;

        while (helper >= 0 && list[helper].rating() < current_item.rating()) {
            list[helper + 1] = list[helper];
            helper = helper - 1;
        }
        list[helper + 1] = current_item;
    }
}

void sort(std::vector<entry::rating>& list) {
    auto current_item = list[1];
    int32_t helper;

    for (uint32_t i = 1; i < list.size(); i++) {
        current_item = list[i];
        helper = i - 1;

        while (helper >= 0 && list[helper].key() > current_item.key()) {
            list[helper + 1] = list[helper];
            helper = helper - 1;
        }
        list[helper + 1] = current_item;
    }
}
}  // namespace sort