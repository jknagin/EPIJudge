#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
vector<int> NextPermutation(vector<int> perm) {
  // Find inversion point - first element from back of perm that is not in decreasing order
  auto inversionPoint = std::is_sorted_until(std::rbegin(perm), std::rend(perm));

  // If the permutation is fully sorted in reverse, then there is no next permutation, so return an empty array
  if (inversionPoint == std::rend(perm)) return {};

  // Find the first element from the back of the permutation that is greater than the inversion point
  // std::upper_bound returns the first element in the iteration whose value is greater than the specified value (*inversionPoint)
  // std::upper_bound only works on SORTED arrays (O(logN) time complexity)
  auto swapPoint = std::upper_bound(std::rbegin(perm), inversionPoint, *inversionPoint);

  // Swap inversion point and swap point
  std::iter_swap(inversionPoint, swapPoint);

  // Reverse subarray that follows the inversion point
  std::reverse(std::rbegin(perm), inversionPoint);

  return perm;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"perm"};
  return GenericTestMain(args, "next_permutation.cc", "next_permutation.tsv",
                         &NextPermutation, DefaultComparator{}, param_names);
}
