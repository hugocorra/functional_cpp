#include <algorithm>
#include <functional>
#include <iostream>
#include <cmath>
#include <fplus/fplus.hpp>

std::vector<int> powerseq(const std::vector<int>& v)
{
    using namespace std::placeholders;
    
    std::vector<int> r;
    auto pow2 = std::bind(static_cast<double (*)(int, int)>(std::pow), _1, 2);
	std::transform(v.begin(), v.end(), std::back_inserter(r), pow2);
	return r;
}

template <int level>
auto add_four_curried_mpl_impl(int a, int b)
{
    using namespace std::placeholders;
    return std::bind(add_four_curried_mpl_impl<level - 1>, _1, a+b);
}

template <>
auto add_four_curried_mpl_impl<1>(int a, int b)
{
    return a + b;
}

template <int level = 4>
auto add_four_curried_mpl(int a)
{
    using namespace std::placeholders;
    return std::bind(add_four_curried_mpl_impl<level - 1>, a, _1);
}

int main()
{
    auto add_four_curried = [](int a) { return [a](int b) { return [a, b](int c) { return [a,b,c](int d) { return a+b+c+d; }; }; }; };

    std::vector<std::vector<int>> xss =
        {{0,1,2}, {3,4,5}};

	std::vector<std::vector<int>> r;

	std::transform(xss.begin(), xss.end(), std::back_inserter(r), powerseq);
	std::cout << fplus::show(r) << std::endl;

    std::cout << add_four_curried(1)(2)(3)(4) << std::endl;
    std::cout << add_four_curried_mpl(1)(2)(3)(4) << std::endl;

    return 0; 
}

// Exercise 1:
//     Square every inner value of xss, so
//     {{0,1,2}, {3,4,5}}
//     turns into
//     {{0,1,4}, {9,16,25}}
//     Try out different possibilities to achieve your goal.

// Exercise 2:
//     Use nested lambda expressions
//     to make a fully curried version of add_four.
//     add_four (Int, Int, Int, Int) -> Int
//     add_four_curried : Int -> Int -> Int -> Int -> Int
//     so that
//     add_four(1,2,3,4)
//     means the same as
//     add_four_curried(1)(2)(3)(4)
