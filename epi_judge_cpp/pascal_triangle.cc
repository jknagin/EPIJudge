#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
vector<vector<int>> GeneratePascalTriangle(int num_rows) {
  std::vector<std::vector<int> >ret(num_rows);
  for (int i = 0; i < num_rows; ++i)
  {
    ret[i].resize(i+1);
    ret[i][0] = 1;
    ret[i][i] = 1;
    for (int j = 1; j < i; ++j)
    {
      ret[i][j] = ret[i - 1][j - 1] + ret[i - 1][j];
    }
  }
  return ret;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num_rows"};
  return GenericTestMain(args, "pascal_triangle.cc", "pascal_triangle.tsv",
                         &GeneratePascalTriangle, DefaultComparator{},
                         param_names);
}
