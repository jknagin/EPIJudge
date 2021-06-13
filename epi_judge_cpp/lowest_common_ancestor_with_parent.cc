#include "binary_tree_with_parent_prototype.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"

int getLength(BinaryTreeNode<int>* node)
{
  int length = 0;
  while (node != nullptr)
  {
    node = node->parent;
    ++length;
  }
  return length;
}

void offsetByK(BinaryTreeNode<int>*& node, int k)
{
  for (int i = 0; i < k; ++i) node = node->parent;
}

// This is the same algorithm as finding the intersection point of two linked lists
BinaryTreeNode<int>* Lca(const unique_ptr<BinaryTreeNode<int>>& node0,
                         const unique_ptr<BinaryTreeNode<int>>& node1) {
  int length0 = getLength(node0.get());
  int length1 = getLength(node1.get());
  BinaryTreeNode<int>* start0 = node0.get();
  BinaryTreeNode<int>* start1 = node1.get();
  int k = std::abs(length1 - length0);
  if (length0 > length1) offsetByK(start0, k);
  else if (length0 < length1) offsetByK(start1, k);
  while (start0 != start1)
  {
    start0 = start0->parent;
    start1 = start1->parent;
  }
  return start0;
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
  return GenericTestMain(args, "lowest_common_ancestor_with_parent.cc",
                         "lowest_common_ancestor.tsv", &LcaWrapper,
                         DefaultComparator{}, param_names);
}
