#include <memory>

#include "list_node.h"
#include "test_framework/generic_test.h"
using std::shared_ptr;

shared_ptr<ListNode<int>> RemoveDuplicates(const shared_ptr<ListNode<int>>& L) {
  if (L == nullptr) return L;
  if (L->next == nullptr) return L;

  shared_ptr<ListNode<int> > writePtr = L;
  shared_ptr<ListNode<int> > p = L->next;

  // Similar to removing duplicates from a sorted array
  // Maintain two pointers, a write pointer, and a normal iteration pointer
  // While we are in bounds of the list
  while (p != nullptr)
  {
    // If the iteration pointer's data is different from the writePtr's data, update writePtr->next and advance writePtr
    if (p->data != writePtr->data)
    {
      writePtr->next = p;
      writePtr = p;
    }

    // Always advance the iteration pointer
    p = p->next;
  }

  // Handle the case of trailing duplicates
  if (writePtr->next != nullptr)
  {
    if (writePtr->data == writePtr->next->data)
    {
      writePtr->next = nullptr;
    }
  }

  return L;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L"};
  return GenericTestMain(args, "remove_duplicates_from_sorted_list.cc",
                         "remove_duplicates_from_sorted_list.tsv",
                         &RemoveDuplicates, DefaultComparator{}, param_names);
}
