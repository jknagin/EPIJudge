#include <string>

#include "test_framework/generic_test.h"
using std::string;

int SSDecodeColID(const string& col) {
  // "A" -> 1 = 1 * 1
  // "Z" -> 26 = 26 * 1
  // "AA" -> 27 = 1*26 + 1*1
  int ret = 0;
  int N = col.length();
  for (int i = 0; i < N; ++i)
  {
    ret *= 26;
    ret += (col[i] - 'A' + 1);
  }
  return ret;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"col"};
  return GenericTestMain(args, "spreadsheet_encoding.cc",
                         "spreadsheet_encoding.tsv", &SSDecodeColID,
                         DefaultComparator{}, param_names);
}
