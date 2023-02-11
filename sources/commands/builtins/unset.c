/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfanucch <dfanucch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:50:03 by dfanucch          #+#    #+#             */
/*   Updated: 2023/02/11 18:03:16 by dfanucch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	exec(t_command *command)
{
	char	**args;
	char	*var;

	args = command->argv + 1;
	while (*args)
	{
		var = ft_strjoin("$", *args);
		if (ft_is_valid_variable(var))
			ft_envp_remove(g_minishell.envp, *args);
		else
		{
			ft_putstr_fd("unset: `", 2);
			ft_putstr_fd(*args, 2);
			ft_putstr_fd("`: not a valid identifier\n", 2);
			command->bash_status = 1;
		}
		free(var);
		args++;
	}
	return (0);
}

t_builtin	*ft_new_unset(void)
{
	t_builtin	*builtin;

	builtin = malloc(sizeof(t_builtin));
	builtin->id = ft_strdup("unset");
	builtin->exec = exec;
	return (builtin);
}
