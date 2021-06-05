#include "test_framework/generic_test.h"
bool IsPalindromeNumber(int x) {
  if (x < 0) return false; // By definition, a negative number cannot be a palindrome

  // Number of digits in x
  int numDigits = static_cast<int>(std::floor(std::log10(x)) + 1);
  
  int msd_mask = std::pow(10, numDigits - 1);
  while (x > 0)
  {
    // Extract most and least significant digits
    int msd = x / msd_mask;
    int lsd = x % 10;

    // If they are unequal, return false
    if (msd != lsd) return false;
  
    // Remove most significant digit from x
    x = x % msd_mask;

    // Remove least significant digit from x
    x /= 10;

    // Since the number of digits remaining has decreased by 2, the msd_mask value decreases by a factor of 10^2 = 100
    msd_mask /= 100;
  }

  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "is_number_palindromic.cc",
                         "is_number_palindromic.tsv", &IsPalindromeNumber,
                         DefaultComparator{}, param_names);
}
