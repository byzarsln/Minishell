/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyarsla <beyarsla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 18:50:09 by beyza             #+#    #+#             */
/*   Updated: 2024/10/18 18:32:29 by beyarsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    status_error(int status)
{
    if (status == DQUOTE)
        perror("unexpected EOF while looking for matching: ""\n");
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
			;
			//TODO close_fds(data->cmd, true);
		//TODOfree_data(data, true);
	}
	exit(exno);
}
