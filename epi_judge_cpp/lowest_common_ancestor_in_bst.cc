#include <memory>

#include "bst_node.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::unique_ptr;

// Input nodes are nonempty and the key at s is less than or equal to that at
// b.

void helper(BstNode<int>* node, BstNode<int>* s, BstNode<int>* b, BstNode<int>*& LCA)
{
  if (LCA != nullptr) return;

  // Trivial case, if the node is one of the target nodes, then it's the LCA
  if (node == s || node == b)
  {
    LCA = node;
    return;
  }

  // If the current node's value is between the two target node values, we've found our node
  // because each subtree of this node has one of the target nodes, and that's true only if the node is the LCA
  if (s->data < node->data && node->data < b->data)
  {
    LCA = node;
    return;
  }
  // Otherwise, recurse left or right, depending on how the current node's value compares to the target node values
  else if (node->data < s->data)
  {
    helper(node->right.get(), s, b, LCA);
  }
  else if (node->data > b->data)
  {
    helper(node->left.get(), s, b, LCA);
  }
}

BstNode<int>* FindLca(const unique_ptr<BstNode<int>>& tree, const unique_ptr<BstNode<int>>& s, const unique_ptr<BstNode<int>>& b)
{
  BstNode<int>* LCA = nullptr;
  helper(tree.get(), s.get(), b.get(), LCA);
  return LCA;
}
int LcaWrapper(TimedExecutor& executor,
               const std::unique_ptr<BstNode<int>>& tree, int key0, int key1) {
  const unique_ptr<BstNode<int>>& node0 = MustFindNode(tree, key0);
  const unique_ptr<BstNode<int>>& node1 = MustFindNode(tree, key1);

  auto result = executor.Run([&] { return FindLca(tree, node0, node1); });

  if (!result) {
    throw TestFailure("Result can not be nullptr");
  }
  return result->data;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "tree", "key0", "key1"};
  return GenericTestMain(args, "lowest_common_ancestor_in_bst.cc",
                         "lowest_common_ancestor_in_bst.tsv", &LcaWrapper,
                         DefaultComparator{}, param_names);
}
