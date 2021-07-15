#include <string>
#include <vector>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;

int LevenshteinDistance(const string& A, const string& B) {
  // Figure out which string is shorter to save space
  std::string shorter = A;
  std::string longer = B;
  if (shorter.length() > longer.length()) std::swap(shorter, longer);
  std::vector<std::vector<int> > dp(2, std::vector<int>(shorter.length() + 1, 0));

  // Fill out Levenshtein table (excpet only using two rows to save space)
  // Base case;
  // table[0][j] = j;
  // table[i][0[ = i;
  // Recursion:
  // if shorter[j-1] == longer[i-1] table[i][j] = table[i-1][j-1]
  // else table[i][j] = 1 + min(table[i-1][j], table[i][j-1], table[i-1][j-1])
  for(int j=0;j<shorter.length() + 1;++j)
  {
    dp[0][j] = j;
  }
  for(int i=1;i<longer.length() + 1;++i)
  {
    dp[1][0] = i;
    for(int j=1;j<shorter.length() +1; ++j)
    {
      if (shorter[j-1] == longer[i-1])
      {
        dp[1][j] = dp[0][j-1];
      }
      else
      {
        int tmp = std::min(dp[1][j-1], dp[0][j]);
        tmp = std::min(tmp, dp[0][j-1]);
        dp[1][j] = 1 + tmp;
      }
    }
    dp[0] = dp[1];
  }

  return dp.back().back();
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "B"};
  return GenericTestMain(args, "levenshtein_distance.cc",
                         "levenshtein_distance.tsv", &LevenshteinDistance,
                         DefaultComparator{}, param_names);
}
