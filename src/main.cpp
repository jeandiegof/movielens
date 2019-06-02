#include <fstream>
#include <iostream>
#include "csv/row.hpp"

std::istream& operator>>(std::istream& str, csv::row& data) {
    data.read_row(str);
    return str;
}

int main() {
    csv::row row;
    std::ifstream file("dataset/minirating.csv");

    while (file >> row) {
        std::cout << row[3] << std::endl;
    }
    return 0;
}