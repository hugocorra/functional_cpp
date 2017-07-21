#include <fplus/fplus.hpp>

struct user
{
    std::string name;
    std::string country;
    std::size_t visits;
};

std::string get_country(const user& u)
{
    return u.country;
}

std::size_t get_visits(const user& u)
{
    return u.visits;
}

int main()
{
    using namespace std::placeholders;

    const std::vector<user> users = {
        {"Nicole", "GER", 2},
        {"Justin", "USA", 1},
        {"Rachel", "USA", 5},
        {"Robert", "USA", 6},
        {"Stefan", "GER", 4}
    };
    
    // n^2 version and breaking in pieces.
    auto r = fplus::group_globally_on_labeled(get_country, users);
    auto x = fplus::transform(fplus::fwd::transform_snd(fplus::fwd::transform(get_visits)), r);
    auto y = fplus::transform(fplus::fwd::transform_snd(fplus::fwd::sum()), x);

    std::cout << "x = " << fplus::show(x) << std::endl;
    std::cout << "y = " << fplus::show(y) << std::endl;
 
    // loop version.
    for (auto i : r)
    {
        std::cout << i.first << std::endl;
        for (const auto j : i.second)
            std::cout << "\t" << j.name << ", " << j.visits << std::endl;


        auto s = fplus::transform(get_visits, i.second);
        auto rs = fplus::sum(s);

        std::cout << "\ttotal = " << rs << std::endl;
    }
    
    // using n * long(n) version. 
    auto result_n_log_n = fplus::fwd::apply(users,
        fplus::fwd::sort_on(get_country),
        fplus::fwd::group_on_labeled(get_country),
        fplus::fwd::transform(fplus::fwd::transform_snd(fplus::fwd::transform(get_visits))),
        fplus::fwd::transform(fplus::fwd::transform_snd(fplus::fwd::sum()))
    );

    std::cout << fplus::show_cont(result_n_log_n) << std::endl;

    // SELECT country, SUM(visits)
    //     FROM users
    //     GROUP BY country;
}

// Exercise:
//     Implement the task solved by the SQL query above
//     in C++ using the following fplus functions:
//     - group_globally_on_labeled
//     - transform_snd
//     - mean
//     Look them up in the API search,
//     and understand the type signatures.

// Bonus Exercise:
//     The run-time complexity of your algorithm will be O(n^2),
//     due to using group_globally_on_labeled.
//     But Strings form a partially ordered set.
//     See if you can get down to O(n*log(n))
//     by using sort and group_on_labeled.
