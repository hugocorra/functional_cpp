#include <cassert>
#include <algorithm>
#include <vector>
#include <iterator>
#include <iostream>

bool is_even(int x)
{
    return x % 2 == 0;
}

template <typename U, typename F>
U keep_if(F& f, U& input)
{
	U result;
	std::copy_if(input.begin(), input.end(), std::back_inserter(result), f);

	return result;	
}


// Exercise:
// Implement keep_if on your own
// so it can be used like this:

int main()
{
    std::vector<int> xs = {0,1,2,3,4};
    const auto ys = keep_if(is_even, xs);
    assert(ys == std::vector<int>({0,2,4}));
}

// Then run some tests with it.

// Bonus:
// See if you can make it work
// for different container types
// (e.g. std::list and std::vector).
