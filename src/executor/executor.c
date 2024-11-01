/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayirmili <ayirmili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:56:08 by beyza             #+#    #+#             */
/*   Updated: 2024/11/01 14:00:45 by ayirmili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	redirect_io(t_io_fds *io)
{
	int	return_status;

	return_status = true;
	if (!io)
		return (return_status);
	io->stdin_backup = dup(STDIN_FILENO);
	if (io->stdin_backup == -1) //kopyalayamadıysa
		return_status = errmsg_cmd("dup", "stdin backup", strerror(errno), false);
	io->stdout_backup = dup(STDOUT_FILENO);
	if (io->stdout_backup == -1)
		return_status = errmsg_cmd("dup", "stdout backup", strerror(errno), false);
	if (io->fd_in != -1)
		if (dup2(io->fd_in, STDIN_FILENO) == -1) //kopyaladığına yazamıyorsa
			return_status = errmsg_cmd("dup2", io->infile, strerror(errno), false);
	if (io->fd_out != -1)
		if (dup2(io->fd_out, STDOUT_FILENO) == -1)
			return_status = errmsg_cmd("dup2", io->outfile, strerror(errno), false);
	return (return_status);
}

int create_pipes(t_data *data)
{
	t_command	*tmp;
	int			*fd;

	tmp = data->cmd;
	while (tmp)
	{
		if (tmp->pipe_output || (tmp->prev && tmp->prev->pipe_output))
		{
			fd = malloc(sizeof * fd * 2);
			if (!fd || pipe(fd) != 0)
			{
				free_data(data, false);
				return (FAILURE);
			}
			tmp->pipe_fd = fd;
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int check_inoutfile(t_io_fds *io)
{
	if (!io || (!io->infile && !io->outfile))
		return (SUCCESS); // hata durumu değil, yalnızca yönlendirme yok bu nedenle success döner.
	if ((io->infile && io->fd_in == -1)
		|| (io->outfile && io->fd_out == -1))
		return (FAILURE);
	return (SUCCESS);
}

static int	check_prep_exec(t_data *data)
{
	if (!data || !data->cmd)
		return (EXIT_SUCCESS); // hata durumu değil, yalnızca yönlendirme yok bu nedenle success döner.
	if (!data->cmd->command)
	{
		if (data->cmd->io_fds
			&& !check_inoutfile(data->cmd->io_fds))
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	if (!create_pipes(data))
		return (EXIT_FAILURE);
	return (COMMAND_NOT_FOUND);
}

int	execute(t_data *data)
{
	int	return_status;

	return_status = check_prep_exec(data);
	if (return_status != COMMAND_NOT_FOUND)
		return (return_status);
	if (!data->cmd->pipe_output && !data->cmd->prev
		&& check_inoutfile(data->cmd->io_fds))
	{
		redirect_io(data->cmd->io_fds);
		return_status = execute_builtin(data, data->cmd);
		restore_io(data->cmd->io_fds);
	}
	// if (return_status != COMMAND_NOT_FOUND)
	// 	return (return_status);
	// return (create_children(data));
}
