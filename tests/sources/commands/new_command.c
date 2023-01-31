#include <minunit.h>
#include <minishell.h>

char	envp[1][4096];
char	**paths;

MU_TEST(test_command_filename_should_ignore_redirect_tokens) {
	t_list		**tokens = ft_newlist();
	t_command	*command;

	ft_lstadd_back(tokens, ft_lstnew(ft_new_token("<<", 0)));
	ft_lstadd_back(tokens, ft_lstnew(ft_new_token("limiter", 0)));
	ft_lstadd_back(tokens, ft_lstnew(ft_new_token("cat", 0)));
	ft_lstadd_back(tokens, ft_lstnew(ft_new_token("\n", 0)));

	command = ft_new_command(tokens, (char **)envp, (char **)paths);
	mu_check(command->filename != NULL);
	mu_check(ft_strncmp(command->filename, "cat", 4) == 0);

	ft_del_command(command);
}

MU_TEST(test_command_filename_should_be_empty) {
	t_list		**tokens = ft_newlist();
	t_command	*command;

	ft_lstadd_back(tokens, ft_lstnew(ft_new_token("\n", 0)));
	command = ft_new_command(tokens, (char **)envp, (char **)paths);
	mu_check(command->filename != NULL);
	mu_check(command->filename[0] == '\0');

	ft_del_command(command);

	tokens = ft_newlist();

	ft_lstadd_back(tokens, ft_lstnew(ft_new_token("<<", 0)));
	ft_lstadd_back(tokens, ft_lstnew(ft_new_token("filename", 0)));
	ft_lstadd_back(tokens, ft_lstnew(ft_new_token("\n", 0)));

	command = ft_new_command(tokens, (char **)envp, (char **)paths);
	mu_check(command->filename != NULL);
	mu_check(command->filename[0] == '\0');

	ft_del_command(command);
}

MU_TEST(test_command_filename_should_be_first_token) {
	t_list		**tokens = ft_newlist();
	t_command	*command;

	ft_lstadd_back(tokens, ft_lstnew(ft_new_token("cat", 0)));
	ft_lstadd_back(tokens, ft_lstnew(ft_new_token("\n", 0)));
	command = ft_new_command(tokens, (char **)envp, (char **)paths);
	mu_check(command->filename != NULL);
	mu_check(ft_strncmp(command->filename, "cat", 4) == 0);

	ft_del_command(command);
}

MU_TEST(test_command_args_should_not_have_newline) {
	t_list **tokens = ft_newlist();
	ft_lstadd_back(tokens, ft_lstnew(ft_new_token("cat", 0)));
	ft_lstadd_back(tokens, ft_lstnew(ft_new_token("Makefile", 0)));
	ft_lstadd_back(tokens, ft_lstnew(ft_new_token("\n", 0)));

	t_command *command = ft_new_command(tokens, (char **)envp, (char **)paths);
	char **args = command->argv;

	while (*(args + 1))
		args++;

	mu_check(ft_strncmp(*args, "\n", 2) != 0);
	mu_check(ft_strncmp(*args, "Makefile", ft_strlen("Makefile") + 1) == 0);

	ft_del_command(command);
}

MU_TEST(test_command_args_should_have_same_values_as_token) {
	t_list	**tokens = ft_newlist();
	ft_lstadd_back(tokens, ft_lstnew(ft_new_token("cat", 0)));
	ft_lstadd_back(tokens, ft_lstnew(ft_new_token("Makefie", 0)));
	ft_lstadd_back(tokens, ft_lstnew(ft_new_token("\n", 0)));
	t_list	*node = *tokens;
	t_command *command = ft_new_command(tokens, (char **)envp, (char **)paths);
	char **argv = command->argv;

	while (node->next)
	{
		t_token *token = node->content;
		mu_check(ft_strncmp(token->original, *argv, ft_strlen(token->original) + 1) == 0);
		argv++;
		node = node->next;
	}

	ft_del_command(command);
}

MU_TEST_SUITE(test_new_command) {
	ft_strlcpy(envp[0], "PATH=/usr/bin", ft_strlen("PATH=/usr/bin"));
	paths = ft_split(envp[0], ':');

	MU_RUN_TEST(test_command_filename_should_ignore_redirect_tokens);
	MU_RUN_TEST(test_command_filename_should_be_empty);
	MU_RUN_TEST(test_command_filename_should_be_first_token);
	MU_RUN_TEST(test_command_args_should_have_same_values_as_token);
	MU_RUN_TEST(test_command_args_should_not_have_newline);

	int i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
}
