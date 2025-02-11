#include "list_node.h"
#include "test_framework/generic_test.h"

bool IsLinkedListAPalindrome(shared_ptr<ListNode<int>> L) {
  // TODO - you fill in here.

    auto iterator = L;

    int length{ 0 };
    while (iterator != nullptr)
    {
        length++;
        iterator = iterator->next;
    }

    if (length <= 1) return true;

    auto range = length / 2;

    iterator = L;
    shared_ptr<ListNode<int>> first_dummy_head(new ListNode<int>());
    for (int i = 0; i < range; i++)
    {
        auto next = iterator->next;
        iterator->next = first_dummy_head->next;
        first_dummy_head->next = iterator;

        iterator = next;
    }

    if (length % 2 != 0)
    {
        iterator = iterator->next;
    }

    auto last_iter = first_dummy_head->next;

    for (int i = 0; i < range; i++)
    {
        if (iterator->data != last_iter->data)
            return false;
        
        iterator = iterator->next;
        last_iter = last_iter->next;
    }

  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L"};
  return GenericTestMain(args, "is_list_palindromic.cc",
                         "is_list_palindromic.tsv", &IsLinkedListAPalindrome,
                         DefaultComparator{}, param_names);
}
