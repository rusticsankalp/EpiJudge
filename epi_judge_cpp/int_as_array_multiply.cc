#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

vector<int> AddMSD(vector<int> addend1, vector<int>addend2)
{
    vector<int>sum;

    int len = addend1.size() > addend2.size() ? addend1.size() : addend2.size();

    int carry = 0;
    for (int i = 0; i < len; i++)
    {
        int dSum = carry;
        if (i < addend1.size())
            dSum += addend1[i];

        if (i < addend2.size())
            dSum += addend2[i];

        sum.push_back(dSum % 10);
        carry = dSum / 10;

    }

    if (carry > 0)
        sum.push_back(carry);

    return sum;
}

vector<int> MulitplyMSDWithDigit(int digit, vector<int> multiplier)
{

    vector<int> product;

    int carry = 0;
    for (int i = 0; i < multiplier.size(); i++)
    {
        int dProd = digit * multiplier[i] + carry;

        product.push_back(dProd % 10);
        carry = dProd / 10;
    }

    if (carry > 0)
    {
        product.push_back(carry);
    }

    return product;
}


vector<int> MulitplyMSD(vector<int> multiplicand, vector<int> multiplier)
{
    vector<int> prod = { 0 }, dProd = multiplicand;

    for (int i = 0; i < multiplier.size(); i++)
    {
        auto t1prod = MulitplyMSDWithDigit(multiplier[i], multiplicand);
        prod = AddMSD(t1prod, prod);
        multiplicand.insert(multiplicand.begin(), 0); //Append 0 at the beginning
    }

    return prod;
}

vector<int> Multiply(vector<int> nums1, vector<int> nums2) {
  
    int sign = (nums1[0] * nums2[0]) < 0 ? -1 : 1;
    nums1[0] = abs(nums1[0]);
    nums2[0] = abs(nums2[0]);

    vector<int> multiplier = nums1;
    reverse(multiplier.begin(), multiplier.end());

    vector<int> muliplicand = nums2;
    reverse(muliplicand.begin(), muliplicand.end());

    auto prod = MulitplyMSD(muliplicand, multiplier);
    
    //remove leading zeroes .. in this case trailing)
    for (int i = prod.size() - 1; i > 0; i--)
    {
        if(prod[i] != 0) break;

        prod.pop_back();
    }

    reverse(prod.begin(), prod.end());

    prod[0] = prod[0] * sign;
    return prod;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num1", "num2"};
  return GenericTestMain(args, "int_as_array_multiply.cc",
                         "int_as_array_multiply.tsv", &Multiply,
                         DefaultComparator{}, param_names);
}
