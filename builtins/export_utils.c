/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayirmili <ayirmili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 20:40:57 by ayirmili          #+#    #+#             */
/*   Updated: 2024/11/08 14:22:01 by ayirmili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*create_tmp_value(char *env_value, bool control)
{
	if (control != false)
		return (ft_strjoin("=", env_value));
	else
		return (ft_strdup(env_value));
}

int	update_or_add_export_env(t_data *data, char *key, char *tmp, int index)
{
	if (index != -1 && data->export_env[index])
	{
		free_pointr(data->export_env[index]);
		data->export_env[index] = ft_strjoin(key, tmp);
	}
	else
	{
		index = env_counter(data->export_env);
		data->export_env = reallocate_env(index + 1, data->export_env);
		if (!data->export_env)
			return (FAILURE);
		data->export_env[index] = ft_strjoin(key, tmp);
	}
	free_pointr(tmp);
	return (SUCCESS);
}

int	handle_export(t_data *data, char *args)
{
	int		return_status;
	char	**tmp;

	return_status = EXIT_SUCCESS;
	if (!is_valid_env_key(args))
	{
		errmsg_cmd("export", args, "not a valid identifier", false);
		return_status = EXIT_FAILURE;
	}
	else if (ft_strchr(args, '=') != NULL)
	{
		tmp = get_key_value_pair(args);
		set_env_var(data, tmp[0], tmp[1]);
		set_export_var(data, tmp[0], tmp[1], true);
		free_str_tab(tmp);
	}
	else if (ft_strchr(args, '=') == NULL)
		set_export_var(data, args, NULL, false);
	return (return_status);
}

void	free_key_export(char **key_value)
{
	free(key_value[0]);
	free(key_value[1]);
	free(key_value);
}
