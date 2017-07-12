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
      answer_bitset = answer_bitset | (1l << i);
    }
  }

  return answer_bitset;
}

static int count_ones (long long set, int n)
{
  int count = 0;
  int i = 0;

  while (set && i < n) {
    if (set & 0x1)
      count++;

    set = set >> 1;
    i++;
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

static int process_single_friend(void)
{
  int i;
  long long diff_set;
  int diff_count;
  int score;
  int addition;
  int improve_space;

  for (i = 0; i < friend_n; i++) {
    diff_set = friend_answers[i].answer ^ my_answer.answer;
    diff_count = count_ones (diff_set, question_n);
    improve_space = question_n - friend_answers[i].score;
    addition = (diff_count <= improve_space) ?
      diff_count :
      improve_space - (diff_count - improve_space);
    score = friend_answers[i].score + addition;
  }

  return score;
}

static int process(void)
{
  if (friend_n == 1)
    return process_single_friend ();

  /* There are four types of answers between friends and me.
   * 1. both are agree with me.
   * 2. friend1 is agree with me.
   * 3. friend2 is agree with me.
   * 4. neither are agree with me.
   *
   * If there are 'a' answers in type1 correct in my answer, I get 'a' score.
   * If there are 'b' answers in type2 correct in my answer, I get 'b' score.
   * If there are 'c' answers in type3 correct in my answer, I get 'c' score.
   * If there are 'd' answers in type4 correct in my answer, I get 'd' score.
   * maximize a + b + c + d */

  int both_agree_n;
  int friend1_agree_n;
  int friend2_agree_n;
  int both_disagree_n;
  long long diff_set1;
  long long diff_set2;
  int i, j, k, l;
  int friend1_score;
  int friend2_score;
  int my_score;
  int max_score;

  diff_set1 = my_answer.answer ^ friend_answers[0].answer;
  diff_set2 = my_answer.answer ^ friend_answers[1].answer;
  both_agree_n = question_n - count_ones (diff_set1 | diff_set2, question_n);
  both_disagree_n = count_ones (diff_set1 & diff_set2, question_n);
  friend1_agree_n = question_n - count_ones (diff_set1, question_n) - both_agree_n;
  friend2_agree_n = question_n - count_ones (diff_set2, question_n) - both_agree_n;

  max_score = 0;
  for (i = 0; i <= both_agree_n; i++) {
    for (j = 0; j <= friend1_agree_n; j++) {
      for (k = 0; k <= friend2_agree_n; k++) {
	for (l = 0; l <= both_disagree_n; l++) {
	  friend1_score = i + j + (friend2_agree_n - k) + (both_disagree_n - l);
	  friend2_score = i + k + (friend1_agree_n - j) + (both_disagree_n - l);
	  my_score = i + j + k + l;
	  if ((friend1_score == friend_answers[0].score) &&
	      (friend2_score == friend_answers[1].score)) {
	    if (my_score > max_score)
	      max_score = my_score;
	  }
	}
      }
    }
  }

  return max_score;
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
