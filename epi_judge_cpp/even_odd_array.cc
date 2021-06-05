#include <set>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::vector;

void EvenOdd(vector<int>* A_ptr) {
  // Use a reference when deferencing A_ptr to modify the array pointed to by A_ptr directly
  std::vector<int>& A = *A_ptr; 

  // left points to an even value
  int left = 0;
  // right points to where the next odd value will go
  int right = static_cast<int>(A.size()) - 1;
  while (left < right)
  {
    // if left is even, all is good, so increase left
    if (A[left] % 2 == 0)
    {
      ++left;
    }
    // Otherwise, if left is odd, then it swap it with right, because right is where the next odd goes, and then decrement right
    // Don't increment left just yet, because the old value at right, before the swapping, might have been odd
    // That would mean that the value pointed to by left would be odd, so we'd need to swap again in the next iteration of the loop
    else
    {
      std::swap(A[left], A[right]);
      --right;
    }
  }
  return;
}
void EvenOddWrapper(TimedExecutor& executor, vector<int> A) {
  std::multiset<int> before(begin(A), end(A));

  executor.Run([&] { EvenOdd(&A); });

  bool in_odd = false;
  for (int a : A) {
    if (a % 2 == 0) {
      if (in_odd) {
        throw TestFailure("Even elements appear in odd part");
      }
    } else {
      in_odd = true;
    }
  }

  std::multiset<int> after(begin(A), end(A));
  if (before != after) {
    throw TestFailure("Elements mismatch");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "A"};
  return GenericTestMain(args, "even_odd_array.cc", "even_odd_array.tsv",
                         &EvenOddWrapper, DefaultComparator{}, param_names);
}
