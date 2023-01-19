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
#include <stdio.h>

static char is_delimiter(t_tokenizer *tokenizer, char c)
{
	char	result;

	result = 0;
	if (ft_strchr(tokenizer->delimiters, c))
		result = 1;
	return (result);
}

static	char **split_tokens(char const *input, int index, t_tokenizer *tokenizer)
{
	char		**list;
	char const	*start;
	char const	*end;

	start = input;
	while (ft_isspace(*start))
		start++;
	if (*start == '\0')
		return ((char **)ft_calloc(index + 1, sizeof(char *)));
	if (*start == '"' || *start == '\'')
	{
		tokenizer->quote = *start;
		tokenizer->is_quoted = 1;
	}
	if (is_delimiter(tokenizer, *start))
	{
		list = split_tokens(start + 1, index + 1, tokenizer);
		list[index] = ft_substr(start, 0, 1);
		return (list);
	}
	end = start;
	if (tokenizer->is_quoted)
		end++;
	while (*end && (!is_delimiter(tokenizer, *end) || tokenizer->is_quoted))
	{
		if (*end == tokenizer->quote)
			tokenizer->is_quoted = 0;
		end++;
	}
	list = split_tokens(end, index + 1, tokenizer);
	if (!list)
		return (list);
	list[index] = ft_substr(start, 0, end - start);
	return (list);
}

t_list	**ft_tokenizer(char *input)
{
	t_list		**list;
	t_token		*token;
	t_tokenizer	tokenizer;
	char	**tokens;
	int	i = 0;

	list = ft_newlist();
	tokenizer.delimiters = "\t\n <>|";
	tokenizer.is_quoted = 0;
	tokenizer.quote = 0;
	tokens = split_tokens(input, 0, &tokenizer);
	while (tokens[i])
	{
		token = ft_new_token(tokens[i], 0);
		ft_lstadd_back(list, ft_lstnew(token));
		free(tokens[i]);
		i++;
	}
	free(tokens);
	return (list);
}
