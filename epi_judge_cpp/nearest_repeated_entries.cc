#include <string>
#include <vector>
#include <unordered_map>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;

int FindNearestRepetition(const vector<string>& paragraph)
{
  int minDistance = std::numeric_limits<int>::max();
  std::unordered_map<std::string, int> indexOf;
  for(int i=0;i<paragraph.size();++i)
  {
    if (indexOf.count(paragraph[i]))
    {
      minDistance = std::min(minDistance, i - indexOf[paragraph[i]]);
    }
    indexOf[paragraph[i]] = i;
  }
  return minDistance != std::numeric_limits<int>::max() ? minDistance : -1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"paragraph"};
  return GenericTestMain(args, "nearest_repeated_entries.cc",
                         "nearest_repeated_entries.tsv", &FindNearestRepetition,
                         DefaultComparator{}, param_names);
}
