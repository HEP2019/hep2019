#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

int main(int argc, char** argv) {
  int in = atoi(argv[1]);
  char out[42];
  char* p = out + sizeof out / sizeof(char);
#define PUSH(x) (*--p = '0' + (x))

loop:
  while (in > 9) {
    // find and store the biggest divisor and repeat with quotient
    for (int i = 9; i > 1; i--) {
      div_t buf = div(in, i);
      if (buf.rem == 0) {
        PUSH(i);
        in = buf.quot;
        goto loop;
      }
    }
    // no divisor
    printf("-1\n");
    exit(EXIT_SUCCESS);
  }
  PUSH(in);

  printf("%s\n", p);
  exit(EXIT_SUCCESS);
}
