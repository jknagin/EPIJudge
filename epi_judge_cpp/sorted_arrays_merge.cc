#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

// This struct is used so we know which array each element belongs to
struct IteratorsCurrEnd
{
  // Overload operator> for min heap sorting
  bool operator>(const IteratorsCurrEnd& other) const
  {
    return *current > *(other.current);
  }

  std::vector<int>::const_iterator current;
  std::vector<int>::const_iterator end;
};

vector<int> MergeSortedArrays(const vector<vector<int>>& sorted_arrays) {
  std::vector<int> ret;
  std::priority_queue<IteratorsCurrEnd, std::vector<IteratorsCurrEnd>, std::greater<> > pq;

  // Fill up the priority queue with the first iterator into each array (as well as the end iterator of each array)
  // Struct is created using { } initialization
  for(int i=0;i<sorted_arrays.size();++i)
  {
    pq.emplace(IteratorsCurrEnd {sorted_arrays[i].cbegin(), sorted_arrays[i].cend()} );
  }

  while(!pq.empty())
  {
    // Top element of queue is the one whose "current" member points to the smallest int in the heap
    IteratorsCurrEnd top = pq.top();
    pq.pop();
    ret.push_back(*(top.current));

    // Add the next iterator of the chosen array to the heap, if it exists
    if (std::next(top.current) != top.end)
    {
      pq.emplace(IteratorsCurrEnd{ std::next(top.current), top.end });
    }
  }

  return ret;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sorted_arrays"};
  return GenericTestMain(args, "sorted_arrays_merge.cc",
                         "sorted_arrays_merge.tsv", &MergeSortedArrays,
                         DefaultComparator{}, param_names);
}
