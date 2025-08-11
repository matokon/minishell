#include "mini.h"

static void one_cmd_free(t_cmd *cmd) // nie jest gotowe jezeli bedziemy dodawali cos do struktury t_cmd to tu tez trzeba
{
    int i;
    if(!cmd)
        return ;
    if(cmd->argv)
    {
        i = 0;
		while (cmd->argv[i])
			free(cmd->argv[i++]);
		free(cmd->argv);
    }
    if(cmd->infile)
        free(cmd->infile)
    if (cmd->outfile)
	{
		i = 0;
	    while (i < cmd->outfile)
		    free(cmd->outfile[i++]);
		free(cmd->outfile);
	}
}

void cmds_free(t_shell *shell)
{
    if(!shell || !shell->cmds)
        return ;
    int i;
    i =-1;
    while(++i < shell->count_cmds)
    {
        if (shell->cmds[i])
		{
			one_cmd_free(shell->cmds[i]);
			free(shell->cmds[i]);
		}
    }
    free(shell->cmds);
	shell->cmds = NULL;
	shell->count_cmds = 0;
}
// tu jakbys miala watpliwosci to nie jest double free, ogarnalem to
// one_cmd_free(shell->cmds[i]) – sprząta pola wewnątrz struktury t_cmd (nie zwalnia samej struktury).

// free(shell->cmds[i]) – zwalnia samą strukturę t_cmd (pojedynczy obiekt).

// free(shell->cmds) – zwalnia tablicę wskaźników (t_cmd **) trzymaną w shell.