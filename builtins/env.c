/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyarsla <beyarsla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 18:20:56 by beyarsla          #+#    #+#             */
/*   Updated: 2024/10/31 20:36:55 by beyarsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_env(t_data *data, char **args, bool is_env)
{
	int		i;
	char	*tmp;
	char	**key_value;

	if (args && args[1])
		return (errmsg_cmd("env", NULL, "too many arguments", 2));
	i = 0;
	if (!data->env)
		return (EXIT_FAILURE);
	while (data->env[i])
	{
		if (is_env)
		{
			tmp = ft_strtrim(data->env[i], "\"");
			ft_putendl_fd(tmp, STDOUT_FILENO);
			free(tmp);
			i++;
		}
		else
		{
			// Split the environment variable by '=' to get key and value
			key_value = ft_split(data->env[i++], '=');
			if (key_value && key_value[0] && key_value[1])
				printf("declare -x %s=\"%s\"\n", key_value[0], key_value[1]);
			else if (key_value && key_value[0]) // Handle variables with no value
				printf("declare -x %s=\"\"\n", key_value[0]);

			// Free the split result
			if (key_value)
			{
				free(key_value[0]);
				free(key_value[1]);
				free(key_value);
			}
		}
	}
	return (EXIT_SUCCESS);
}

