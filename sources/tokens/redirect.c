/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfanucch <dfanucch@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:11:29 by dfanucch          #+#    #+#             */
/*   Updated: 2023/01/18 14:11:30 by dfanucch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	ft_is_redirection_token(char *token)
{
	char	*redirect;

	redirect = ft_search_metacharacter(token, '<');
	if (!redirect)
		redirect = ft_search_metacharacter(token, '>');
	if (!redirect)
		return (0);
	return (1);
}

char	ft_should_append_redirect_token(char *str, char delimiter)
{
	char	result;

	result = 0;
	if ((delimiter == '<' || delimiter == '>')
		&& ft_is_number(str) && ft_atoi(str) >= 0)
		result = 1;
	free(str);
	return (result);
}

void	ft_append_redirect_token(char **end)
{
	if (end[0][0] == end[0][1])
		*end += 1;
	*end += 1;
}
