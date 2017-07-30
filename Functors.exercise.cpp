#include <type_traits>
#include <fplus/fplus.hpp>

// Exercise:
//     write lift_dict as a function template on your own
//     and test it with the following code.

// lift_dict : ((a -> b), Map key a) -> Map key b

template <typename TOutputValue, typename TFunc, typename TInputKey, typename TInputValue>
auto lift_dict(TFunc f, std::map<TInputKey, TInputValue>& m)
{   
    std::map<TInputKey, TOutputValue> r;
    std::for_each(m.begin(), m.end(), [&r, &f](const std::pair<TInputKey, TInputValue>& p) { r[p.first] = f(p.second); });
    return r;
}


int main()
{
    using namespace fplus;
    std::map<int, double> dict =
        {{2, 1.41}, {3, 1.73}, {4, 2.0}};
    auto dict_squared = lift_dict<double>(square<double>, dict);
    auto dict_shown = lift_dict<std::string>(show<double>, dict);
    std::cout << show_cont(dict_squared) << std::endl;
    std::cout << show_cont(dict_shown) << std::endl;
}
