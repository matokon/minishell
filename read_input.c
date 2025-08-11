#include "mini.h"

static int parse_and_execute(char *input, t_shell shell)
{
    if (!input || !*input)
		return (0);
    input = deal_with_quotes(input, &shell);

}

int read_input(t_shell *shell)
{
    //int exit_status; jeszcze nie potrzebne ale bedzie
    char *input;

    set_path(shell);
    while(true)
    {
        input = readline("\033[1;32mminishell$ \033[0m");
        if (!input)
        {
        	fprintf(stderr, "Error: readline error!\n");
          exit(shell->exit_status);
          //zwolnienie wartosci zrobie kiedys moze :)
        }
        if (*input)
        {
          add_history(input); // obsluga zapamietywania wpisanych komend(wbudowana funckja)
          parse_and_execute(input, *shell);
        }
    }
    return (0);
}