/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfanucch <dfanucch@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 09:34:54 by dfanucch          #+#    #+#             */
/*   Updated: 2023/02/16 09:34:54 by dfanucch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_search_metacharacter(char *input, char meta_char)
{
	char	quoted;

	quoted = 0;
	while (*input)
	{
		if (quoted && quoted == *input)
		{
			quoted = 0;
			input++;
			continue ;
		}
		if (*input == meta_char && !quoted)
			return (input);
		if (ft_is_quote(*input))
			quoted = *input;
		input++;
	}
	return (NULL);
}
