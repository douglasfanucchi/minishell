/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfanucch <dfanucch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 10:53:10 by dfanucch          #+#    #+#             */
/*   Updated: 2023/02/14 00:37:15 by dfanucch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_exec_builtin(t_command *command)
{
	t_builtin	*builtin;

	builtin = ft_new_builtin(command->filename);
	if (!builtin)
	{
		command->bash_status = 1;
		return (-1);
	}
	builtin->exec(command);
	ft_del_builtin((void *)builtin);
	return (0);
}
