#include <vector>
#include <numeric>

#include "test_framework/generic_test.h"
using std::vector;
// Given n, return all primes up to and including n.
vector<int> GeneratePrimesp1(int n) {
    vector<bool> prime_candidates(n+1,true);

    for (int i = 2; i <= n; i++)
    {

        if (prime_candidates[i] == false)
            continue;
        //start from twice , jump by i's 
        for (int j = i *2; j <= n; j+=i)
        {
            if ((j % i) == 0)
                prime_candidates[j] = false;
        }
    }

    vector<int> primes;
    for (int i = 2; i <= n; i++)
    {
        if (prime_candidates[i])
            primes.push_back(i);
    }
  
    return primes;
}


struct PrimeValue {

public:
    int num;
    bool isPrime;

    PrimeValue(int v)
    {
        PrimeValue(v, true);
    }
    PrimeValue(int v, bool prime = true) : num{ v }, isPrime{ prime }
    {

    }
};


vector<int> GeneratePrimes(int n) {
    vector<PrimeValue> prime_candidates{};
    std::iota(begin(prime_candidates), begin(prime_candidates) + n + 1, 0);

    std::for_each(begin(prime_candidates) + 2, end(prime_candidates),
        [](PrimeValue &primeValue) 
        {




        });

    return {};
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "prime_sieve.cc", "prime_sieve.tsv",
                         &GeneratePrimes, DefaultComparator{}, param_names);
}
