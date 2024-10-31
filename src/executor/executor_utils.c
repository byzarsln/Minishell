/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyarsla <beyarsla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:18:34 by beyza             #+#    #+#             */
/*   Updated: 2024/10/31 18:51:09 by beyarsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int execute_builtin(t_data *data, t_command *cmd)
{
	int return_status;

	return_status = COMMAND_NOT_FOUND;
	if (ft_strncmp(cmd->command, "cd", 3) == 0)
		return_status = builtin_cd(data, cmd->args);
	else if (ft_strncmp(cmd->command, "echo", 5) == 0)
		return_status = builtin_echo(data, cmd->args);
	else if (ft_strncmp(cmd->command, "env", 4) == 0)
		return_status = builtin_env(data, cmd->args, true);
	else if (ft_strncmp(cmd->command, "export", 7) == 0)
		return_status = builtin_export(data, cmd->args);
}
