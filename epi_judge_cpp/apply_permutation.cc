#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
void ApplyPermutation(vector<int> perm, vector<int>* A_ptr) {
  std::vector<int>& A = *A_ptr;
  for (int i = 0; i < perm.size(); ++i)
  {
    // We would like perm to be like [0, 1, 2, 3], so there is no more permuting to do
    // While this is not the case:
    while (perm[i] != i)
    {
      // Put the i'th element of A in the correct position (perm[i])
      std::swap(A[i], A[perm[i]]);

      // Perform the swap in the perm array to record the swap we just did in the A array
      std::swap(perm[i], perm[perm[i]]);
    }
  }
  return;
}
vector<int> ApplyPermutationWrapper(const vector<int>& perm, vector<int> A) {
  ApplyPermutation(perm, &A);
  return A;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"perm", "A"};
  return GenericTestMain(args, "apply_permutation.cc", "apply_permutation.tsv",
                         &ApplyPermutationWrapper, DefaultComparator{},
                         param_names);
}
