#include <memory>
#include <vector>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;

vector<vector<int>> BinaryTreeDepthOrder(
  const unique_ptr<BinaryTreeNode<int>>& tree) {
  if (tree == nullptr) return {};
  std::queue<BinaryTreeNode<int>* > queue_;
  queue_.push(tree.get());
  std::vector<std::vector<int> > ret;
  while (!queue_.empty())
  {
    int size_ = queue_.size();
    ret.push_back({});
    for (int i = 0; i < size_; ++i)
    {
      BinaryTreeNode<int>* curr = queue_.front();
      queue_.pop();
      ret.back().push_back(curr->data);
      if (curr->left) queue_.push(curr->left.get());
      if (curr->right) queue_.push(curr->right.get());
    }
  }
  return ret;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_level_order.cc", "tree_level_order.tsv",
                         &BinaryTreeDepthOrder, DefaultComparator{},
                         param_names);
}
