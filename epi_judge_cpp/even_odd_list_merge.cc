#include "list_node.h"
#include "test_framework/generic_test.h"
shared_ptr<ListNode<int>> EvenOddMerge(const shared_ptr<ListNode<int>>& L) 
{
    shared_ptr<ListNode<int>> odd_dummy_head(new ListNode<int>), even_dummy_head(new ListNode<int>);
    shared_ptr<ListNode<int>> odd_tail{ odd_dummy_head }, even_tail{ even_dummy_head };

    auto iter = L;

    //:this is even odd positions and not even odd numbers
    bool turn = false;
    while (iter)
    {
        auto next = iter->next;
        if (turn)
        {
            odd_tail->next = iter;
            odd_tail = iter;
            //not setting the end to be null here but at the end
        }
        else
        {
            even_tail->next = iter;
            even_tail = iter;
            //not setting the end to be null here but at the end
        }

        turn = !turn;
        iter = next;
    }


    odd_tail->next = nullptr;
    even_tail->next = odd_dummy_head->next;
  
  return even_dummy_head->next;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L"};
  return GenericTestMain(args, "even_odd_list_merge.cc",
                         "even_odd_list_merge.tsv", &EvenOddMerge,
                         DefaultComparator{}, param_names);
}
