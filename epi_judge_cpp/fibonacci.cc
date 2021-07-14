#include "test_framework/generic_test.h"
int Fibonacci(int n) {
  if (n < 2) return n;
  int arr[2] = {0, 1};
  for(int i=2;i<=n;++i)
  {
    int f = arr[0] + arr[1];
    arr[0] = arr[1];
    arr[1] = f;
  }
  return arr[1];
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "fibonacci.cc", "fibonacci.tsv", &Fibonacci,
                         DefaultComparator{}, param_names);
}
