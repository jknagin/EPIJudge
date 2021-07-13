#include <memory>

#include "binary_tree_with_parent_prototype.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::unique_ptr;

BinaryTreeNode<int>* Lca(const unique_ptr<BinaryTreeNode<int>>& node0, const unique_ptr<BinaryTreeNode<int>>& node1)
{
  std::unordered_set<BinaryTreeNode<int>* > seen;
  BinaryTreeNode<int>* p0;
  BinaryTreeNode<int>* p1;
  p0 = node0.get();
  p1 = node1.get();
  
  // Trivial case: starting nodes are equal
  if (p0 == p1) return p0;

  // Increment pointers, check if we've seen the pointers already, then add the pointers to seen set
  seen.insert(p0);
  seen.insert(p1);
  while(p0 || p1)
  {
    p0 = p0 == nullptr ? p0 : p0->parent;
    if (p0 != nullptr && seen.count(p0)) return p0;
    seen.insert(p0);

    p1 = p1 == nullptr ? p1 : p1->parent;
    if (p1 != nullptr && seen.count(p1)) return p1;
    seen.insert(p1);
  }
  return nullptr; // Should never reach here
}
int LcaWrapper(TimedExecutor& executor,
               const unique_ptr<BinaryTreeNode<int>>& tree, int key0,
               int key1) {
  const unique_ptr<BinaryTreeNode<int>>& node0 = MustFindNode(tree, key0);
  const unique_ptr<BinaryTreeNode<int>>& node1 = MustFindNode(tree, key1);

  auto result = executor.Run([&] { return Lca(node0, node1); });

  if (!result) {
    throw TestFailure("Result can not be nullptr");
  }
  return result->data;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "tree", "key0", "key1"};
  return GenericTestMain(args, "lowest_common_ancestor_close_ancestor.cc",
                         "lowest_common_ancestor.tsv", &LcaWrapper,
                         DefaultComparator{}, param_names);
}
