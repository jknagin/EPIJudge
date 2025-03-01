#include <algorithm>
#include <iterator>
#include <memory>
#include <vector>

#include "list_node.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::shared_ptr;
shared_ptr<ListNode<int>> ListPivoting(const shared_ptr<ListNode<int>>& l,
                                       int x) {
  if (l == nullptr) return l;

  // Maintain three lists - less, equal, greater
  // As we traverse the list, append the current node to the appropriate list
  shared_ptr<ListNode<int> > lessHead, equalHead, greaterHead, less, equal, greater, p;
  p = l;
  while (p != nullptr)
  {
    if (p->data < x)
    {
      if (lessHead == nullptr)
      {
        lessHead = p;
        less = p;
      }
      else
      {
        less->next = p;
        less = less->next;
      }
    }
    else if (p->data == x)
    {
      if (equalHead == nullptr)
      {
        equalHead = p;
        equal = p;
      }
      else
      {
        equal->next = p;
        equal = equal->next;
      }
    }
    else
    {
      if (greaterHead == nullptr)
      {
        greaterHead = p;
        greater = p;
      }
      else
      {
        greater->next = p;
        greater = greater->next;
      }
    }

    p = p->next;
  }

  // Build the lists less->equal->greater  
  if (lessHead != nullptr)
  {
    if (equalHead != nullptr)
    {
      less->next = equalHead;
      if (greaterHead != nullptr)
      {
        equal->next = greaterHead;
        greater->next = nullptr;
      }
      else
      {
        equal->next = nullptr;
      }
    }
    else
    {
      less->next = nullptr;
    }
    return lessHead;
  }
  else if (equalHead != nullptr)
  {
    if (greaterHead != nullptr)
    {
      equal->next = greaterHead;
      greater->next = nullptr;
    }
    else
    {
      equal->next = nullptr;
    }
    return equalHead;
  }
  else if (greaterHead != nullptr)
  {
    greater->next = nullptr;
    return greaterHead;
  }

  return l; // Should never get here
}
std::vector<int> ListToVector(const shared_ptr<ListNode<int>>& l) {
  std::vector<int> v;
  ListNode<int>* it = l.get();
  while (it) {
    v.push_back(it->data);
    it = it->next.get();
  }
  return v;
}

void ListPivotingWrapper(TimedExecutor& executor,
                         const shared_ptr<ListNode<int>>& l, int x) {
  std::vector<int> original = ListToVector(l);

  std::shared_ptr<ListNode<int>> pivoted_list =
      executor.Run([&] { return ListPivoting(l, x); });

  std::vector<int> pivoted = ListToVector(pivoted_list);
  enum class Mode { kLess, kEq, kGreater } mode = Mode::kLess;
  for (auto& i : pivoted) {
    switch (mode) {
      case Mode::kLess:
        if (i == x) {
          mode = Mode::kEq;
        } else if (i > x) {
          mode = Mode::kGreater;
        }
        break;
      case Mode::kEq:
        if (i < x) {
          throw TestFailure("List is not pivoted");
        } else if (i > x) {
          mode = Mode::kGreater;
        }
        break;
      case Mode::kGreater:
        if (i <= x) {
          throw TestFailure("List is not pivoted");
        }
    }
  }
  std::sort(begin(original), end(original));
  std::sort(begin(pivoted), end(pivoted));
  if (original != pivoted) {
    throw TestFailure("Result list contains different values");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "l", "x"};
  return GenericTestMain(args, "pivot_list.cc", "pivot_list.tsv",
                         &ListPivotingWrapper, DefaultComparator{},
                         param_names);
}
