/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayirmili <ayirmili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 21:29:12 by beyza             #+#    #+#             */
/*   Updated: 2024/11/07 18:25:09 by ayirmili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*get_heredoc_name(void)
{
	static int	i;
	char		*name;
	char		*number;

	number = ft_itoa(i);
	if (!number)
		return (NULL);
	name = ft_strjoin(HEREDOC_NAME, number);
	free(number);
	i++;
	return (name);
}

static char	*get_delim(char *delim, bool *quotes)
{
	int	len;

	len = ft_strlen(delim);
	if ((delim[0] == '\"' && delim[len - 1] == '\"') || (delim[0] == '\''
			&& delim[len - 1] == '\''))
	{
		*quotes = true;
		return (ft_strtrim(delim, "\'\""));
	}
	return (ft_strdup(delim));
}

// int	take_status(t_command *cmd, t_io_fds *files, int pid, int exit_code)
// {
// 	int	status;

// 	global_signal = 0;
// 	waitpid(pid, &status, 0);
// 	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
// 		exit_code = 1;
// 	else
// 		exit_code = WEXITSTATUS(status);
// 	close(files->fd_in);
// 	if (exit_code != 0)
// 		return (3);
// 	else
// 		return (0);
// }


int	take_status(t_command *cmd, t_io_fds *files, int pid, int exit_code)
{
	int	status;

	global_signal = 2;
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		exit_code = 1;
	else
		exit_code = WEXITSTATUS(status);
	if (exit_code != 0)
		return (3);
	else
		return (0);
}

bool	heredoc_process(t_data *data, t_io_fds *io, int fd, int exit_code)
{
	int		pid;
	char	*line;
	bool	return_status;

	pid = fork();
	return_status = false;
	line = NULL;
	if (pid == -1)
	{
		perror("fork");
		return (return_status);
	}
	if (pid == 0)
	{
		global_signal = HEREDOC;
		while (1)
		{
			line = readline(">");
			if (!evaluate_heredoc_line(data, &line, &return_status, exit_code))
				break ;
			ft_putendl_fd(line, fd);
			free_pointr(line);
		}
	}
	else
	{
		global_signal = 2;
		waitpid(pid, NULL, 0);
	}
	
	free_pointr(line);
	return (return_status);
}

bool	get_heredoc(t_data *data, t_io_fds *io, int exit_code)
{
	int		tmp_fd;
	bool	return_status;

	return_status = true;
	tmp_fd = open(io->infile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	return_status = heredoc_process(data, io, tmp_fd, exit_code);
	close(tmp_fd);
	return (return_status);
}

void	parse_cmd_heredoc(t_data *data, t_command **last_cmd,
		t_token **token_lst, int exit_code)
{
	t_token		*temp;
	t_command	*cmd;
	t_io_fds	*io;

	temp = *token_lst;
	cmd = lst_last_cmd(*last_cmd);
	init_io(cmd);
	io = cmd->io_fds;
	if (!remove_old_file_ref(io, true))
		return ;
	io->infile = get_heredoc_name();
	io->heredoc_delimiter = get_delim(temp->next->value, &(io->heredoc_quotes));
	if (get_heredoc(data, io, exit_code))
		io->fd_in = open(io->infile, O_RDONLY);
	else
		io->fd_in = -1;
	if (temp->next->next)
		temp = temp->next->next;
	else
		temp = temp->next;
	*token_lst = temp;
}
