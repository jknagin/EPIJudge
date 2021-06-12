#include "list_node.h"
#include "test_framework/generic_test.h"

shared_ptr<ListNode<int> > reverseList(shared_ptr<ListNode<int> > L, int k)
{
  shared_ptr<ListNode<int> > prev, curr, next;
  prev = nullptr;
  curr = L;
  for (int i = 0; i < k; ++i)
  {
    next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }
  return prev;
}
shared_ptr<ListNode<int>> ReverseSublist(shared_ptr<ListNode<int>> L, int start,
                                         int finish) {
  // If L has 0 or 1 nodes, its reverse is the same
  if (L == nullptr) return L;
  if (L->next == nullptr) return L;

  // Number of nodes to reverse
	int k = finish - start + 1;
  shared_ptr<ListNode<int> > p1 = L;

  // Different logic if start is 1 or greater than 1
  if (start > 1)
  {
		for(int i=0;i<start - 2;++i) p1 = p1->next;
    shared_ptr<ListNode<int> > p2 = p1->next;
    shared_ptr<ListNode<int> > p4 = p2;
    for (int i = 0; i < k; ++i) p4 = p4->next;
		p1->next = reverseList(p2, k);
    p2->next = p4;
    return L;
  }
  else
  {
    shared_ptr<ListNode<int> > p4 = p1;
    for (int i = 0; i < k; ++i) p4 = p4->next;
		shared_ptr<ListNode<int> > ret = reverseList(p1, k);
    p1->next = p4;
    return ret;
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L", "start", "finish"};
  return GenericTestMain(args, "reverse_sublist.cc", "reverse_sublist.tsv",
                         &ReverseSublist, DefaultComparator{}, param_names);
}
