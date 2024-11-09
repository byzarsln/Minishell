/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayirmili <ayirmili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 18:31:19 by beyarsla          #+#    #+#             */
/*   Updated: 2024/11/08 12:57:13 by ayirmili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_export_var(t_data *data, char *key, char *env_value, bool control)
{
	int		index;
	char	*tmp;

	index = env_find_index(data->export_env, key);
	if (control == false && env_find_value(data->export_env, key) != NULL)
		return (SUCCESS);
	if (env_value == NULL)
		env_value = "";
	tmp = create_tmp_value(env_value, control);
	if (!tmp)
		return (FAILURE);
	return (update_or_add_export_env(data, key, tmp, index));
}

int	write_export(t_data *data, char **args)
{
	int		i;
	char	**key_value;

	if (args && args[1])
		return (errmsg_cmd("env", NULL, "too many arguments", 2));
	i = 0;
	if (!data->export_env)
		return (EXIT_FAILURE);
	while (data->export_env[i])
	{
		key_value = ft_split(data->export_env[i++], '=');
		if (key_value && key_value[0] && key_value[1])
			printf("declare -x %s=\"%s\"\n", key_value[0], key_value[1]);
		else if (key_value && key_value[0])
		{
			if (env_find_value(data->env, key_value[0]) != 0)
				printf("declare -x %s=\"\"\n", key_value[0]);
			else
				printf("declare -x %s\n", key_value[0]);
		}
		if (key_value)
			free_key_export(key_value);
	}
	return (EXIT_SUCCESS);
}

bool	is_valid_env_key(char *var)
{
	int	i;

	i = 0;
	if (ft_isalpha(var[i]) == 0 && var[i] != '_')
		return (false);
	i++;
	while (var[i] && var[i] != '=')
	{
		if (ft_isalnum(var[i]) == 0 && var[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

char	**get_key_value_pair(char *arg)
{
	char	**tmp;
	char	*eq_pos;

	eq_pos = ft_strchr(arg, '=');
	tmp = malloc(sizeof * tmp * (2 + 1));
	tmp[0] = ft_substr(arg, 0, eq_pos - arg);
	if (*(eq_pos + 1) == '\0')
		tmp[1] = NULL;
	else
		tmp[1] = ft_substr(eq_pos + 1, 0, ft_strlen(eq_pos + 1));
	tmp[2] = NULL;
	return (tmp);
}

int	builtin_export(t_data *data, char **args)
{
	int	i;
	int	return_status;

	return_status = EXIT_SUCCESS;
	i = 1;
	if (!args[i])
		return (write_export(data, NULL));
	while (args[i])
	{
		return_status = handle_export(data, args[i]);
		i++;
	}
	return (return_status);
}
