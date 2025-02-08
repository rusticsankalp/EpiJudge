#include <string>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::string;

void ReverseWords(string* s) {


   /* std::stringstream tokenStream(*s);

    string token;

    std::vector<string> tokens;
    while (tokenStream>> token)
    {
        tokens.push_back(token);
    }*/

    string input = *s;
    std::vector<string> tokens;
    string token{};
    bool  stateflag = std::isalnum(input[0]) > 0;
    for (int i = 0; i < s->size(); i++)
    {
        bool alflag = std::isalnum(input[i]) > 0;
        if (stateflag == alflag)
        {
            token.push_back(input[i]);
            continue;
        }

        tokens.push_back(token);
        token.clear();
        token.push_back(input[i]);
        stateflag = alflag;
    }

    tokens.push_back(token);
       

    std::reverse(begin(tokens), end(tokens));

    string res = accumulate(begin(tokens)+1, end(tokens), tokens[0], [](std::string s, std::string v)
    { 
        s = s+ v;
        return s; 
    });


    *s = res;

  // TODO - you fill in here.
  return;
}
string ReverseWordsWrapper(TimedExecutor& executor, string s) {
  string s_copy = s;

  executor.Run([&] { ReverseWords(&s_copy); });

  return s_copy;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "s"};
  return GenericTestMain(args, "reverse_words.cc", "reverse_words.tsv",
                         &ReverseWordsWrapper, DefaultComparator{},
                         param_names);
}
