#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MAX_PIECES 8
#define MAX_CODE_LEN 4

#ifndef STRUCT_H
#define STRUCT_H

typedef struct game_info {
    char pieces[MAX_PIECES + 1];
    char code[MAX_CODE_LEN + 1];
    int tries;
    int c_flag;
    int input_failure;
} info;

#endif

#ifndef MY_MASTERMIND_H
#define MY_MASTERMIND_H

info *init_info(info*);
void print_info(info*);
info *input_handler(info*, int, char**);
info *generate_code(info*);
int valid_code(char*);
int valid_pieces(char*);
void print_game_start(info*);
void mastermind(info*);

#endif