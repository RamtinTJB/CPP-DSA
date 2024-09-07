/*
An example to demonstrate how to write a custom view
fib view generates fibonacci numbers using an iterator
and can be used with all the views adaptors
*/

#include <iterator>
#include <ranges>
#include <iostream>

class fib_iterator {
public:
  using value_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::forward_iterator_tag;

  const std::size_t& operator*() const { return cur_; }

  fib_iterator& operator++() {
    cur_ = std::exchange(next_, next_ + cur_);
    return *this;
  }

  fib_iterator operator++(int) {
    auto temp = *this;
    ++*this;
    return temp;
  }

  bool operator==(const fib_iterator&) const = default;
private:
  std::size_t cur_ = 0;
  std::size_t next_ = 1;
};

namespace views {
  constexpr auto fibonacci =
    std::ranges::subrange<fib_iterator, std::unreachable_sentinel_t>{};
}

void fib_fun(int n, int k) {
  using namespace std::views;

  auto view = views::fibonacci
    | filter([k](auto i) { return i % k == 0; })
    | take(n);

  std::ranges::copy(view, std::ostream_iterator<std::size_t>(std::cout, ", "));
}

int main() {
  fib_fun(5, 3);

  return 0;
}