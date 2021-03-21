#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


int main(void) {
    // build cache
    char cache[256][40];
    int lengths[256];
    memcpy(cache[0], "❤️👉👈", 14);
    lengths[0] = 14;
    for (int i = 1; i < 256; i++) {
        char *b = cache[i];
        int l = 0;
        int r = i;
        while (r) {
            	if (r >= 200) { r -= 200; memcpy(&b[l], "🫂", 4); l += 4; }
           else if (r >= 50)  { r -= 50;  memcpy(&b[l], "💖", 4); l += 4; }
           else if (r >= 10)  { r -= 10;  memcpy(&b[l], "✨", 3); l += 3; }
           else if (r >= 5)   { r -= 5;   memcpy(&b[l], "🥺", 4); l += 4; }
           else               { r -= 1;   b[l++] = ','; }
        }
        memcpy(b+l, "👉👈", 8);
        l += 8;
        lengths[i] = l;
    }

    setvbuf(stdout, NULL, _IONBF, 0);

    char buffer[8192];
    unsigned int l = 0;

    // here goes
    int c;
    while ((c = getchar()) != EOF) {
        if (l + lengths[c] > sizeof buffer) {
            fwrite(buffer, l, 1, stdout);
            l = 0;
        }
        memcpy(&buffer[l], cache[c], lengths[c]);
        l += lengths[c];
    }
    fwrite(buffer, l, 1, stdout);
    return 0;
}
