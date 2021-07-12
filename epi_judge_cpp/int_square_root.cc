#include "test_framework/generic_test.h"

unsigned long long square(int n) { return (unsigned long long)n*(unsigned long long)n; }

int SquareRoot(int k) {
  int left = 0;
  int right = k;
  while(left <= right)
  {
    int mid = (right - left) / 2 + left;
    unsigned long long squaremid = square(mid);
    if (squaremid == k) return mid;
    else if (squaremid < k && square(mid + 1) > k) return mid;
    else if (squaremid < k) left = mid + 1;
    else right = mid - 1;
  }
  return 0;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"k"};
  return GenericTestMain(args, "int_square_root.cc", "int_square_root.tsv",
                         &SquareRoot, DefaultComparator{}, param_names);
}
