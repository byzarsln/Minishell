/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyza <beyza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:36:36 by ayirmili          #+#    #+#             */
/*   Updated: 2024/10/15 23:00:19 by beyza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_last_exit_code;

void    free_tmp(void *tmp)
{
    if (tmp != NULL)
    {
        free(tmp);
        tmp = NULL;
    }
}

char    *env_find_value(char **env, char *var)
{
    int         i;
    char    *tmp;

    tmp = ft_strjoin(var, "=");
    if(!tmp)
        return(NULL);
    i = 0;
    while(env[i])
    {
        if(ft_strncmp(tmp, env[i], ft_strlen(tmp)) == 0)
        {
            free_tmp(tmp);
            return(ft_strchr(env[i], '=') + 1);
        }
        i++;
    }
    free_tmp(tmp);
    return(NULL);
}

int env_find_index(char **env, char *var)
{
    int		i;
	char	*tmp;

	tmp = ft_strjoin(var, "=");
	if (!tmp)
		return (-1);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(tmp, env[i], ft_strlen(tmp)) == 0)
		{
			free_tmp(tmp);
			return (i);
		}
		i++;
	}
	free_tmp(tmp);
	return (-1);
}

int init_work_direc(t_data *data)
{
    char buff[PATH_MAX];
    char *working_dir;

    working_dir = getcwd(buff, PATH_MAX); //getcwd (current working directory) programın çalıştığı dizini alıyor
    data->work_direc = ft_strdup(working_dir);
    if (!data->work_direc)
        return(0);
    if (env_find_index(data->env, "OLDPWD") != -1)
    {
        data->old_work_direc = ft_strdup(env_find_value(data->env, "OLDPWD"));
        if(!data->old_work_direc)
            return(0);
    }
    else
    {
        data->old_work_direc = ft_strdup(working_dir);
        if (!data->old_work_direc)
            return(0);
    }
    return(1);
}

int check_init_env(t_data *data, char **env)
{
	int		i;

    i = 0;
    while(env[i] && env)
        i++;
    data->env = ft_calloc((i + 1), sizeof * data->env); //yer açıp içini null atıyor.
	if (!data->env)
		return (false);
	i = 0;
    while(env[i])
    {
        data->env[i] = ft_strdup(env[i]);
        if(!data->env[i])
            return(0);
        i++;
    }
    return(1);
}

int check_init_data(t_data *data, char **env)
{
    if(!check_init_env(data, env))
    {
        perror("Fatal: Could not initialize environment");
        return(0);
    }
    if(!init_work_direc(data))
    {
        perror("Fatal: Could not initialize working directories");
        return(0);
    }
    data->cmd = NULL;
    data->pid = -1;
    data->token = NULL;
    data->user_input = NULL;
    g_last_exit_code = 0;
    return(1);
}

int	main(int ac, char **av, char **env)
{
    t_data data;

    ft_memset(&data, 0, sizeof(t_data)); //datanın içine null atanıyor
    if(ac != 1)
    {
        perror("This program does not accept arguments\n");
        exit_shell(NULL, EXIT_FAILURE);
    }
    if(!check_init_data(&data, env))
        exit_shell(NULL, EXIT_FAILURE);
}
