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

t_shell	g_minishell;

void	ft_child_exit_shell(t_list **commands, char status)
{
	ft_lstclear(commands, ft_del_command);
	free(commands);
	ft_del_envp(g_minishell.envp);
	exit(status);
}

int	main(void)
{
	return (0);
}
