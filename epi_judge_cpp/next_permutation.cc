#include <vector>
#include <algorithm>

//using namespace std;

#include "test_framework/generic_test.h"
using std::vector;
vector<int> NextPermutation(vector<int> perm) {
	auto inversion_point = is_sorted_until(rbegin(perm), rend(perm));
	if (inversion_point == rend(perm))
	{
		return {};
	}

	auto replacement_candidate = upper_bound(rbegin(perm), inversion_point, *inversion_point);

	iter_swap(inversion_point, replacement_candidate);

	reverse(rbegin(perm), inversion_point);

	return perm;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"perm"};
  return GenericTestMain(args, "next_permutation.cc", "next_permutation.tsv",
                         &NextPermutation, DefaultComparator{}, param_names);
}
