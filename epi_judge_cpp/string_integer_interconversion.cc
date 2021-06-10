#include <string>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
using std::string;

string IntToString(int x) {
  // 123 -> "123"
  std::string ret = "";
  bool negative = x < 0;
  if (x == 0) return "0";
  while (x != 0)
  {
    int digit = std::abs(x % 10); // absolute value of modulo because x % 10 is negative for x < 0
    x /= 10;
    ret += (digit + '0'); // adding '0' turns it from an integer to a char, giving a value between 48 and 57 (see ASCII table)
  }
  if (negative) ret += '-';
  std::reverse(ret.begin(), ret.end());
  return ret;
}
int StringToInt(const string& s) {
  // "123" -> 123
  int ret = 0;
  bool negative = s[0] == '-';
  int start = 0;
  if (!std::isdigit(s[0]))
  {
    start = 1;
  }
  for (int i = start; i < s.length(); ++i)
  {
    ret *= 10;
    ret += (s[i] - '0');
  }
  return negative ? -ret : ret;
}

void Wrapper(int x, const string& s) {
  if (stoi(IntToString(x)) != x) {
    throw TestFailure("Int to string conversion failed");
  }

  if (StringToInt(s) != x) {
    throw TestFailure("String to int conversion failed");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "s"};
  return GenericTestMain(args, "string_integer_interconversion.cc",
                         "string_integer_interconversion.tsv", &Wrapper,
                         DefaultComparator{}, param_names);
}
