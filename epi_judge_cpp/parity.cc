#include "test_framework/generic_test.h"

// O(k), where k = number of bits that are set
short Parity(unsigned long long x)
{
  short ret = 0;
  while (x)
  {
    // ret alternates between 0 and 1
    ret ^= 1;

    // clears the lowest set bit in x
    x &= (x - 1);
  }
  return ret;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "parity.cc", "parity.tsv", &Parity,
                         DefaultComparator{}, param_names);
}
