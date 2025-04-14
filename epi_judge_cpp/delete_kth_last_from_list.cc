#include <memory>

#include "list_node.h"
#include "test_framework/generic_test.h"
using std::shared_ptr;

// Assumes L has at least k nodes, deletes the k-th last node in L.
shared_ptr<ListNode<int>> RemoveKthLast(const shared_ptr<ListNode<int>>& L,
                                        int k) {
  // TODO - you fill in here.

    int length = 0;

    auto dummy_head = make_shared<ListNode<int>>();
    dummy_head->next = L;
    auto iter = L; 
    while (iter)
    {
        iter = iter->next;
        length++;
    }

    if (length < k)
        return nullptr;

    auto nth = length - k;

    iter = dummy_head;
    // use 1..nth instead of 0..<nth
    for (int i = 1; i <= nth; i++)
    {
        iter = iter->next;
    }

    iter->next = iter->next->next;

  return dummy_head->next;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L", "k"};
  return GenericTestMain(args, "delete_kth_last_from_list.cc",
                         "delete_kth_last_from_list.tsv", &RemoveKthLast,
                         DefaultComparator{}, param_names);
}
