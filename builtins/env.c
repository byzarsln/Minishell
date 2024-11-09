/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayirmili <ayirmili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 18:20:56 by beyarsla          #+#    #+#             */
/*   Updated: 2024/11/07 21:08:27 by ayirmili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_env(t_data *data, char **args)
{
	int		i;
	char	*tmp;

	if (args && args[1])
		return (errmsg_cmd("env", NULL, "too many arguments", 2));
	i = 0;
	if (!data->env)
		return (EXIT_FAILURE);
	while (data->env[i])
	{
		tmp = ft_strtrim(data->env[i], "\"");
		ft_putendl_fd(tmp, STDOUT_FILENO);
		free(tmp);
		i++;
	}
	return (EXIT_SUCCESS);
}
