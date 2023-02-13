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

static void	reset_fds(char *tty)
{
	int		fd;

	if (!tty)
		return ;
	fd = open(tty, O_RDWR);
	dup2(fd, 0);
	dup2(fd, 1);
	dup2(fd, 2);
	close(fd);
}

void	ft_executor(char *input)
{
	t_command	*command;
	char		*tty;

	tty = ttyname(0);
	if (!validate_input(input))
		return ;
	g_minishell.commands = ft_commands(input);
	if (!*g_minishell.commands)
		return ;
	command = (*g_minishell.commands)->content;
	if (ft_lstsize(*g_minishell.commands) == 1 && command->is_builtin)
	{
		ft_set_command_redirects(command);
		ft_expand_args(command);
		ft_quote_removal(command);
		dup_file_descriptors(NULL, command, NULL);
		ft_exec_builtin(command);
		reset_fds(tty);
	}
	else
		ft_exec_commands(g_minishell.commands);
	ft_lstclear(g_minishell.commands, ft_del_command);
	free(g_minishell.commands);
	g_minishell.commands = NULL;
}
