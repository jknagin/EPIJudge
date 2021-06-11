#include <string>

#include "test_framework/generic_test.h"
using std::string;
bool IsPalindrome(const string& s) {
  int left = 0;
  int right = s.length() - 1;
  while (left < right)
  {
    // Get to the next alphanumeric character from the left and the right
    while (left < s.length() && !std::isalnum(s[left])) ++left;
    while (right >= 0 && !std::isalnum(s[right])) --right;
    
    // If we are now out of bounds, we're done checking the string, so break
    if (left >= right) break;

    // We're not out of bounds yet, so convert both characters to lowercase and compare them
		if (std::tolower(s[left]) != std::tolower(s[right])) return false;

    // Advance pointers
    ++left;
    --right;
  }
  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "is_string_palindromic_punctuation.cc",
                         "is_string_palindromic_punctuation.tsv", &IsPalindrome,
                         DefaultComparator{}, param_names);
}
