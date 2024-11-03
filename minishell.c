/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyarsla <beyarsla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:36:36 by ayirmili          #+#    #+#             */
/*   Updated: 2024/11/03 18:59:28 by beyarsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_interactive(t_data *data)
{
	while (1)
	{
		set_signals();
		data->user_input = readline(PROMPT);
		if (!data->user_input)
		{
			ft_putendl_fd("exit", 2);
			break ;
		}
		if (*data->user_input)
		{
            add_history(data->user_input);
			if(parse_input(data) == SUCCESS)
				g_last_exit_code = execute(data);
			else
				g_last_exit_code = 1;
			free_data(data,false);
		}
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	ft_memset(&data, 0, sizeof(t_data));
	if (ac != 1)
	{
		perror("This program does not accept arguments\n");
		exit_shell(NULL, EXIT_FAILURE);
	}
	if (!check_init_data(&data, env))
		exit_shell(NULL, EXIT_FAILURE);
	mini_interactive(&data);
	exit_shell(&data, g_last_exit_code);
	return (0);
}
