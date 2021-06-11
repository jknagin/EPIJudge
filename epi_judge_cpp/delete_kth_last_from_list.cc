#include <memory>

#include "list_node.h"
#include "test_framework/generic_test.h"
using std::shared_ptr;

// Assumes L has at least k nodes, deletes the k-th last node in L.
shared_ptr<ListNode<int>> RemoveKthLast(const shared_ptr<ListNode<int>>& L,
                                        int k) {
  std::shared_ptr<ListNode<int> > p1 = L;
  std::shared_ptr<ListNode<int> > p2 = L;
  
  // Advance p2 by k nodes
  for (int i = 0; i < k; ++i) p2 = p2->next;

  // If p2 == nullptr, this means we are removing the first node (k = len(L)), so just return the next node
  if (p2 == nullptr) return p1->next;

  // Otherwise, advance both pointers simultaneously
  while (p2->next != nullptr)
  {
    p1 = p1->next;
    p2 = p2->next;
  }

  // When p2 reaches the end of the list, p1->next is the node to be deleted
  p1->next = p1->next->next;

  // Return the head of the list again
  return L;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L", "k"};
  return GenericTestMain(args, "delete_kth_last_from_list.cc",
                         "delete_kth_last_from_list.tsv", &RemoveKthLast,
                         DefaultComparator{}, param_names);
}
