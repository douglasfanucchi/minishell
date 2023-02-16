/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfanucch <dfanucch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 08:23:53 by dfanucch          #+#    #+#             */
/*   Updated: 2023/02/13 19:05:17 by dfanucch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_list	**ft_commands(char *input)
{
	char	*end_input;
	char	*input_substr;
	t_list	**commands;

	commands = ft_newlist();
	while (*input)
	{
		if (ft_isspace(*input))
		{
			input++;
			continue ;
		}
		end_input = ft_search_metacharacter(input, '|');
		if (!end_input)
			end_input = input + ft_strlen(input);
		input_substr = ft_substr(input, 0, end_input - input);
		ft_lstadd_back(commands, ft_lstnew(ft_new_command(
					ft_tokenizer(input_substr), g_minishell.envp,
					ft_get_paths(g_minishell.envp))));
		free(input_substr);
		if (*end_input == '|')
			end_input++;
		input = end_input;
	}
	return (commands);
}
