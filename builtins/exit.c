/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyarsla <beyarsla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 22:07:43 by ayirmili          #+#    #+#             */
/*   Updated: 2024/11/08 15:23:52 by beyarsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	check_out_of_range(int neg, unsigned long long num, bool *error)
{
	if ((neg == 1 && num > LONG_MAX) || (neg == -1 && \
		num > -(unsigned long)LONG_MIN))
		*error = true;
	return (*error);
}

static int	ft_atoi_long(const char *str, bool *error)
{
	unsigned long long	num;
	int					neg;
	int					i;

	num = 0;
	neg = 1;
	i = 0;
	while (str[i] && is_space(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		neg *= -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		num = (num * 10) + (str[i] - '0');
		if (check_out_of_range(neg, num, error))
			break ;
		i++;
	}
	return (num * neg);
}

static int	get_exit_code(char *arg, bool *error, int exit_code)
{
	unsigned long long	i;

	if (!arg)
		return (exit_code);
	i = 0;
	while (is_space(arg[i]))
		i++;
	if (arg[i] == '\0')
		*error = true;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	if (!ft_isdigit(arg[i]))
		*error = true;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]) && !is_space(arg[i]))
			*error = true;
		i++;
	}
	i = ft_atoi_long(arg, error);
	return (i % 256);
}

static bool	is_quiet_mode(t_data *data)
{
	t_command	*cmd;

	cmd = data->cmd;
	if (!cmd)
		return (false);
	if (cmd->next != NULL || cmd->prev != NULL)
		return (true);
	return (false);
}

int	builtin_exit(t_data *data, char **args, int exit_code)
{
	int		exit_return;
	bool	error;
	bool	quiet;

	quiet = is_quiet_mode(data);
	error = false;
	if (!quiet)
		ft_putendl_fd("exit", 2);
	if (!args || !args[1])
		exit_return = exit_code;
	else
	{
		exit_return = get_exit_code(args[1], &error, exit_code);
		if (error)
			exit_return = errmsg_cmd("exit", args[1], \
			"numeric argument required", 255);
		else if (args[2])
			return (errmsg_cmd("exit", NULL, "too many arguments", 1));
	}
	exit_shell(data, exit_return);
	return (2);
}
