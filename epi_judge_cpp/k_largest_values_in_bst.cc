#include <memory>
#include <vector>

#include "bst_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;

void reverseIOT(const std::unique_ptr<BstNode<int> >& tree, const int& k, std::vector<int>& ret)
{
  if (tree == nullptr) return;
  reverseIOT(tree->right, k, ret);
  if (ret.size() == k) return;
  ret.emplace_back(tree->data);
  reverseIOT(tree->left, k, ret);
}

vector<int> FindKLargestInBST(const unique_ptr<BstNode<int> >& tree, int k) {
  std::vector<int> ret;
  reverseIOT(tree, k, ret);
  return ret;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree", "k"};
  return GenericTestMain(args, "k_largest_values_in_bst.cc",
                         "k_largest_values_in_bst.tsv", &FindKLargestInBST,
                         UnorderedComparator{}, param_names);
}
