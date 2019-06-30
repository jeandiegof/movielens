#include "sort/sort.hpp"
#include <algorithm>

namespace sort {
int32_t partition(std::vector<entry::rating>& list, int32_t low, int32_t high) {
    float pivot = list[high].get_rating();
    int32_t i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (list[j].get_rating() <= pivot) {
            i++;
            std::swap(list[i], list[j]);
        }
    }
    std::swap(list[i + 1], list[high]);
    return (i + 1);
}

void quicksort(std::vector<entry::rating>& list, int32_t low, int32_t high) {
    if (low < high) {
        int32_t pi = partition(list, low, high);

        quicksort(list, low, pi - 1);
        quicksort(list, pi + 1, high);
    }
}

void sort(std::vector<uint32_t>& list) {
    auto current_item = list[1];
    int32_t helper;

    for (uint32_t i = 1; i < list.size(); i++) {
        current_item = list[i];
        helper = i - 1;

        while (helper >= 0 && list[helper] > current_item) {
            list[helper + 1] = list[helper];
            helper = helper - 1;
        }
        list[helper + 1] = current_item;
    }
}

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