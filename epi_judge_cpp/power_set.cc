#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

vector<vector<int>> GeneratePowerSet(const vector<int>& input_set) {
  std::vector<std::vector<int> > ret;
  ret.push_back({});
  for(int i=0;i<input_set.size();++i)
  {
    size_t s = ret.size();
    for(int j=0;j<s;++j)
    {
      std::vector<int> curr = ret[j];
      curr.push_back(input_set[i]);
      ret.push_back(curr);
    }
  }
  return ret;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"input_set"};
  return GenericTestMain(args, "power_set.cc", "power_set.tsv",
                         &GeneratePowerSet, UnorderedComparator{}, param_names);
}
