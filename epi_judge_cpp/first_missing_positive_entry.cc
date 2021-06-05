#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

// A is passed by value argument, since we change it.
int FindFirstMissingPositive(vector<int> A) {
    // TODO - you fill in here.
    int n = A.size();
    for (int i = 0; i < n; ++i)
    {
        while (A[i] >= 1 && A[i] <= n && A[i] != A[A[i] - 1])
        {
            std::swap(A[i], A[A[i] - 1]);
        }
    }
    for (int i = 0; i < n; ++i)
    {
        if (A[i] != i + 1) return i + 1;
    }
    return A.size() + 1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "first_missing_positive_entry.cc",
                         "first_missing_positive_entry.tsv",
                         &FindFirstMissingPositive, DefaultComparator{},
                         param_names);
}
