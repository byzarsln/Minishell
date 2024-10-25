/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyarsla <beyarsla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:06:47 by ayirmili          #+#    #+#             */
/*   Updated: 2024/10/25 18:58:47 by beyarsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "lib/libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
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

# define PROMPT "\001\e[45m\002>>> \001\e[0m\e[33m\002 Minishell 🤠>$ \001\e[0m\002"

# define SUCCESS 1
# define FAILURE 0

# define DEFAULT 10
# define SQUOTE 11
# define DQUOTE 12

# define SPACES 13
# define WORD 14
# define VAR 15
# define PIPE 16 // |
# define INPUT 17 // <
# define TRUNC 18 // >
# define HEREDOC 19 // <<
# define APPEND 20 // >>
# define END 21 // \0

extern int g_last_exit_code; // global değişken

typedef struct s_token
{
	char				*value_backup;
	char				*value;
	int					type;
	int					status;
	bool				var_exists;
	bool				join;
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
void    				status_error(int status);
void					free_data(t_data *data, bool clear_history);
void					free_pointr(void *pointr);
void					free_mult_str(char **str);
void					free_str_tab(char **tab);
void					lst_clear_token(t_token **token_lst, void (*del)(void *));
void					lst_delone_token(t_token *token_node, void (*del)(void *));

// initialize functions
int						check_init_data(t_data *data, char **env);
int						init_work_direc(t_data *data);
int						env_find_index(char **env, char *var);
char					*env_find_value(char **env, char *var);

// parser functions
char					*search_env_var(t_data *data, char *var);
char					*identify_var(char *str);
int						parse_input(t_data *data);
int						tokenizer(t_data *data, char *user_input);
int						save_word(t_token **token_lst, char *user_input, int index, int start);
int						save_separator(t_token **token_lst, char *user_input, int index, int type);
int						check_var(t_token **token_lst);
int						var_length(char *str);
int						var_exists(t_data *data, char *var);
int						handle_replace_var(t_token **token_node, char *var_value, int index);
void					handle_dollar(t_data *data, t_token **token_lst);
void					change_status_to_quote(t_token **token_node, int *i);
void					lst_add_back_token(t_token **token_lst, t_token *created_token);
int						handle_quotes(t_data *data);
int						if_quotes_and_default(t_token **token_node, int i);
int						change_back_to_default(t_token **token_node, int *i);
t_token					*lst_new_token(char *value, char *value_backup, int type, int status);

//commands functions
t_command				*lst_last_cmd(t_command *cmd);
void					split_var_cmd_token(t_command *last_cmd, char *cmd_str);
void					create_commands(t_data *data, t_token *token);
bool					contains_space(char *str);
int						fill_args(t_token **token_node, t_command *last_cmd);
int						create_args_echo_mode(t_token **token_node, t_command *last_cmd);
int						add_args_echo_mode(t_token **token_node, t_command *last_cmd);
char					**copy_in_new_tab(int len, char **new_tab, t_command *last_cmd, t_token *tmp);
int						add_args_default_mode(t_token **token_node, t_command *last_cmd);
int						create_args_default_mode(t_token **token_node, t_command *last_cmd);
char					*join_vars(t_token **token_node);

#endif