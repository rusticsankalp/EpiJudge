#include <array>
#include <stack>
#include <string>
#include <vector>
#include <iostream>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::array;
using std::stack;
using std::vector;
const int kNumPegs = 3;


void computeTransfers(int num_rings, vector<stack<int>> &pegs, int from, int to, int use, vector<vector<int>>& result)
{
    if (num_rings <= 0)
        return;

    computeTransfers(num_rings - 1, pegs, from, use, to, result);

    pegs[to].push(pegs[from].top());
    pegs[from].pop();
    
    result.push_back(vector<int>{from, to});
    

    computeTransfers(num_rings - 1, pegs, use, to, from, result);
}

void computeTransfersIterative(int num_rings, vector<stack<int>>& pegs, int from, int to, int use, vector<vector<int>>& result)
{
    if (num_rings <= 0)
        return;

    computeTransfers(num_rings - 1, pegs, from, use, to, result);

    pegs[to].push(pegs[from].top());
    pegs[from].pop();

    result.push_back(vector<int>{from, to});


    computeTransfers(num_rings - 1, pegs, use, to, from, result);
}


vector<vector<int>> ComputeTowerHanoi(int num_rings) {

    vector<stack<int>> pegStack(3, stack<int>{});
    vector<vector<int>> result{};

    for (int i = num_rings; i > 0; i--)
    {
        pegStack[0].push(i);
    }

    computeTransfers(num_rings, pegStack, 0, 1, 2 , result);

    std::cout << std::endl;
    
  // TODO - you fill in here.
  return result;
}
void ComputeTowerHanoiWrapper(TimedExecutor& executor, int num_rings) {
  array<stack<int>, kNumPegs> pegs;
  for (int i = num_rings; i >= 1; --i) {
    pegs[0].push(i);
  }

  vector<vector<int>> result =
      executor.Run([&] { return ComputeTowerHanoi(num_rings); });

  for (const vector<int>& operation : result) {
    int from_peg = operation[0], to_peg = operation[1];
    if (!pegs[to_peg].empty() && pegs[from_peg].top() >= pegs[to_peg].top()) {
      throw TestFailure("Illegal move from " +
                        std::to_string(pegs[from_peg].top()) + " to " +
                        std::to_string(pegs[to_peg].top()));
    }
    pegs[to_peg].push(pegs[from_peg].top());
    pegs[from_peg].pop();
  }
  array<stack<int>, kNumPegs> expected_pegs1, expected_pegs2;
  for (int i = num_rings; i >= 1; --i) {
    expected_pegs1[1].push(i);
  }
  for (int i = num_rings; i >= 1; --i) {
    expected_pegs2[2].push(i);
  }
  if (pegs != expected_pegs1 && pegs != expected_pegs2) {
    throw TestFailure("Pegs doesn't place in the right configuration");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "num_rings"};
  return GenericTestMain(args, "hanoi.cc", "hanoi.tsv",
                         &ComputeTowerHanoiWrapper, DefaultComparator{},
                         param_names);
}
