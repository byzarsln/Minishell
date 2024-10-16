/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyza <beyza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:06:47 by ayirmili          #+#    #+#             */
/*   Updated: 2024/10/15 23:47:01 by beyza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "lib/libft/libft.h"
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
# include <errno.h>

//linux ve MAC te bir dosya yolunun max uzunluğu
#  ifndef PATH_MAX
#   define PATH_MAX 4096
#  endif

# define PROMPT "\001\e[45m\002>>> \001\e[0m\e[33m\002 Minishell 🤠>$ \001\e[0m\002"

# define SUCCESS 0
# define FAILURE 1


extern int	g_last_exit_code; //global değişken


typedef struct	s_token
{
	char			*value;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

typedef struct s_io_fds
{
	char	*infile;
	char	*outfile;
	char	*heredoc_delimiter;
	bool	heredoc_quotes;
	int		fd_in;
	int		fd_out;
	int		stdin_backup;
	int		stdout_backup;
}	t_io_fds;

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
	t_token		*token;
	t_command	*cmd;
	char		*user_input;
	char		**env;
	char		*work_direc;
	char		*old_work_direc;
	pid_t		pid;
}				t_data;


void	exit_shell(t_data *data, int exno);

#endif