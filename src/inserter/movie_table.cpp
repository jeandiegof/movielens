#include "inserter/movie_table.hpp"
#include <algorithm>

std::istream& operator>>(std::istream& str, csv::row& data) {
    data.read_row(str);
    return str;
}

namespace inserter {
movie_table::movie_table(std::ifstream& movies, std::ifstream& ratings, table_type& table)
    : _movies(movies),
      _ratings(ratings),
      _table(table) {
}

void movie_table::load() {
    from_ratings();
    from_movies();
}

void movie_table::from_movies() {
    csv::row row;
    // eliminates the table header
    _movies >> row;

    while (_movies >> row) {
        uint32_t const movie_id = std::stoi(row[0]);

        entry::movie entry;
        entry.set_key(movie_id);
        entry.set_genres(row[2]);
        entry.set_average_rating(_rating_map[movie_id].first);
        entry.set_rating_count(_rating_map[movie_id].second);
        entry.print();

        _table.insert(entry.key(), entry);
    }
}

void movie_table::from_ratings() {
    std::vector<entry::rating> entries;
    csv::row row;
    _ratings >> row;

    std::cout << "Parsing..." << std::endl;
    while (_ratings >> row) {
        uint32_t const movie_id = std::stoi(row[1]);
        float const rating = std::stof(row[2]);

        entry::rating entry;
        entry.set_key(movie_id);
        entry.set_rating(rating);
        entries.push_back(entry);
    }
    average_rating(entries);
}

void movie_table::sort_rating(std::vector<entry::rating>& entries) {
    std::cout << "Sorting..." << std::endl;
    std::sort(entries.begin(), entries.end(), [](const auto& lhs, const auto& rhs) {
        return lhs.key() < rhs.key();
    });
}

void movie_table::average_rating(std::vector<entry::rating>& entries) {
    sort_rating(entries);
    std::cout << "Evaluating average rating..." << std::endl;
    auto last = entries[0];
    uint32_t occurrences = 0;
    float rating = 0;

    for (uint32_t i = 0; i < entries.size(); i++) {
        if (entries[i].key() == last.key()) {
            occurrences++;
            rating += entries[i].get_rating();
        } else {
            rating /= occurrences;
            _rating_map.insert({last.key(), {rating, occurrences}});
            last = entries[i];
            rating = entries[i].get_rating();
            occurrences = 1;
        }
    }
}
}  // namespace inserter