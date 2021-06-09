#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::vector;
// Returns the number of valid entries after deletion.
int DeleteDuplicates(vector<int>* A_ptr) {
  std::vector<int>& A = *A_ptr;
  if (A.size() < 2) return A.size();

  int write_index = 0;
  for (int i = 1; i < A.size(); ++i)
  {
    // If the current number is different from the number written to at write_index
    if (A[i] != A[write_index])
    {
      // increment the write_index and write the new number there
      ++write_index;
      A[write_index] = A[i];
    }
  }
  return write_index + 1;
}
vector<int> DeleteDuplicatesWrapper(TimedExecutor& executor, vector<int> A) {
  int end = executor.Run([&] { return DeleteDuplicates(&A); });
  A.resize(end);
  return A;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "A"};
  return GenericTestMain(
      args, "sorted_array_remove_dups.cc", "sorted_array_remove_dups.tsv",
      &DeleteDuplicatesWrapper, DefaultComparator{}, param_names);
}
