#include <algorithm>
#include <cmath>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_utils.h"
using std::vector;

struct Star {
  bool operator<(const Star& that) const {
    return Distance() < that.Distance();
  }

  double Distance() const { return sqrt(x * x + y * y + z * z); }

  double x, y, z;
};

vector<Star> FindClosestKStars(vector<Star>::const_iterator stars_begin,
                               const vector<Star>::const_iterator& stars_end,
                               int k) {
  std::priority_queue<Star, std::vector<Star>, std::less<> > maxHeap;
  // Priority queue to stores stars with k smallest distance (max heap)
  // Add to max heap until its size is k
  // Then, if we find an element whose value is less than the top value of k, push and pop to maintain the heap size k
  for(auto it = stars_begin;it != stars_end;++it)
  {
    if (maxHeap.size() < k)
    {
      maxHeap.push(*it);
    }
    else if (*it < maxHeap.top())
    {
      maxHeap.push(*it);
      maxHeap.pop();
    }
  }

  // At the end, the stars in the heap are the k smallest stars
  std::vector<Star> ret(maxHeap.size());
  for(int i=0;i<ret.size();++i)
  {
    ret[i] = maxHeap.top();
    maxHeap.pop();
  }

  return ret;
}

namespace test_framework {
template <>
struct SerializationTrait<Star> : UserSerTrait<Star, double, double, double> {};
}  // namespace test_framework

std::ostream& operator<<(std::ostream& out, const Star& s) {
  return out << s.Distance();
}

bool Comp(const vector<double>& expected, vector<Star> output) {
  if (output.size() != expected.size()) {
    return false;
  }

  std::sort(begin(output), end(output));

  for (int i = 0; i < output.size(); ++i) {
    if (!DefaultComparator()(output[i].Distance(), expected[i])) {
      return false;
    }
  }
  return true;
}

vector<Star> FindClosestKStarsWrapper(const vector<Star>& stars, int k) {
  return FindClosestKStars(cbegin(stars), cend(stars), k);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"stars", "k"};
  return GenericTestMain(args, "k_closest_stars.cc", "k_closest_stars.tsv",
                         &FindClosestKStarsWrapper, &Comp, param_names);
}
