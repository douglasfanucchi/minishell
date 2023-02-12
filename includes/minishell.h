/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfanucch <dfanucch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:47:05 by dfanucch          #+#    #+#             */
/*   Updated: 2023/02/11 18:42:04 by dfanucch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <libft.h>
# include <stdio.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_shell {
	char			**envp;
	unsigned char	status;
	t_list			**commands;
}	t_shell;

extern t_shell	g_minishell;

typedef struct s_token {
	char	should_expand;
	char	*original;
	char	*expanded;
	t_list	**variables;
}	t_token;

typedef struct s_tokenizer {
	char	quote;
	char	is_quoted;
	char	*delimiters;
}	t_tokenizer;

typedef struct s_analyser {
	char	*(*analyse)(t_list *);
}	t_analyser;

typedef struct s_command {
	char	*pathname;
	char	*filename;
	char	**envp;
	char	**argv;
	pid_t	pid;
	char	bash_status;
	int		pipe[2];
	char	is_builtin;
	t_list	**tokens;
	t_list	**redirects;
	t_list	**errors;
	char	**paths;
}	t_command;

typedef struct s_redirect {
	int	old_fd;
	int	new_fd;
}	t_redirect;

typedef struct s_variable {
	size_t	position;
	size_t	len;
	char	*value;
}	t_variable;

typedef struct s_builtin {
	char	*id;
	int		(*exec)(t_command *command);
}	t_builtin;

t_list		**ft_tokenizer(char *input);
t_token		*ft_new_token(char *str);
void		ft_del_token(void *param);
void		ft_del_tokens(void *param);
char		ft_should_append_redirect_token(char *str, char delimiter);
void		ft_append_redirect_token(char **end);
t_analyser	*get_redirection_analyser(void);
t_analyser	*get_pipe_analyser(void);
t_analyser	*get_quoted_analyser(void);
char		*ft_analyse_token(t_list *node);
char		*ft_analyse_command(t_command *command);
char		ft_is_redirection_token(char *token);
t_command	*ft_new_command(t_list **tokens, char **envp, char **paths);
void		ft_del_command(void *cmd);
int			ft_get_redirect_file_descriptor(t_list *node);
t_redirect	*ft_new_redirect(t_list *node);
char		**ft_find_arg(char **argv, char *arg);
void		ft_remove_arg(char **argv, char *arg);
void		ft_set_command_redirects(t_command *command);
void		ft_expand_args(t_command *command);
char		ft_is_variable(char *str);
char		ft_is_valid_variable(char *str);
char		ft_is_valid_variable_char(char c);
t_variable	*ft_new_variable(size_t position, char *value);
void		ft_del_variable(void *content);
void		ft_quote_removal(t_command *command);
void		ft_executor(char *input);
void		ft_exec_commands(t_list **commands);
void		ft_del_redirect(void *content);
void		check_command_errors(t_command *command);
void		dup_file_descriptors(t_command *prev, t_command *cmd,
				t_command *next);
char		**ft_get_paths(char **envp);
void		ft_del_paths(char **paths);
char		**ft_new_envp(char **envp);
void		ft_del_envp(char **envp);
void		ft_child_exit_shell(t_list **commands, char status);
t_list		**ft_commands(char *input);
char		*get_pathname(char *bin, char **paths);
char		ft_is_quote(char c);
char		ft_is_builtin(t_command *command);
t_builtin	*ft_new_echo(void);
t_builtin	*ft_new_change_directory(void);
t_builtin	*ft_new_pwd(void);
t_builtin	*ft_new_unset(void);
t_builtin	*ft_new_exit(void);
t_builtin	*ft_new_env(void);
t_builtin	*ft_new_builtin(char *id);
t_builtin	*ft_new_export(void);
void		ft_del_builtin(void *content);
int			ft_exec_builtin(t_command *command);
char		*ft_envp_value(char **envp, char *var);
int			ft_envp_update_var(char **envp, char *var, char *value);
int			ft_envp_remove(char **envp, char *var);
void		ft_envp_add(char ***envp, char *str);
char		*ft_get_var_from_envp_str(char *str);
char		*ft_get_value_from_envp_str(char *str);
char		*ft_path_after_navigate(t_list **dirs, char *cmd_navigation);

#endif
