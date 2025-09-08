#include "mini.h"

int apply_in_redir(t_cmd *cmd)
{
    if (cmd->in_fd >= 0)
    {
        int tmp = cmd->in_fd;
        if (dup2(tmp, STDIN_FILENO) < 0)
        {
            close(tmp);
            cmd->in_fd = -1;
            return (1);
        }
        close(tmp);
        cmd->in_fd = -1;
    }
    return (0);
}
int apply_out_redir(t_cmd *cmd)
{
    if (cmd->out_fd >= 0)
    {
        int tmp = cmd->out_fd;
        if (dup2(tmp, STDOUT_FILENO) < 0)
        {
            close(tmp);
            cmd->out_fd = -1;
            return (1);
        }
        close(tmp);
        cmd->out_fd = -1;
    }
    return (0);
}