/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfanucch <dfanucch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 20:03:00 by dfanucch          #+#    #+#             */
/*   Updated: 2023/02/13 16:39:06 by dfanucch         ###   ########.fr       */
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

void	ft_handle_sigint(int signal)
{
	if (signal != SIGINT)
		return ;
	if (!g_minishell.waiting)
	{
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else
		ft_putchar_fd('\n', 1);
	g_minishell.cancel_cmd = 1;
	g_minishell.status = 130;
}

int	main(int argc, char **argv, char **env)
{
	char	*line;

	signal(SIGINT, ft_handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	if (!argc || !argv[0])
		return (1);
	g_minishell.status = 0;
	g_minishell.waiting = 0;
	g_minishell.envp = ft_new_envp(env);
	g_minishell.commands = NULL;
	line = readline("$> ");
	while (line)
	{
		g_minishell.cancel_cmd = 0;
		ft_executor(line);
		add_history(line);
		line = readline("$> ");
	}
	ft_del_envp(g_minishell.envp);
	return (g_minishell.status);
}
