/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyza <beyza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 18:50:09 by beyza             #+#    #+#             */
/*   Updated: 2024/10/15 17:46:50 by beyza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
