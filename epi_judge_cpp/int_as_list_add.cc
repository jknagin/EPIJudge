#include "list_node.h"
#include "test_framework/generic_test.h"

shared_ptr<ListNode<int>> AddTwoNumbers(shared_ptr<ListNode<int>> L1,
  shared_ptr<ListNode<int>> L2) {
  shared_ptr<ListNode<int> > retHead = nullptr;
  shared_ptr<ListNode<int> > ret = retHead;
  shared_ptr<ListNode<int> > p1, p2;
  p1 = L1;
  p2 = L2;
  bool carry = false;

  // While we still have to traverse either of the lists or we have a (trailing) carry
  while (p1 != nullptr || p2 != nullptr || carry)
  {
    // Calculate the digit with whatever we have left to process
    int digit = (p1 ? p1->data : 0) + (p2 ? p2->data : 0) + (carry ? 1 : 0);

    // Account for overflow past 9
    carry = false;
    if (digit >= 10)
    {
      digit -= 10;
      carry = true;
    }

    // Build return list
    if (retHead == nullptr)
    {
      retHead = make_shared<ListNode<int> >(digit, nullptr);
      ret = retHead;
    }
    else
    {
			ret->next = make_shared<ListNode<int> >(digit, nullptr);
      ret = ret->next;
    }

    // Advance pointers
    p1 = (p1 ? p1->next : nullptr);
    p2 = (p2 ? p2->next : nullptr);
  }

  return retHead;

}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L1", "L2"};
  return GenericTestMain(args, "int_as_list_add.cc", "int_as_list_add.tsv",
                         &AddTwoNumbers, DefaultComparator{}, param_names);
}
