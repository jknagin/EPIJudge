#include <algorithm>
#include <functional>
#include <iterator>
#include <vector>
#include <random>

#include "test_framework/generic_test.h"
#include "test_framework/random_sequence_checker.h"
#include "test_framework/timed_executor.h"
using std::bind;
using std::vector;
void RandomSampling(int k, vector<int>* A_ptr) {
  std::vector<int>& A = *A_ptr;
  std::default_random_engine seed((std::random_device())());

  // For each i in [0, k-1] inclusive, generate index j in [i, A.size() - 1] inclusive, and swap i and j
  int N = static_cast<int>(A.size());
  for (int i = 0; i < k; ++i)
  {
    int j = std::uniform_int_distribution<int>{ i, N - 1 }(seed);
    std::swap(A[i], A[j]);
  }
  return;
}
bool RandomSamplingRunner(TimedExecutor& executor, int k, vector<int> A) {
  using namespace test_framework;
  vector<vector<int>> results;

  executor.Run([&] {
    for (int i = 0; i < 100000; ++i) {
      RandomSampling(k, &A);
      results.emplace_back(begin(A), begin(A) + k);
    }
  });

  int total_possible_outcomes = BinomialCoefficient(A.size(), k);
  sort(begin(A), end(A));
  vector<vector<int>> combinations;
  for (int i = 0; i < BinomialCoefficient(A.size(), k); ++i) {
    combinations.emplace_back(ComputeCombinationIdx(A, A.size(), k, i));
  }
  vector<int> sequence;
  for (vector<int> result : results) {
    sort(begin(result), end(result));
    sequence.emplace_back(
        distance(begin(combinations),
                 find(begin(combinations), end(combinations), result)));
  }
  return CheckSequenceIsUniformlyRandom(sequence, total_possible_outcomes,
                                        0.01);
}

void RandomSamplingWrapper(TimedExecutor& executor, int k,
                           const vector<int>& A) {
  RunFuncWithRetries(
      bind(RandomSamplingRunner, std::ref(executor), k, std::cref(A)));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "k", "A"};
  return GenericTestMain(args, "offline_sampling.cc", "offline_sampling.tsv",
                         &RandomSamplingWrapper, DefaultComparator{},
                         param_names);
}
