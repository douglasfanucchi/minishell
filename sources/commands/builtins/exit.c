/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfanucch <dfanucch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 18:14:25 by dfanucch          #+#    #+#             */
/*   Updated: 2023/02/11 18:49:55 by dfanucch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	validate_args(char **args, t_command *command)
{
	if (!args[0])
		return (1);
	if (!ft_is_number(args[0]))
	{
		command->bash_status = 2;
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (0);
	}
	if (args[1])
	{
		command->bash_status = 1;
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (0);
	}
	return (1);
}

static void	ft_exit(int status)
{
	ft_lstclear(g_minishell.commands, ft_del_command);
	free(g_minishell.commands);
	ft_del_envp(g_minishell.envp);
	exit(status);
}

static int	exec(t_command *command)
{
	int	status;

	validate_args(command->argv + 1, command);
	ft_putstr("exit\n");
	if (command->bash_status == 1)
		return (-1);
	if (command->bash_status == 2)
		ft_exit(2);
	if (!command->argv[1])
		ft_exit(g_minishell.status);
	ft_exit(ft_atoi(command->argv[1]));
	return (0);
}

t_builtin	*ft_new_exit(void)
{
	t_builtin	*builtin;

	builtin = malloc(sizeof(t_builtin));
	builtin->id = ft_strdup("exit");
	builtin->exec = exec;
	return (builtin);
}
