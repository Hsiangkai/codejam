#include <stdio.h>
#include <stdlib.h>

#define MAX_CITY_N 2000

struct bus_schedule {
  int start_time;
  int frequency;
  int duration;
};

struct records {
  int time;
  int city_n;
  struct records *next;
};

struct records *record_table[MAX_CITY_N];

static void init_table (void)
{
  int i;

  for (i = 0; i < MAX_CITY_N; i++)
    record_table[i] = NULL;
}

static void clean_table (void)
{
  int i;
  struct records *entry;

  for (i = 0; i < MAX_CITY_N; i++) {
    while (record_table[i]) {
      entry = record_table[i]->next;
      free (record_table[i]);
      record_table[i] = entry;
    }
  }
}

static int find (int n, int time)
{
  struct records *entry = record_table[n];

  while (entry) {
    if (entry->time == time)
      return entry->city_n;
    entry = entry->next;
  }

  return -1;
}

static void insert (int n, int time, int city_n)
{
  struct records **entry;

  entry = &(record_table[n]);

  while (*entry) {
    entry = &((*entry)->next);
  }

  *entry = malloc (sizeof (struct records));
  (*entry)->next = NULL;
  (*entry)->time = time;
  (*entry)->city_n = city_n;
}

int travel (int n, int sightseeing_time, int final_time, struct bus_schedule *buses)
{
  int final_time_with_visit;
  int final_time_without_visit;
  int with_visit_city_n;
  int without_visit_city_n;
  int latest_take_bus_time;
  struct bus_schedule *bus;
  int round;

  if (final_time < 0)
    return -1;

  if (n == 1)
    return 0;

  bus = &buses[n-2];
  latest_take_bus_time = final_time - bus->duration;
  if (latest_take_bus_time < bus->start_time)
    return -1;

  round = (latest_take_bus_time - bus->start_time) / bus->frequency;
  if ((bus->start_time + round * bus->frequency) <= latest_take_bus_time)
    latest_take_bus_time = bus->start_time + round * bus->frequency;
  else
    return -1;

  final_time_with_visit = latest_take_bus_time - sightseeing_time;
  final_time_without_visit = latest_take_bus_time;

  with_visit_city_n = find (n - 1, final_time_with_visit);
  if (with_visit_city_n == -1) {
    with_visit_city_n = travel (n - 1, sightseeing_time,
        final_time_with_visit, buses);
    insert (n - 1, final_time_with_visit, with_visit_city_n);
  }
  without_visit_city_n = find (n - 1, final_time_without_visit);
  if (without_visit_city_n == -1) {
    without_visit_city_n = travel (n - 1, sightseeing_time,
        final_time_without_visit, buses);
    insert (n - 1, final_time_without_visit, without_visit_city_n);
  }

  if ((with_visit_city_n == -1) && (without_visit_city_n == -1))
    return -1;
  else if (with_visit_city_n == -1)
    return without_visit_city_n;
  else if (without_visit_city_n == -1)
    return with_visit_city_n + 1;

  if (with_visit_city_n + 1 > without_visit_city_n)
    return with_visit_city_n + 1;
  else
    return without_visit_city_n;
}

int process (void)
{
  int n;
  int sightseeing_time;
  int final_time;
  int i;
  struct bus_schedule buses[MAX_CITY_N];
  int city_n;

  /* input */
  scanf ("%d %d %d\n", &n, &sightseeing_time, &final_time);
  i = 0;
  while (i < n - 1) {
    scanf ("%d %d %d\n", &(buses[i].start_time), &(buses[i].frequency), &(buses[i].duration));
    i++;
  }

  /* process */
  init_table ();
  city_n = travel (n, sightseeing_time, final_time, buses);
  clean_table ();

  return city_n;
}

int main ()
{
  int case_n;
  int i;
  int city_n;

  scanf ("%d\n", &case_n);
  i = 1;
  while (case_n) {
    printf ("Case #%d: ", i++);
    city_n = process ();
    if (city_n == -1)
      printf ("IMPOSSIBLE\n");
    else
      printf ("%d\n", city_n);

    case_n--;
  }

  return 0;
}
