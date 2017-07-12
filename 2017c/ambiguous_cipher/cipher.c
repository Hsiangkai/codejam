#include <stdio.h>
#include <string.h>

#define CHARACTER_NUM 26
#define WORD_LEN 51

static int module_26 (int value)
{
  if (value < 0) {
    while (value < 0) {
      value += 26;
    }
  } else {
    while (value > 25) {
      value -= 26;
    }
  }

  return value;
}

/* return -1 if ambiguous */
static int decode(char *encrypted, char *decrypted)
{
  int length = strlen (encrypted);
  int i;
  int decrypt;
  if (length % 2)
    return -1;

  /**
   * encrypted[0] = decrypted[1]
   * encrypted[2] = (decrypted[1] + decrypted[3]) % 26
   */
  decrypted[length] = '\0';
  decrypted[1] = encrypted[0];
  for (i = 2; i < length; i += 2) {
    decrypt = encrypted[i] - decrypted[i - 1];
    decrypted[i + 1] = module_26 (decrypt) + 'A';
  }
  /**
   * encrypted[n-1] = decrypted[n-2]
   * encrypted[n-3] = (decrypted[n-2] + decrypted[n-4]) % 26
   */
  decrypted[length - 2] = encrypted[length - 1];
  for (i = length - 3; i >= 0; i -= 2) {
    decrypt = encrypted[i] - decrypted[i + 1];
    decrypted[i - 1] = module_26 (decrypt) + 'A';
  }

  return 0;
}

int main()
{
  char encrypted[WORD_LEN];
  char decrypted[WORD_LEN];
  int case_n;
  int i;

  scanf ("%d\n", &case_n);
  i = 1;
  while (case_n) {
    scanf ("%s\n", encrypted);

    printf ("Case #%d: ", i++);
    if (decode (encrypted, decrypted) == -1) {
      printf ("AMBIGUOUS\n");
    } else {
      printf ("%s\n", decrypted);
    }
    case_n--;
  }

  return 0;
}
