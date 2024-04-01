#include <iostream>
#include <random>
#include <cmath>

int main(int argc, const char** argv) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0, 1.0);

  int num_iter = 100000;
  double insideCircle = 0, outsideCirlce = 0;

  for (int i = 0; i < num_iter; ++i) {
    double x = dis(gen);
    double y = dis(gen);
    if (x*x + y*y <= 1) insideCircle++;
    else outsideCirlce++;
  }

  std::cout << (insideCircle / num_iter) * 4 << std::endl;

  return 0;
}
