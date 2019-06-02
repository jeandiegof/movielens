#pragma once
#include <string>
#include <vector>

// heavily based on Martin York code.
// https://stackoverflow.com/questions/1120140/how-can-i-read-and-parse-csv-files-in-c

namespace csv {
class row {
   public:
    void read_row(std::istream& str);
    std::size_t size() const {
        return _data.size();
    }
    std::string const& operator[](std::size_t index) const {
        return _data[index];
    }

   private:
    std::vector<std::string> _data;
};
}  // namespace csv
