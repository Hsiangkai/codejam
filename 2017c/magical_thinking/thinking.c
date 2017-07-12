#include <stdio.h>

#define PEOPLE_N 2
#define QUESTION_N 50

struct answer_t {
  long long answer;
  int score;
};

struct answer_t friend_answers[PEOPLE_N];
struct answer_t my_answer;
int friend_n;
int question_n;

static long long convert_to_bitset (char *answer)
{
  int i;
  long long answer_bitset = 0;
  
  for (i = 0; i < question_n; i++) {
    if (answer[i] == 'T') {
      answer_bitset = answer_bitset | (1 << i);
    }
  }

  return answer_bitset;
}

static int count_ones (long long set)
{
  int count = 0;

  while (set) {
    if (set & 0x1)
      count++;

    set = set >> 1;
  }

  return count;
}

static void input()
{
  int i;
  char answer[QUESTION_N + 1];

  scanf ("%d %d\n", &friend_n, &question_n);
  for (i = 0; i < friend_n; i++) {
    scanf ("%s\n", answer);
    friend_answers[i].answer = convert_to_bitset (answer);
  }
  scanf ("%s\n", answer);
  my_answer.answer = convert_to_bitset (answer);
  for (i = 0; i < friend_n; i++) {
    scanf ("%d", &(friend_answers[i].score));
  }
}

static int process(void)
{
  int i;
  long long diff_set;
  int diff_count;
  int score;
  int addition;
  int improve_space;

  for (i = 0; i < friend_n; i++) {
    diff_set = friend_answers[i].answer ^ my_answer.answer;
    diff_count = count_ones (diff_set);
    improve_space = question_n - friend_answers[i].score;
    addition = (diff_count <= improve_space) ?
      diff_count :
      improve_space - (diff_count - improve_space);
    score = friend_answers[i].score + addition;
  }

  return score;
}

int main(void)
{
  int case_n;
  int i;
  int score;

  i = 1;
  scanf ("%d\n", &case_n);
  while (case_n) {
    input ();
    printf ("Case #%d: ", i++);
    score = process ();
    printf ("%d\n", score);
    case_n--;
  }

  return 0;
}
