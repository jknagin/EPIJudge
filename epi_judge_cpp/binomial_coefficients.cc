#include "test_framework/generic_test.h"

/*
Recursive method (top-down DP) for compute N choose K without worrying about overflow from computing large factorials.
This is REALLY useful!
Base cases:
  C(r, r) = 0
  C(r, 0) = 0
Recursion:
  C(n, k) = C(n - 1, k) + C(n - 1, k - 1)
*/
int NChooseK(int n, int k, std::vector<std::vector<int> >& cache)
{
  if (cache[n][k]) return cache[n][k];
  if (n == k || k == 0)
  {
    cache[n][k] = 1;
    return cache[n][k];
  }
  int x = NChooseK(n - 1, k, cache);
  int y = NChooseK(n - 1, k - 1, cache);
  cache[n][k] = x + y;
  return cache[n][k];
}
int ComputeBinomialCoefficient(int n, int k) {
  std::vector<std::vector<int> >cache(n + 1, std::vector<int>(k + 1, 0));
  return NChooseK(n, k, cache);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n", "k"};
  return GenericTestMain(
      args, "binomial_coefficients.cc", "binomial_coefficients.tsv",
      &ComputeBinomialCoefficient, DefaultComparator{}, param_names);
}
