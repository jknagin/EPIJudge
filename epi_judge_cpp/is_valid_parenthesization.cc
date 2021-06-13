#include <string>

#include "test_framework/generic_test.h"
using std::string;
bool IsWellFormed(const string& s) {
  std::stack<char> brackets;
  for (const auto& bracket : s)
  {
    if (bracket == '(' || bracket == '[' || bracket == '{') brackets.push(bracket);
    else
    {
      if (brackets.empty()) return false;
      char top = brackets.top();
      brackets.pop();
      if (top == '(' && bracket != ')' ||
        top == '[' && bracket != ']' ||
        top == '{' && bracket != '}' ) return false;
    }
  }
  return brackets.empty();
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "is_valid_parenthesization.cc",
                         "is_valid_parenthesization.tsv", &IsWellFormed,
                         DefaultComparator{}, param_names);
}
