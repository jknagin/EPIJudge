#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include <limits>

using std::vector;
struct MinMax {
  int smallest, largest;
};

MinMax FindMinMax(const vector<int>& A) {
  MinMax ret;
  ret.smallest = std::numeric_limits<int>::max();
  ret.largest = std::numeric_limits<int>::min();

  // Process two elements at a time
  for(int i=0;i<A.size() - 1;i += 2)
  {
    int n1 = A[i];
    int n2 = A[i+1];
    ret.smallest = std::min(ret.smallest, std::min(n1, n2));
    ret.largest = std::max(ret.largest, std::max(n1, n2));
  }

  // if there are an odd number of elements, the last element will not belong to a pair, so check for it separately
  if (A.size() % 2 == 1)
  {
    ret.smallest = std::min(ret.smallest, A.back());
    ret.largest = std::max(ret.largest, A.back());
  }

  return ret;
};
namespace test_framework {
template <>
struct SerializationTrait<MinMax> : UserSerTrait<MinMax, int, int> {};
}  // namespace test_framework

bool operator==(const MinMax& lhs, const MinMax& rhs) {
  return std::tie(lhs.smallest, lhs.largest) ==
         std::tie(rhs.smallest, rhs.largest);
}

std::ostream& operator<<(std::ostream& out, const MinMax& x) {
  return out << "min: " << x.smallest << ", max: " << x.largest;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "search_for_min_max_in_array.cc",
                         "search_for_min_max_in_array.tsv", &FindMinMax,
                         DefaultComparator{}, param_names);
}
