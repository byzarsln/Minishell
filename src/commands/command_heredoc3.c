/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_heredoc3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyarsla <beyarsla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:05:38 by beyarsla          #+#    #+#             */
/*   Updated: 2024/11/08 14:36:52 by beyarsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	heredoc_child_process(t_data *data, int fd, int exit_code)
{
	char	*line;
	bool	return_status;

	return_status = false;
	g_global_signal = HEREDOC;
	while (1)
	{
		line = readline(">");
		if (!evaluate_heredoc_line(data, &line, &return_status, exit_code))
			break ;
		ft_putendl_fd(line, fd);
		free_pointr(line);
	}
	free_pointr(line);
	exit(0);
}

bool	heredoc_parent_process(int pid)
{
	int		status;
	bool	return_status;

	return_status = false;
	g_global_signal = 2;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && g_global_signal != 13)
		return_status = (WEXITSTATUS(status) == 0);
	return (return_status);
}

char	*make_str_from_tab(char **tab)
{
	char	*str;
	char	*tmp;
	int		i;

	i = -1;
	while (tab[++i])
	{
		tmp = str;
		if (i == 0)
			str = ft_strdup(tab[0]);
		else
		{
			str = ft_strjoin(tmp, tab[i]);
			free_pointr(tmp);
		}
		if (tab[i + 1])
		{
			tmp = str;
			str = ft_strjoin(tmp, " ");
			free_pointr(tmp);
		}
	}
	free_str_tab(tab);
	return (str);
}
