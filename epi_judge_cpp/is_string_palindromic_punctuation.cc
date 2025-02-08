#include <string>

#include "test_framework/generic_test.h"
using std::string;
bool IsPalindrome(const string& s) {
    // TODO - you fill in here.

    int processedEnd = -1;


    auto s2 = std::accumulate(begin(s), end(s), string(""), [](string a, char c)
    {
        if (isalnum(c))
        {
            a.push_back(std::tolower(c));
            return a;
        }
        else
            return a;
    });

    return std::equal(begin(s2), end(s2), rbegin(s2));
}
    
int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "is_string_palindromic_punctuation.cc",
                         "is_string_palindromic_punctuation.tsv", &IsPalindrome,
                         DefaultComparator{}, param_names);
}
