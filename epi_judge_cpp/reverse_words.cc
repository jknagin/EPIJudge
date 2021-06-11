#include <string>

#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::string;

int findNextCharacter(int i, const std::string& str)
{
  while (i < str.length() && str[i] == ' ') ++i;
  return i < str.length() ? i : -1;
}

int findNextWhitespace(int i, const std::string& str)
{
  while (i < str.length() && str[i] != ' ') ++i;
  return i < str.length() ? i : -1;
}

void ReverseWords(string* s)
{
  std::string& str = *s;
  if (str.length() == 0) return;

  // Reverse entire string
  std::reverse(str.begin(), str.end());

  // Reverse individual words
  int start = 0;
  int end = 0;
  while (start < str.length())
  {
    start = findNextCharacter(start, str);
    end = findNextWhitespace(start + 1, str);

    if (start == -1) break;
    end = end == -1 ? str.length() - 1 : end - 1;

    // At this point, there is a word in [start, end] inclusive
    std::reverse(str.begin() + start, str.begin() + end + 1);

    // Move on past this word
    start = end + 1;
    end = start;
  }
  return;
}
string ReverseWordsWrapper(TimedExecutor& executor, string s) {
  string s_copy = s;

  executor.Run([&] { ReverseWords(&s_copy); });

  return s_copy;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "s"};
  return GenericTestMain(args, "reverse_words.cc", "reverse_words.tsv",
                         &ReverseWordsWrapper, DefaultComparator{},
                         param_names);
}
