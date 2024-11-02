/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayirmili <ayirmili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 18:31:19 by beyarsla          #+#    #+#             */
/*   Updated: 2024/11/02 17:52:02 by ayirmili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int set_export_var(t_data *data, char *key, char *env_value, bool control)
{
	int index;
	char *tmp;

	index = env_find_index(data->export_env, key);
	if (env_value == NULL)
		env_value = "";
	if (control != false)
		tmp = ft_strjoin("=", env_value);
	else
		tmp = ft_strdup(env_value);
	if (!tmp)
		return (FAILURE);
	if (control == false && env_find_value(data->export_env, key, control) != NULL)
		return (SUCCESS);
	if (index != -1 && data->export_env[index])
	{
		free_pointr(data->export_env[index]);
		data->export_env[index] = ft_strjoin(key, tmp);
	}
	else
	{
		index = env_counter(data->export_env);
		data->export_env = reallocate_env(data, index + 1, data->export_env); // Reallocates memory for the global variable g_env_vars. dizinin ortasından tek bir değeri değiştirirken eski verilerin kaybolmaması için bunları kopyalıyoruz.daha düzenli bir yapı yapıyoruz.
		if (!data->export_env)
			return (FAILURE);
		data->export_env[index] = ft_strjoin(key, tmp);
	}
	free_pointr(tmp);
	return (SUCCESS);
}

int	write_export(t_data *data, char **args)
{
	int		i;
	char	*tmp;
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
			if (env_find_value(data->env, key_value[0], true) != 0)
				printf("declare -x %s=\"\"\n", key_value[0]);
			else
				printf("declare -x %s\n", key_value[0]);
		}

		if (key_value)
		{
			free(key_value[0]);
			free(key_value[1]);
			free(key_value);
		}
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

static char	**get_key_value_pair(char *arg)
{
	char	**tmp;
	char	*eq_pos;

	eq_pos = ft_strchr(arg, '=');
	tmp = malloc(sizeof * tmp * (2 + 1));
	tmp[0] = ft_substr(arg, 0, eq_pos - arg);
	tmp[1] = ft_substr(eq_pos, 1, ft_strlen(eq_pos));
    if (*(eq_pos + 1) == '\0')
        tmp[1] = NULL;
	tmp[2] = NULL;
	return (tmp);
}

int	builtin_export(t_data *data, char **args)
{
	int		i;
	char	**tmp;
	int		return_status;

	return_status = EXIT_SUCCESS;
	i = 1;

	if (!args[i])
		return (write_export(data, NULL));
	while (args[i])
	{
		if (!is_valid_env_key(args[i]))
		{
			errmsg_cmd("export", args[i], "not a valid identifier", false);
			return_status = EXIT_FAILURE;
		}
		else if (ft_strchr(args[i], '=') != NULL)
		{
			tmp = get_key_value_pair(args[i]);
			set_env_var(data, tmp[0], tmp[1]);
			set_export_var(data, tmp[0], tmp[1], true);
			free_str_tab(tmp);
		}
		else if(ft_strchr(args[i], '=') == NULL)
			set_export_var(data, args[i], NULL, false);
		i++;
	}
	return (return_status);
}
