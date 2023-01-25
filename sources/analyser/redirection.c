/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfanucch <dfanucch@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 07:26:24 by dfanucch          #+#    #+#             */
/*   Updated: 2023/01/21 07:26:24 by dfanucch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	ft_is_redirection_token(char *token)
{
	char	result;
	size_t	i;

	if (token[0] == '\'' || token[0] == '"')
		return (0);
	i = 0;
	while (token[i] && token[i] != '<' && token[i] != '>')
		i++;
	return (ft_strlen(token) != i);
}

static char	*analyse(t_list *node)
{
	t_token	*token;
	t_token	*next_token;

	token = node->content;
	next_token = node->next->content;
	if (ft_is_redirection_token(next_token->original)
		|| next_token->original[0] == '|' || next_token->original[0] == '\n')
		return (next_token->original);
	return (NULL);
}

t_analyser	*get_redirection_analyser(void)
{
	t_analyser	*analyser;

	analyser = malloc(sizeof(t_analyser));
	analyser->analyse = &analyse;
	return (analyser);
}
