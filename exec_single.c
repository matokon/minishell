#include "mini.h"

static int	call_builtin(t_shell *sh, char **argv)
{
	if (ft_strcmp(argv[0], "cd") == 0)
		return (ft_cd(sh, argv));
	if (ft_strcmp(argv[0], "pwd") == 0)
		return (ft_pwd(sh, argv));
	if (ft_strcmp(argv[0], "echo") == 0)
		return (ft_echo(sh, argv));
	if (ft_strcmp(argv[0], "export") == 0)
		return (ft_export(sh, argv));
	if (ft_strcmp(argv[0], "unset") == 0)
		return (ft_unset(sh, argv));
	if (ft_strcmp(argv[0], "env") == 0)
		return (ft_env(sh, argv));
	if (ft_strcmp(argv[0], "exit") == 0)
		return (ft_exit(sh, argv));
	return (1);
}

int run_single_builtin(t_shell *shell)
{
    t_cmd	*cmd;
	// int		sav_in;
	// int		sav_out;
	int		status;

	cmd = shell->cmds;
	// sav_in = -1;
	// sav_out = -1;
    // redirekcje doczytaj ~okon TODO
    status = exec_buildin(shell, cmd->argv);
    //TODOprzywrócenie poprzednie STDIN_FILENO i STDOUT_FILENO, które były zapisane na początku
    shell->last_status = status;
    return status;
}

int	exec_builtin(t_shell *sh, char **argv)
{
	if (!argv || !argv[0])
		return (0);
	return (call_builtin(sh, argv));
}
