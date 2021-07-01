#include <algorithm>
#include <iterator>
#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

bool canPlaceQueen(int i, int j, const std::unordered_set<int>& colSet, const std::unordered_set<int>& upSet, const std::unordered_set<int>& downSet)
{
  if (colSet.count(j)) return false;
  if (upSet.count(i + j)) return false;
  if (downSet.count(i - j)) return false;
  return true;
}

void helper(const int n, int i, std::unordered_set<int>& colSet, std::unordered_set<int>& upSet, std::unordered_set<int>& downSet, std::vector<int>& placement, std::vector<std::vector<int> >& placements)
{
  if (i == n)
  {
    placements.push_back(placement);
    return;
  }

  for(int j=0;j<n;++j)
  {
    if (canPlaceQueen(i, j, colSet, upSet, downSet))
    {
      placement[i] = j;
      colSet.insert(j);
      upSet.insert(i + j);
      downSet.insert(i - j);
      helper(n, i + 1, colSet, upSet, downSet, placement, placements);
      colSet.erase(j);
      upSet.erase(i + j);
      downSet.erase(i - j);
    }    
  }
}

vector<vector<int>> NQueens(int n) {
  std::unordered_set<int> colSet, upSet, downSet;
  std::vector<int> placement(n);
  std::vector<std::vector<int> > placements;
  helper(n, 0, colSet, upSet, downSet, placement, placements);
  return placements;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "n_queens.cc", "n_queens.tsv", &NQueens,
                         UnorderedComparator{}, param_names);
}
