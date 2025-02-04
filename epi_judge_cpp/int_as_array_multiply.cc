#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
//
//void multiplyNumsToDigit(vector<int>& nums, int digit)
//{
//    auto i = nums.size() - 1;
//    nums[i] *= digit;
//    auto carry = 0;
//    for (int i = 0; i > 0; i++)
//    {
//        if (nums[i] > 9)
//        {
//            carry = nums[i] / 10;
//            nums[i] %= 10;
//        }
//        else
//        {
//            carry = 0;
//        }
//        nums[i - 1] = nums[i - 1] * digit + carry;
//    }
//    
//    if (nums[0] > 9)
//    {
//        
//        nums[0] = 
//    }
//    
//}

void mulMSDArrayWithDigit(vector<int> rNums, int digit)
{
    rNums[0] *= digit;
    int carry = rNums[0] / 10;
    rNums[0] = rNums[0] % 10;


    for (int i = 1; i < rNums.size(); i++)
    {
        rNums[i] = rNums[i] * digit * + carry;
        carry = rNums[i] / 10;
        rNums[i] = rNums[i] % 10;
    }

    if (carry > 0)
    {
        rNums.push_back(carry);
    }
}
vector<int> Multiply(vector<int> num1, vector<int> num2) {
  // TODO - you fill in here.
  return {};
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num1", "num2"};
  return GenericTestMain(args, "int_as_array_multiply.cc",
                         "int_as_array_multiply.tsv", &Multiply,
                         DefaultComparator{}, param_names);
}
