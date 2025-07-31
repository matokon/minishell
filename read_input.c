#include "mini.h"

int read_input(t_shell *shell)
{
    int exit_status;
    char *input;

    set_path(shell); // ustawia sciezke do structa
    while(true)
    {
        input = readline("\033[1;32mminishell$ \033[0m");
        if (!input)
		{
            fprintf(stderr, "Error: readline error!\n");
            //zwolnienie wartosci zrobie jutro moze :)
		}
		if (*input)
		{
            // tu bedzie caly syf sie dzial nie chce o tym myslec nawet X(
		}
    }
    return (0);
}