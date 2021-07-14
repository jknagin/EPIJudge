#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

void helper(int i, std::vector<int>& A, std::vector<std::vector<int> >& perms)
{
  if (i == A.size() - 1)
  {
    perms.push_back(A);
    return;
  }
  for(int j=i;j<A.size();++j)
  {
    if (A[i] == A[j] && i != j) continue;
    std::swap(A[i], A[j]);
    helper(i + 1, A, perms);
  }
  for(int j=A.size() - 1;j>=i;--j) std::swap(A[i], A[j]);
}

vector<vector<int>> Permutations(vector<int> A) {
  std::vector<std::vector<int> > perms;
  helper(0, A, perms);
  return perms;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "permutations.cc", "permutations.tsv",
                         &Permutations, UnorderedComparator{}, param_names);
}
