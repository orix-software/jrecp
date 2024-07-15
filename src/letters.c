#include "display.h"

char *numbers[]= {
    "UN",
    "DEUX",
    "TROIS",
    "QUATRE",
    "CINQ",
    "SIX",
    "SEPT",
    "HUIT",
    "NEUF",
    "DIX"
};

char *picture_guess_to_letter[]= {
    "GRENOUILLE",
    "RAT",
    "CROCODILE",
    "CHAT",
    "COCHON"
};

void alphabet() {
    unsigned char letter, size = 0;
    for (letter = 'A'; letter < 'E' + 1; letter++) {
        size  += display_letter(size, 0, letter);

    }
}


void letters_numbers() {
    unsigned char digit;
    //digit = random(modulo);

    // Level


}