/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayirmili <ayirmili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:18:34 by beyza             #+#    #+#             */
/*   Updated: 2024/11/01 15:26:12 by ayirmili         ###   ########.fr       */
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
		return_status = builtin_env(data, cmd->args); 
	else if (ft_strncmp(cmd->command, "export", 7) == 0)
		return_status = builtin_export(data, cmd->args);
	else if (ft_strncmp(cmd->command, "pwd", 4) == 0)
		return_status = buildin_pwd(data, cmd->args);
	else if (ft_strncmp(cmd->command, "unset", 6) == 0)
		return_status = builtin_unset(data, cmd->args);
	else if (ft_strncmp(cmd->command, "exit", 5) == 0)
		return_status = builtin_exit(data, cmd->args);
	return (return_status);
}
