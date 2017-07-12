#include <stdio.h>

static int reduce_sum(int sum, int num, int min, int mean, int median)
{
  if (min + median >= 2 * mean)
    return -1;

  while (sum > num * mean) {
    sum += min; 
    sum += median;
    num += 2;
  }

  return num;
}

static int increase_sum(int sum, int num, int max, int mean, int median)
{
  if (max + median <= 2 * mean)
    return -1;

  while (sum < num * mean) {
    sum += max;
    sum += median;
    num += 2;
  }

  return num;
}

static int least_odd_department(int min, int max, int mean, int median)
{
  int sum = min + max + median;
  int i = 3;

  if (sum > i * mean) {
    return reduce_sum (sum, i, min, mean, median);
  } else {
    return increase_sum (sum, i, max, mean, median);
  }
}

static int least_even_department(int min, int max, int mean, int median)
{
  int sum = min + max + median + median;
  int i = 4;

  if (sum > i * mean) {
    return reduce_sum (sum, i, min, mean, median);
  } else {
    return increase_sum (sum, i, max, mean, median);
  }
}

static int process(int min, int max, int mean, int median)
{
  if (min > max)
    return -1;

  if (min == max) {
    if ((mean != min) || (median != min))
      return -1;

    return 1;
  }

  if (min > median)
    return -1;

  if (min > mean)
    return -1;

  if (max < median)
    return -1;

  if (max < mean)
    return -1;

  int sum;
  sum = min + max;
  if ((sum == (2 * mean)) && (sum == (2 * median))) {
    return 2;
  }

  int least_odd = least_odd_department (min, max, mean, median);
  int least_even = least_even_department (min, max, mean, median);

  if (least_odd == -1)
    return least_even;
  if (least_even == -1)
    return least_odd;

  if ((least_odd == -1) && (least_even == -1))
    return -1;

  if (least_odd < least_even)
    return least_odd;
  else
    return least_even;
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
