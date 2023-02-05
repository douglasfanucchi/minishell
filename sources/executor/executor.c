/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfanucch <dfanucch@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 14:13:56 by dfanucch          #+#    #+#             */
/*   Updated: 2023/02/04 14:13:58 by dfanucch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	validate_commands_syntax(void *content)
{
	t_command	*command;
	char		*unexpected_token;

	if (g_bash_status != 0)
		return ;
	command = content;
	unexpected_token = ft_analyse_command(command);
	if (unexpected_token)
	{
		if (ft_strncmp(unexpected_token, "\n", 2) == 0)
			unexpected_token = "newline";
		printf("-minishell: syntax error near unexpected token `%s`\n",
			unexpected_token);
		g_bash_status = 2;
	}
}

void	ft_executor(t_list **commands)
{
	ft_lstiter(*commands, validate_commands_syntax);
	if (g_bash_status == 0)
		ft_exec_commands(commands);
	ft_lstclear(commands, ft_del_command);
	ft_delete_here_docs();
	free(commands);
}
