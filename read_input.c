#include "mini.h"

static int parse_and_execute(char *input, t_shell shell)
{
    if (!input || !*input)
		return (0);
    input = deal_with_quotes(input, &shell);
    split_input_to_tokens(input);
    //tutaj bedzie wywolana funckja parsujaca input do struktury t_cmd
    if (!shell->cmds || shell->count_cmds == 0 || !shell->cmds[0])
      return (cmds_free(shell), 0);
}

int read_input(t_shell *shell)
{
    char *input;

    set_path(shell);
    while(true)
    {
        input = readline("\033[1;32mminishell$ \033[0m");
        if (!input)
        {
        	fprintf(stderr, "Error: readline error!\n");
          cmds_free(shell);
          exit(1);
        }
        if (*input)
        {
          add_history(input);
          parse_and_execute(input, *shell);
        }
    }
    return (0);
}