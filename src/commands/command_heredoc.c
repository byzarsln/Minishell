/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyza <beyza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 21:29:12 by beyza             #+#    #+#             */
/*   Updated: 2024/10/27 00:05:32 by beyza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*get_heredoc_name(void)//geçici dosya adlarını oluşturur. Bu dosyalar, heredoc girdisini geçici olarak saklamak için kullanılır.
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

static char	*get_delim(char *delim, bool *quotes)//tırnak varsa silip, yoksa delimiterı döndürüyor.
{
	int	len;

	len = ft_strlen(delim);
	if ((delim[0] == '\"' && delim[len - 1] == '\"')
		|| (delim[0] == '\'' && delim[len - 1] == '\''))
	{
		*quotes = true;
		return (ft_strtrim(delim, "\'\""));
	}
	return (ft_strdup(delim));
}

bool	heredoc_process(t_data *data, t_io_fds *io, int fd)// tmpfile a girdileri kopyalar. envden vs değiştirilecek değerleri($PWD nin env deki karşılığı gibi) değiştirerek yazma işlemlerini yapar.) 
{
	char	*line;
	bool	return_status;

	return_status = false;
	line = NULL;
	while (1)
	{
		set_signals();
		line = readline(">"); //döngüde başına koymak için
		if (!evaluate_heredoc_line(data, &line, io, &return_status))
			break ;
		ft_putendl_fd(line, fd);
		free_pointr(line);
	}
	free_pointr(line);
	return (return_status);
}

bool	get_heredoc(t_data *data, t_io_fds *io) //dosyanın içerisine başarıyla yazılıp yazılamayacağı durumunu döndürüyor.
{
	int		tmp_fd;
	bool	return_status;

	return_status = true;
	tmp_fd = open(io->infile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	return_status = heredoc_process(data, io, tmp_fd);
	close(tmp_fd);
	return (return_status);
}

void	parse_cmd_heredoc(t_data *data, t_command **last_cmd, t_token **token_lst)
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
	if (get_heredoc(data, io))
		io->fd_in = open(io->infile, O_RDONLY);
	else
		io->fd_in = -1;
	if (temp->next->next)
		temp = temp->next->next;
	else
		temp = temp->next;
	*token_lst = temp;
}
