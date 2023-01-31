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

static char	is_delimiter(t_tokenizer *tokenizer, char c)
{
	char	result;

	result = 0;
	if (ft_strchr(tokenizer->delimiters, c))
		result = 1;
	return (result);
}

static void	set_quoting_status(t_tokenizer *tokenizer, char c)
{
	char	*quotes;

	quotes = "\"'";
	if (!tokenizer->is_quoted && ft_strchr(quotes, c))
	{
		tokenizer->is_quoted = 1;
		tokenizer->quote = c;
		return ;
	}
	if (tokenizer->is_quoted && tokenizer->quote == c)
	{
		tokenizer->is_quoted = 0;
		tokenizer->quote = 0;
	}
}

static char	**split_tokens(char *start, int index, t_tokenizer *tokenizer)
{
	char	**list;
	char	*end;

	while (ft_isspace(*start))
		start++;
	if (*start == '\0')
		return ((char **)ft_calloc(index + 1, sizeof(char *)));
	end = start;
	if (is_delimiter(tokenizer, *end))
	{
		end++;
		if (start[0] == start[1])
			end++;
		list = split_tokens(end, index + 1, tokenizer);
		list[index] = ft_substr(start, 0, end - start);
		return (list);
	}
	while (*end && (!is_delimiter(tokenizer, *end) || tokenizer->is_quoted))
		set_quoting_status(tokenizer, *(end++));
	if (ft_should_append_redirect_token(ft_substr(start, 0, end - start), *end))
		ft_append_redirect_token(&end);
	list = split_tokens(end, index + 1, tokenizer);
	list[index] = ft_substr(start, 0, end - start);
	return (list);
}

void	ft_del_tokens(void *param)
{
	t_list	**tokenizer;

	tokenizer = param;
	ft_lstclear(tokenizer, ft_del_token);
	free(tokenizer);
}

t_list	**ft_tokenizer(char *input)
{
	t_list		**list;
	t_token		*token;
	t_tokenizer	tokenizer;
	char		**tokens;
	int			i;

	i = 0;
	list = ft_newlist();
	tokenizer.delimiters = "\t\n <>|";
	tokenizer.is_quoted = 0;
	tokenizer.quote = 0;
	tokens = split_tokens(input, 0, &tokenizer);
	while (tokens[i])
	{
		token = ft_new_token(tokens[i]);
		ft_lstadd_back(list, ft_lstnew(token));
		free(tokens[i]);
		i++;
	}
	ft_lstadd_back(list, ft_lstnew(ft_new_token("\n")));
	free(tokens);
	return (list);
}
