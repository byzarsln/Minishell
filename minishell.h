/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyza <beyza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:06:47 by ayirmili          #+#    #+#             */
/*   Updated: 2024/10/14 19:00:36 by beyza            ###   ########.fr       */
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


# define SUCCESS 0
# define FAILURE 1


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
}				t_data;



// typedef struct	s_env
// {
// 	char			*value;
// 	struct s_env	*next;
// }				t_env;

// typedef struct	s_mini
// {
// 	t_token			*start;
// 	t_env			*env;
// 	t_env			*secret_env;
// 	int				in;
// 	int				out;
// 	int				fdin;
// 	int				fdout;
// 	int				pipein;
// 	int				pipeout;
// 	int				pid;
// 	int				charge;
// 	int				parent;
// 	int				last;
// 	int				ret;
// 	int				exit;
// 	int				no_exec;
// }				t_mini;

#endif