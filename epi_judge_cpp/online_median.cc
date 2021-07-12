#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

vector<double> OnlineMedian(vector<int>::const_iterator sequence_begin, const vector<int>::const_iterator& sequence_end) {

  std::priority_queue<int, std::vector<int>, std::greater<int> > minheap;
  std::priority_queue<int, std::vector<int>, std::less<int> > maxheap;
  std::vector<double> ret;
  while(sequence_begin != sequence_end)
  {
    int num = *sequence_begin;
    if (maxheap.empty()) maxheap.push(num);
    else if (maxheap.top() >= num) maxheap.push(num);
    else minheap.push(num);
    if (minheap.size() > maxheap.size())
    {
      maxheap.push(minheap.top());
      minheap.pop();
    }
    else if (maxheap.size() > minheap.size() + 1)
    {
      minheap.push(maxheap.top());
      maxheap.pop();
    }
    size_t N = minheap.size() + maxheap.size();
    if (N % 2 == 0) ret.push_back(0.5*(maxheap.top() + minheap.top()));
    else ret.push_back(static_cast<double>(maxheap.top()));
    sequence_begin = std::next(sequence_begin);
  }
  return ret;
}
vector<double> OnlineMedianWrapper(const vector<int>& sequence) {
  return OnlineMedian(cbegin(sequence), cend(sequence));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sequence"};
  return GenericTestMain(args, "online_median.cc", "online_median.tsv",
                         &OnlineMedianWrapper, DefaultComparator{},
                         param_names);
}
