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
	struct stat	file_status;

	if (!*command->pathname)
	{
		ft_lstadd_back(command->errors, ft_lstnew(
				ft_strjoin(command->filename, ": command not found\n")));
		command->bash_status = 127;
		return ;
	}
	if (access(command->pathname, X_OK) != 0)
	{
		ft_lstadd_back(command->errors, ft_lstnew(
				ft_strjoin(command->filename, ": Permission denied\n")));
		command->bash_status = 126;
		return ;
	}
	stat(command->pathname, &file_status);
	if (*command->filename && S_ISDIR(file_status.st_mode))
	{
		ft_lstadd_back(command->errors, ft_lstnew(
				ft_strjoin(command->filename, ": Is a directory\n")));
		command->bash_status = 126;
		return ;
	}
	command->bash_status = 1;
}
