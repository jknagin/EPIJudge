#include "test_framework/generic_test.h"
int Fibonacci(int n) {
  // TODO - you fill in here.
    if (n == 0 || n == 1) return n;
    std::array<int, 2> fib;
    fib[0] = 0;
    fib[1] = 1;
    for (int i = 2; i <= n; ++i)
    {
        int newFib = fib[0] + fib[1];
        fib[0] = fib[1];
        fib[1] = newFib;
    }
    return fib[1];
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "fibonacci.cc", "fibonacci.tsv", &Fibonacci,
                         DefaultComparator{}, param_names);
}
