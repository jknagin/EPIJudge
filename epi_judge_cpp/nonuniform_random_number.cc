#include <algorithm>
#include <functional>
#include <unordered_map>
#include <vector>
#include <random>

#include "test_framework/generic_test.h"
#include "test_framework/random_sequence_checker.h"
#include "test_framework/timed_executor.h"
using std::abs;
using std::bind;
using std::unordered_map;
using std::vector;
int NonuniformRandomNumberGeneration(const vector<int>& values,
                                     const vector<double>& probabilities) {
  std::vector<double> cProbabilities(probabilities);
  for (int i = 1; i < cProbabilities.size(); ++i)
  {
    cProbabilities[i] += cProbabilities[i - 1];
  }

  std::default_random_engine seed;
  std::uniform_real_distribution<double> dist(0.0, 1.0);
  double r = dist(seed);
  double cProb = 0.0;
  for (int i = 0; i + 1< cProbabilities.size(); ++i)
  {
		cProb += probabilities[i];
		if (cProb >= r)
		{
			return values[i];
		}
  }
  return values[0];
}
bool NonuniformRandomNumberGenerationRunner(
    TimedExecutor& executor, const vector<int>& values,
    const vector<double>& probabilities) {
  constexpr int kN = 1000000;
  vector<int> results;

  executor.Run([&] {
    for (int i = 0; i < kN; ++i) {
      results.emplace_back(
          NonuniformRandomNumberGeneration(values, probabilities));
    }
  });

  unordered_map<int, int> counts;
  for (int result : results) {
    ++counts[result];
  }
  for (int i = 0; i < values.size(); ++i) {
    const int v = values[i];
    const double p = probabilities[i];
    if (kN * p < 50 || kN * (1.0 - p) < 50) {
      continue;
    }
    const double sigma = sqrt(kN * p * (1.0 - p));
    if (abs(counts[v] - (p * kN)) > 5 * sigma) {
      return false;
    }
  }
  return true;
}

void NonuniformRandomNumberGenerationWrapper(
    TimedExecutor& executor, const vector<int>& values,
    const vector<double>& probabilities) {
  RunFuncWithRetries(bind(NonuniformRandomNumberGenerationRunner,
                          std::ref(executor), std::cref(values),
                          std::cref(probabilities)));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "values", "probabilities"};
  return GenericTestMain(args, "nonuniform_random_number.cc",
                         "nonuniform_random_number.tsv",
                         &NonuniformRandomNumberGenerationWrapper,
                         DefaultComparator{}, param_names);
}
