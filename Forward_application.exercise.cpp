#include <fplus/fplus.hpp>

typedef std::pair<float, float> point;
typedef std::pair<point, point> edge;
typedef std::vector<point> points;

float point_distance(const point& p1, const point& p2)
{
    const float dx = p2.first - p1.first;
    const float dy = p2.second - p1.second;
    return std::sqrt(dx * dx + dy * dy);
}

float edge_length(const edge& e)
{
    return point_distance(e.first, e.second);
}

std::vector<edge> get_edges(const points& polygon)
{
    return fplus::overlapping_pairs_cyclic(polygon);
}

int main()
{
    using namespace std;
    using namespace fplus;

    vector<point> polygon =
        { {1,2}, {7,3}, {6,5}, {4,4}, {2,9} };

    const auto result = fwd::apply(polygon, 
        get_edges,
        fwd::maximum_on(edge_length));

    
    //    edge_length,
      //  maximum_on);


    /*
     fplus::maximum_on(
        edge_length,
        get_edges(polygon)); */

    cout << fplus::show(result) << endl;
}

// Exercise 1:
//     Rewrite the the longest-edge code
//     in forward-application style.

// Exercise 2:
//     Invent a quite long chain of function applications,
//     at least 5 functions,
//     and implement its application to an input value
//     in all three styles:
//         1) Assign intermediate values to variables.
//         2) Nested function calls
//         3) Foward-application style
//     Compare all three versions and contemplate
//     the readability of all of them.
