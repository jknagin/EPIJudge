#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

// Determine if duplicates are in the sudoku board in the 2D interval [startRow, endRow] x [startCol, endCol], inclusive
bool hasDuplicates(const std::vector<std::vector<int> >& sudoku, int startRow, int endRow, int startCol, int endCol)
{
  std::unordered_set<int> seen;
  for (int i = startRow; i <= endRow; ++i)
  {
    for (int j = startCol; j <= endCol; ++j)
    {
      if (sudoku[i][j] != 0 && seen.find(sudoku[i][j]) != seen.end()) return true;
			seen.insert(sudoku[i][j]);
    }
  }
  return false;
}

// Check if a partially filled matrix has any conflicts.
bool IsValidSudoku(const vector<vector<int>>& partial_assignment) {
  int n = static_cast<int>(partial_assignment.size());
  
  // Check rows
  for (int i = 0; i < n; ++i) if (hasDuplicates(partial_assignment, i, i, 0, n - 1)) return false;
	// Check cols
  for (int j = 0; j < n; ++j) if (hasDuplicates(partial_assignment, 0, n - 1, j, j)) return false;
  // Check subgrids
  int sqrtn = static_cast<int>(std::sqrt(n));
  for (int i = 0; i < sqrtn; ++i)
  {
    for (int j = 0; j < sqrtn; ++j)
    {
      if (hasDuplicates(partial_assignment, sqrtn * i, sqrtn * i + sqrtn - 1, sqrtn * j, sqrtn * j + sqrtn - 1)) return false;
    }
  }
  
  // If all good, return true
  return true;
}



int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"partial_assignment"};
  return GenericTestMain(args, "is_valid_sudoku.cc", "is_valid_sudoku.tsv",
                         &IsValidSudoku, DefaultComparator{}, param_names);
}
