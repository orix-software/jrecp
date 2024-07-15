#include "alphabet.h"
#include <peekpoke.h>
#include <string.h>

// Position letter in hrs picture
//                                A    B   C   D   E   F   G   H   I   J   K   L   M  N    O   P   Q   R   S   T   U   V   W   X    Y
unsigned char alphabet_pos_x[] =  {0,  5,  9,  14, 19, 23, 26, 31, 36, 38, 41, 45, 49, 55, 60, 65, 69, 74, 78, 81, 85, 90, 95, 102, 107, 111};
unsigned char alphabet_pos_y[] =  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   0,   0 };
unsigned char alphabet_length[] = {5,  4,  5,  5,  4,  3,  5,  5,  2,  3,  4,  4,  6,  5,  5,  4,  5,  4,  3,  4,  5,  5,  7,  5,   4,   4 };
unsigned char alphabet_height[] = {26, 26, 26, 26, 26, 26, 26, 26, 26, 32, 26, 26, 26, 26, 26, 26, 32, 26, 26, 26, 26, 26, 26, 26,  26,  26 };

// Returns the length of the char
unsigned char display_letter(unsigned char x, unsigned char y, unsigned char letter) {
    //alphabet_pos_x[]
    unsigned int offset;
    unsigned char i,j=0;
    letter = letter - 65;

    offset = alphabet_pos_x[letter] + alphabet_pos_y[letter]*188;

    for (j=0;j<alphabet_height[letter];j++) {
        for (i=0;i<alphabet_length[letter];i++) {
            POKE(0xA000+i+j*40 + x + y*40, alphabet_pic[offset]);
            offset++;
        }
        offset += 188-i;
    }
    return alphabet_length[letter];
}

void display_string (unsigned char x, unsigned char y, unsigned char *str) {
    unsigned char i;

    for (i=0;i<strlen(str);i++) {
        if (str[i] == 32)
            x = x + 2;
        else {
            display_letter(x, y, str[i]);
            x = x + alphabet_length[str[i] - 65];
        }
    }

}