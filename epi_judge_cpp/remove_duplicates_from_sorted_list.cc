#include <memory>

#include "list_node.h"
#include "test_framework/generic_test.h"
using std::shared_ptr;

shared_ptr<ListNode<int>> RemoveDuplicates(const shared_ptr<ListNode<int>>& L) 
{
    
    auto dummy_head = make_shared<ListNode<int>>();
    dummy_head->next = L;

    auto iter = dummy_head->next;
    while (iter)
    {
        if (iter->next)
        {
            if (iter->data == iter->next->data)
            {
                iter->next = iter->next->next;
                //add Continue for this case and do not advance
                continue;
            }
        }
        
        //Advance in all other cases
        iter = iter->next;
    }


    return dummy_head->next;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L"};
  return GenericTestMain(args, "remove_duplicates_from_sorted_list.cc",
                         "remove_duplicates_from_sorted_list.tsv",
                         &RemoveDuplicates, DefaultComparator{}, param_names);
}
