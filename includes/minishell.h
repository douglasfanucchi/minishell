/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfanucch <dfanucch@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:47:05 by dfanucch          #+#    #+#             */
/*   Updated: 2023/01/18 13:47:06 by dfanucch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <libft.h>

typedef struct s_token {
	char	should_expand;
	char	*original;
	char	*expanded;
}	t_token;

typedef struct s_tokenizer {
	char	quote;
	char	is_quoted;
	char	*delimiters;
}	t_tokenizer;

t_list	**ft_tokenizer(char *input);
t_token	*ft_new_token(char *str, char should_expand);
void	ft_del_token(void *param);
void	ft_del_tokens(void *param);

#endif
