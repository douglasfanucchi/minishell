/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfanucch <dfanucch@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:47:05 by dfanucch          #+#    #+#             */
/*   Updated: 2023/01/18 13:47:06 by dfanucch         ###   ########.fr       */
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

typedef struct s_token {
	char	should_expand;
	char	*original;
	char	*expanded;
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
	t_list	**redirects;
}	t_command;

typedef struct s_redirect {
	int	old_fd;
	int	new_fd;
}	t_redirect;

t_list		**ft_tokenizer(char *input);
t_token		*ft_new_token(char *str, char should_expand);
void		ft_del_token(void *param);
void		ft_del_tokens(void *param);
char		ft_should_append_redirect_token(char *str, char delimiter);
void		ft_append_redirect_token(char **end);
t_analyser	*get_redirection_analyser(void);
t_analyser	*get_pipe_analyser(void);
t_analyser	*get_quoted_analyser(void);
char		*ft_analyse_token(t_list *node);
char		ft_is_redirection_token(char *token);
t_command	*ft_new_command(t_list **tokens, char **envp, char **paths);
void		ft_del_command(void *cmd);
int			ft_get_redirect_file_descriptor(t_list *node);
t_redirect	*ft_new_redirect(t_list *node);
char		**ft_find_arg(char **argv, char *arg);
void		ft_remove_arg(char **argv, char *arg);

#endif
