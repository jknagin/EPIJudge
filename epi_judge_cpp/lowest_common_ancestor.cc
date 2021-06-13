#include <memory>

#include "binary_tree_node.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::unique_ptr;

// Post order traversal to find the deepest node and its subtree containing both node0 and node1
// Also with early termination
int numChildren(BinaryTreeNode<int>* tree,
                BinaryTreeNode<int>* node0,
                BinaryTreeNode<int>* node1,
                BinaryTreeNode<int>*& LCA)
{
  // Early terminatino
  if (LCA != nullptr) return 0;

  // Base case
  if (tree == nullptr) return 0;

  // Number of "special" children on the left subtree
  int nLeft = numChildren(tree->left.get(), node0, node1, LCA);
  if (LCA != nullptr) return 0; // Early termination

  // Number of "special" children on the right subtree
  int nRight = numChildren(tree->right.get(), node0, node1, LCA);
  if (LCA != nullptr) return 0; // Early termination

  /* Total number of "special" children in tree rooted at tree:
  * number of special children in left subtree, plus
  * number of special children in right subtree, plus,
  * whether or not tree is a special child
  */

  // At this point, neither left nor right subtrees contain both special children, since LCA is still nullptr
  // If we have found all the special children at this tree, this node is the LCA
  int ret = nLeft + nRight + static_cast<int>(tree == node0 || tree == node1);
  if (ret == 2) LCA = tree;
  return ret;
}

BinaryTreeNode<int>* Lca(const unique_ptr<BinaryTreeNode<int>>& tree,
                         const unique_ptr<BinaryTreeNode<int>>& node0,
                         const unique_ptr<BinaryTreeNode<int>>& node1) {
  BinaryTreeNode<int>* LCA = nullptr;
  numChildren(tree.get(), node0.get(), node1.get(), LCA);
  return LCA;
}
int LcaWrapper(TimedExecutor& executor,
               const unique_ptr<BinaryTreeNode<int>>& tree, int key0,
               int key1) {
  const unique_ptr<BinaryTreeNode<int>>& node0 = MustFindNode(tree, key0);
  const unique_ptr<BinaryTreeNode<int>>& node1 = MustFindNode(tree, key1);

  auto result = executor.Run([&] { return Lca(tree, node0, node1); });

  if (!result) {
    throw TestFailure("Result can not be nullptr");
  }
  return result->data;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "tree", "key0", "key1"};
  return GenericTestMain(args, "lowest_common_ancestor.cc",
                         "lowest_common_ancestor.tsv", &LcaWrapper,
                         DefaultComparator{}, param_names);
}
