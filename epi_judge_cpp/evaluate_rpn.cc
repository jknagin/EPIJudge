#include <string>
#include <unordered_map>

#include "test_framework/generic_test.h"
using std::string;
int Evaluate(const string& expression) {
  std::stack<int> numbers;
  std::stringstream ss(expression);
  std::string token;
  const std::unordered_map<std::string, std::function<int(int, int)> > operators = {
    {"+", [](int x, int y) -> int { return x + y; }},
    {"-", [](int x, int y) -> int { return x - y; } },
    {"*", [](int x, int y) -> int { return x * y; } },
    {"/", [](int x, int y) -> int { return x / y; } } };
  while (std::getline(ss, token, ','))
  {
    // If a token is not an operation, it's a number, so convert it to an integer and add it to the numbers stack
    if (operators.find(token) == operators.end())
    {
      numbers.push(std::stoi(token));
    }
    // Else if a token is an operation, pop the top two numbers from the stack, operate on them, and push the result to the stack
    else
    {
      int num2 = numbers.top();
      numbers.pop();
      int num1 = numbers.top();
      numbers.pop();
      numbers.push(operators.at(token)(num1, num2));
    }
  }
  return numbers.top();
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"expression"};
  return GenericTestMain(args, "evaluate_rpn.cc", "evaluate_rpn.tsv", &Evaluate,
                         DefaultComparator{}, param_names);
}
