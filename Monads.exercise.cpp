#include <fplus/fplus.hpp>

using namespace fplus;
using namespace std;

typedef vector<int> Ints;
typedef vector<string> Strings;

result<string, string> get_input_filepath(const Strings& args)
{
    assert(args.size() > 0);
    if (args.size() != 2)
        return error<string, string>("Usage: " + args[0] + " FILEPATH");
    else
        return ok<string, string>(args[1]);
}

result<string, string> read_file(const string& filepath)
{
    const auto maybe_content = read_text_file_maybe(filepath)();
    const auto trimmed = lift_maybe(trim_whitespace<string>, maybe_content);
    return from_maybe(string("Unable to open ") + filepath, trimmed);
}

result<Ints, string> parse_content(const string& content)
{
    const auto maybe_values = fwd::apply(content
        , fwd::split(',', false)
        , fwd::transform(read_value<int>));

    if (all_by(is_just<int>, maybe_values))
        return ok<Ints, string>(justs(maybe_values));
    else
        return error<Ints, string>("Can not parse file.");
}

result<int, string> calc_median(const vector<int>& xs)
{
    if (is_not_empty(xs))
        return ok<int, string>(median(xs));
    return error<int, string>("Need at least one value.");
}

string show_median(int value)
{
    return "The median is " + show(value);
}

string show_error(const string& error)
{
    return "ERROR: " + error;
}

// Exercise:
//     Let's rewrite our command line tool
//     using Result instead of Maybe,
//     so it provides meaningful error messages
//     to the user in case of failure.
//     Implement the and_then part of the result
//     monad on your own.
template <typename Res, typename Error, typename F, typename A>
result<Res, Error> my_and_then_result(F f, const result<A, Error>& r)
{
    if (is_ok(r))
        return f(unsafe_get_ok(r));
    else
        return error<Res, Error>(r.unsafe_get_error());


}

int main(int argc, char* argv[])
{
    const Strings arguments(argv, argv + argc);

    const string error_msg = "An error occured.";
    const auto input_filepath = get_input_filepath(arguments);
    const auto file_content = my_and_then_result<string>(read_file, input_filepath);
    const auto values = my_and_then_result<Ints>(parse_content, file_content);
    const auto res = my_and_then_result<int>(calc_median, values);

    const auto output = unify_result(show_median, show_error, res);
    cout << output << endl;
}
