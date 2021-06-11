#include <memory>

#include "list_node.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::shared_ptr;

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
void HasCycleWrapper(TimedExecutor& executor,
                     const shared_ptr<ListNode<int>>& head, int cycle_idx) {
  int cycle_length = 0;
  if (cycle_idx != -1) {
    if (!head) {
      throw std::runtime_error("Can't cycle empty list");
    }
    shared_ptr<ListNode<int>> cycle_start, cursor = head;
    while (cursor->next) {
      if (cursor->data == cycle_idx) {
        cycle_start = cursor;
      }
      cursor = cursor->next;
      cycle_length += !!cycle_start;
    }
    if (cursor->data == cycle_idx) {
      cycle_start = cursor;
    }
    if (!cycle_start) {
      throw std::runtime_error("Can't find a cycle start");
    }
    cursor->next = cycle_start;
    cycle_length++;
  }
  shared_ptr<ListNode<int>> result =
      executor.Run([&] { return HasCycle(head); });

  if (cycle_idx == -1) {
    if (result != nullptr) {
      throw TestFailure("Found a non-existing cycle");
    }
  } else {
    if (result == nullptr) {
      throw TestFailure("Existing cycle was not found");
    }

    auto cursor = result;
    do {
      cursor = cursor->next;
      cycle_length--;
      if (!cursor || cycle_length < 0) {
        throw TestFailure(
            "Returned node does not belong to the cycle or is not the "
            "closest node to the head");
      }
    } while (cursor != result);

    if (cycle_length != 0) {
      throw TestFailure(
          "Returned node does not belong to the cycle or is not the closest "
          "node to the head");
    }
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "head", "cycle_idx"};
  return GenericTestMain(args, "is_list_cyclic.cc", "is_list_cyclic.tsv",
                         &HasCycleWrapper, DefaultComparator{}, param_names);
}
