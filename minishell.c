/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyarsla <beyarsla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:36:36 by ayirmili          #+#    #+#             */
/*   Updated: 2024/11/08 15:27:04 by beyarsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_interactive(t_data *data, int exit_code)
{
	while (1)
	{
		g_global_signal = 0;
		set_signals();
		data->user_input = readline(PROMPT);
		if (!data->user_input)
		{
			ft_putendl_fd("exit", 2);
			break ;
		}
		exit_code = main_signal_control(exit_code);
		if (*data->user_input)
		{
			add_history(data->user_input);
			if (parse_input(data, exit_code) == SUCCESS)
				exit_code = execute(data, exit_code);
			else
				exit_code = 1;
			free_data(data, false);
		}
		else
			free_data(data, false);
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	int		exit_code;

	exit_code = 0;
	(void)av;
	ft_memset(&data, 0, sizeof(t_data));
	if (ac != 1)
	{
		perror("This program does not accept arguments\n");
		exit_shell(NULL, EXIT_FAILURE);
	}
	if (!check_init_data(&data, env))
		exit_shell(NULL, EXIT_FAILURE);
	mini_interactive(&data, exit_code);
	exit_shell(&data, exit_code);
	return (0);
}
