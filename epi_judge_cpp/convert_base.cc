#include <string>

#include "test_framework/generic_test.h"
using std::string;

int toBase10(const std::string& num_as_string, int b)
{
  if (num_as_string.length() == 0) return 0;
  if (num_as_string == "0") return 0;

  int ret = 0;
  bool negative = num_as_string[0] == '-';
  int start = std::isalnum(num_as_string[0]) ? 0 : 1;
  for (int i = num_as_string.length() - 1; i >= start; --i)
  {
    char digit = num_as_string[i];
    if ('0' <= digit && digit <= '9')
    {
      ret += (digit - '0') * std::pow(b, num_as_string.length() - 1 - i);
    }
    else
    {
      ret += (digit - 55) * std::pow(b, num_as_string.length() - 1 - i);
    }
  }
  return negative ? -ret : ret;
}

std::string fromBase10(int num, int b)
{
  if (num == 0) return "0";

  std::string ret = "";
  bool negative = num < 0;
  while (num != 0)
  {
    int digit = std::abs(num % b);
    num /= b;
    if (0 <= digit && digit <= 9)
    {
      ret += (digit + '0');
    }
    else
    {
      ret += (char)(digit + 55);
    }
  }
  if (negative) ret += '-';
  std::reverse(ret.begin(), ret.end());
  return ret;
}

string ConvertBase(const string& num_as_string, int b1, int b2) {
  int b10 = toBase10(num_as_string, b1);
  //std::cout << "\nTo base 10: " << b10 << std::endl;
  std::string ret = fromBase10(b10, b2);
  //std::cout << "From base 10: " << ret << std::endl;
  return fromBase10(toBase10(num_as_string, b1), b2);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num_as_string", "b1", "b2"};
  return GenericTestMain(args, "convert_base.cc", "convert_base.tsv",
                         &ConvertBase, DefaultComparator{}, param_names);
}
