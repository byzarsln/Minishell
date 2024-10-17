/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayirmili <ayirmili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:06:47 by ayirmili          #+#    #+#             */
/*   Updated: 2024/10/17 14:15:01 by ayirmili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "lib/libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

// linux ve MAC te bir dosya yolunun max uzunluğu
# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

# define PROMPT "\e[33m\002 Minishell 🤠>$ \001\e[0m\002"

# define SUCCESS 0
# define FAILURE 1

extern int	g_last_exit_code; // global değişken

typedef struct s_token
{
	char				*value;
	int					type;
	struct s_token		*prev;
	struct s_token		*next;
}						t_token;

typedef struct s_io_fds
{
	char				*infile;
	char				*outfile;
	char				*heredoc_delimiter;
	bool				heredoc_quotes;
	int					fd_in;
	int					fd_out;
	int					stdin_backup;
	int					stdout_backup;
}						t_io_fds;

typedef struct s_command
{
	char				*command;
	char				*path;
	char				**args;
	bool				pipe_output;
	int					*pipe_fd;
	t_io_fds			*io_fds;
	struct s_command	*next;
	struct s_command	*prev;
}						t_command;

typedef struct s_data
{
	t_token				*token;
	t_command			*cmd;
	char				*user_input;
	char				**env;
	char				*work_direc;
	char				*old_work_direc;
	pid_t				pid;
}						t_data;

// signals functions
void					set_signals(void);

// free.c
void					free_tmp(void *tmp);
void					exit_shell(t_data *data, int exno);

// initialize functions
int						check_init_data(t_data *data, char **env);
int						init_work_direc(t_data *data);
int						env_find_index(char **env, char *var);
char					*env_find_value(char **env, char *var);

#endif