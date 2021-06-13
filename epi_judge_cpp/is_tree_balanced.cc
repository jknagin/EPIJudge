#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

int height(BinaryTreeNode<int>* node, bool& balanced)
{
  if (node == nullptr) return 0;
  if (!balanced) return 0;
  int leftHeight = height(node->left.get(), balanced);
  if (!balanced) return 0;
  int rightHeight = height(node->right.get(), balanced);
  if (!balanced) return 0;
  balanced = std::abs(rightHeight - leftHeight) <= 1;
  if (!balanced) return 0;
  return std::max(leftHeight, rightHeight) + 1;
}

bool IsBalanced(const unique_ptr<BinaryTreeNode<int>>& tree) {
  bool balanced = true;
  height(tree.get(), balanced);
  return balanced;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_balanced.cc", "is_tree_balanced.tsv",
                         &IsBalanced, DefaultComparator{}, param_names);
}
