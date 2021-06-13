#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

// Each child receives a COPY of the currentSum and a REFERENCE to the runningSum
void preOrderTraversal(BinaryTreeNode<int>* root, int currentSum, int& runningSum)
{
  if (root == nullptr) return;

  // The values in each node are binary digits and the root to leaf paths represent binary numbers, so we need to add them this way
  // root is MSB, later values are less significant bits
  currentSum = 2 * currentSum + root->data;

  // If we are at a leaf node, add the current sum to the running sum
  if (root->left == nullptr && root->right == nullptr) runningSum += currentSum;

  // Recurse on children now for pre order traversal
  preOrderTraversal(root->left.get(), currentSum, runningSum);
  preOrderTraversal(root->right.get(), currentSum, runningSum);
}

int SumRootToLeaf(const unique_ptr<BinaryTreeNode<int>>& tree) {
  int runningSum = 0;
  preOrderTraversal(tree.get(), 0, runningSum);
  return runningSum;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "sum_root_to_leaf.cc", "sum_root_to_leaf.tsv",
                         &SumRootToLeaf, DefaultComparator{}, param_names);
}
