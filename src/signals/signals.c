/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyarsla <beyarsla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:39:05 by ayirmili          #+#    #+#             */
/*   Updated: 2024/11/08 14:36:52 by beyarsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	main_signal_control(int exit_code)
{
	if (g_global_signal == 17)
	{
		exit_code = 1;
		g_global_signal = 0;
	}
	if (g_global_signal == 13)
	{
		exit_code = 130;
		g_global_signal = 0;
	}
	return (exit_code);
}

void	sigint_reset(int signal_no)
{
	if (g_global_signal == IN_CAT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		g_global_signal = 13;
	}
	else if (g_global_signal == HEREDOC)
	{
		exit(1);
	}
	else
	{
		(void)signal_no;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_global_signal = 17;
	}
}

void	ignore_sigquit(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}

void	set_signals(void)
{
	struct sigaction	signl;

	ignore_sigquit();
	ft_memset(&signl, 0, sizeof(signl));
	signl.sa_handler = &sigint_reset;
	sigaction(SIGINT, &signl, NULL);
}
