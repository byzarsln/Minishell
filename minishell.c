/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyza <beyza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:36:36 by ayirmili          #+#    #+#             */
/*   Updated: 2024/10/28 01:17:53 by beyza            ###   ########.fr       */
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
			if(parse_input(data) == SUCCESS)
				g_last_exit_code = execute(data); // TODO
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
	printf("%s", av[0]);
}
