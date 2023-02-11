/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfanucch <dfanucch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 14:13:56 by dfanucch          #+#    #+#             */
/*   Updated: 2023/02/11 18:42:56 by dfanucch         ###   ########.fr       */
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
	t_list		**commands;
	t_command	*command;

	if (!validate_input(input))
		return ;
	commands = ft_commands(input);
	g_minishell.commands = commands;
	if (!*commands)
		return ;
	command = (*commands)->content;
	if (ft_lstsize(*commands) == 1 && command->is_builtin)
	{
		ft_set_command_redirects(command);
		ft_expand_args(command);
		ft_quote_removal(command);
		dup_file_descriptors(NULL, command, NULL);
		ft_exec_builtin(command);
	}
	else
		ft_exec_commands(commands);
	ft_lstclear(commands, ft_del_command);
	free(commands);
	g_minishell.commands = NULL;
}
