/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfanucch <dfanucch@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 14:56:49 by dfanucch          #+#    #+#             */
/*   Updated: 2023/02/04 14:56:49 by dfanucch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	dup_file_descriptors(t_command *prev_command, t_command *command,
		t_command *next_command)
{
	t_list		*node;
	t_redirect	*redirect;
	t_list		**redirects;

	if (prev_command)
	{
		dup2(prev_command->pipe[0], 0);
		close(prev_command->pipe[0]);
	}
	if (next_command)
		dup2(command->pipe[1], 1);
	node = *command->redirects;
	while (node)
	{
		redirect = node->content;
		if (redirect->old_fd == -1)
		{
			node = node->next;
			command->bash_status = 1;
			continue ;
		}
		dup2(redirect->old_fd, redirect->new_fd);
		node = node->next;
	}
}

static void	print_command_error(t_command *command)
{
	t_list	*error;

	error = *command->errors;
	if (!error)
	{
		g_minishell.status = 1;
		return ;
	}
	ft_putstr_fd(error->content, 2);
	g_minishell.status = command->bash_status;
}

static int	exec_cmd(t_command *prev_command, t_command *command,
		t_command *next_command)
{
	pipe(command->pipe);
	ft_set_command_redirects(command);
	command->pid = fork();
	if (command->pid != 0)
	{
		close(command->pipe[1]);
		return (1);
	}
	ft_expand_args(command);
	ft_quote_removal(command);
	dup_file_descriptors(prev_command, command, next_command);
	close(command->pipe[1]);
	close(command->pipe[0]);
	command->pathname = get_pathname(command->filename, command->paths);
	if (command->bash_status == 0 && !command->is_builtin)
		execve(command->pathname, command->argv, command->envp);
	else if (command->is_builtin)
		ft_exec_builtin(command);
	check_command_errors(command);
	print_command_error(command);
	return (0);
}

static void	set_status_and_wait_pid(pid_t pid, t_list *node)
{
	int	wstatus;

	if (pid == 0)
		return ;
	wstatus = -1;
	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
		g_minishell.status = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus))
		g_minishell.status = 128 + WTERMSIG(wstatus);
	while (node->next)
	{
		wait(NULL);
		node = node->next;
	}
}

void	ft_exec_commands(t_list **commands)
{
	t_list		*node;
	t_command	*command;
	t_command	*prev_command;
	t_command	*next_command;
	int			wstatus;

	node = *commands;
	while (node)
	{
		prev_command = NULL;
		next_command = NULL;
		command = node->content;
		if (node->prev)
			prev_command = node->prev->content;
		if (node->next)
			next_command = node->next->content;
		if (!exec_cmd(prev_command, command, next_command))
			ft_child_exit_shell(commands, command->bash_status);
		if (prev_command)
			close(prev_command->pipe[0]);
		node = node->next;
	}
	close(command->pipe[0]);
	command = ft_lstlast(*commands)->content;
	set_status_and_wait_pid(command->pid, *commands);
}
