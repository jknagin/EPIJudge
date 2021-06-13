#include <iterator>
#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
vector<int> ExamineBuildingsWithSunset(
    vector<int>::const_iterator sequence_begin,
    const vector<int>::const_iterator& sequence_end) {

  // We have to go backwards, this is enforced by the iterators
  struct Building
  {
    int idx;
    int height;
    Building(int i, int h) : idx(i), height(h) {}
  };

  // The idea is to enforce that the elements of the stack are strictly less than all the elements that are already in the stack
  std::stack<Building> st; 
  int i = 0;
  for (auto it = sequence_begin; it != sequence_end; ++it)
  {
    // No elements to compare against, so add the current index and height to the stack
    if (st.empty())
    {
      st.push(Building(i, *it));
    }
    else
    {
      // Pop elements until the top of the stack is strictly greater than the current building's height
      while (!st.empty() && *it >= st.top().height)
      {
        st.pop();
      }

      // Add the current building to the stack
      st.push(Building(i, *it));
    }

    ++i;
  }

  // Build return vector of building indices
  std::vector<int> ret;
  while (!st.empty())
  {
    ret.push_back(st.top().idx);
    st.pop();
  }
  return ret;
}
vector<int> ExamineBuildingsWithSunsetWrapper(const vector<int>& sequence) {
  return ExamineBuildingsWithSunset(cbegin(sequence), cend(sequence));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sequence"};
  return GenericTestMain(args, "sunset_view.cc", "sunset_view.tsv",
                         &ExamineBuildingsWithSunsetWrapper,
                         DefaultComparator{}, param_names);
}
