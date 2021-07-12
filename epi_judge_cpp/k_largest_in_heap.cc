#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

struct HeapEntry
{
  int index;
  int value;
  HeapEntry(int i, int v) : index(i), value(v) {}
  bool operator<(const HeapEntry& other) { return value < other.value; } 
};

// Push values from array to max heap
// Since the array is heapified, the first largest element is at index 0
// Add element 0 to the max heap
// In loop, pop the top element from the heap and add its left and right children to the heap
vector<int> KLargestInBinaryHeap(const vector<int>& A, int k) {
  std::priority_queue<HeapEntry, std::vector<HeapEntry>, std::less<> > maxheap;

  maxheap.emplace(HeapEntry{0, A[0]});
  std::vector<int> ret;
  for(int i=0;i<k;++i)
  {
    int index = maxheap.top().index;
    int value = maxheap.top().value;
    maxheap.pop();
    ret.push_back(value);
    int left = 2*index + 1;
    int right = left + 1;
    
    if (left < A.size()) maxheap.emplace(HeapEntry{left, A[left]});
    if (right < A.size()) maxheap.emplace(HeapEntry{right, A[right]});
  }

  return ret;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "k"};
  return GenericTestMain(args, "k_largest_in_heap.cc", "k_largest_in_heap.tsv",
                         &KLargestInBinaryHeap, UnorderedComparator{},
                         param_names);
}
