#include "mini.h"

//static void free_strv(char **v)
//{
//	int i;

//	if (!v)
//		return;
//	i = 0;
//	while (v[i])
//		free(v[i++]);
//	free(v);
//}

static void	one_cmd_free(t_cmd *cmd)// TODO NORMINETTE mokon
{
	int i;

	if (!cmd)
		return ;
	if (cmd->argv != NULL)
	{
		i = 0;
		while (cmd->argv[i])
		{
			free(cmd->argv[i]);
			i++;
		}
		free(cmd->argv);
	}
	if (cmd->infile)
		free(cmd->infile);
	if (cmd->outs)
	{
		i = -1;
		while (++i < cmd->outs_len)
		{
			if (cmd->outs[i].path)
				free(cmd->outs[i].path);
		}
		free(cmd->outs);
	}
	if (cmd->heredocs)
		free_hrdc(cmd);
}

void cmds_free(t_shell *shell)
{
    if (!shell || !shell->cmds)
        return;

    t_cmd *cur = shell->cmds;
    while (cur) {
        t_cmd *next = cur->next;
        one_cmd_free(cur);
        free(cur);
        cur = next;
    }
    shell->cmds = NULL;
    shell->count_cmds = 0;
}



void	free_hrdc(t_cmd *command)
{
	int	i;

	i = command->heredoc_cnt;
	while (i--)
	{
		free(command->heredocs[i].delim);
		free(command->heredocs[i].tmp_path);
	}
	free(command->heredocs);
	command->heredocs = NULL;
	command->heredoc_cnt = 0;
}

void	free_split(char **tab)
{
	int i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}