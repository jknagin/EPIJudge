#include "test_framework/generic_test.h"

void swapBits(unsigned long long& x, int i, int j)
{
  if (((x >> i) & 1) != ((x >> j) & 1))
  {
    unsigned long long bitmask = (1ull << i) | (1ull << j);
    x ^= bitmask;
  }
}

unsigned long long ReverseBits(unsigned long long x) {
  int left = 0;
  int right = sizeof(unsigned long long) * 8 - 1;
  while(left < right) swapBits(x, left++, right--);
  return x;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "reverse_bits.cc", "reverse_bits.tsv",
                         &ReverseBits, DefaultComparator{}, param_names);
}
