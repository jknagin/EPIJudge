#include <memory>

#include "bst_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;

// Preorder_sequence[start] is the root of the tree in the interval [start, end]
// Everything after start until the next greater element belongs in the left subtree
// Everything after that is in the right subtree
std::unique_ptr<BstNode<int> > helper(const std::vector<int>& preorder_sequence, int start, int end)
{
  if (start > end) return nullptr;
  
  // Find index of next greater element
  int nextGreaterIdx = end + 1;
  for(int i=start+1;i<=end;++i)
  {
    if (preorder_sequence[i] > preorder_sequence[start])
    {
      nextGreaterIdx = i;
      break;
    }
  }

  // Recurse
  return std::make_unique<BstNode<int> >(BstNode<int>{preorder_sequence[start],
          helper(preorder_sequence, start + 1, nextGreaterIdx - 1),
          helper(preorder_sequence, nextGreaterIdx, end)});
}

unique_ptr<BstNode<int>> RebuildBSTFromPreorder( const vector<int>& preorder_sequence)
{
  return helper(preorder_sequence, 0, preorder_sequence.size() - 1);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"preorder_sequence"};
  return GenericTestMain(args, "bst_from_preorder.cc", "bst_from_preorder.tsv",
                         &RebuildBSTFromPreorder, DefaultComparator{},
                         param_names);
}
