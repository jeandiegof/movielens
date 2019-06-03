#include "csv/row.hpp"
#include <iostream>
#include <sstream>

namespace csv {
void row::read_row(std::istream& str) {
    std::string line;
    std::getline(str, line);

    std::stringstream line_stream(line);
    std::string cell;

    _data.clear();
    while (std::getline(line_stream, cell, ',')) {
        _data.push_back(cell);
    }
}
}  // namespace csv
