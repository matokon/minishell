# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>
# include <errno.h>
# include <sys/stat.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <limits.h>
# include <signal.h>
# include "libft/libft.h"

typedef enum e_token_type //typ tokena
{
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_REDIRECT_IN,
    TOKEN_REDIRECT_OUT,
    TOKEN_REDIRECT_APPEND,
    TOKEN_HEREDOC,
} t_token_type;

typedef struct s_token //reprezentacja jednego tokena
{
    char *value;
    t_token_type type;
    struct s_token *next;
} t_token;

typedef struct s_cmd // reprezentacja pojedynczej komendy
{
    char **argv; // np. ["ls", "-la", "NULL"]
    char *infile; // < input.txt
    char *outfile; // > output.txt
    int append; // 1 jezeli >>, 0 jezeli >
    int heredoc; // 1 jezeli <<
    int in_fd; // fd do odczytu
    int out_fd; // fd do zapisu
    struct s_cmd *next; // jezeli pipe: ls | grep txt
} t_cmd;

typedef struct s_env // zmienne srodowiskowe
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env; 

typedef struct s_shell // stan calego shella
{
    char *path; // sciezka
    t_env *env; // lista zmiennych srodowiskowych
    t_cmd *cmds; // lista komend (po parserze)
    char *line; // linia wejsciowa
    int exit_status;
} t_shell;

void	*safe_malloc(size_t bytes);
