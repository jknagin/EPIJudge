#include <memory>

#include "list_node.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::shared_ptr;

int listLength(shared_ptr<ListNode<int> > head)
{
  shared_ptr<ListNode<int> > p = head;
  int len = 0;
  while (p != nullptr)
  {
    p = p->next;
    ++len;
  }
  return len;
}

shared_ptr<ListNode<int>> OverlappingNoCycleLists(
    shared_ptr<ListNode<int>> l0, shared_ptr<ListNode<int>> l1) {
  if (l0 == nullptr || l1 == nullptr) return nullptr;
  int length0 = listLength(l0);
  int length1 = listLength(l1);

  // Offset pointer to longer list by difference between list lengths
  shared_ptr<ListNode<int> > p0 = l0;
  shared_ptr<ListNode<int> > p1 = l1;

  if (length0 < length1)
  {
    for (int i = length0; i < length1; ++i) p1 = p1->next;
  }
  else if (length1 < length0)
  {
    for (int i = length1; i < length0; ++i) p0 = p0->next;
  }

  // Increment both pointers, returning either of them if they are equal
  while (p0 != p1)
  {
    p0 = p0->next;
    p1 = p1->next;
  }
  
  // This works even if there is no intersection, because then p0 = p1 = null and we want to return null if there is no intersection
  return p0;
}
void OverlappingNoCycleListsWrapper(TimedExecutor& executor,
                                    shared_ptr<ListNode<int>> l0,
                                    shared_ptr<ListNode<int>> l1,
                                    shared_ptr<ListNode<int>> common) {
  if (common) {
    if (l0) {
      auto i = l0;
      while (i->next) {
        i = i->next;
      }
      i->next = common;
    } else {
      l0 = common;
    }

    if (l1) {
      auto i = l1;
      while (i->next) {
        i = i->next;
      }
      i->next = common;
    } else {
      l1 = common;
    }
  }

  auto result = executor.Run([&] { return OverlappingNoCycleLists(l0, l1); });

  if (result != common) {
    throw TestFailure("Invalid result");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "l0", "l1", "common"};
  return GenericTestMain(
      args, "do_terminated_lists_overlap.cc", "do_terminated_lists_overlap.tsv",
      &OverlappingNoCycleListsWrapper, DefaultComparator{}, param_names);
}
