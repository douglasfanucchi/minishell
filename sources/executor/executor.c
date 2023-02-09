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

static char	validate_input(char *input)
{	
	t_list		**tokens;
	t_list		*node;
	char		*unexpected_token;

	tokens = ft_tokenizer(input);
	node = *tokens;
	while (node)
	{
		unexpected_token = ft_analyse_token(node);
		if (unexpected_token)
		{
			if (ft_strncmp(unexpected_token, "\n", 2) == 0)
				unexpected_token = "newline";
			printf("syntax error near unexpected token `%s`\n",
				unexpected_token);
			g_minishell.status = 2;
			ft_lstclear(tokens, ft_del_token);
			free(tokens);
			return (0);
		}
		node = node->next;
	}
	ft_lstclear(tokens, ft_del_token);
	free(tokens);
	return (1);
}

void	ft_executor(char *input)
{
	t_list	**commands;

	if (!validate_input(input))
		return ;
	commands = ft_commands(input);
	if (!*commands)
		return ;
	ft_exec_commands(commands);
	ft_lstclear(commands, ft_del_command);
	free(commands);
}
