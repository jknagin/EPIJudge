#include "test_framework/generic_test.h"

double square(double x) { return x * x; }

int compare(const double& a, const double& b)
{
  double diff = (a - b) / std::max(std::abs(a), std::abs(b)); // normalized difference
  if (diff < -std::numeric_limits<double>::epsilon()) return -1;
  if (diff > std::numeric_limits<double>::epsilon()) return 1;
  return 0;
}

double SquareRoot(double x) {
  // sqrt(x) > x for x in (0, 1), so lower and upper bounds are computed differently in this case
  double left = x < 1 ? 0 : 1;
  double right = x < 1 ? 1 : x;

  while(compare(left, right) == -1)
  {
    double mid = (right - left) / 2 + left;
    double sqmid = square(mid);
    int cmp = compare(sqmid, x);
    switch (cmp)
    {
    case 0:
      return mid;
      break;
    case 1:
      right = mid;
      break;
    case -1:
      left = mid;
      break; 
    default:
      break;
    }
  }

  // left >= right, so return either left or right
  return right;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "real_square_root.cc", "real_square_root.tsv",
                         &SquareRoot, DefaultComparator{}, param_names);
}
