/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoted.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfanucch <dfanucch@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:02:25 by dfanucch          #+#    #+#             */
/*   Updated: 2023/01/23 10:02:25 by dfanucch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*analyse(t_list *node)
{
	t_token	*token;
	t_token	*next_token;
	char	unclosed_quote;
	char	*token_content;

	token = node->content;
	token_content = token->original;
	unclosed_quote = token_content[0];
	token_content++;
	next_token = node->next->content;
	while (*token_content)
	{
		if (*token_content == unclosed_quote)
			unclosed_quote = 0;
		else if (!unclosed_quote && *token_content == '\''
			|| *token_content == '"')
			unclosed_quote = *token_content;
		token_content++;
	}
	if (unclosed_quote)
		return (next_token->original);
	return (NULL);
}

t_analyser	*get_quoted_analyser(void)
{
	t_analyser	*analyser;

	analyser = malloc(sizeof(t_analyser));
	analyser->analyse = analyse;
	return (analyser);
}
