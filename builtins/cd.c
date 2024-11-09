/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayirmili <ayirmili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:04:35 by beyarsla          #+#    #+#             */
/*   Updated: 2024/11/08 12:50:31 by ayirmili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_env_var(t_data *data, char *key, char *env_value)
{
	int		index;
	char	*tmp;

	index = env_find_index(data->env, key);
	if (env_value == NULL)
		env_value = "";
	tmp = ft_strjoin("=", env_value);
	if (!tmp)
		return (FAILURE);
	if (index != -1 && data->env[index])
	{
		free_pointr(data->env[index]);
		data->env[index] = ft_strjoin(key, tmp);
	}
	else
	{
		index = env_counter(data->env);
		data->env = reallocate_env(index + 1, data->env);
		if (!data->env)
			return (FAILURE);
		data->env[index] = ft_strjoin(key, tmp);
	}
	free_pointr(tmp);
	return (SUCCESS);
}

static void	update_work_direc(t_data *data, char *wd)
{
	set_env_var(data, "OLDPWD", env_find_value(data->env, "PWD"));
	set_env_var(data, "PWD", wd);
	if (data->old_work_direc)
	{
		free_pointr(data->old_work_direc);
		data->old_work_direc = ft_strdup(data->work_direc);
	}
	if (data->work_direc)
	{
		free_pointr(data->work_direc);
		data->work_direc = ft_strdup(wd);
	}
	free_pointr(wd);
}

int	change_dir(t_data *data, char *path)
{
	char	*return_status;
	char	*tmp;
	char	cwd[PATH_MAX];

	return_status = NULL;
	if (chdir(path) != 0)
		return (chdir_errno_mod(path));
	return_status = getcwd(cwd, PATH_MAX);
	if (!return_status)
	{
		errmsg_cmd("cd: error retrieving current directory",
			"getcwd: cannot access parent directories", strerror(errno), errno);
		return_status = ft_strjoin(data->work_direc, "/");
		tmp = return_status;
		return_status = ft_strjoin(tmp, path);
		free_pointr(tmp);
	}
	else
		return_status = ft_strdup(cwd);
	update_work_direc(data, return_status);
	return (SUCCESS);
}

int	builtin_cd(t_data *data, char **args)
{
	char	*path;

	if (!args || !args[1] || is_space(args[1][0]) || args[1][0] == '\0'
		|| ft_strncmp(args[1], "--", 3) == 0 || ft_strncmp(args[1], "~", \
			2) == 0)
	{
		path = env_find_value(data->env, "HOME");
		if (!path || *path == '\0' || is_space(*path))
			return (errmsg_cmd("cd", NULL, "HOME not set", EXIT_FAILURE));
		return (!change_dir(data, path));
	}
	if (ft_strncmp(args[1], "-", 2) == 0)
	{
		path = env_find_value(data->env, "OLDPWD");
		if (!path)
			return (errmsg_cmd("cd", NULL, "OLDPWD not set", EXIT_FAILURE));
		return (!change_dir(data, path));
	}
	return (!change_dir(data, args[1]));
}
