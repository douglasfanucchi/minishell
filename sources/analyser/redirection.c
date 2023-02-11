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

static char	*analyse(t_list *node)
{
	t_token	*next_token;

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
