#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
vector<int> PlusOne(vector<int> A) {
  bool carry = false;
  A[A.size() - 1] += 1;
  for (int i = static_cast<int>(A.size()) - 1; i >= 0; --i)
  {
    if (carry) A[i] += 1;
    carry = false;
    if (A[i] >= 10)
    {
      A[i] -= 10;
      carry = true;
    }
    if (!carry) return A;
  }
  std::vector<int> ret(A.size() + 1, 0);
  ret[0] = 1;
  return ret;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "int_as_array_increment.cc",
                         "int_as_array_increment.tsv", &PlusOne,
                         DefaultComparator{}, param_names);
}
