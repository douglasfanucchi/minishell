/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfanucch <dfanucch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:25:16 by dfanucch          #+#    #+#             */
/*   Updated: 2023/02/11 17:31:21 by dfanucch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	exec(t_command *command)
{
	char	*cwd;

	if (!command->argv[0])
		return (-1);
	cwd = getcwd(NULL, 0);
	if (cwd)
		ft_putstr(cwd);
	ft_putstr("\n");
	free(cwd);
	return (0);
}

t_builtin	*ft_new_pwd(void)
{
	t_builtin	*builtin;

	builtin = malloc(sizeof(t_builtin));
	builtin->id = ft_strdup("pwd");
	builtin->exec = exec;
	return (builtin);
}
