#include <string>
#include <vector>
#include <iostream>

template <class T>
class better_ostream_iterator {
private:
    std::string delim;
    std::string input_delim;
    std::ostream& os;
public:
    better_ostream_iterator(std::ostream& os) : os(os) {}
    better_ostream_iterator(std::ostream& os, const std::string& d) :
        os(os), input_delim(d) {}

    better_ostream_iterator<T>& operator=(const T& elem) {
        os << delim << elem;
        delim = input_delim;
        return *this;
    }

    better_ostream_iterator<T>& operator*() { return *this; }
    better_ostream_iterator<T>& operator++() { return *this; }
    better_ostream_iterator<T>& operator++(int) { return *this; }
};

int main() {
    std::vector<int> nums = {1, 2, 3, 4, 5};

    std::copy(nums.begin(), nums.end(),
            better_ostream_iterator<int>(std::cout, ","));
    std::cout << '\n';

    return 0;
}
