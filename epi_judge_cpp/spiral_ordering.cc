#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
vector<int> MatrixInSpiralOrder(const vector<vector<int>>& square_matrix) {
  std::vector<int> ret;
  int start = 0;
  int end = square_matrix.size() - 1;
  while (start < end)
  {
    // Right
    for (int i=start, j = start; j < end; ++j) ret.push_back(square_matrix[i][j]);

    // Down
    for (int j = end, i = start; i < end; ++i) ret.push_back(square_matrix[i][j]);

    // Left
    for (int i = end, j = end; j > start; --j) ret.push_back(square_matrix[i][j]);
    
    // Up
    for (int j = start, i = end; i > start; --i) ret.push_back(square_matrix[i][j]);

    // Increase start, decrease end
    ++start;
    --end;
  }

  // Edge case if start == end
  if (start == end) ret.push_back(square_matrix[start][start]);

  return ret;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"square_matrix"};
  return GenericTestMain(args, "spiral_ordering.cc", "spiral_ordering.tsv",
                         &MatrixInSpiralOrder, DefaultComparator{},
                         param_names);
}
