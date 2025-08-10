/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochmurzy <ochmurzy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:38:42 by ochmurzy          #+#    #+#             */
/*   Updated: 2025/08/10 21:54:53 by ochmurzy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

# define _XOPEN_SOURCE 700
# include "libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum e_token_type // typ tokena
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_REDIRECT_APPEND,
	TOKEN_HEREDOC,
}				t_token_type;

typedef struct s_token // reprezentacja jednego tokena
{
	t_token_type type;
	char *value;
	struct s_token *next;
}				t_token;

typedef struct s_cmd // reprezentacja pojedynczej komendy
{
	char **argv;        // np. ["ls", "-la", "NULL"]
	char *infile;       // < input.txt
	char *outfile;      // > output.txt
	int append;         // 1 jezeli >>, 0 jezeli >
	int heredoc;        // 1 jezeli <<
	int in_fd;          // fd do odczytu
	int out_fd;         // fd do zapisu
	struct s_cmd *next; // jezeli pipe: ls | grep txt
}				t_cmd;

typedef struct s_env // zmienne srodowiskowe
{
	char *key;
	char *value;
	struct s_env *next;
}				t_env;

typedef struct s_shell // stan calego shella
{
	char *path;     // sciezka
	t_env *env;     // lista zmiennych srodowiskowych
	int count_cmds; // ilosc komend bedzie potrzebna do zwalniania pamieci
	t_cmd *cmds;    // lista komend (po parserze)
	char *line;     // linia wejsciowa
	int exit_status;
}				t_shell;

//****MAIN****
int				main(int argc, char **argv, char **env);

//****Environment_things****
void			create_list_env(t_env **stack, char **env);
void			split_env(t_env **stack, char **str);
void			*find_last(void *stack, size_t offset);
t_env			*find_env(t_env *env, const char *key);
void			update_env_val(t_env **env, const char *key,
					const char *new_val);
t_env			*add_new_env(t_env **env, const char *key, const char *val);
//****Input****
int				read_input(t_shell *shell);

//****Errors****
void			error_exit(const char *error);

//****Utils functions****
void			*safe_malloc(size_t bytes);

//****Input tokenization****
char			**split_input_to_tokens(char *input);
static int		len_of_input(char *input);
static void		add_spaces(char *input, char *parsed_input, int *i, int *j);
t_token			*token_list(char **tab_of_tokens);
t_token_type	type_def(char *token);

//****Init****
void			set_path(t_shell *shell);
void			value_init(t_shell *shell);

//****Signals****
void			signals_things(void);
void			sig_handler(int signal);

//****Utils****
void			*safe_malloc(size_t bytes);

//****Tests****
void			print_stack_all(const t_env *stack);

#endif