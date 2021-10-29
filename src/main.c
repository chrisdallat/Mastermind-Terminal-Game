#include "../include/list.h"

int main(int argc, char **argv)
{
    info *info = NULL;
    info = malloc(sizeof(info));
    info = init_info(info);
    info = input_handler(info, argc, argv);

    if (info->input_failure != 0) //Exit if user input invalid game parameters force to execute agaim
        return 1;
    if (info->c_flag == 0)
        info = generate_code(info);

    print_game_start(info);

    mastermind(info);

    return 0;

}