/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfanucch <dfanucch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 20:03:00 by dfanucch          #+#    #+#             */
/*   Updated: 2023/02/11 18:51:21 by dfanucch         ###   ########.fr       */
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

int	main(int argc, char **argv, char **env)
{
	char	*line;

	if (!argc || !argv[0])
		return (1);
	g_minishell.status = 0;
	g_minishell.envp = ft_new_envp(env);
	g_minishell.commands = NULL;
	line = readline("$> ");
	while (line)
	{
		ft_executor(line);
		add_history(line);
		line = readline("$> ");
	}
	ft_del_envp(g_minishell.envp);
	return (g_minishell.status);
}
