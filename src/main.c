#include <stdio.h>
#include <telestrat.h>
#include <tgi.h>
#include <conio.h>
#include <peekpoke.h>

#include "bandeau.h"
#include "display.h"

extern unsigned char display_letter(unsigned char x, unsigned char y, unsigned char letter);
extern void display_string (unsigned char x, unsigned char y, unsigned char *str);
extern void alphabet();
#define CLASSE_CP  0x04
#define CLASSE_CE1 0x05
#define CLASSE_CE2 0x06

#define ADDITION_OPERATEUR     0x01
#define SOUSTRACTION_OPERATEUR 0x02

// Modulo pour les levels
unsigned char level_mod[] =           {2, 3, 4, 5, 6, 7, 8, 9, 10};
// Operateurs affichés
unsigned char level_operators[] =    {ADDITION_OPERATEUR, ADDITION_OPERATEUR, ADDITION_OPERATEUR, ADDITION_OPERATEUR, ADDITION_OPERATEUR, ADDITION_OPERATEUR, ADDITION_OPERATEUR, ADDITION_OPERATEUR, ADDITION_OPERATEUR, ADDITION_OPERATEUR};
unsigned char level_number_tests[] = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10};

struct user {
    unsigned char exp;
    unsigned char level;
    unsigned char classe;
    unsigned char name[15];
};

    struct user user;

    unsigned char users[255];


void init_user() {
    user.level = 1;
    user.classe = CLASSE_CP;
    user.exp = 0;
}

void bar_menu (unsigned char item) {
    unsigned char i;
    for (i=0; i <30; i++) {
        POKE(0xA000+i*40, 0x12);
    }
}

void menu() {
    FILE *fp;
    unsigned char key, x=0, y=100;

    //clrscr();
    fp = fopen("/root/jrep/users.txt","r");
    if (fp != NULL) {
        fread( users, 255, 1, fp );
    }

    display_string (1, 0, "NOUVEAU");
    //display_string (1, 0, "CLEMENCE");

    bar_menu (0);
    key = cgetc();
    if (key == 13) {
        while (1) {
            tgi_clear();
            display_string (1, 0, "PRENOM");
            while (1) {
                key = cgetc();
                switch(key) {
                    case 13:
                        break;
                    case 127:
                        break;
                    default:
                        x += display_letter(x, y, key);
                        break;
                    }
            }
        }
    }

}


unsigned char egal[170]=
{
    0x40,0x40,0x40,0x40,0x40,
	0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,
	0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,
	0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x7f,0x7f,0x7f,
	0x7f,0x60,0x7f,0x7f,0x7f,0x7f,0x60,0x7f,0x7f,0x7f,0x7f,0x60,0x7f,0x7f,0x7f,0x7f,
	0x60,0x7f,0x7f,0x7f,0x7f,0x60,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,
	0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x7f,0x7f,0x7f,0x7f,0x60,0x7f,
	0x7f,0x7f,0x7f,0x60,0x7f,0x7f,0x7f,0x7f,0x60,0x7f,0x7f,0x7f,0x7f,0x60,0x7f,0x7f,
	0x7f,0x7f,0x60,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,
	0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,
	0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,
	0x40,0x40,0x40,0x40,0x40
};

unsigned char plus[170]=
{    0x40,0x40,0x40,0x40,0x40,
	0x40,0x41,0x70,0x40,0x40,0x40,0x41,0x70,0x40,0x40,0x40,0x41,0x70,0x40,0x40,0x40,
	0x41,0x70,0x40,0x40,0x40,0x41,0x70,0x40,0x40,0x40,0x41,0x70,0x40,0x40,0x40,0x41,
	0x70,0x40,0x40,0x40,0x41,0x70,0x40,0x40,0x40,0x41,0x70,0x40,0x40,0x40,0x41,0x70,
	0x40,0x40,0x40,0x41,0x70,0x40,0x40,0x40,0x41,0x70,0x40,0x40,0x40,0x41,0x70,0x40,
	0x40,0x40,0x41,0x70,0x40,0x40,0x40,0x41,0x70,0x40,0x40,0x7f,0x7f,0x7f,0x7f,0x60,
	0x7f,0x7f,0x7f,0x7f,0x60,0x7f,0x7f,0x7f,0x7f,0x60,0x40,0x41,0x70,0x40,0x40,0x40,
	0x41,0x70,0x40,0x40,0x40,0x41,0x70,0x40,0x40,0x40,0x41,0x70,0x40,0x40,0x40,0x41,
	0x70,0x40,0x40,0x40,0x41,0x70,0x40,0x40,0x40,0x41,0x70,0x40,0x40,0x40,0x41,0x70,
	0x40,0x40,0x40,0x41,0x70,0x40,0x40,0x40,0x41,0x70,0x40,0x40,0x40,0x41,0x70,0x40,
	0x40,0x40,0x41,0x70,0x40,0x40,0x40,0x41,0x70,0x40,0x40,0x40,0x41,0x70,0x40,0x40,
	0x40,0x41,0x70,0x40,0x40
};


unsigned char number_0[170]=
{
    0x40,0x40,0x40,0x40,0x40,
	0x40,0x47,0x7c,0x40,0x40,0x40,0x5c,0x47,0x40,0x40,0x40,0x78,0x43,0x60,0x40,0x41,
	0x70,0x41,0x70,0x40,0x43,0x60,0x40,0x78,0x40,0x43,0x60,0x40,0x78,0x40,0x47,0x40,
	0x40,0x5c,0x40,0x47,0x40,0x40,0x5c,0x40,0x4f,0x40,0x40,0x5e,0x40,0x4f,0x40,0x40,
	0x5e,0x40,0x4e,0x40,0x40,0x4e,0x40,0x5e,0x40,0x40,0x4f,0x40,0x5e,0x40,0x40,0x4f,
	0x40,0x5e,0x40,0x40,0x4f,0x40,0x5e,0x40,0x40,0x4f,0x40,0x5e,0x40,0x40,0x4f,0x40,
	0x5e,0x40,0x40,0x4f,0x40,0x5e,0x40,0x40,0x4f,0x40,0x5e,0x40,0x40,0x4f,0x40,0x5e,
	0x40,0x40,0x4f,0x40,0x5e,0x40,0x40,0x4f,0x40,0x5e,0x40,0x40,0x4e,0x40,0x4e,0x40,
	0x40,0x4e,0x40,0x4e,0x40,0x40,0x4e,0x40,0x4f,0x40,0x40,0x5e,0x40,0x47,0x40,0x40,
	0x5c,0x40,0x47,0x40,0x40,0x5c,0x40,0x43,0x60,0x40,0x58,0x40,0x43,0x60,0x40,0x78,
	0x40,0x41,0x70,0x40,0x70,0x40,0x40,0x78,0x41,0x60,0x40,0x40,0x5c,0x47,0x40,0x40,
	0x40,0x47,0x7c,0x40,0x40
};

unsigned char number_1[170]=
{
    0x40,0x40,0x40,0x40,0x40,
	0x40,0x40,0x50,0x40,0x40,0x40,0x43,0x70,0x40,0x40,0x40,0x4f,0x70,0x40,0x40,0x40,
	0x7f,0x70,0x40,0x40,0x41,0x43,0x70,0x40,0x40,0x40,0x43,0x70,0x40,0x40,0x40,0x43,
	0x70,0x40,0x40,0x40,0x43,0x70,0x40,0x40,0x40,0x43,0x70,0x40,0x40,0x40,0x43,0x70,
	0x40,0x40,0x40,0x43,0x70,0x40,0x40,0x40,0x43,0x70,0x40,0x40,0x40,0x43,0x70,0x40,
	0x40,0x40,0x43,0x70,0x40,0x40,0x40,0x43,0x70,0x40,0x40,0x40,0x43,0x70,0x40,0x40,
	0x40,0x43,0x70,0x40,0x40,0x40,0x43,0x70,0x40,0x40,0x40,0x43,0x70,0x40,0x40,0x40,
	0x43,0x70,0x40,0x40,0x40,0x43,0x70,0x40,0x40,0x40,0x43,0x70,0x40,0x40,0x40,0x43,
	0x70,0x40,0x40,0x40,0x43,0x70,0x40,0x40,0x40,0x43,0x70,0x40,0x40,0x40,0x43,0x70,
	0x40,0x40,0x40,0x43,0x70,0x40,0x40,0x40,0x43,0x70,0x40,0x40,0x40,0x43,0x70,0x40,
	0x40,0x40,0x43,0x70,0x40,0x40,0x40,0x43,0x70,0x40,0x40,0x40,0x47,0x78,0x40,0x40,
	0x41,0x7f,0x7f,0x60,0x40
};

unsigned char number_2[170]=
{
    0x40,0x40,0x40,0x40,0x40,
	0x40,0x47,0x78,0x40,0x40,0x40,0x7f,0x7e,0x40,0x40,0x41,0x7f,0x7f,0x40,0x40,0x43,
	0x7f,0x7f,0x60,0x40,0x47,0x60,0x5f,0x70,0x40,0x46,0x40,0x47,0x70,0x40,0x4c,0x40,
	0x43,0x78,0x40,0x4c,0x40,0x43,0x78,0x40,0x58,0x40,0x41,0x78,0x40,0x50,0x40,0x41,
	0x78,0x40,0x40,0x40,0x41,0x78,0x40,0x40,0x40,0x41,0x78,0x40,0x40,0x40,0x41,0x70,
	0x40,0x40,0x40,0x41,0x70,0x40,0x40,0x40,0x43,0x60,0x40,0x40,0x40,0x43,0x60,0x40,
	0x40,0x40,0x47,0x40,0x40,0x40,0x40,0x46,0x40,0x40,0x40,0x40,0x4c,0x40,0x40,0x40,
	0x40,0x58,0x40,0x40,0x40,0x40,0x50,0x40,0x40,0x40,0x40,0x60,0x40,0x40,0x40,0x41,
	0x40,0x40,0x40,0x40,0x42,0x40,0x40,0x40,0x40,0x44,0x40,0x40,0x40,0x40,0x48,0x40,
	0x40,0x40,0x40,0x50,0x40,0x41,0x40,0x40,0x60,0x40,0x42,0x40,0x41,0x40,0x40,0x46,
	0x40,0x43,0x7f,0x7f,0x7c,0x40,0x47,0x7f,0x7f,0x7c,0x40,0x4f,0x7f,0x7f,0x7c,0x40,
	0x5f,0x7f,0x7f,0x78,0x40
};

unsigned char number_3[170]=
{
    0x40,0x40,0x40,0x40,0x40,
	0x40,0x47,0x7c,0x40,0x40,0x40,0x5f,0x7f,0x40,0x40,0x40,0x7f,0x7f,0x60,0x40,0x43,
	0x70,0x5f,0x70,0x40,0x43,0x40,0x47,0x70,0x40,0x46,0x40,0x43,0x78,0x40,0x44,0x40,
	0x41,0x78,0x40,0x48,0x40,0x41,0x78,0x40,0x40,0x40,0x41,0x78,0x40,0x40,0x40,0x41,
	0x78,0x40,0x40,0x40,0x41,0x70,0x40,0x40,0x40,0x43,0x60,0x40,0x40,0x40,0x47,0x60,
	0x40,0x40,0x40,0x4e,0x40,0x40,0x40,0x40,0x7c,0x40,0x40,0x40,0x43,0x7f,0x40,0x40,
	0x40,0x5f,0x7f,0x70,0x40,0x40,0x40,0x5f,0x78,0x40,0x40,0x40,0x43,0x7c,0x40,0x40,
	0x40,0x41,0x7c,0x40,0x40,0x40,0x40,0x7e,0x40,0x40,0x40,0x40,0x7e,0x40,0x40,0x40,
	0x40,0x5e,0x40,0x40,0x40,0x40,0x5e,0x40,0x40,0x40,0x40,0x5e,0x40,0x40,0x40,0x40,
	0x5c,0x40,0x40,0x40,0x40,0x5c,0x40,0x40,0x40,0x40,0x78,0x40,0x40,0x40,0x41,0x70,
	0x40,0x4f,0x40,0x43,0x60,0x40,0x4f,0x70,0x47,0x40,0x40,0x4f,0x7f,0x7c,0x40,0x40,
	0x43,0x7f,0x60,0x40,0x40
};


unsigned char number_4[170]=
{
    0x40,0x40,0x40,0x40,0x40,
    0x40,0x40,0x41,0x70,0x40,0x40,0x40,0x43,0x70,0x40,0x40,0x40,0x43,0x70,0x40,0x40,
	0x40,0x47,0x70,0x40,0x40,0x40,0x4f,0x70,0x40,0x40,0x40,0x5b,0x70,0x40,0x40,0x40,
	0x7b,0x70,0x40,0x40,0x40,0x73,0x70,0x40,0x40,0x41,0x63,0x70,0x40,0x40,0x43,0x43,
	0x70,0x40,0x40,0x46,0x43,0x70,0x40,0x40,0x4e,0x43,0x70,0x40,0x40,0x4c,0x43,0x70,
	0x40,0x40,0x58,0x43,0x70,0x40,0x40,0x70,0x43,0x70,0x40,0x41,0x60,0x43,0x70,0x40,
	0x43,0x60,0x43,0x70,0x40,0x43,0x40,0x43,0x70,0x40,0x46,0x40,0x43,0x70,0x40,0x4c,
	0x40,0x43,0x70,0x40,0x58,0x40,0x43,0x70,0x40,0x78,0x40,0x43,0x70,0x40,0x7f,0x7f,
	0x7f,0x7f,0x60,0x7f,0x7f,0x7f,0x7f,0x60,0x7f,0x7f,0x7f,0x7f,0x60,0x40,0x40,0x43,
	0x70,0x40,0x40,0x40,0x43,0x70,0x40,0x40,0x40,0x43,0x70,0x40,0x40,0x40,0x43,0x70,
	0x40,0x40,0x40,0x43,0x70,0x40,0x40,0x40,0x43,0x70,0x40,0x40,0x40,0x43,0x70,0x40,
	0x40,0x40,0x43,0x70,0x40
};


unsigned char number_5[170]=
{
	0x40,0x40,0x40,0x43,0x40,0x40,0x47,0x7f,0x7e,0x40,0x40,0x47,0x7f,0x7e,0x40,0x40,
	0x4f,0x7f,0x7e,0x40,0x40,0x4f,0x7f,0x7c,0x40,0x40,0x58,0x40,0x40,0x40,0x40,0x58,
	0x40,0x40,0x40,0x40,0x70,0x40,0x40,0x40,0x40,0x70,0x40,0x40,0x40,0x41,0x60,0x40,
	0x40,0x40,0x41,0x7c,0x40,0x40,0x40,0x43,0x7f,0x78,0x40,0x40,0x43,0x7f,0x7e,0x40,
	0x40,0x43,0x7f,0x7f,0x60,0x40,0x40,0x47,0x7f,0x70,0x40,0x40,0x40,0x5f,0x78,0x40,
	0x40,0x40,0x47,0x7c,0x40,0x40,0x40,0x41,0x7e,0x40,0x40,0x40,0x40,0x7e,0x40,0x40,
	0x40,0x40,0x5f,0x40,0x40,0x40,0x40,0x5f,0x40,0x40,0x40,0x40,0x4f,0x40,0x40,0x40,
	0x40,0x4f,0x40,0x40,0x40,0x40,0x4f,0x40,0x40,0x40,0x40,0x4f,0x40,0x40,0x40,0x40,
	0x4e,0x40,0x40,0x40,0x40,0x4e,0x40,0x40,0x40,0x40,0x5c,0x40,0x40,0x40,0x40,0x5c,
	0x40,0x40,0x40,0x40,0x78,0x40,0x4f,0x40,0x41,0x70,0x40,0x5f,0x78,0x47,0x40,0x40,
	0x5f,0x7f,0x7c,0x40,0x40,0x47,0x7f,0x60,0x40,0x40
};

unsigned char number_6[170]=
{   0x40,0x40,0x40,0x40,0x40,
	0x40,0x40,0x40,0x7e,0x40,0x40,0x40,0x47,0x70,0x40,0x40,0x40,0x7e,0x40,0x40,0x40,
	0x43,0x70,0x40,0x40,0x40,0x47,0x60,0x40,0x40,0x40,0x4f,0x40,0x40,0x40,0x40,0x5e,
	0x40,0x40,0x40,0x40,0x7c,0x40,0x40,0x40,0x41,0x78,0x40,0x40,0x40,0x43,0x70,0x40,
	0x40,0x40,0x47,0x70,0x40,0x40,0x40,0x47,0x60,0x40,0x40,0x40,0x4f,0x43,0x7e,0x40,
	0x40,0x4f,0x5f,0x7f,0x60,0x40,0x4f,0x70,0x47,0x78,0x40,0x5f,0x60,0x41,0x7c,0x40,
	0x5f,0x40,0x40,0x7e,0x40,0x5e,0x40,0x40,0x7e,0x40,0x5e,0x40,0x40,0x5f,0x40,0x5e,
	0x40,0x40,0x5f,0x40,0x5e,0x40,0x40,0x4f,0x40,0x5e,0x40,0x40,0x4f,0x40,0x5e,0x40,
	0x40,0x4f,0x40,0x4e,0x40,0x40,0x4f,0x40,0x4f,0x40,0x40,0x4f,0x40,0x4f,0x40,0x40,
	0x4e,0x40,0x47,0x40,0x40,0x4e,0x40,0x47,0x60,0x40,0x5c,0x40,0x43,0x60,0x40,0x5c,
	0x40,0x41,0x70,0x40,0x78,0x40,0x40,0x78,0x40,0x70,0x40,0x40,0x4e,0x43,0x60,0x40,
	0x40,0x43,0x7c,0x40,0x40
};

unsigned char number_7[170]=
{
    0x40,0x40,0x40,0x40,0x40,
	0x43,0x7f,0x7f,0x7f,0x60,0x43,0x7f,0x7f,0x7f,0x60,0x47,0x7f,0x7f,0x7f,0x40,0x47,
	0x7f,0x7f,0x7f,0x40,0x4e,0x40,0x40,0x47,0x40,0x4c,0x40,0x40,0x4e,0x40,0x58,0x40,
	0x40,0x4e,0x40,0x50,0x40,0x40,0x5e,0x40,0x40,0x40,0x40,0x5c,0x40,0x40,0x40,0x40,
	0x5c,0x40,0x40,0x40,0x40,0x78,0x40,0x40,0x40,0x40,0x78,0x40,0x40,0x40,0x40,0x78,
	0x40,0x40,0x40,0x41,0x70,0x40,0x40,0x40,0x41,0x70,0x40,0x40,0x40,0x43,0x70,0x40,
	0x40,0x40,0x43,0x60,0x40,0x40,0x40,0x43,0x60,0x40,0x40,0x40,0x47,0x60,0x40,0x40,
	0x40,0x47,0x40,0x40,0x40,0x40,0x47,0x40,0x40,0x40,0x40,0x4e,0x40,0x40,0x40,0x40,
	0x4e,0x40,0x40,0x40,0x40,0x4e,0x40,0x40,0x40,0x40,0x5c,0x40,0x40,0x40,0x40,0x5c,
	0x40,0x40,0x40,0x40,0x7c,0x40,0x40,0x40,0x40,0x78,0x40,0x40,0x40,0x40,0x78,0x40,
	0x40,0x40,0x41,0x70,0x40,0x40,0x40,0x41,0x70,0x40,0x40,0x40,0x41,0x70,0x40,0x40,
	0x40,0x43,0x60,0x40,0x40
};

unsigned char number_8[170]=
{
    0x40,0x40,0x40,0x40,0x40,
	0x40,0x4f,0x7e,0x40,0x40,0x41,0x78,0x47,0x60,0x40,0x43,0x60,0x41,0x78,0x40,0x47,
	0x40,0x40,0x7c,0x40,0x4e,0x40,0x40,0x5c,0x40,0x5e,0x40,0x40,0x5e,0x40,0x5e,0x40,
	0x40,0x5e,0x40,0x5e,0x40,0x40,0x5e,0x40,0x5f,0x40,0x40,0x5e,0x40,0x5f,0x60,0x40,
	0x7c,0x40,0x4f,0x70,0x41,0x78,0x40,0x4f,0x78,0x43,0x70,0x40,0x47,0x7e,0x47,0x60,
	0x40,0x43,0x7f,0x7e,0x40,0x40,0x41,0x7f,0x78,0x40,0x40,0x40,0x5f,0x7c,0x40,0x40,
	0x40,0x4f,0x7f,0x40,0x40,0x40,0x7f,0x7f,0x60,0x40,0x41,0x70,0x7f,0x78,0x40,0x43,
	0x60,0x4f,0x7c,0x40,0x47,0x40,0x47,0x7c,0x40,0x4f,0x40,0x41,0x7e,0x40,0x4e,0x40,
	0x40,0x7f,0x40,0x5e,0x40,0x40,0x5f,0x40,0x5e,0x40,0x40,0x4f,0x40,0x5e,0x40,0x40,
	0x4f,0x40,0x5e,0x40,0x40,0x4f,0x40,0x5e,0x40,0x40,0x4e,0x40,0x4f,0x40,0x40,0x4e,
	0x40,0x47,0x60,0x40,0x5c,0x40,0x43,0x70,0x40,0x78,0x40,0x40,0x7c,0x43,0x60,0x40,
	0x40,0x4f,0x7e,0x40,0x40
};

unsigned char number_9[170]=
{
    0x40,0x40,0x40,0x40,0x40,
	0x40,0x4f,0x7c,0x40,0x40,0x40,0x78,0x47,0x40,0x40,0x41,0x70,0x43,0x60,0x40,0x43,
	0x60,0x41,0x70,0x40,0x47,0x40,0x40,0x78,0x40,0x4f,0x40,0x40,0x5c,0x40,0x4e,0x40,
	0x40,0x5c,0x40,0x4e,0x40,0x40,0x5e,0x40,0x5e,0x40,0x40,0x4e,0x40,0x5e,0x40,0x40,
	0x4f,0x40,0x5e,0x40,0x40,0x4f,0x40,0x5e,0x40,0x40,0x4f,0x40,0x5e,0x40,0x40,0x4f,
	0x40,0x5f,0x40,0x40,0x4f,0x40,0x4f,0x40,0x40,0x4f,0x40,0x4f,0x40,0x40,0x4f,0x40,
	0x4f,0x60,0x40,0x4f,0x40,0x47,0x70,0x40,0x7e,0x40,0x43,0x7c,0x43,0x7e,0x40,0x41,
	0x7f,0x7f,0x5e,0x40,0x40,0x4f,0x78,0x5c,0x40,0x40,0x40,0x40,0x7c,0x40,0x40,0x40,
	0x40,0x78,0x40,0x40,0x40,0x41,0x78,0x40,0x40,0x40,0x43,0x70,0x40,0x40,0x40,0x43,
	0x60,0x40,0x40,0x40,0x47,0x40,0x40,0x40,0x40,0x5e,0x40,0x40,0x40,0x40,0x7c,0x40,
	0x40,0x40,0x43,0x70,0x40,0x40,0x40,0x4f,0x40,0x40,0x40,0x41,0x7c,0x40,0x40,0x40,
	0x4f,0x40,0x40,0x40,0x40
};

void display_number(unsigned char x, unsigned char y, unsigned char number[]) {

    int pos=0;
    unsigned char i,j=0;

    for (j=0;j<34;j++) {
        for (i=0;i<5;i++) {
            POKE(0xA000+i+j*40+x+y*40, number[pos]);
            pos++;
        }
    }

}

void display_clear(unsigned char x, unsigned char y) {

    int pos=0;
    unsigned char i,j=0;

    for (j=0;j<34;j++) {
        for (i=0;i<5;i++) {
            POKE(0xA000+i+j*40+x+y*40,0x40);
            pos++;
        }
    }

}

void display_bandeau(unsigned char x, unsigned char y) {

    int pos=0;
    unsigned char i,j=0;

    for (j=0;j<62;j++) {
        for (i=0;i<40;i++) {
            POKE(0xA000+i+j*40+x+y*40,bandeau[pos]);
            pos++;
        }
    }

}


void calcul() {

}

unsigned char random(unsigned char mod)
{
    return PEEK(0x309)%mod;
}

void display_one_digit(unsigned char x, unsigned char y, unsigned char digit)
{
    switch (digit) {
        case 0:
            display_number(x, y, number_0);
            break;
        case 1:
            display_number(x, y, number_1);
            break;
        case 2:
            display_number(x, y, number_2);
            break;
        case 3:
            display_number(x, y, number_3);
            break;
        case 4:
            display_number(x, y, number_4);
            break;
        case 5:
            display_number(x, y, number_5);
            break;
        case 6:
            display_number(x, y, number_6);
            break;
        case 7:
            display_number(x, y, number_7);
            break;
        case 8:
            display_number(x, y, number_8);
            break;
        case 9:
            display_number(x, y, number_9);
            break;
    }
}


void blink(unsigned char color) {
    unsigned char i;
    unsigned char loop = 0;

    for (loop=0;loop<10;loop++) {
        for (i=0;i<34;i++)
            POKE(0xA000+i*40,color);
        for (i=0;i<34;i++)
            POKE(0xA000+i*40,0x10);
    }
}



unsigned char add_and_one_digit(unsigned char modulo) {
    unsigned char digit,digit2,adigit=0,adigit2=0;
    unsigned char answer;
    unsigned char mychar;
    unsigned char pos_input = 0;

    display_clear(22 + pos_input * 5, 0);
    display_clear(27 + pos_input * 5, 0);

    digit = random(modulo);
    display_one_digit(1,0,digit);

    display_number(6, 0, plus);

    digit2 = random(modulo);
    display_one_digit(11,0,digit2);

    display_number(17, 0, egal);


    while (1) {
        mychar = cgetc();
        if (mychar == 127 && pos_input != 0) {
            pos_input --;
            display_clear(22 + pos_input*5, 0);
        };

        if (mychar == 13) {
            if (pos_input == 1 && digit + digit2 == adigit ) {
                //zap();
                blink(0x12);
                return 1;
            }
            if (pos_input == 2 && digit + digit2 == adigit*10 +  adigit2 ) {
                //zap();
                blink(0x12);
                return 1;
            }
            blink(0x11);
            return 0;
        }

        if (mychar == 27) break;
        if (mychar < 58 && mychar >= 48) {
            if (pos_input==0) adigit = mychar - 48;
            if (pos_input==1) adigit2 = mychar - 48;
            if (pos_input!=2)
                display_one_digit(22 + pos_input*5, 0, mychar - 48);
            else
                oups();
            if (pos_input==0 || pos_input == 1)
                pos_input ++;
        }
    }
    //display_one_digit(15, 0, unsigned char digit);

}

void display_level_up() {
    tgi_clear();
    display_bandeau(0, 5);
    display_one_digit(19, 22, user.level);
}

main() {
    unsigned char  i = 0;
    unsigned int score = 0;
    unsigned char key;
    unsigned char right_answer = 0;




    clrscr();
    tgi_install(tgi_static_stddrv); //Include the driver statically instead of loading it.
    tgi_init(); //Set up the default palette and clear the screen.

    // display_string (6, 0, "JE RENTRE");
    // display_string (10, 50, "EN");
    // display_string (6, 100, "PRIMAIRE");
    // key = cgetc();
    menu();
    key = cgetc();

    //display_pic(0, 0, 40, 62, bandeau);

    //alphabet();
    //display_string (0, 0, "SIX");

    //display_letter(0,0,'A');
    cgetc();
    // display_bandeau(0, 5);
    // display_number(20, 20, number_0);

    init_user();
    // display_level_up();

    tgi_clear();

    while (1) {
        for (i=0;i<level_number_tests[user.level];i++) {
            right_answer += add_and_one_digit(level_mod[user.level]);
            if (right_answer == level_number_tests[user.level]) {
                user.level ++;
                display_level_up();
                //val = cgetc();
                //if (val == 27) break;
                tgi_clear();
                right_answer = 0;
            }
        }
        //if (val == 27) break;
    }

    tgi_done();

}