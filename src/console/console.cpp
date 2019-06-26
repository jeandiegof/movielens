#include "console/console.hpp"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

namespace console {
console::console(hash_table::quadratic_probing<uint32_t, entry::movie>& movie_table,
                 hash_table::quadratic_probing<uint32_t, entry::user>& user_table,
                 trie::trie& trie)
    : _movie_table(movie_table),
      _user_table(user_table),
      _trie(trie) {
}

void console::start() {
    std::string query = get_query();
    handle_query(query);
    start();
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
            std::cout << "Handling user" << std::endl;
            break;
        case query_class::top_n:
            std::cout << "Handling topn" << std::endl;
            break;
        case query_class::tags:
            std::cout << "Tags are not supported yet." << std::endl;
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
    std::istringstream stream(query);
    stream >> query;  // movie

    std::string data;
    stream >> data;  // id or title/prefix

    uint32_t movie_id = 0;
    if (is_numeric(data)) {
        movie_id = std::stoi(data);
        auto result = _movie_table.find(movie_id);
        result.print();
    } else {
        auto list = _trie.contains_prefix(data);
        std::for_each(list.begin(), list.end(), [](auto movie) {
            movie.print();
        })
    }
}

bool console::is_numeric(std::string const& string) {
    return !string.empty() &&
           std::find_if(string.begin(), string.end(), [](char ch) {
               return !std::isdigit(ch);
           }) == string.end();
}
}  // namespace console
