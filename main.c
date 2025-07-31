#include "mini.h"

int main(int argc, char **argv, char **env)
{
    t_shell				*shell;
    (void)argv;

    if(argc != 1)
        return (1);
    if (env == NULL)
	{
		error_exit("Error: wrong env value!\n");
	}
    shell = safe_malloc(sizeof(t_shell));

    
    return (0);
}