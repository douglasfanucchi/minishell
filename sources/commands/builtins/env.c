/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfanucch <dfanucch@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 23:35:51 by dfanucch          #+#    #+#             */
/*   Updated: 2023/02/11 23:35:52 by dfanucch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	exec(t_command *command)
{
	char	**envp;
	char	*value;

	if (command->argv[1])
	{
		ft_putstr_fd("env: too many arguments\n", 2);
		command->bash_status = 1;
		return (-1);
	}
	envp = g_minishell.envp;
	while (*envp)
	{
		value = ft_get_value_from_envp_str(*envp);
		if (*value)
		{
			ft_putstr(*envp);
			ft_putstr("\n");
		}
		free(value);
		envp++;
	}
	return (0);
}

t_builtin	*ft_new_env(void)
{
	t_builtin	*builtin;

	builtin = malloc(sizeof(t_builtin));
	builtin->id = ft_strdup("env");
	builtin->exec = exec;
	return (builtin);
}
