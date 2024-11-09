/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyarsla <beyarsla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:06:47 by ayirmili          #+#    #+#             */
/*   Updated: 2024/11/08 14:52:56 by beyarsla         ###   ########.fr       */
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

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

# include <limits.h>

# define HEREDOC_NAME "/tmp/.minishell_heredoc_"
# define PROMPT "\001\e[45m\002>>> \001\e[0m\e[33m\002 \
Minishell >$ \001\e[0m\002"

# define SUCCESS 1
# define FAILURE 0

# define IN_CAT 2

# define DEFAULT 10
# define SQUOTE 11
# define DQUOTE 12

# define SPACES 13
# define WORD 14
# define VAR 15
# define PIPE 16
# define INPUT 17
# define TRUNC 18
# define HEREDOC 19
# define APPEND 20
# define END 21  

# define DLLR_IN_DQUOTE 22
# define DLLR_IN_SQUOTE 23

# define COMMAND_NOT_FOUND 127
# define CMD_NOT_EXECUTABLE 126

int						g_global_signal;

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
	bool				open_check;
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
	char				**export_env;
	char				*work_direc;
	char				*old_work_direc;
	pid_t				pid;
}						t_data;

void					set_signals(void);
int						main_signal_control(int exit_code);

void					free_tmp(void *tmp);
void					exit_shell(t_data *data, int exno);
void					status_error(int status);
void					free_data(t_data *data, bool clear_history);
void					free_pointr(void *pointr);
void					free_mult_str(char **str);
void					free_str_tab(char **tab);
void					free_io(t_io_fds *io);
void					free_key_export(char **key_value);
void					lst_clear_token(t_token **token_lst,
							void (*del)(void *));
void					lst_delone_token(t_token *token_node,
							void (*del)(void *));

int						check_init_data(t_data *data, char **env);
int						init_work_direc(t_data *data);
int						env_find_index(char **env, char *var);
char					*env_find_value(char **env, char *var);

char					*search_env_var(t_data *data, char *var);
char					*identify_var(char *str);
int						parse_input(t_data *data, int exit_code);
int						tokenizer(t_data *data, char *user_input);
int						save_word(t_token **token_lst, char *user_input,
							int index, int start);
int						save_separator(t_token **token_lst, char *user_input,
							int index, int type);
int						check_var(t_token **token_lst);
int						var_length(char *str);
int						var_exists(t_data *data, char *var);
int						handle_replace_var(t_token **token_node,
							char *var_value, int index);
void					handle_dollar(t_data *data, t_token **token_lst,
							int exit_code);
void					change_status_to_quote(t_token **token_node, int *i);
void					lst_add_back_token(t_token **token_lst,
							t_token *created_token);
int						handle_quotes(t_data *data, int exit_code);
int						if_quotes_and_default(t_token **token_node, int i);
int						change_back_to_default(t_token **token_node, int *i);
t_token					*lst_new_token(char *value, char *value_backup,
							int type, int status);
int						remove_quotes(t_token **token_node);
char					*recover_val(t_token *token, char *str, t_data *data,
							int exit_code);

t_command				*lst_last_cmd(t_command *cmd);
t_command				*lst_new_cmd(bool value);
void					split_var_cmd_token(t_command *last_cmd, char *cmd_str);
void					create_commands(t_data *data, t_token *token,
							int exit_code);
bool					contains_space(char *str);
int						fill_args(t_token **token_node, t_command *last_cmd);
int						create_args_echo_mode(t_token **token_node,
							t_command *last_cmd);
int						add_args_echo_mode(t_token **token_node,
							t_command *last_cmd);
char					**copy_in_new_tab(int len, char **new_tab,
							t_command *last_cmd, t_token *tmp);
int						add_args_default_mode(t_token **token_node,
							t_command *last_cmd);
int						create_args_default_mode(t_token **token_node,
							t_command *last_cmd);
int						remove_old_file_ref(t_io_fds *io, bool infile);
int						is_next_char_a_sep(char c);
int						var_between_quotes(char *str, int i);
int						evaluate_heredoc_line(t_data *data, char **line,
							bool *return_status, int exit_code);
char					*join_vars(t_token **token_node);
char					*erase_and_replace(t_token **token_list, char *str,
							char *var_value, int index);
char					*make_str_from_tab(char **tab);
void					lst_add_back_cmd(t_command **alst, t_command *new_node);
void					parse_cmd_input(t_command **last_cmd,
							t_token **token_lst);
void					parse_cmd_trunc(t_command **last_cmd,
							t_token **token_lst);
void					open_outfile_trunc(t_io_fds *io, char *file,
							char *var_filename);
void					parse_cmd_heredoc(t_data *data, t_command **last_cmd,
							t_token **token_lst, int exit_code);
void					parse_cmd_append(t_command **last_cmd,
							t_token **token_lst);
void					parse_cmd_pipe(t_command **cmd, t_token **token_lst);
bool					heredoc_parent_process(int pid);
bool					heredoc_child_process(t_data *data, int fd,
							int exit_code);
int						is_any_quotes(char *str);
int						handle_heredoc_append(t_token **token_lst,
							char *user_input, int index, int type);

int						execute(t_data *data, int exit_code);
int						execute_builtin(t_data *data, t_command *cmd,
							int exit_code);
bool					restore_io(t_io_fds *io);
int						create_children(t_data *data, int exit_code);
bool					check_infile_outfile(t_io_fds *io);
bool					redirect_io(t_io_fds *io);
int						execute_local_bin(t_data *data, t_command *cmd);
int						get_env_var_index(char **env, char *var);
bool					cmd_is_dir(char *cmd);
bool					set_pipe_fds(t_command *cmds, t_command *c);
int						get_children(t_data *data);
char					*find_valid_cmd_path(char *cmd, char **paths);
char					*get_cmd_path(t_data *data, char *name);
void					close_pipe_fds(t_command *cmds, t_command *skip_cmd);
void					close_fds(t_command *cmds, bool close_backups);
char					*get_env_var_value(char **env, char *var);

int						builtin_cd(t_data *data, char **args);
int						is_space(int c);
int						chdir_errno_mod(char *path);
int						env_counter(char **env);
char					**reallocate_env(int size, char **data_env);
int						builtin_echo(t_data *data, char **args);
int						builtin_env(t_data *data, char **args);
int						write_export(t_data *data, char **args);
int						builtin_export(t_data *data, char **args);
int						buildin_pwd(t_data *data, char **args);
int						builtin_unset(t_data *data, char **args);
int						builtin_exit(t_data *data, char **args, int exit_code);
int						set_env_var(t_data *data, char *key, char *env_value);
int						set_export_var(t_data *data, char *key, char *env_value,
							bool control);
bool					is_valid_env_key(char *var);
int						handle_export(t_data *data, char *args);
char					**get_key_value_pair(char *arg);
int						update_or_add_export_env(t_data *data, char *key,
							char *tmp, int index);
char					*create_tmp_value(char *env_value, bool control);

void					init_io(t_command *cmd);
void					open_infile(t_io_fds *io, char *file,
							char *original_filename);

int						errmsg_cmd(char *command, char *detail,
							char *error_message, int error_nb);

#endif