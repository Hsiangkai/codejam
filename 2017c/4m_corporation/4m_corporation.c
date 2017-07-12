#include <stdio.h>

static int process(int min, int max, int mean, int median)
{
  if (min > max)
    return -1;

  if (min == max) {
    if ((mean != min) || (median != min))
      return -1;

    return 1;
  }

  return 0;
}

int main()
{
  int case_n;
  int i;
  int min, max;
  int mean, median;
  int department_n;

  scanf ("%d\n", &case_n);
  for (i = 0; i < case_n; i++) {
    scanf ("%d %d %d %d\n", &min, &max, &mean, &median);
    printf ("Case #%d: ", i+1);
    department_n = process (min, max, mean, median);
    if (department_n == -1)
      printf ("IMPOSSIBLE\n");
    else
      printf ("%d\n", department_n);
  }

  return 0;
}
