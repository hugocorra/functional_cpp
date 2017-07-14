#include <fplus/fplus.hpp>

double str_to_double(const std::string& str)
{
    double result;
    std::istringstream(str) >> result;
    return result;
}

int main()
{
    const std::string input = "1.1,5,4,7,2,2,3";
    const auto parts = fplus::split(',', false, input);

    const auto nums =
        fplus::transform(str_to_double, parts);

    const auto result =
        fplus::reduce(std::plus<double>(), 0.0, nums);


    std::cout << result << std::endl;
}

// Exercise:
//
//     Modify the code,
//     so that the numbers are not multiplied but added.
//
//     Additionally change it
//     so that is works with floating point numbers too.
//     For this you should parse doubles instead of ints.
