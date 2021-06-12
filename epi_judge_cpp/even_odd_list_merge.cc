#include "list_node.h"
#include "test_framework/generic_test.h"
shared_ptr<ListNode<int>> EvenOddMerge(const shared_ptr<ListNode<int>>& L) {
  if (L == nullptr) return L;
  if (L->next == nullptr) return L;

  // At this point, L has at least two nodes, so there will be an even list and an odd list
  // Maintain four list pointers, two for even numbered nodes and two for odd numbered nodes
  shared_ptr<ListNode<int> > oddHead, evenHead, odd, even, p;
  evenHead = L;
  oddHead = L->next;
  odd = oddHead;
  even = evenHead;

  // Iteration pointer
  p = odd->next;

  // Determine whether we are at an even or an odd node
  int parity = 0;
  while (p != nullptr)
  {
    //odd
    if (parity)
    {
      // Append the current node to the odd list and advance the odd list pointer
			odd->next = p;
			odd = odd->next;
    }
    //even
    else
    {
      // Append the current node to the even list and advance the even list pointer
			even->next = p;
			even = even->next;
    }

    // Advance iteration pointer and flip parity
    p = p->next;
    parity = !parity;
  }
 
  // Connect end of even list to beginning of odd list and return combined list
	even->next = oddHead;
	odd->next = nullptr;
	return evenHead;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L"};
  return GenericTestMain(args, "even_odd_list_merge.cc",
                         "even_odd_list_merge.tsv", &EvenOddMerge,
                         DefaultComparator{}, param_names);
}
