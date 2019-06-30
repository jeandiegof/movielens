#include "inserter/inserter.hpp"
#include <algorithm>
#include <sstream>
#include "sort/sort.hpp"

std::istream& operator>>(std::istream& str, csv::row& data) {
    data.read_row(str);
    return str;
}

namespace inserter {
inserter::inserter(std::ifstream& movies, std::ifstream& ratings, std::ifstream& tags,
                   movie_table& movie_table, user_table& user_table,
                   trie::trie& trie, trie::tags_trie& tags_trie)
    : _movies(movies),
      _ratings(ratings),
      _tags(tags),
      _movie_table(movie_table),
      _user_table(user_table),
      _trie(trie),
      _tags_trie(tags_trie) {
}

void inserter::load() {
    from_ratings();
    from_movies();
    from_tags();
}

void inserter::from_movies() {
    csv::row row;
    // eliminates the table header
    _movies >> row;

    while (_movies >> row) {
        uint32_t const movie_id = std::stoi(row[0]);

        entry::movie entry;
        entry.set_key(movie_id);
        // CSV row is not able to escape commas yet, so
        // we have a workaround
        std::stringstream string_sum;
        for (size_t i = 1; i < row.size() - 1; i++) {
            string_sum << row[i] << ",";
        }
        std::string const final_title(string_sum.str(), 1, string_sum.str().size() - 3);
        entry.set_title(final_title);

        std::string const& genres = row[row.size() - 1];
        std::string final_genres(genres, 1, genres.size() - 3);
        entry.set_genres(final_genres);

        entry.set_average_rating(_rating_map[movie_id].first);
        entry.set_rating_count(_rating_map[movie_id].second);

        _movie_table.insert(entry.key(), entry);
        _trie.insert(final_title, movie_id);
    }
}

void inserter::from_tags() {
    csv::row row;
    _tags >> row;  // header

    while (_tags >> row) {
        uint32_t const movie_id = std::stoi(row[1]);
        std::string const final_tag(row[2], 1, row[2].size() - 2);

        _tags_trie.insert(final_tag, movie_id);
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

    rating_map map;

    while (_ratings >> row) {
        uint32_t const user_id = std::stoi(row[0]);
        uint32_t const movie_id = std::stoi(row[1]);
        float const rating = std::stof(row[2]);

        // accumulate rating for a movie_id
        auto entry = map.find(movie_id);
        if (entry != map.end()) {
            float old_rating = entry->second.first;
            uint32_t old_count = entry->second.second;
            entry->second.first = old_rating + rating;
            entry->second.second = ++old_count;
        } else {
            map.insert({movie_id, {rating, 1}});
        }

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
    _user_table.insert(user_entry.key(), user_entry);
    average_rating(map);
}

void inserter::average_rating(rating_map& map) {
    for (auto& entry : map) {
        uint32_t movie_id = entry.first;
        float rating = entry.second.first;
        uint32_t count = entry.second.second;

        _rating_map.insert({movie_id, {rating / count, count}});
    }
}
}  // namespace inserter