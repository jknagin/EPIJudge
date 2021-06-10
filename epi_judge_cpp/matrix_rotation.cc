#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

void transpose(std::vector<std::vector<int> >& A)
{
  for (int i = 0; i < A.size(); ++i)
  {
    for (int j = i + 1; j < A.size(); ++j)
    {
      std::swap(A[i][j], A[j][i]);
    }
  }
}

void reverseRows(std::vector<std::vector<int> >& A)
{
  int row1 = 0;
  int row2 = A.size() - 1;
  while (row1 < row2)
  {
    std::swap(A[row1++], A[row2--]);
  }
}

// To rotate a matrix 90 degrees clockwise, reverse the rows and transpose the resulting matrix
void RotateMatrix(vector<vector<int>>* square_matrix_ptr) {
  std::vector<std::vector<int> >& A = *square_matrix_ptr;
  reverseRows(A);
  transpose(A);
  return;
}
vector<vector<int>> RotateMatrixWrapper(vector<vector<int>> square_matrix) {
  RotateMatrix(&square_matrix);
  return square_matrix;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"square_matrix"};
  return GenericTestMain(args, "matrix_rotation.cc", "matrix_rotation.tsv",
                         &RotateMatrixWrapper, DefaultComparator{},
                         param_names);
}
