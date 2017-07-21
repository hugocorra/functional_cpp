#include <fplus/fplus.hpp>

typedef std::pair<float, float> point;

float point_distance(const point& p1, const point& p2)
{
    const float dx = p2.first - p1.first;
    const float dy = p2.second - p1.second;
    return std::sqrt(dx * dx + dy * dy);
}

int main()
{
    using namespace std;

    vector<point> polygon =
        { {1,2}, {7,3}, {6,5}, {4,4}, {2,9} };

    const auto edges =
        fplus::overlapping_pairs_cyclic(polygon);

    const auto result =
        fplus::maximum_on([](std::pair<point, point>& ppoint) 
			    {
					return point_distance(ppoint.first, ppoint.second);

			    },
				edges);

    cout << fplus::show(result) << endl;
}

// Exercise:
//     Change the call to maximum_on
//     by using a lambda function
//     using point_distance internally,
//     so the code compiles and runs as intended.
