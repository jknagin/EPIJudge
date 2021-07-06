#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

// Include solution to sorted_arrays_merge.cc without messing up definition of main
#define main _main
#include "sorted_arrays_merge.cc"
#undef main


vector<int> SortKIncreasingDecreasingArray(const vector<int>& A) {

  // Separate array into several sorted (increasing) arrays
  std::vector<std::vector<int> > sortedArrays;
  bool increasing = true;
  int start = 0;
  for(int i=1;i<=A.size();++i)
  {
    if (i == A.size())
    {
      if (increasing)
      {
        sortedArrays.emplace_back(A.begin() + start, A.begin() + i);
      }
      else
      {
        sortedArrays.emplace_back(A.rbegin() + A.size() - i, A.rbegin() + A.size() - start);
      }
    }
    else if (increasing && A[i-1] > A[i])
    {
      increasing = false;
      sortedArrays.emplace_back(A.begin() + start, A.begin() + i);
      start = i;
    }
    else if (!increasing && A[i-1] <= A[i])
    {
      increasing = true;
      sortedArrays.emplace_back(A.rbegin() + A.size() - i, A.rbegin() + A.size() - start);
      start = i;
    }
  }

  // Merge sorted arrays
  return MergeSortedArrays(sortedArrays);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "sort_increasing_decreasing_array.cc",
                         "sort_increasing_decreasing_array.tsv",
                         &SortKIncreasingDecreasingArray, DefaultComparator{},
                         param_names);
}
