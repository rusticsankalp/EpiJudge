#include <memory>
#include <vector>

#include "bst_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;


void FindKLargestValueInBSTHelper(const unique_ptr<BstNode<int>>& tree, int k, vector<int>& kLargest) {
    if (tree != nullptr && kLargest.size() < k) {
        FindKLargestValueInBSTHelper(tree->right, k, kLargest);
        if (kLargest.size() < k) {
            kLargest.emplace_back(tree->data);
            FindKLargestValueInBSTHelper(tree->left, k, kLargest);
        }
    
    }
}

vector<int> FindKLargestInBST(const unique_ptr<BstNode<int>>& tree, int k) {
    vector<int> kLargest;
    FindKLargestValueInBSTHelper(tree, k, kLargest);
    return kLargest;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree", "k"};
  return GenericTestMain(args, "k_largest_values_in_bst.cc",
                         "k_largest_values_in_bst.tsv", &FindKLargestInBST,
                         UnorderedComparator{}, param_names);
}
