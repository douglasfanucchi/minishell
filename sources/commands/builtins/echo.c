/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfanucch <dfanucch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:10:11 by dfanucch          #+#    #+#             */
/*   Updated: 2023/02/10 11:55:53 by dfanucch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	remove_newline_flag(char **args)
{
	return (ft_strncmp(args[0], "-n", ft_strlen("-n") + 1) == 0);
}

static int	exec(t_command *command)
{
	char	remove_newline;
	char	**args;

	remove_newline = 0;
	args = command->argv + 1;
	if (!args[0])
	{
		ft_putstr("\n");
		return (0);
	}
	if (remove_newline_flag(args))
	{
		remove_newline = 1;
		while (args[0] && remove_newline_flag(args))
			args++;
	}
	while (*args)
	{
		ft_putstr(*args++);
		if (*args)
			ft_putstr(" ");
	}
	if (!remove_newline)
		ft_putstr("\n");
	return (0);
}

t_builtin	*ft_new_echo(void)
{
	t_builtin	*echo;

	echo = malloc(sizeof(t_builtin));
	echo->id = ft_strdup("echo");
	echo->exec = exec;
	return (echo);
}
