#include <memory>

#include "bst_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;

BstNode<int>* FindFirstGreaterThanK(const unique_ptr<BstNode<int>>& tree, int k) {
  BstNode<int>* p = tree.get();
  BstNode<int>* ret = nullptr;

  while(p)
  {
    // If the current node's value is greater than k, it's the best candidate for returning so far
    if (p->data > k)
    {
      ret = p;
      p = p->left.get();
    }
    // Else, the current node's value and all of its left subtree values are <= k, so ignore them entirely
    else
    {
      p = p->right.get();
    }
  }
  return ret;
}
int FindFirstGreaterThanKWrapper(const unique_ptr<BstNode<int>>& tree, int k) {
  auto result = FindFirstGreaterThanK(tree, k);
  return result ? result->data : -1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree", "k"};
  return GenericTestMain(args, "search_first_greater_value_in_bst.cc",
                         "search_first_greater_value_in_bst.tsv",
                         &FindFirstGreaterThanKWrapper, DefaultComparator{},
                         param_names);
}
