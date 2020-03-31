#include <bits/stdc++.h>

namespace ggeometry{
    ////////////////////////////////////////////////////////////////////////////
    // Forward declaration of structs and classes                             //
    ////////////////////////////////////////////////////////////////////////////

    template <typename CoordType>
    struct Point;

    ////////////////////////////////////////////////////////////////////////////
    // Constants                                                              //
    ////////////////////////////////////////////////////////////////////////////

    template <typename NumericT>
    const NumericT INF = 1e18;

    ////////////////////////////////////////////////////////////////////////////
    // Point                                                                  //
    ////////////////////////////////////////////////////////////////////////////

    //Point class
    template <typename CoordType>
    struct Point{
        CoordType x;
        CoordType y;
    };
    

    // Get distance between points
    // CoordType is got automatically from context (Point)
    template <typename DistanceType, typename CoordType>
    DistanceType Distance(Point<CoordType> p1, Point<CoordType> p2) {
        auto dx = p2.x - p1.x;
        auto dy = p2.y - p1.y;
        return powl(dx * dx + dy * dy, 0.5);  
    };

    // Output to std::ostream
    template <typename CoordType>
    std::ostream& operator<<(std::ostream& os,
                             const Point<CoordType>& point_to_show) {
      return os << point_to_show.x << ' ' << point_to_show.y;
    }

    // Input from std::istream
    template <typename CoordType>
    std::istream& operator >> (std::istream& is,
                               Point<CoordType>& point_to_get) {
        return is >> point_to_get.x >> point_to_get.y;
    }
}

////////////////////////////////////////////////////////////////////////////////
// Solution                                                                   //
////////////////////////////////////////////////////////////////////////////////

using namespace ggeometry;
using namespace std;

bool x_comp(const Point<long double>& p1, const Point<long double>& p2) {
  return p1.x < p2.x;
};


bool y_comp(const Point<long double>& p1, const Point<long double>& p2) {
  return p1.y < p2.y;
};

long double get_new_h(const vector<Point<long double>>& half_edge1,
                 const vector<Point<long double>>& half_edge2,
                 long double h) {
  long double new_h = h;
  size_t j = 0;
  for (size_t i = 0; i < half_edge1.size(); ++i) {
    for (;
         j < half_edge2.size() &&
         half_edge2[j].y < half_edge1[i].y - h;
         ++j) {}
    for (size_t k = j;
         k < half_edge2.size() &&
         half_edge2[k].y <= half_edge1[i].y + h;
         ++k) {
      new_h = min(new_h,
                  Distance<long double>(half_edge1[i], half_edge2[k]));
    }
  }
  return new_h;
}

long double solution_(vector<Point<long double>>& points) {
  size_t n = points.size();
  vector<Point<long double>> first_half(points.begin(), points.begin() + n / 2);
  vector<Point<long double>> second_half(points.begin() + n / 2, points.end());
  if (first_half.size() + second_half.size() <= 1) {
    return INF<long double>;
  }

  long double h1 = solution_(first_half);
  long double h2 = solution_(second_half);
  long double h = min(h1, h2);
  long double border;
  if (!first_half.empty()) {
    border = first_half.rbegin()->x;
  } 
  else {
    border = second_half.begin()->x;
  }

  vector<Point<long double>> first_half_edge;
  vector<Point<long double>> second_half_edge;
  for (size_t i = 0; i < n / 2; ++i) {
    if (first_half[i].x > border - h) {
      first_half_edge.push_back(first_half[i]);
    }
  }
  for (size_t i = 0; i < second_half.size(); ++i) {
    if (second_half[i].x < border + h) {
      second_half_edge.push_back(second_half[i]);
    }
  }
  auto new_h = min(h, get_new_h(first_half_edge, second_half_edge, h));
  
  points.clear();
  merge(first_half.begin(), first_half.end(),
        second_half.begin(), second_half.end(),
        back_inserter(points), y_comp);
  return new_h;
}


void solution() {
  int n;
  cin >> n;
  vector<Point<long double>> points(n);
  for (int i = 0; i < n; ++i) {
    cin >> points[i];
  }
  sort(points.begin(), points.end(), x_comp);
  long double answer = solution_(points);
  cout << setprecision(12) << fixed << powl(answer, 2);
}


int main() {
  solution();
  return 0;
}
