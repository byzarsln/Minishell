/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayirmili <ayirmili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 21:58:08 by ayirmili          #+#    #+#             */
/*   Updated: 2024/11/01 16:19:55 by ayirmili         ###   ########.fr       */
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
	data->export_env = reallocate_env(data, count, data->export_env);
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
	data->env = reallocate_env(data, count, data->env);
	if (!data->env)
		return (false);
	return (true);
}

int	builtin_unset(t_data *data, char **args)
{
	int	i;
	int	idx;
	int	ret;

	ret = EXIT_SUCCESS;
	i = 1;
	while (args[i])
	{
		if (!is_valid_env_key(args[i]) || ft_strchr(args[i], '=') != NULL)
		{
			errmsg_cmd("unset", args[i], "not a valid identifier", false);
			ret = EXIT_FAILURE;
		}
		else
		{
			idx = env_find_index(data->env, args[i]);
			if (idx != -1)
			{
				remove_env_var(data, idx);
				remove_export_var(data, idx);
			}
		}
		i++;
	}
	return (ret);
}
