#include "inserter/inserter.hpp"
#include <algorithm>

std::istream& operator>>(std::istream& str, csv::row& data) {
    data.read_row(str);
    return str;
}

namespace inserter {
inserter::inserter(std::ifstream& movies, std::ifstream& ratings,
                   movie_table& movie_table, user_table& user_table)
    : _movies(movies),
      _ratings(ratings),
      _movie_table(movie_table),
      _user_table(user_table) {
}

void inserter::load() {
    from_ratings();
    from_movies();
}

void inserter::from_movies() {
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

        _movie_table.insert(entry.key(), entry);
    }
}

void inserter::from_ratings() {
    std::vector<entry::rating> rating_entries;

    entry::user user_entry;
    uint32_t _last_user = 1;
    user_entry.set_key(1);

    std::cout << "Parsing..." << std::endl;
    csv::row row;
    _ratings >> row;

    while (_ratings >> row) {
        uint32_t const user_id = std::stoi(row[0]);
        uint32_t const movie_id = std::stoi(row[1]);
        float const rating = std::stof(row[2]);

        entry::rating rating_entry;
        rating_entry.set_key(movie_id);
        rating_entry.set_rating(rating);
        rating_entries.push_back(rating_entry);

        if (_last_user != user_id) {
            _user_table.insert(user_entry.key(), user_entry);
            user_entry.clear();
            user_entry.set_key(user_id);
            user_entry.add_rating({movie_id, rating});
            _last_user = user_id;
        } else {
            user_entry.add_rating({movie_id, rating});
        }
    }
    // don't forget the last one
    _user_table.insert(user_entry.key(), user_entry);
    average_rating(rating_entries);
}

void inserter::sort_rating(std::vector<entry::rating>& entries) {
    std::cout << "Sorting..." << std::endl;
    std::sort(entries.begin(), entries.end(), [](const auto& lhs, const auto& rhs) {
        return lhs.key() < rhs.key();
    });
}

void inserter::average_rating(std::vector<entry::rating>& entries) {
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