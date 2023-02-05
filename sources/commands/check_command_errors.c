/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command_errors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 17:48:47 by coder             #+#    #+#             */
/*   Updated: 2023/02/05 17:48:47 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	check_command_errors(t_command *command)
{
	if (!command->pathname && !command->is_builtin)
	{
		ft_lstadd_back(command->errors, ft_lstnew(
				ft_strjoin(command->filename, ": command not found\n")));
		command->bash_status = 127;
		return ;
	}
	if (!command->is_builtin && access(command->pathname, X_OK) != 0)
	{
		ft_lstadd_back(command->errors, ft_lstnew(
				ft_strjoin(command->filename, ": Permission denied\n")));
		command->bash_status = 126;
		return ;
	}
}
