#include "list_node.h"
#include "test_framework/generic_test.h"
shared_ptr<ListNode<int>> MergeTwoSortedLists(shared_ptr<ListNode<int>> L1,
                                              shared_ptr<ListNode<int>> L2) {
  if (L1 == nullptr) return L2;
  if (L2 == nullptr) return L1;

  std::shared_ptr<ListNode<int> > retHead;
	std::shared_ptr<ListNode<int> > p1 = L1;
	std::shared_ptr<ListNode<int> > p2 = L2;
  std::shared_ptr<ListNode<int> > curr;
  if (L1->data <= L2->data)
  {
    retHead = L1;
    p1 = L1->next;
  }
  else
  {
    retHead = L2;
    p2 = L2->next;
  }

  curr = retHead;

  while (p1 != nullptr && p2 != nullptr)
  {
    if (p1->data <= p2->data)
    {
      curr->next = p1;
      p1 = p1->next;
    }
    else
    {
      curr->next = p2;
      p2 = p2->next;
    }
    curr = curr->next;
  }
  if (p1 == nullptr)
  {
    curr->next = p2;
  }
  else if (p2 == nullptr)
  {
    curr->next = p1;
  }
  return retHead;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L1", "L2"};
  return GenericTestMain(args, "sorted_lists_merge.cc",
                         "sorted_lists_merge.tsv", &MergeTwoSortedLists,
                         DefaultComparator{}, param_names);
}
