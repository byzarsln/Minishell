/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyarsla <beyarsla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:05:06 by beyarsla          #+#    #+#             */
/*   Updated: 2024/11/08 12:05:07 by beyarsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_pointr(void *pointr)
{
	if (pointr != NULL)
	{
		free(pointr);
		pointr = NULL;
	}
}

void	free_mult_str(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (str[i])
			{
				free_pointr(str[i]);
				str[i] = NULL;
			}
			i++;
		}
		free(str);
		str = NULL;
	}
}

void	status_error(int status)
{
	if (status == DQUOTE)
		perror("unexpected EOF while looking for matching: " \
				"\n");
	else if (status == SQUOTE)
		perror("unexpected EOF while looking for matching: ''\n");
	perror("syntax error: unexpected EOF");
}

void	free_tmp(void *tmp)
{
	if (tmp != NULL)
	{
		free(tmp);
		tmp = NULL;
	}
}

void	exit_shell(t_data *data, int exno)
{
	if (data)
	{
		if (data->cmd && data->cmd->io_fds)
			close_fds(data->cmd, true);
		free_data(data, true);
	}
	exit(exno);
}
