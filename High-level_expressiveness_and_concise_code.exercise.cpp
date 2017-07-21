#include <fplus/fplus.hpp>

typedef std::pair<float, float> point;

float point_distance(const point& p1, const point& p2)
{
    const float dx = p2.first - p1.first;
    const float dy = p2.second - p1.second;
    return std::sqrt(dx * dx + dy * dy);
}


template <typename T>
auto get_edges(const T& polygon)
{
	return 
	        fplus::overlapping_pairs_cyclic(polygon);
}


auto edge_length(const std::pair<point, point>& edges)
{
	return point_distance(edges.first, edges.second);
}


int main()
{
    using namespace std;

    vector<point> polygon =
        { {1,2}, {7,3}, {6,5}, {4,4}, {2,9} };

    const auto result = fplus::maximum_on(
        edge_length,
        get_edges(polygon));

    std::vector<float> r;
    auto edges = get_edges(polygon);
    std::transform(edges.begin(), edges.end(), std::back_inserter(r),  edge_length);

   cout << fplus::show(r) << std::endl;

    cout << fplus::show(get_edges(polygon)) << std::endl;

    cout << fplus::show(result) << endl;
}

// Exercise:
//     Implement edge_length and get_edges
//     so the improved code from above works.
