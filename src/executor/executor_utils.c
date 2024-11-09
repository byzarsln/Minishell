/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyarsla <beyarsla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:06:21 by beyarsla          #+#    #+#             */
/*   Updated: 2024/11/08 14:36:52 by beyarsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	execute_sys_bin(t_data *data, t_command *cmd)
{
	if (!cmd->command || cmd->command[0] == '\0')
		return (COMMAND_NOT_FOUND);
	if (cmd_is_dir(cmd->command))
		return (COMMAND_NOT_FOUND);
	cmd->path = get_cmd_path(data, cmd->command);
	if (!cmd->path)
		return (COMMAND_NOT_FOUND);
	if (execve(cmd->path, cmd->args, data->env) == -1)
		errmsg_cmd("execve", NULL, strerror(errno), errno);
	return (EXIT_FAILURE);
}

void	close_fds(t_command *cmds, bool close_backups)
{
	if (cmds->io_fds)
	{
		if (cmds->io_fds->fd_in != -1)
			close(cmds->io_fds->fd_in);
		if (cmds->io_fds->fd_out != -1)
			close(cmds->io_fds->fd_out);
		if (close_backups)
			restore_io(cmds->io_fds);
	}
	close_pipe_fds(cmds, NULL);
}

static int	execute_command(t_data *data, t_command *cmd, int exit_code)
{
	int	ret;

	if (!cmd || !cmd->command)
		exit_shell(data, errmsg_cmd("child", NULL,
				"parsing error: no command to execute!", EXIT_FAILURE));
	if (!check_infile_outfile(cmd->io_fds))
		exit_shell(data, EXIT_FAILURE);
	set_pipe_fds(data->cmd, cmd);
	redirect_io(cmd->io_fds);
	close_fds(data->cmd, false);
	if (ft_strchr(cmd->command, '/') == NULL)
	{
		ret = execute_builtin(data, cmd, exit_code);
		if (ret != COMMAND_NOT_FOUND)
			exit_shell(data, ret);
		ret = execute_sys_bin(data, cmd);
		if (ret != COMMAND_NOT_FOUND)
			exit_shell(data, ret);
	}
	ret = execute_local_bin(data, cmd);
	exit_shell(data, ret);
	return (ret);
}

int	create_children(t_data *data, int exit_code)
{
	t_command	*cmd;

	cmd = data->cmd;
	g_global_signal = IN_CAT;
	while (data->pid != 0 && cmd)
	{
		data->pid = fork();
		if (data->pid == -1)
			return (errmsg_cmd("fork", NULL, strerror(errno), EXIT_FAILURE));
		else if (data->pid == 0)
			execute_command(data, cmd, exit_code);
		cmd = cmd->next;
	}
	return (get_children(data));
}

int	execute_builtin(t_data *data, t_command *cmd, int exit_code)
{
	int	return_status;

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
		return_status = builtin_exit(data, cmd->args, exit_code);
	return (return_status);
}
