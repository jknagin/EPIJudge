#include <set>
#include <stdexcept>

#include "list_node.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"

shared_ptr<ListNode<int>> HasCycle(const shared_ptr<ListNode<int>>& head) {
  if (head == nullptr) return nullptr;

  // Determine if there is a cycle
  shared_ptr<ListNode<int> > slow, fast;
  slow = head;
  fast = head->next;
  while (fast != slow)
  {
    if (fast == nullptr) return nullptr;
    fast = fast->next;
    if (fast == nullptr) return nullptr;
    fast = fast->next;
    slow = slow->next;
  }

  // At this point, there is a cycle because slow == fast
  // Calculate the length of the cycle
  int cycleLength = 1;
  fast = fast->next;
  while (slow != fast)
  {
    fast = fast->next;
    ++cycleLength;
  }

  // Reset both pointers, offset fast by length of cycle
  slow = head;
  fast = slow;
  for (int i = 0; i < cycleLength; ++i) fast = fast->next;
  
  // Increment both pointers the same amount until they intersect.
  // The intersection point is the start of the cycle
  while (fast != slow)
  {
    slow = slow->next;
    fast = fast->next;
  }
  return slow;
}

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

shared_ptr<ListNode<int>> OverlappingLists(shared_ptr<ListNode<int>> l0,
                                           shared_ptr<ListNode<int>> l1) {
  shared_ptr<ListNode<int> > cycleStart0 = HasCycle(l0);
  shared_ptr<ListNode<int> > cycleStart1 = HasCycle(l1);

  // If one list has a cycle and the other doesn't, the lists cannot overlap
  if ((cycleStart0 == nullptr) ^ (cycleStart1 == nullptr)) return nullptr;

  // If neither list has a cycle, do the normal cycle detection algorithm for non-cyclic lists
  if (cycleStart0 == nullptr && cycleStart1 == nullptr)
  {
    return OverlappingNoCycleLists(l0, l1);
  }

  // Here, both lists contain cycles
  // Iterate over one of the cycles, and if any node equals the starting node of the other cycle, return either node
  // If we get back to the starting node if the cycle we started iterating over, return nullptr, because the two lists have different cycles
  if (cycleStart0 == cycleStart1) return cycleStart0;
  shared_ptr<ListNode<int> > p0 = cycleStart0->next;
  while (p0 != cycleStart0)
  {
    if (p0 == cycleStart1) return p0;
    p0 = p0->next;
  }
  return nullptr;
}
void OverlappingListsWrapper(TimedExecutor& executor,
                             shared_ptr<ListNode<int>> l0,
                             shared_ptr<ListNode<int>> l1,
                             shared_ptr<ListNode<int>> common, int cycle0,
                             int cycle1) {
  if (common) {
    if (!l0) {
      l0 = common;
    } else {
      auto it = l0;
      while (it->next) {
        it = it->next;
      }
      it->next = common;
    }

    if (!l1) {
      l1 = common;
    } else {
      auto it = l1;
      while (it->next) {
        it = it->next;
      }
      it->next = common;
    }
  }

  if (cycle0 != -1 && l0) {
    auto last = l0;
    while (last->next) {
      last = last->next;
    }
    auto it = l0;
    while (cycle0-- > 0) {
      if (!it) {
        throw std::runtime_error("Invalid input data");
      }
      it = it->next;
    }
    last->next = it;
  }

  if (cycle1 != -1 && l1) {
    auto last = l1;
    while (last->next) {
      last = last->next;
    }
    auto it = l1;
    while (cycle1-- > 0) {
      if (!it) {
        throw std::runtime_error("Invalid input data");
      }
      it = it->next;
    }
    last->next = it;
  }

  std::set<shared_ptr<ListNode<int>>> common_nodes;
  auto it = common;
  while (it && common_nodes.count(it) == 0) {
    common_nodes.insert(it);
    it = it->next;
  }

  auto result = executor.Run([&] { return OverlappingLists(l0, l1); });

  if (!((common_nodes.empty() && result == nullptr) ||
        common_nodes.count(result) > 0)) {
    throw TestFailure("Invalid result");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "l0",     "l1",
                                       "common",   "cycle0", "cycle1"};
  return GenericTestMain(args, "do_lists_overlap.cc", "do_lists_overlap.tsv",
                         &OverlappingListsWrapper, DefaultComparator{},
                         param_names);
}
