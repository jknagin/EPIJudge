#include <iterator>
#include <string>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::vector;

int ReplaceAndRemove(int size, char s[]) {
  // a, c, d, b, b, c, a -> d, d, c, d, c, d, d
  // Remove b's and count a's
  int writeIndex = 0;
  int aCount = 0;
  for (int i = 0; i < size; ++i)
  {
    if (s[i] != 'b') s[writeIndex++] = s[i];
    if (s[i] == 'a') ++aCount;
  }

  // Replace a's with two d's, starting from the back
  // a, c, d, c, a, _, _
  int start = writeIndex - 1; // the last element written to previously is at writeIndex - 1 because writeIndex is incremented one extra time in the previous for loop
  writeIndex += (aCount - 1); // now writeIndex points to the last element of the entire s array, which is where we want to start writing to fit in the d's
  const int ret = writeIndex + 1; // final size of array after performing all operations
  for (int i = start; i >= 0; --i)
  {
    // If the i'th character is an a, write two d's
    if (s[i] == 'a')
    {
      s[writeIndex] = 'd';
      s[writeIndex - 1] = 'd';
      writeIndex -= 2;
    }
    // Otherwise, just write the i'th character
    else
    {
      s[writeIndex] = s[i];
      writeIndex -= 1;
    }
  }

  return ret;
}
vector<string> ReplaceAndRemoveWrapper(TimedExecutor& executor, int size,
                                       const vector<string>& s) {
  std::vector<char> s_copy(s.size(), '\0');
  for (int i = 0; i < s.size(); ++i) {
    if (!s[i].empty()) {
      s_copy[i] = s[i][0];
    }
  }

  int res_size =
      executor.Run([&] { return ReplaceAndRemove(size, s_copy.data()); });

  vector<string> result;
  for (int i = 0; i < res_size; ++i) {
    result.emplace_back(string(1, s_copy[i]));
  }
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "size", "s"};
  return GenericTestMain(args, "replace_and_remove.cc",
                         "replace_and_remove.tsv", &ReplaceAndRemoveWrapper,
                         DefaultComparator{}, param_names);
}
