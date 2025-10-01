#include "mini.h"

static int parse_and_execute(char *input, t_shell *shell)
{
	t_token *list;

	if (!input || !*input)
		return (0);
	cmds_free(shell);
	input = deal_with_quotes(input, shell);
	if (!input)
		return (shell->last_status = 130);
	list = lexer(input, shell);
	shell->cmds = adding_command(list, shell);
	if (!shell->cmds || shell->count_cmds == 0 || !(&shell->cmds[0]))
		return (cmds_free(shell), 0);
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
			fprintf(stderr, "Goodbye! ;*\n");
			cmds_free(shell);
			free_env_list(shell->env);
			free(shell);
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
