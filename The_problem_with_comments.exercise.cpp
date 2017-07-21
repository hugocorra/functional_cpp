#include <algorithm>
#include <fplus/fplus.hpp>

int str_to_int(const std::string& str)
{
    int result;
    std::istringstream(str) >> result;
    return result;
}

template <typename T>
typename T::value_type product(const T& container)
{
	return fplus::reduce(std::multiplies<typename T::value_type>(), typename T::value_type(1), container);
}

template <typename T>
typename T::value_type sum(const T& container)
{
	return fplus::reduce(std::plus<typename T::value_type>(), typename T::value_type(0), container);
}

int main()
{
    const std::string input = "1,5,4,7,2,2,3";
    const auto parts = fplus::split(',', false, input);
    const auto nums = fplus::transform(str_to_int, parts);
    const auto result_product = product(nums);
    const auto result_sum = sum(nums);
    std::cout << "product result = " << result_product << std::endl;
    std::cout << "sum result = " << result_sum << std::endl;
}

// Exercise:
//     Implement the functions product and sum.
// Bonus:
//     Make them function templates
//     to work with different types of values.
