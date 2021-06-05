#include "test_framework/generic_test.h"
long long SwapBits(long long x, int i, int j) {
  // If the bits at i and j are not equal, then we need to swap them
  if (((x >> i) & 1) != ((x >> j) & 1))
  {
    // Bitmask is all 0s except for 1's at positions i and j
    // 1ull: 1 as an unsigned long long
    unsigned long long bitmask = (1ull << i) | (1ull << j);
    // x = x ^ bitmask negates the values of bits i and j because a ^ 0 = a and a ^ 1 = !a
    //x ^= bitmask;
    x = x ^ bitmask;
  }
  return x;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "i", "j"};
  return GenericTestMain(args, "swap_bits.cc", "swap_bits.tsv", &SwapBits,
                         DefaultComparator{}, param_names);
}
