#include "list_node.h"
#include "test_framework/generic_test.h"

shared_ptr<ListNode<int> > reverse(shared_ptr<ListNode<int> > L)
{
  shared_ptr<ListNode<int> > prev, curr, next;
  prev = nullptr;
  curr = L;
  next = L->next;
  while (curr != nullptr)
  {
    next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }
  return prev;
}

int length(shared_ptr<ListNode<int> > L)
{
  shared_ptr<ListNode<int> > p = L;
  int len = 0;
  while (p != nullptr)
  {
    ++len;
    p = p->next;
  }
  return len;
}

shared_ptr<ListNode<int> > getMidNode(shared_ptr<ListNode<int> > L)
{
  shared_ptr<ListNode<int> > slow, fast;
  slow = L;
  fast = L;
  while (fast != nullptr)
  {
    fast = fast->next;
    if (fast == nullptr) break;
    fast = fast->next;
    slow = slow->next;
  }
  return slow;
}

bool IsLinkedListAPalindrome(shared_ptr<ListNode<int>> L)
{
  // Get the length of the entire list
  int len = length(L);
  if (len < 2) return true;

  shared_ptr<ListNode<int> > p1, p2;

  // Get middle node and reverse the second half of the list
  shared_ptr<ListNode<int> > mid = getMidNode(L);

  p1 = L; // points to beginning of first half of list
  p2 = reverse(mid); // points to begnning of second half of list, which has been reversed

  // Iterate over both halves of the list simultaneously and compare pointer values
  for (int i = 0; i < len / 2; ++i)
  {
    if (p1->data != p2->data) return false;
    p1 = p1->next;
    p2 = p2->next;
  }
  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L"};
  return GenericTestMain(args, "is_list_palindromic.cc",
                         "is_list_palindromic.tsv", &IsLinkedListAPalindrome,
                         DefaultComparator{}, param_names);
}
