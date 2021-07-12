#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

int SearchFirstOfK(const vector<int>& A, int k) {
  int left = 0;
  int right = A.size() - 1;
  while(left <= right)
  {
    int mid = (right - left) / 2 + left;
    if (A[mid] == k)
    {
      if (mid == 0 || mid > 0 && A[mid - 1] < k) return mid;
      else right = mid - 1;
    }
    else if (A[mid] > k) right = mid - 1;
    else left = mid + 1;
  }
  return -1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "k"};
  return GenericTestMain(args, "search_first_key.cc", "search_first_key.tsv",
                         &SearchFirstOfK, DefaultComparator{}, param_names);
}
