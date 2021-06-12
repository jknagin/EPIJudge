#include <memory>

#include "list_node.h"
#include "test_framework/generic_test.h"
using std::shared_ptr;

int len(const std::shared_ptr<ListNode<int> >& L)
{
  int length = 0;
  shared_ptr<ListNode<int> > p = L;
  while (p != nullptr)
  {
    ++length;
    p = p->next;
  }
  return length;
}

shared_ptr<ListNode<int>> CyclicallyRightShiftList(shared_ptr<ListNode<int>> L,
                                                   int k) {
  // Manipulate the four pointers
  if (L == nullptr) return nullptr;
  std::shared_ptr<ListNode<int> > p1, p2, p3, p4;
  p1 = L;
  p2 = L;
  p3 = L;
  p4 = L;
  int length = len(L);
  k = k % length;
  if (k == 0) return L;
  for (int i = 0; i < length - k - 1; ++i)
  {
    p1 = p1->next;
    p3 = p3->next;
  }
  p2 = p1->next;
  while (p3->next != nullptr)
  {
    p3 = p3->next;
  }
  p1->next = nullptr;
  p3->next = p4;
  return p2;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L", "k"};
  return GenericTestMain(
      args, "list_cyclic_right_shift.cc", "list_cyclic_right_shift.tsv",
      &CyclicallyRightShiftList, DefaultComparator{}, param_names);
}
