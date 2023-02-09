/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfanucch <dfanucch@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 07:30:28 by dfanucch          #+#    #+#             */
/*   Updated: 2023/02/04 07:30:31 by dfanucch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

static char	is_expanded_char(t_token *token, size_t i)
{
	t_list		*var_node;
	t_variable	*variable;
	size_t		var_end;

	var_node = *token->variables;
	while (var_node)
	{
		variable = var_node->content;
		var_end = variable->position + variable->len;
		if (i >= variable->position && i < var_end)
			return (1);
		var_node = var_node->next;
	}
	return (0);
}

static void	update_variable_positions(t_list *node, size_t index)
{
	t_variable	*variable;

	while (node)
	{
		variable = node->content;
		if (variable->position > index)
			variable->position -= 1;
		node = node->next;
	}
}

static void	remove_quotes(char *str, t_token *token)
{
	char	quoted;
	size_t	i;

	quoted = 0;
	i = 0;
	while (str[i])
	{
		if (!is_quote(str[i]) || (quoted && quoted != str[i])
			|| is_expanded_char(token, i))
		{
			i++;
			continue ;
		}
		if (!quoted || quoted == str[i])
		{
			if (!quoted)
				quoted = str[i];
			else
				quoted = 0;
			ft_memmove(str + i, str + i + 1, ft_strlen(str + i));
			update_variable_positions(*token->variables, i);
			continue ;
		}
		i++;
	}
}

void	ft_quote_removal(t_command *command)
{
	t_list	*tokens_node;
	t_token	*token;
	char	**argv;

	tokens_node = *command->tokens;
	argv = command->argv;
	token = tokens_node->content;
	remove_quotes(command->filename, token);
	while (tokens_node->next)
	{
		token = tokens_node->content;
		remove_quotes(*argv, token);
		tokens_node = tokens_node->next;
		argv++;
	}
}
