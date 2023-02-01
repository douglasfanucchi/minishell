/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfanucch <dfanucch@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 20:03:00 by dfanucch          #+#    #+#             */
/*   Updated: 2023/01/17 20:03:00 by dfanucch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char g_bash_status;

int	main(void)
{
	t_list	**tokens = ft_tokenizer("<< limiter cat");
	t_command	*command = ft_new_command(tokens, (char **)(NULL), (char **)(NULL));
	ft_set_command_redirects(command);
	return (0);
}
