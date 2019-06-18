#include "inserter/movie_table.hpp"

std::istream& operator>>(std::istream& str, csv::row& data) {
    data.read_row(str);
    return str;
}

namespace inserter {

void movie_table(std::ifstream& file, hash_table::quadratic_probing<uint32_t, entry::movie>& table) {
    csv::row row;
    // eliminates the table header
    file >> row;
    while (file >> row) {
        uint32_t const movie_id = std::stoi(row[0]);

        entry::movie entry;
        entry.set_key(movie_id);
        entry.set_genres(row[2]);

        table.insert(entry.key(), entry);
    }
}
}  // namespace inserter