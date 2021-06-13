#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

bool areMirrorReflections(BinaryTreeNode<int>* left, BinaryTreeNode<int>* right)
{
  /* Two trees are mirror reflections of each other if:
     * their roots have the same value
     * their near children are mirror reflections
     * their far children are mirror reflections
  */
  if (left == nullptr && right == nullptr) return true;
  if ((left == nullptr) || (right == nullptr)) return false;
  return left->data == right->data && areMirrorReflections(left->left.get(), right->right.get()) && areMirrorReflections(left->right.get(), right->left.get());
}

bool IsSymmetric(const unique_ptr<BinaryTreeNode<int>>& tree) {
  // A tree is symmetric if its children are mirror reflections of each other
  if (tree == nullptr) return true;
  return areMirrorReflections(tree->left.get(), tree->right.get());
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_symmetric.cc", "is_tree_symmetric.tsv",
                         &IsSymmetric, DefaultComparator{}, param_names);
}
