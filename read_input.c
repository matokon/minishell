#include "mini.h"

static int parse_and_execute(char *input, t_shell *shell)
{
	char  **arr;
	t_token *list;

	if (!input || !*input)
		return (0);
	cmds_free(shell);
    shell->cmds = NULL;
    shell->count_cmds = 0;
	input = deal_with_quotes(input, *shell);
	arr = split_input_to_tokens(input);
	list = token_list(arr);
	shell->cmds = adding_command(list, shell);
	if (!shell->cmds || shell->count_cmds == 0 || !(&shell->cmds[0]))
		return (cmds_free(shell), 0); //zwalnianie pamieci w przypadku bledu
	if (shell->count_cmds == 1 && shell->cmds->argv && is_builtin(shell->cmds->argv[0]))
		{
			int st = run_single_builtin(shell);//uruchamiane bez forka na rodzicu
			shell->last_status = st;
			return st;
		}
		else
		{
			return run_pipeline_or_external(shell);
		}
	return (0);
}

int read_input(t_shell *shell)
{
	char *input;

	set_path(shell);
	while(true)
	{
		input = readline("\033[38;5;198mminishell$ \033[0m");
		if (!input)
		{
			fprintf(stderr, "Error: readline error!\n");
			cmds_free(shell);
		exit(1);
		}
		if (*input)
		{
		add_history(input);
		parse_and_execute(input, shell);
		}
	}
	return (0);
}