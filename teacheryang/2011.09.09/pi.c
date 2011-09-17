#include <stdio.h>
#include <math.h>

int main(int argc, char **argv)
{
  int n = 10000;
  int i;

  double step;
  double x, y;

  // x^2 + y^2 = r^2
  // double sqrt(double x);
  // y = sqrt(r^2 - x^2)

  step = 1.0f / n / 2.0f;

  double total = 0;

  for (i = 0; i < n; i++)
  {
    //x = (double) i / (double) n;
    x = 1.0f / n * i + step;
    y = sqrt(1 - x * x);

    fprintf(stdout, "x = %f, y = %f\n", x, y);

    total += 1.0f / n * y;
  }

  fprintf(stdout, "total = %f\n", total);
  fprintf(stdout, "pi = %.15f\n", total * 4);

  return 0;
}
