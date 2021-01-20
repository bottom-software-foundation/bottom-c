#include <stdio.h>
#include <stdint.h>

int main() {
    int c;
    int sum = 0;
    while ((c = getchar()) != EOF) {
        switch (c) {
          case ',':
            sum++;
            break;
          case 226:
            if (getchar() == 156) {
                getchar();
                sum += 10;
            } else {
                getchar();
                getchar();
                getchar();
                getchar();
            }
            break;
          case 240:
            getchar();
            switch (getchar()) {
              case 171:
                sum += 200;
                break;
              case 146:
                sum += 50;
                break;
              case 165:
                sum += 5;
                break;
              case 145:
                getchar();
                getchar();
                getchar();
                getchar();
                putchar(sum);
                sum = 0;
                break;
            }
            getchar();
            break;
        }
    }
}
