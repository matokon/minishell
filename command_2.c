
#include "mini.h"

void	add_heredock(t_cmd *command, t_token *delim)
{
	t_heredoc *new_hrdc;

	new_hrdc = (t_heredoc *)malloc(sizeof(t_heredoc) * (command->heredoc_cnt + 1));
	if (!new_hrdc)
		return ;
	if (command->heredoc_cnt > 0)
		ft_memcpy(new_hrdc, command->heredocs, sizeof(t_heredoc) * command->heredoc_cnt);
	new_hrdc[command->heredoc_cnt].delim = ft_strdup(delim->next);
	if (/*jesli jest w pojedynczysz cudzyslowach*/)
		new_hrdc[command->heredoc_cnt].expand = 0; // tu chodzi o jakies quoty to nw co z tym jeszcze zrobic
	else if (/*jesli jest w "" cudzyslowach*/)
		new_hrdc[command->heredoc_cnt].expand = 1;
	while (1)
	{
		new_hrdc[command->heredoc_cnt].tmp_path;
	}
	free(command->heredocs);//tu chyba potrzebna funkcja do zwolnienia
	command->heredocs = new_hrdc;
	command->heredoc_cnt++;
}