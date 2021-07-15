#include "test_framework/generic_test.h"

// #define BASIC_RECURSION 1
#ifdef BASIC_RECURSION
// Basic recursion: O(mn) space
int helper(int i, int j, std::vector<std::vector<int> >& cache)
{
  if (cache[i][j]) return cache[i][j];
  int top = helper(i - 1, j, cache);
  int left = helper(i, j - 1, cache);
  cache[i][j] = left + top;
  return cache[i][j];
}
#endif

int NumberOfWays(int n, int m) {
#ifdef BASIC_RECURSION
  // Using basic recursion: O(mn) space due to cache
  std::vector<std::vector<int> > cache(n, std::vector<int>(m, 0));
  for(int i=0;i<cache.size();++i) cache[i][0] = 1;
  for(int j=0;j<cache[0].size();++j) cache[0][j] = 1;
  return helper(n - 1, m - 1, cache);

#else
  // Space-efficient DP:  O(min(n, m)) space due to dp struct
  int shorter = n;
  int longer = m;
  if (shorter == 1) return 1;

  if(shorter > longer) std::swap(shorter, longer);
  std::vector<std::vector<int> > dp(2, std::vector<int>(shorter, 0));
  for(int j=0;j<dp[0].size();++j) dp[0][j] = 1;
  dp[1][0] = 1;
  for(int i=1;i<longer;++i)
  {
    for(int j=1;j<shorter;++j) dp[1][j] = dp[0][j] + dp[1][j-1];
    dp[0] = dp[1];
  }
  return dp.back().back();
#endif
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n", "m"};
  return GenericTestMain(args, "number_of_traversals_matrix.cc",
                         "number_of_traversals_matrix.tsv", &NumberOfWays,
                         DefaultComparator{}, param_names);
}
