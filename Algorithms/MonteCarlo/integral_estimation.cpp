#include <random>
#include <iostream>
#include <cmath>

double mathFunction(double x) {
  return pow(x, 4) * exp(-x);
}

double monteCarloEstimation(double lowBound, double upBound, int iterations) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0, 1.0);

  double totalSum = 0;

  int iter = 0;

  while (iter < iterations) {
    double randNum = lowBound + (float(dis(gen))) * (upBound - lowBound);
    double val = mathFunction(randNum);

    totalSum += val;

    iter++;
  }

  double estimate = (upBound - lowBound) * totalSum / iterations;

  return estimate;
}

int main() {
  double lowerBound = 1, upperBound = 5;
  int iterations = 100000;

  std::cout << monteCarloEstimation(lowerBound, upperBound, iterations) << std::endl;

  return 0;
}
