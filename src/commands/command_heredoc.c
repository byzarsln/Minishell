/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyarsla <beyarsla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:05:24 by beyarsla          #+#    #+#             */
/*   Updated: 2024/11/08 12:05:26 by beyarsla         ###   ########.fr       */
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

static bool	heredoc_process(t_data *data, int fd, int exit_code)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (false);
	}
	if (pid == 0)
		heredoc_child_process(data, fd, exit_code);
	else
		return (heredoc_parent_process(pid));
	return (false);
}

bool	get_heredoc(t_data *data, t_io_fds *io, int exit_code)
{
	int		tmp_fd;
	bool	return_status;

	return_status = true;
	tmp_fd = open(io->infile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	return_status = heredoc_process(data, tmp_fd, exit_code);
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
