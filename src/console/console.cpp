#include "console/console.hpp"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include "sort/sort.hpp"

namespace console {
console::console(hash_table::quadratic_probing<uint32_t, entry::movie>& movie_table,
                 hash_table::quadratic_probing<uint32_t, entry::user>& user_table,
                 trie::trie& trie, trie::tags_trie& tags_trie)
    : _movie_table(movie_table),
      _user_table(user_table),
      _trie(trie),
      _tags_trie(tags_trie) {
}

void console::start() {
    std::string query = get_query();
    handle_query(query);
    start();  // shouldn't be here
}

std::string console::get_query() {
    std::cout << "> ";

    std::string query;
    std::getline(std::cin, query);
    return query;
}

bool console::handle_query(std::string query) {
    query_class result = parse_query(query);
    switch (result) {
        case query_class::movie:
            handle_movie(query);
            break;
        case query_class::user:
            handle_user(query);
            break;
        case query_class::top_n:
            handle_top_n(query);
            break;
        case query_class::tags:
            handle_tags(query);
            break;
        case query_class::exit:
            exit(0);
            break;
        case query_class::unexpected:
            std::cout << "Invalid query." << std::endl;
            break;
    }
    return true;
}

console::query_class console::parse_query(std::string query) {
    if (query.rfind("movie", 0) == 0) {
        return query_class::movie;
    } else if (query.rfind("user", 0) == 0) {
        return query_class::user;
    } else if (query.rfind("top", 0) == 0) {
        return query_class::top_n;
    } else if (query.rfind("tags", 0) == 0) {
        return query_class::tags;
    } else if (query.rfind("exit", 0) == 0) {
        return query_class::exit;
    }
    return query_class::unexpected;
}

void console::handle_movie(std::string query) {
    if (is_by_id(query)) {
        find_movie_id(query);
    } else {
        find_movie_string(query);
    }
    return;
}

void console::handle_user(std::string query) {
    std::string id(query, 5, query.size());
    auto user_id = std::stoi(id);
    auto ratings = _user_table.find(user_id).get_ratings();

    for (auto&& rating : ratings) {
        auto movie = _movie_table.find(rating.first);

        std::cout << std::right
                  << std::setw(8)
                  << rating.second << "    "
                  << std::left
                  << std::setw(65) << std::setfill(' ')
                  << ((movie.title().size() > 55) ? movie.title().substr(0, 55) + "..." : movie.title())
                  << std::right
                  << std::setw(8)
                  << movie.rating() << "    "
                  << std::right
                  << movie.count() << std::endl;
    }
}

void console::handle_top_n(std::string query) {
    auto separator_index = query.find(" ");
    std::string n_str(query, 3, separator_index - 1);
    uint32_t n = std::stoi(n_str);
    std::string genre(query, separator_index + 1, query.size() - 1);

    std::vector<entry::movie> movies;
    auto movie_ids = _trie.subwords();

    for (auto movie_id : movie_ids) {
        entry::movie movie = _movie_table.find(movie_id);
        if (movie.key() != 0) {
            if (check_genre(movie, genre)) {
                movies.push_back(movie);
            }
        }
    }

    if (movies.size() > 1) {
        sort::sort(movies);
    }
    for (size_t i = 0; i < movies.size() && i < n; i++) {
        movies[i].print();
    }
}

void console::handle_tags(std::string query) {
    std::string tag;
    std::istringstream stream(query);
    stream >> tag;  // tags

    std::vector<std::string> tags;
    while (stream >> tag) {
        std::string without_marks(tag, 1, tag.size() - 2);
        tags.push_back(without_marks);
    }

    std::vector<std::vector<uint32_t>> list;
    for (auto& entry : tags) {
        list.push_back(_tags_trie.contains(entry));
    }

    std::vector<uint32_t> movie_ids(100);

    if (tags.size() > 1) {
        for (size_t i = 1; i < list.size(); i++) {
            sort::sort(list[i - 1]);
            sort::sort(list[i]);
            std::set_intersection(list[i - 1].begin(), list[i - 1].end(),
                                  list[i].begin(), list[i].end(), movie_ids.begin());
        }
    } else {
        movie_ids = list[0];
    }

    for (auto id : movie_ids) {
        if (id != 0) _movie_table.find(id).print();
    }
}

bool console::check_genre(entry::movie& movie, std::string genre) {
    std::string genres = movie.genres();
    std::string const& begin = genre + "|";
    std::string const& middle = "|" + genre + "|";
    std::string const& end = "|" + genre;

    if ((genres.find(begin) != std::string::npos ||
         genres.find(middle) != std::string::npos ||
         genres.find(end) != std::string::npos) &&
        movie.count() > 1000) {
        return true;
    }
    return false;
}

void console::find_movie_id(std::string query) {
    std::istringstream stream(query);
    stream >> query;  // movie

    std::string data;
    stream >> data;  // movie_id

    uint32_t movie_id = std::stoi(data);
    auto result = _movie_table.find(movie_id);
    if (result.key() != 0) {
        result.print();
        return;
    }
    std::cout << "movie_id not found" << std::endl;
}

void console::find_movie_string(std::string query) {
    std::string prefix(query, 6, query.size() - 1);
    auto list = _trie.contains_prefix(prefix);
    std::for_each(list.begin(), list.end(), [&](auto movie) {
        auto result = _movie_table.find(movie);
        result.print();
    });
}

bool console::is_by_id(std::string const& query) {
    bool is_id = true;
    for (size_t i = 6; i < query.size(); i++) {
        if (query[i] == ' ' || i > 20 || !std::isdigit(query[i])) {
            is_id = false;
        }
    }
    return is_id;
}
}  // namespace console
