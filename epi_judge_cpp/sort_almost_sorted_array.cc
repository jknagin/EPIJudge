#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
vector<int> SortApproximatelySortedData(
    vector<int>::const_iterator sequence_begin,
    const vector<int>::const_iterator& sequence_end, int k)
{
  /* Main idea:
    After traversing k + 1 elements, the smallest of these goes before all the other ones in the sorted array.
    Collect k + 1 elements
    Loop through the rest of the array:
      Find the minimum in the pq
      Add it to the sorted array
      Add the next element to the pq
    After, pop the remaining elements from the pq
  */

  // Store k+1 elements in a min heap
  // Stop if there are fewer than k elements
  std::priority_queue<int, std::vector<int>, std::greater<int> > pq;
  for(int i=0;i<k+1 && sequence_begin != sequence_end;++i)
  {
    pq.push(*sequence_begin);
    sequence_begin++;
  }    

  // Iterate through the rest of the elements in the array, popping and pushing onto the pq
  // Extract the smallest each time
  std::vector<int> ret;
  while(sequence_begin != sequence_end)
  {
    ret.push_back(pq.top());
    pq.pop();
    pq.push(*sequence_begin);
    sequence_begin++;
  }
  
  // Pop off the rest of the elements of the queue
  while(!pq.empty())
  {
    ret.push_back(pq.top());
    pq.pop();
  }

  return ret;
}
vector<int> SortApproximatelySortedDataWrapper(const vector<int>& sequence,
                                               int k) {
  return SortApproximatelySortedData(cbegin(sequence), cend(sequence), k);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sequence", "k"};
  return GenericTestMain(
      args, "sort_almost_sorted_array.cc", "sort_almost_sorted_array.tsv",
      &SortApproximatelySortedDataWrapper, DefaultComparator{}, param_names);
}
