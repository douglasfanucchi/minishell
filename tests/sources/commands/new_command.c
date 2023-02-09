#include <minunit.h>
#include <minishell.h>

MU_TEST(test_command_filename_should_ignore_redirect_tokens) {
	t_list		**tokens = ft_newlist();
	t_command	*command;

	ft_lstadd_back(tokens, ft_lstnew(ft_new_token("<<")));
	ft_lstadd_back(tokens, ft_lstnew(ft_new_token("limiter")));
	ft_lstadd_back(tokens, ft_lstnew(ft_new_token("cat")));
	ft_lstadd_back(tokens, ft_lstnew(ft_new_token("\n")));

	command = ft_new_command(tokens, g_minishell.envp, ft_get_paths(g_minishell.envp));
	mu_check(command->filename != NULL);
	mu_check(ft_strncmp(command->filename, "cat", 4) == 0);

	ft_del_command(command);
}

MU_TEST(test_command_filename_should_be_empty) {
	t_list		**tokens = ft_newlist();
	t_command	*command;

	ft_lstadd_back(tokens, ft_lstnew(ft_new_token("\n")));
	command = ft_new_command(tokens, g_minishell.envp, ft_get_paths(g_minishell.envp));
	mu_check(command->filename != NULL);
	mu_check(command->filename[0] == '\0');

	ft_del_command(command);

	tokens = ft_newlist();

	ft_lstadd_back(tokens, ft_lstnew(ft_new_token("<<")));
	ft_lstadd_back(tokens, ft_lstnew(ft_new_token("filename")));
	ft_lstadd_back(tokens, ft_lstnew(ft_new_token("\n")));

	command = ft_new_command(tokens, g_minishell.envp, ft_get_paths(g_minishell.envp));
	mu_check(command->filename != NULL);
	mu_check(command->filename[0] == '\0');

	ft_del_command(command);
}

MU_TEST(test_command_filename_should_be_first_token) {
	t_list		**tokens = ft_newlist();
	t_command	*command;

	ft_lstadd_back(tokens, ft_lstnew(ft_new_token("cat")));
	ft_lstadd_back(tokens, ft_lstnew(ft_new_token("\n")));
	command = ft_new_command(tokens, g_minishell.envp, ft_get_paths(g_minishell.envp));
	mu_check(command->filename != NULL);
	mu_check(ft_strncmp(command->filename, "cat", 4) == 0);

	ft_del_command(command);
}

MU_TEST(test_command_args_should_not_have_newline) {
	t_list **tokens = ft_newlist();
	ft_lstadd_back(tokens, ft_lstnew(ft_new_token("cat")));
	ft_lstadd_back(tokens, ft_lstnew(ft_new_token("Makefile")));
	ft_lstadd_back(tokens, ft_lstnew(ft_new_token("\n")));

	t_command *command = ft_new_command(tokens, g_minishell.envp, ft_get_paths(g_minishell.envp));
	char **args = command->argv;

	while (*(args + 1))
		args++;

	mu_check(ft_strncmp(*args, "\n", 2) != 0);
	mu_check(ft_strncmp(*args, "Makefile", ft_strlen("Makefile") + 1) == 0);

	ft_del_command(command);
}

MU_TEST(test_command_args_should_have_same_values_as_token) {
	t_list	**tokens = ft_newlist();
	ft_lstadd_back(tokens, ft_lstnew(ft_new_token("cat")));
	ft_lstadd_back(tokens, ft_lstnew(ft_new_token("Makefie")));
	ft_lstadd_back(tokens, ft_lstnew(ft_new_token("\n")));
	t_list	*node = *tokens;
	t_command *command = ft_new_command(tokens, g_minishell.envp, ft_get_paths(g_minishell.envp));
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
	MU_RUN_TEST(test_command_filename_should_ignore_redirect_tokens);
	MU_RUN_TEST(test_command_filename_should_be_empty);
	MU_RUN_TEST(test_command_filename_should_be_first_token);
	MU_RUN_TEST(test_command_args_should_have_same_values_as_token);
	MU_RUN_TEST(test_command_args_should_not_have_newline);
}
