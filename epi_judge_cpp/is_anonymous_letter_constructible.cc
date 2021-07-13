#include <string>
#include <unordered_map>
#include "test_framework/generic_test.h"
using std::string;

std::unordered_map<char, int> fcounter(const std::string& str)
{
  std::unordered_map<char, int> counter;
  for(const auto& c : str)
  {
    if (!counter.count(c)) counter[c] = 0;
    ++counter[c];
  }
  return counter;
}

bool IsLetterConstructibleFromMagazine(const string& letter_text, const string& magazine_text)
{
  // Create frequency counters for letter_text and magazine_text
  std::unordered_map<char, int> letterCounter = fcounter(letter_text);
  std::unordered_map<char, int> magazineCounter = fcounter(magazine_text);

  // For each character in letter, check that it appears at least as many times in magazine
  for(auto it = letterCounter.begin();it != letterCounter.end();++it)
  {
    if (magazineCounter[it->first] < it->second) return false;
  }
  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"letter_text", "magazine_text"};
  return GenericTestMain(args, "is_anonymous_letter_constructible.cc",
                         "is_anonymous_letter_constructible.tsv",
                         &IsLetterConstructibleFromMagazine,
                         DefaultComparator{}, param_names);
}
