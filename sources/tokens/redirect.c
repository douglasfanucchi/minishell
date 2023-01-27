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
	size_t	i;

	if (token[0] == '\'' || token[0] == '"')
		return (0);
	i = 0;
	while (token[i] && token[i] != '<' && token[i] != '>')
		i++;
	return (ft_strlen(token) != i);
}

char	ft_should_append_redirect_token(char *str, char delimiter)
{
	char	result;

	result = 0;
	if ((delimiter == '<' || delimiter == '>') && ft_is_number(str))
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
