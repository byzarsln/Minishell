/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyza <beyza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:36:36 by ayirmili          #+#    #+#             */
/*   Updated: 2024/10/14 18:56:25 by beyza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
    t_data *data;

    data = (t_data *)malloc(sizeof(t_data));
    if(!data)
        return(0);
    if(ac != 1)
    {
        printf("%s", "This program does not accept arguments\n");
        exit_shell(NULL, EXIT_FAILURE);
    } 
}
