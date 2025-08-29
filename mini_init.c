#include "mini.h"

void set_path(t_shell *shell)
{
    char *current_path;

    if (!shell)
		return ;
    current_path = getcwd(NULL, 0);// get_env_val("PWD", env);zamiencie getcwd na wlasna funkcje I NIE UZYWAJVIE GETENV ZEB DOSTAC PATH
    if (!current_path)
	{
		printf("Error: path problem!");
		shell->exit_status = 1;
        return ;
	}
    if (shell->path)
		free(shell->path);
    shell->path = ft_strdup(current_path);
    free(current_path);
    if (!shell->path)
	{
		free(current_path);
		shell->exit_status = 1;
		return ;
	}
    update_env_val(shell->env, "PWD", shell->path);
	shell->exit_status = 0;
}

void value_init(t_shell *shell)
{
    if (!shell)
        return;   
    shell->path = NULL;
    shell->last_status = 0; 
    shell->env = NULL;
    shell->count_cmds = 0;
    shell->cmds = NULL;
    shell->line = NULL;
    shell->exit_status = 0;
    signals_things();
}
