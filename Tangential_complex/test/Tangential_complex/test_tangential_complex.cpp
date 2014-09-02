#include <CGAL/Epick_d.h>
#include <CGAL/Tangential_complex.h>
#include <CGAL/point_generators_3.h>

int main()
{
  typedef CGAL::Epick_d<CGAL::Dimension_tag<3> >  Kernel;
  typedef Kernel::Point_d                         Point;
  const int INTRINSIC_DIMENSION = 2;

  CGAL::Random_points_on_sphere_3<Point> generator(3.0);
  std::vector<Point> points;
  points.reserve(50);
  for (int i = 0; i != 50; ++i)
    points.push_back(*generator++);

  CGAL::Tangential_complex<Kernel, INTRINSIC_DIMENSION> tc(
                                                 points.begin(), points.end());
  tc.compute_tangential_complex();

  return 0;
}