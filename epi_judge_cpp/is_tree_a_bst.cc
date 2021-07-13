#include <memory>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;


bool isBST(BinaryTreeNode<int>* tree, int low, int high)
{
  if (tree == nullptr) return true;

  // Check if data is in bounds
  if (tree->data < low || tree->data > high) return false;

  // Recurse:
  // Bounds for left subtree are [low, data], for right subtree [data, high]
  return isBST(tree->left.get(), low, tree->data) && isBST(tree->right.get(), tree->data, high);
}

bool IsBinaryTreeBST(const unique_ptr<BinaryTreeNode<int>>& tree) {
  return isBST(tree.get(), INT_MIN, INT_MAX);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_a_bst.cc", "is_tree_a_bst.tsv",
                         &IsBinaryTreeBST, DefaultComparator{}, param_names);
}
