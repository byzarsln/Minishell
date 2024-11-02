/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayirmili <ayirmili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:52:02 by beyza             #+#    #+#             */
/*   Updated: 2024/11/02 19:58:48 by ayirmili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool is_n_flag(char *arg)
{
    int i;
    bool n_flag;

    n_flag = false;
    i = 0;
    if (arg[i] != '-')
        return (n_flag);
    i++;
    while (arg[i] && arg[i] == 'n')
        i++;
    if (arg[i] == '\0')
        n_flag = true;
    return (n_flag);
}

static void echo_print_args(char **args, bool n_flag, int i)
{
    if (!args[i])
    {
        if (!n_flag)
            ft_putchar_fd('\n', STDOUT_FILENO);
        return;
    }
    while (args[i])
    {
        ft_putstr_fd(args[i], STDOUT_FILENO);
        if (args[i + 1])
            ft_putchar_fd(' ', STDOUT_FILENO);
        else if (!args[i + 1] && !n_flag)
            ft_putchar_fd('\n', STDOUT_FILENO);
        i++;
    }
}

int builtin_echo(t_data *data, char **args) // TODO BURASI
{
    int i;
    bool n_flag;

    (void)data;
    n_flag = false;
    i = 1;
    while (args[i] && is_n_flag(args[i]))
    {
        n_flag = true;
        i++;
    }
    echo_print_args(args, n_flag, i);
    return (EXIT_SUCCESS);
}
