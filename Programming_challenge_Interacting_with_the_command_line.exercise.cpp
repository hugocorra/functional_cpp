#include <fplus/fplus.hpp>
#include <iostream>

// cmd_line_interact : (String -> String) -> ()

template <typename T>
void cmd_line_interact(T fn)
{
    std::string input(
        std::istreambuf_iterator<char>(std::cin.rdbuf()),
        std::istreambuf_iterator<char>());

    std::string output(fn(input));
    std::cout << output << std::endl;
}

int main()
{
    using namespace fplus;
    //cmd_line_interact(fwd::to_upper_case());

    cmd_line_interact(
        fplus::fwd::compose(
            fplus::fwd::split_lines(false),
            fplus::fwd::sort(),
            fplus::fwd::join(std::string("\n"))));

}

// Exercises:
//     1) Implement the function cmd_line_interact
//     so that it can be used as shown above
//     for the shout program.

//     2) Modify sort_lines in the same way.
//     Use your knowledge about function composition
//     from the previous lecture to express
//     the processing chain in point-free notation.
