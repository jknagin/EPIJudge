#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

int SearchSmallest(const vector<int>& A) {
  int left = 0;
  int right = A.size() - 1;
  while(left <= right)
  {
    int mid = (right - left) / 2 + left;

    // Check left and right of mid for split point
    if (mid > 0 && A[mid - 1] > A[mid]) return mid;
    else if (mid + 1 < A.size() && A[mid] > A[mid + 1]) return mid + 1;

    // If left half is sorted, split is not on left, so eliminate left
    if (A[left] < A[mid]) left = mid + 1;

    // Else, split is in left half, so eliminate right
    else right = mid - 1;
  }

  // No split found, means array is sorted, so element 0 is the smallest element
  return 0;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "search_shifted_sorted_array.cc",
                         "search_shifted_sorted_array.tsv", &SearchSmallest,
                         DefaultComparator{}, param_names);
}
