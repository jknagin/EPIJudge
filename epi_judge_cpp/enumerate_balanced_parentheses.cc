#include <string>
#include <vector>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;

void helper(int open, int close, std::string& str, std::vector<std::string>& ret)
{
  if (open == 0 && close == 0)
  {
    ret.push_back(str);
    return;
  }
  if (open > 0)
  {
    str.push_back('(');
    helper(open - 1, close, str, ret);
    str.pop_back();
  }
  if (open < close)
  {
    str.push_back(')');
    helper(open, close - 1, str, ret);
    str.pop_back();
  }
}

vector<string> GenerateBalancedParentheses(int num_pairs) {
  std::string str = "";
  std::vector<std::string> ret;
  helper(num_pairs, num_pairs, str, ret);
  return ret;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num_pairs"};
  return GenericTestMain(args, "enumerate_balanced_parentheses.cc",
                         "enumerate_balanced_parentheses.tsv",
                         &GenerateBalancedParentheses, UnorderedComparator{},
                         param_names);
}
