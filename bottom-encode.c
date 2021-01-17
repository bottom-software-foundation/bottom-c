#include <stdio.h>
#include <wchar.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


// fast UTF-8 decoding

// Copyright (c) 2008-2010 Bjoern Hoehrmann <bjoern@hoehrmann.de>
// See http://bjoern.hoehrmann.de/utf-8/decoder/dfa/ for details.

#define UTF8_ACCEPT 0
#define UTF8_REJECT 12

static const uint8_t utf8d[] = {
  // The first part of the table maps bytes to character classes that
  // to reduce the size of the transition table and create bitmasks.
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
   7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
   8,8,2,2,2,2,2,2,2,2,2,2,2,2,2,2,  2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
  10,3,3,3,3,3,3,3,3,3,3,3,3,4,3,3, 11,6,6,6,5,8,8,8,8,8,8,8,8,8,8,8,

  // The second part is a transition table that maps a combination
  // of a state of the automaton and a character class to a state.
   0,12,24,36,60,96,84,12,12,12,48,72, 12,12,12,12,12,12,12,12,12,12,12,12,
  12, 0,12,12,12,12,12, 0,12, 0,12,12, 12,24,12,12,12,12,12,24,12,24,12,12,
  12,12,12,12,12,12,12,24,12,12,12,12, 12,24,12,12,12,12,12,12,12,24,12,12,
  12,12,12,12,12,12,12,36,12,36,12,12, 12,36,12,12,12,12,12,36,12,36,12,12,
  12,36,12,12,12,12,12,12,12,12,12,12, 
};

uint32_t decode(uint32_t* state, uint32_t* codep, uint32_t byte) {
  uint32_t type = utf8d[byte];

  *codep = (*state != UTF8_ACCEPT) ?
    (byte & 0x3fu) | (*codep << 6) :
    (0xff >> type) & (byte);

  *state = utf8d[256 + *state + type];
  return *state;
}


// main code

int main(void) {
    // build cache
    char *cache[200];
    int lengths[200];
    cache[0] = "❤️";
    lengths[0] = 6;
    for (int i = 0; i < 200; i++) {
        char *b = malloc(40);
        long l = 0;
        int r = i;
        while (r) {
            if      (r >= 50) { r -= 50;  memcpy(&b[l], "💖", 4); l += 4; }
            else if (r >= 10) { r -= 10;  memcpy(&b[l], "✨", 3); l += 3; }
            else if (r >= 5)  { r -= 5;   memcpy(&b[l], "🥺", 4); l += 4; }
            else              { r -= 1;   b[l++] = ','; }
        }
        memcpy(b+l, "👉👈", 8);
        l += 8;
        b = realloc(b, l);
        cache[i] = b;
        lengths[i] = l;
    }

    char buffer[8192];
    setvbuf(stdout, buffer, _IOFBF, sizeof buffer);

    // here goes
    int c;
    uint32_t codepoint;
    uint32_t state = UTF8_ACCEPT;
    while ((c = getchar()) != EOF) {
        if (!decode(&state, &codepoint, c)) {
            for (uint32_t i = 0; i < codepoint / 200; i++) {
                printf("🫂");
            }
            uint32_t n = codepoint % 200;
            fwrite(cache[n], 1, lengths[n], stdout);
        } else if (state == UTF8_REJECT) {
            fprintf(stderr, "Error occurred decoding UTF-8\n");
            return 1;
        }
    }
    return 0;
}
