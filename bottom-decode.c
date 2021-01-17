#include <stdio.h>
#include <stdint.h>

int main() {
    int c;
    uint32_t sum = 0;
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
                // output codepoint; isn't very cool but lazy code best code
                if (sum <= 0x7F) {
                    putchar(sum);
                } else if (sum <= 0x7FF) {
                    putchar(0xC0 | (sum >> 6));
                    putchar(0x80 | (sum & 0x3F));
                }
                else if (sum <= 0xFFFF) {
                    putchar(0xE0 | (sum >> 12));
                    putchar(0x80 | ((sum >> 6) & 0x3F));
                    putchar(0x80 | (sum & 0x3F));
                } else if (sum <= 0x10FFFF) {
                    putchar(0xF0 | (sum >> 18));
                    putchar(0x80 | ((sum >> 12) & 0x3F));
                    putchar(0x80 | ((sum >> 6) & 0x3F));
                    putchar(0x80 | (sum & 0x3F));
                }
                sum = 0;
            }
            getchar();
            break;
        }
    }
}
