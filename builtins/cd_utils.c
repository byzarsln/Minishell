/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayirmili <ayirmili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:08:12 by beyza             #+#    #+#             */
/*   Updated: 2024/11/03 21:32:21 by ayirmili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_counter(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

int	chdir_errno_mod(char *path)
{
	if (errno == ESTALE)
		errno = ENOENT;
	errmsg_cmd("cd", path, strerror(errno), errno);
	return (FAILURE);
}

int	is_space(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v'
		|| c == '\f')
		return (c);
	return (0);
}

char	**reallocate_env(t_data *data, int size, char **data_env)
{
	char	**new_env;
	int		i;

	new_env = ft_calloc(size + 1, sizeof * new_env);
	if (!new_env)
		return (NULL);
	i = 0;
	while (data_env[i] && i < size)
	{
		new_env[i] = ft_strdup(data_env[i]);
		free_pointr(data_env[i]);
		i++;
	}
	free(data_env);
	return (new_env);
}
