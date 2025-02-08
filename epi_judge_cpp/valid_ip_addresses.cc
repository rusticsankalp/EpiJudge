#include <algorithm>
#include <string>
#include <vector>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;


//19216811
//100123454


bool IsValid(const string& s)
{
    //
    //check if it is min size ??
    if (s.size() <= 0 || s.size() >4)
        return false;

    //check if it starts with 0 ?
    if (s.starts_with('0') && s.size() > 1)
        return false;

    //check if the integer conversion meets validity requirements
    auto part = stoi(s);

    if (part < 0 || part > 255)
        return false;

    return true;
}

/// <summary>
/// Stoi does not convert numbers largter than int range 
/// substr takes start and the size 
/// In this problem use sizes of max 4 in the loops
/// <Look again later>
/// </summary>
/// <param name="s"></param>
/// <returns></returns>
vector<string> GetValidIpAddress(const string& s) {

    vector<string> result{};
    for (int i = 1; i < 4 && i < size(s); i++)
    {
        auto first = s.substr(0, i);
        //std::cout << "\nfirst:"<<first;
        if (!IsValid(first)) 
            continue;

        for (int j = i+1; j < (4+i) && j< size(s) ; j++)
        {
            auto second = s.substr(i,j-i);
            //std::cout << " second:" << second;
            if (!IsValid(second))
                continue;

            for (int k = j+1; k < (4+j) && k < size(s); k++)
            {
                auto third = s.substr(j, k-j);
                //std::cout <<" third:" <<  third;

                auto fourth = s.substr(k);
                //std::cout <<" fourth:" << fourth;

                if (!IsValid(third) || !IsValid(fourth))
                    continue;

                //std::cout << "\n Result:" << first + "." + second + "." + third + "." + fourth;

                result.push_back(first + "." + second + "." + third + "." + fourth);
            }
        }
    }
  
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "valid_ip_addresses.cc",
                         "valid_ip_addresses.tsv", &GetValidIpAddress,
                         UnorderedComparator{}, param_names);
}
