#include "test_framework/generic_test.h"
unsigned long long ClosestIntSameBitCount(unsigned long long x) {
  // Suppose we swap bits at indices k1 and k2, with k1 > k2
  // The difference in value before and after swapping is 2^k1 - 2^k2
  // To minimize this, make k1 as small as possible, and make k2 one less than k1
  // To preserve signedness, the bits pointed to by k1 and k2 must be opposite values
  // In all, this means to swap the two rightmost bits that differ
  for (int i = 0; i < 8*sizeof(unsigned long long) - 1; ++i)
  {
    // If the ith bit is not equal to the (i+1)st bit
    if (((x >> i) & 1) != (x >> (i + 1) & 1))
    {
      // swap bits i and i+1, and break;
      unsigned long long bitmask = (1ull << i) | (1ull << (i + 1));
      x ^= bitmask;
      break;
    }
  }
  return x;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "closest_int_same_weight.cc",
                         "closest_int_same_weight.tsv", &ClosestIntSameBitCount,
                         DefaultComparator{}, param_names);
}
