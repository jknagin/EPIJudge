#include <vector>
#include <unordered_set>

#include "test_framework/generic_test.h"
using std::vector;
// Given n, return all primes up to and including n.
vector<int> GeneratePrimes(int n)
{
  // Sieve of Eratosthenes

  // Initialize a vector of bools of size n + 1, all true initially
  std::vector<bool> isPrime(n + 1, true);
  std::vector<int> primes;

  // Start from 2 because 2 is the first prime number
  for (int i = 2; i <= n; ++i)
  {
    // If the i'th number is primend set its multiples to not prime
    if (isPrime[i])
    {
      // Add it to the vector of primes a
      primes.push_back(i);

      // Set multiples of i to not prime
      for (int j = i * 2; j <= n; j += i)
      {
        isPrime[j] = false;
      }
    }
  }
	return primes;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "prime_sieve.cc", "prime_sieve.tsv",
                         &GeneratePrimes, DefaultComparator{}, param_names);
}
