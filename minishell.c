/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyarsla <beyarsla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:36:36 by ayirmili          #+#    #+#             */
/*   Updated: 2024/10/21 19:17:00 by beyarsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_last_exit_code;

void	mini_interactive(t_data *data)
{
	while (1)
	{
		set_signals();
		data->user_input = readline(PROMPT);
		if (!data->user_input)
		{
			printf("exit\n");
			break ;
		}
		if (*data->user_input)
		{
            add_history(data->user_input);
			if(parse_input(data) == FAILURE)
				g_last_exit_code = 1;
			else
				;
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
	printf("%s", av[0]);
}
