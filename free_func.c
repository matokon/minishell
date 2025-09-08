#include "mini.h"

static void free_strv(char **v)
{
	int i;

	if (!v)
		return;
	i = 0;
	while (v[i])
		free(v[i++]);
	free(v);
}

static void	one_cmd_free(t_cmd *cmd)// TODO NORMINETTE mokon
{
	int i;

	if (!cmd)
		return;

	free_strv(cmd->argv);
	cmd->argv = NULL;
	cmd->argc = 0;

	if (cmd->infile)
	{
		free(cmd->infile);
		cmd->infile = NULL;
	}

	if (cmd->outs)
	{
		i = 0;
		while (i < cmd->outs_len)
		{
			free(cmd->outs[i].path);
			i++;
		}
		free(cmd->outs);
		cmd->outs = NULL;
		cmd->outs_len = 0;
	}

	if (cmd->heredocs)
	{
		i = 0;
		while (i < cmd->heredoc_cnt)
		{
			free(cmd->heredocs[i].delim);
			free(cmd->heredocs[i].tmp_path);
			i++;
		}
		free(cmd->heredocs);
		cmd->heredocs = NULL;
		cmd->heredoc_cnt = 0;
	}
}

void	cmds_free(t_shell *shell)
{
	int i;

	if (!shell || !shell->cmds)
		return;
	i = 0;
	while (i < shell->count_cmds)
	{
		/* shell->cmds to tablica **struktur**, więc przekazujemy adres */
		one_cmd_free(&shell->cmds[i]);
		i++;
	}
	free(shell->cmds);          /* zwalniamy samą tablicę */
	shell->cmds = NULL;
	shell->count_cmds = 0;
}
