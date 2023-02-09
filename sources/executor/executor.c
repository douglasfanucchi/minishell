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

static char	validate_commands(t_list *node)
{	
	t_command	*command;
	char		*unexpected_token;

	while (node)
	{
		command = node->content;
		unexpected_token = ft_analyse_command(command);
		if (unexpected_token)
		{
			if (ft_strncmp(unexpected_token, "\n", 2) == 0)
				unexpected_token = "newline";
			printf("syntax error near unexpected token `%s`\n",
				unexpected_token);
			g_minishell.status = 2;
			return (0);
		}
		node = node->next;
	}
	return (1);
}

void	ft_executor(t_list **commands)
{
	if (!*commands || !validate_commands(*commands))
		return ;
	ft_exec_commands(commands);
	ft_lstclear(commands, ft_del_command);
	free(commands);
}
