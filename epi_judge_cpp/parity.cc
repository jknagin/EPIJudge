#include "test_framework/generic_test.h"

// O(k), where k = number of bits that are set
short Parity(unsigned long long x) {
	int ret = 0;
	while (x > 0)
	{
			ret = ret ^ 1; // alternate ret between 0 and 1, since we only care about the parity of the number of times this loop has run
			x = x & (x - 1); // x & (x - 1) clears the lowest set bit of x
	}
	return ret;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "parity.cc", "parity.tsv", &Parity,
                         DefaultComparator{}, param_names);
}
