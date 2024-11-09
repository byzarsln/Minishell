/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayirmili <ayirmili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 21:58:08 by ayirmili          #+#    #+#             */
/*   Updated: 2024/11/07 22:10:24 by ayirmili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	remove_export_var(t_data *data, int idx)
{
	int	i;
	int	count;

	if (idx > env_counter(data->export_env))
		return (false);
	free_pointr(data->export_env[idx]);
	i = idx;
	count = idx;
	while (data->export_env[i + 1])
	{
		data->export_env[i] = ft_strdup(data->export_env[i + 1]);
		free_pointr(data->export_env[i + 1]);
		count++;
		i++;
	}
	data->export_env = reallocate_env(count, data->export_env);
	if (!data->env)
		return (false);
	return (true);
}

static bool	remove_env_var(t_data *data, int idx)
{
	int	i;
	int	count;

	if (idx > env_counter(data->env))
		return (false);
	free_pointr(data->env[idx]);
	i = idx;
	count = idx;
	while (data->env[i + 1])
	{
		data->env[i] = ft_strdup(data->env[i + 1]);
		free_pointr(data->env[i + 1]);
		count++;
		i++;
	}
	data->env = reallocate_env(count, data->env);
	if (!data->env)
		return (false);
	return (true);
}

static int	unset_var(t_data *data, char *arg)
{
	int	idx;
	int	idx1;

	if (!is_valid_env_key(arg) || ft_strchr(arg, '=') != NULL)
	{
		errmsg_cmd("unset", arg, "not a valid identifier", false);
		return (EXIT_FAILURE);
	}
	idx = env_find_index(data->env, arg);
	idx1 = env_find_index(data->export_env, arg);
	if (idx != -1)
		remove_env_var(data, idx);
	if (idx1 != -1)
		remove_export_var(data, idx1);
	return (EXIT_SUCCESS);
}

int	builtin_unset(t_data *data, char **args)
{
	int	i;
	int	ret;

	i = 1;
	ret = EXIT_SUCCESS;
	while (args[i])
	{
		if (unset_var(data, args[i]) == EXIT_FAILURE)
			ret = EXIT_FAILURE;
		i++;
	}
	return (ret);
}
