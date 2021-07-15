#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

int helper(int x, const std::vector<int>& individual_play_scores, std::vector<int>& cache)
{
  if (x < 0) return 0;
  if (cache[x] >= 0) return cache[x];

  int ret = 0;
  for(int i=0;i<individual_play_scores.size();++i)
  {
    if (x - individual_play_scores[i] >= 0) ret += helper(x - individual_play_scores[i], individual_play_scores, cache);
  }
  std::cout << x << ": " << ret << std::endl;
  cache[x] = ret;
  return ret;
}

// Same as "Number of Ways to Make Change"
int NumCombinationsForFinalScore(int final_score, const vector<int>& individual_play_scores) {
  std::vector<int> dp(final_score + 1, 0);
  dp[0] = 1;

  // Ordinarily, would want to sort scores first, but here it is guaranteed that scores are already sorted
  // std::sort(individual_play_scores.begin(), individual_play_scores.end());
  
  for(const int& score : individual_play_scores)
  {
    for(int i=score;i<dp.size();++i)
    {
      dp[i] += dp[i-score];
    }
  }
  return dp.back();
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"final_score", "individual_play_scores"};
  return GenericTestMain(args, "number_of_score_combinations.cc",
                         "number_of_score_combinations.tsv",
                         &NumCombinationsForFinalScore, DefaultComparator{},
                         param_names);
}
