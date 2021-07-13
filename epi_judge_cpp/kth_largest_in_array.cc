#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

// The numbering starts from one, i.e., if A = [3, 1, -1, 2] then
// FindKthLargest(1, A) returns 3, FindKthLargest(2, A) returns 2,
// FindKthLargest(3, A) returns 1, and FindKthLargest(4, A) returns -1.

// Standard quickselect algorithm
int FindKthLargest(int k, vector<int>* A_ptr) {
  std::vector<int>& A = *A_ptr;
  int start = 0;
  int end = A.size() - 1;
  while(start <= end)
  {
    int pivot = start;
    int left = pivot + 1;
    int right = end;
    while(left <= right)
    {
      if (A[left] > A[pivot] && A[right] < A[pivot]) std::swap(A[left], A[right]);
      if (A[left] <= A[pivot]) ++left;
      if (A[right] >= A[pivot]) --right;
    }
    std::swap(A[pivot], A[right]);
    if (right == A.size() - k) return A[right];
    else if (right < A.size() - k)
    {
      start = right + 1;
    }
    else
    {
      end = right - 1;
    }
  }
  return 0;
}
int FindKthLargestWrapper(int k, vector<int>& A) {
  return FindKthLargest(k, &A);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"k", "A"};
  return GenericTestMain(args, "kth_largest_in_array.cc",
                         "kth_largest_in_array.tsv", &FindKthLargestWrapper,
                         DefaultComparator{}, param_names);
}
