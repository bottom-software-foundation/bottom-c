#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main(void) {
    // build cache
    char *cache[256];
    int lengths[256];
    cache[0] = "❤️";
    lengths[0] = 6;
    for (int i = 1; i < 256; i++) {
        char *b = malloc(40);
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
        b = realloc(b, l);
        cache[i] = b;
        lengths[i] = l;
    }

    char buffer[8192];
    unsigned int l = 0;

    // here goes
    int c;
    while ((c = getchar()) != EOF) {
        if (l + lengths[c] > sizeof buffer) {
            write(1, buffer, l);
            l = 0;
        }
        memcpy(&buffer[l], cache[c], lengths[c]);
        l += lengths[c];
    }
    write(1, buffer, l);
    return 0;
}
