#include "../include/list.h"

info *init_info(info *info)
{
    strcpy(info->pieces, "01234567");
    info->pieces[8] = '\0';

    strcpy(info->code, "1234"); //default code
    info->code[4] = '\0';

    info->tries = 10;
    info->c_flag = 0;
    info->input_failure = 0;

    return info;
}

void print_info(info *info)
{
    printf("Code: %s\n", info->code);
    printf("Pieces: %s\n", info->pieces);
    printf("Tries: %d\n", info->tries);
    printf("c flag: %d\n", info->c_flag);
    printf("input failure: %d\n", info->input_failure);
}

info *input_handler(info *info, int argc, char **argv)
{
    int i = 0;
    while (i < argc)
    {
        if (strcmp(argv[i], "-p") == 0)
        {
            if (valid_pieces(argv[i + 1]) == 0) //check valid unique number of 8 pieces
            {
                int len = strlen(argv[i + 1]);

                for (int j = 0; j < len; j++)
                {
                    info->pieces[j] = argv[i + 1][j]; //overwrite the default pieces if valid
                }
            }
            else
            {
                printf("PIECES input format: 8 UNIQUE NUMBERS 0-9 '-p XXXXXXXX', RE-INPUT GAME PARAMETERS OR LEAVE TO DEFAULT\n");
                info->input_failure++; //if not valid code, flag input failure to exit program after!
            }
        }

        if (strcmp(argv[i], "-c") == 0) //find a user input secret code on execution
        {
            info->c_flag++;
            if (valid_code(argv[i + 1]) == 0) //check valid unique number code of 4 digits entered
            {
                int len = strlen(argv[i + 1]);
                for (int j = 0; j < len; j++)
                {
                    info->code[j] = argv[i + 1][j]; //overwrite the default code if valid
                }
            }
            else
            {
                printf("CODE input format: 4 UNIQUE NUMBERS FROM USERS PIECES OR 0-7 IF DEFAULT PIECES: '-c XXXX', RE-INPUT GAME PARAMETERS OR LEAVE TO DEFAULT\n");
                info->input_failure++; //if not valid code, flag input failure to exit program after!
            }
        }
        if (strcmp(argv[i], "-t") == 0) //find input of user attempts parameter on execution
        {
            if (atoi(argv[i + 1]) > 0 && atoi(argv[i + 1]) < 100)
            {
                info->tries = atoi(argv[i + 1]);
            }
            else
            {
                printf("TRIES input format: NUMBER 0-99 '-t XX', RE-INPUT GAME PARAMETERS OR LEAVE TO DEFAULT\n");
                info->input_failure++; //if not valid code, flag input failure to exit program after!
            }
        }
        i++;
    }
    return info;
}

info *generate_code(info *info)
{
    int index[4];
    srand(time(0));
    int r = rand() % 8;
    index[0] = r; //first random number
    r = rand() % 8;    //generate next random and check

    while (r == index[0])
        r = rand() % 8;
    index[1] = r;
    
    while (r == index[0] || r == index[1])
        r = rand() % 8;
    index[2] = r;

    while (r == index[0] || r == index[1] || r == index[2])
        r = rand() % 8;
    index[3] = r;

    for (int i = 0; i < 4; i++)
    {
        printf("%d ", index[i]);
        info->code[i] = info->pieces[index[i]];
    }
    return info;
}

int valid_code(char *guess)
{
    int i = 0;
    int j = 0;
    int count = 0;

    while (guess[i] != '\0')
    {
        if (guess[i] >= '0' && guess[i] <= '9')
            i++;
        else
        {
            count++;
            i++;
        }
    }
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (guess[i] == guess[j])
                count++;
        }
    }
    if ((count == 4) && (strlen(guess) == 4))
        return 0;
    else
        return 1;
}

//Function to validate if user input pieces string is correct length and of unique numbers.
int valid_pieces(char *pieces)
{
    int i = 0, j = 0, count = 0;

    while (pieces[i] != '\0')
    {
        if (pieces[i] >= '0' && pieces[i] <= '9')
            i++;
        else
        {
            count++;
            i++;
        }
    }

    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 8; j++)
        {
            if (pieces[i] == pieces[j])
                count++;
        }
    }
    if ((count == 8) && (strlen(pieces) == 8))
        return 0;
    else
        return 1;
}

void print_game_start(info *info)
{
    //printf("Secret Code: %s\n", info->code);
    //outline the game and its parameters, exit option, and start attempts.
    printf("-------------\n");
    printf("Can You Guess The SECRET CODE: XXXX\n");
    printf("-------------\n");
    if (info->c_flag == 0)
        printf("Secret Code: RANDOM\n"); //tell player its random code
    else
        printf("Secret Code: USER INPUT\n"); //tell player its user input code
    printf("Pieces: %s\n", info->pieces);
    printf("Attempts: %d\n", info->tries);
    printf("Enter 'q' to quit at any point!\n");
    printf("-------------\n");
    printf("Attempt 1:\n");
}

void mastermind(info *info)
{
    char guess[5];
    int count = 1, i = 0, j = 0;
    int well_placed;
    int mis_placed;

    while (1) //infinite game loop until broken
    {
        if (count <= info->tries) //while there are attempts remaining
        {
            read(0, guess, sizeof(guess)); //take user input guesses
            guess[4] = '\0';               //null terminate user input string
            //escape key (q)uit to leave game
            if (guess[0] == 'q')
                return;

            well_placed = 0;
            mis_placed = 0;

            if (valid_code(guess) != 0)
                printf("Wrong Input!\n");
            else
            {
                for (i = 0; i < 4; i++)
                {
                    for (j = 0; j < 4; j++)
                    {
                        if (guess[i] == info->code[j] && i == j)      //number is matched and in place
                            well_placed++;                            //increment well_placed pieces when occur
                        else if (guess[i] == info->code[j] && i != j) //number is matched but not in place
                            mis_placed++;                             //increment misPlaced pieces when occur
                    }
                }
                if (well_placed == 4) //if correct guess, winner message & exit out.
                {
                    printf("Congratulations! YOU WIN!\n");
                    return;
                }
                else //else increment tries, give hints and continue game.
                {
                    count++;
                    printf("Well placed pieces: %d\n", well_placed);
                    printf("Misplaced pieces: %d\n", mis_placed);
                }
                printf("-------------\n");
                printf("Attempt %d:\n", count);
            }
        }
        else //no tries remaining, display failure and exit!
        {
            printf("You have no tries left, Loser!!\n");
            return;
        }
    }
    return;
}