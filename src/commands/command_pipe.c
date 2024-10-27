/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyza <beyza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 00:57:28 by beyza             #+#    #+#             */
/*   Updated: 2024/10/28 01:12:42 by beyza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	parse_cmd_pipe(t_command **cmd, t_token **token_lst)
{
	t_command	*last_cmd;

	last_cmd = lst_last_cmd(*cmd);
	last_cmd->pipe_output = true; //true olması komutun çıktısının bir sonraki komuta aktarılacağı anlamına gelir.
	lst_add_back_cmd(&last_cmd, lst_new_cmd(false)); //pipeın öncesindeki komutu sonrasına ekler. False ekler çünkü başka pipe işlemi yoktur. 
	*token_lst = (*token_lst)->next;
}

// EXAMPLE: echo "hello" | grep "h"

// echo "hello" nun pipe_outputu true.
// grep "h" nin pipe_outputu false çünkü kod burda bitiyor ve başka bir pipe yok.