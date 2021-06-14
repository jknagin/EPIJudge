#include "binary_tree_with_parent_prototype.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"

BinaryTreeNode<int>* FindSuccessor(
    const unique_ptr<BinaryTreeNode<int>>& node) {
  // If there is a right subtree, the in order successor is the leftmost child of the right subtree
  if (node->right != nullptr)
  {
    BinaryTreeNode<int>* curr = node->right.get();
    while (curr->left != nullptr)
    {
      curr = curr->left.get();
    }
    return curr;
  }
  // If there is not a right subtree, go up the parent chain
  // Once we get to a node up the chain where the node is a left child of its parent, the parent is the successor
  else
  {
    BinaryTreeNode<int>* curr = node.get();
    BinaryTreeNode<int>* parent = curr->parent;
    while (parent != nullptr && curr != parent->left.get())
    {
      curr = parent;
      parent = parent->parent;
    }
    return parent;
  }
}
int FindSuccessorWrapper(const unique_ptr<BinaryTreeNode<int>>& tree,
                         int node_idx) {
  auto result = FindSuccessor(MustFindNode(tree, node_idx));
  return result ? result->data : -1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree", "node_idx"};
  return GenericTestMain(args, "successor_in_tree.cc", "successor_in_tree.tsv",
                         &FindSuccessorWrapper, DefaultComparator{},
                         param_names);
}
