#include <string>
#include <unordered_map>
#include "test_framework/generic_test.h"
using std::string;

bool CanFormPalindrome(const string& s) {
  // Create frequency count of characters in s
  std::unordered_map<char, int> m;
  for(const auto& c : s)
  {
    if (!m.count(c)) m[c] = 0;
    ++m[c];
  }

  // Ensure that at most one elements in s appears an odd number of times
  bool oddseen = false;
  for(auto it = m.begin();it != m.end();++it)
  {
    if(it->second % 2 == 1)
    {
      if (oddseen) return false;
      oddseen = true;
    } 
  }
  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "is_string_permutable_to_palindrome.cc",
                         "is_string_permutable_to_palindrome.tsv",
                         &CanFormPalindrome, DefaultComparator{}, param_names);
}
