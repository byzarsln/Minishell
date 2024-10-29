/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyza <beyza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:18:34 by beyza             #+#    #+#             */
/*   Updated: 2024/10/29 17:08:54 by beyza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int execute_builtin(t_data *data, t_command *cmd)
{
	int return_status;

	return_status = COMMAND_NOT_FOUND;
	if (ft_strncmp(cmd->command, "cd", 3) == 0)
		return_status = builtin_cd(data, cmd->args);
}
