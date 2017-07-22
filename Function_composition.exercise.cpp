#include <fplus/fplus.hpp>

double str_to_double(const std::string& str)
{
    double result;
    std::istringstream(str) >> result;
    return result;
}

int main()
{
    const std::string input = "1,5,4,7,2,2,3.34";

    const auto result = fplus::fwd::apply(input
        , fplus::fwd::split(',', false)
        , fplus::fwd::transform(str_to_double)
        , fplus::fwd::product()
    );

    std::cout << result << std::endl;
}

// Exercise:
//     Express the solution to the previous
//     parse-and-product challange
//     with function composition
//     instead of forward application.