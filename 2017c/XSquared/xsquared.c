#include <stdio.h>

#define N 56

struct row {
  int column1;
  int column2;
};

struct row matrix[N];
int row_count[N];
int column_count[N];

static void init (void)
{
  int i;

  for (i = 0; i < N; i++) {
    matrix[i].column1 = -1;
    matrix[i].column2 = -1;
    row_count[i] = 0;
    column_count[i] = 0;
  }
}

static int process (void)
{
  char line[N];
  int row_n;
  int i;
  int j;
  int center_column;
  int valid;

  valid = 1;
  scanf ("%d\n", &row_n);
  for (i = 0; i < row_n; i++) {
    scanf ("%s\n", line);
    /* record row 'X' */
    for (j = 0; line[j] != '\0'; j++) {
      if (line[j] == 'X') {
	row_count[i]++;
	if (matrix[i].column1 == -1)
	  matrix[i].column1 = j;
	else if (matrix[i].column2 == -1)
	  matrix[i].column2 = j;
	else
	  valid = 0;
      }
    }
  }
  
  if (!valid)
    return -1;

  /* calculate column 'X' */
  for (i = 0; i < row_n; i++) {
    if (matrix[i].column1 != -1)
      column_count[matrix[i].column1]++;
    if (matrix[i].column2 != -1)
      column_count[matrix[i].column2]++;
  }

  center_column = -1;
  for (i = 0; i < row_n; i++) {
    if (column_count[i] == 2) {
      continue;
    } else if ((center_column == -1) && (column_count[i] == 1)) {
      center_column = i;
    } else {
      return -1;
    }
  }

  if (center_column == -1)
    return -1;

  for (i = 0; i < row_n; i++) {
    if (matrix[i].column1 == center_column) {
      if (matrix[i].column2 != -1)
	return -1;
    } else if (matrix[i].column2 == center_column) {
      return -1;
    }
  }

  for (i = 0; i < row_n; i++) {
    for (j = i+1; j < row_n; j++) {
      if (matrix[j].column1 == matrix[i].column1) {
	if (matrix[j].column2 != matrix[i].column2) {
	  return -1;
	} else {
	  break;
	}
      }
    }
  }

  return 0;
}

int main()
{
  int case_n;
  int i;

  scanf ("%d\n", &case_n);
  i = 1;
  while (case_n) {
    printf ("Case #%d: ", i++);
    init ();
    if (process () == -1) {
      printf ("IMPOSSIBLE\n");
    } else {
      printf ("POSSIBLE\n");
    }
    case_n--;
  }
}
