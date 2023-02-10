#include <minishell.h>
#include <minunit.h>

MU_TEST(test_ft_is_builtin_should_return_true) {
	t_command	*command = ft_new_command(ft_tokenizer("echo 'hello world'"), g_minishell.envp, ft_get_paths(g_minishell.envp));

	mu_check(ft_is_builtin(command));
	ft_del_command(command);
}

MU_TEST(test_ft_is_builtin_should_return_false) {
	t_command	*command = ft_new_command(ft_tokenizer("cat Makefile"), g_minishell.envp, ft_get_paths(g_minishell.envp));

	mu_check(!ft_is_builtin(command));
	ft_del_command(command);

	command = ft_new_command(ft_tokenizer("git status"), g_minishell.envp, ft_get_paths(g_minishell.envp));

	mu_check(!ft_is_builtin(command));
	ft_del_command(command);
}

MU_TEST(test_properly_sets_command_as_builtin) {
	t_command	*command = ft_new_command(ft_tokenizer("echo 'hello'"), g_minishell.envp, ft_get_paths(g_minishell.envp));

	mu_check(command->is_builtin);
	ft_del_command(command);

	command = ft_new_command(ft_tokenizer("cat 'hello'"), g_minishell.envp, ft_get_paths(g_minishell.envp));

	mu_check(!command->is_builtin);
	ft_del_command(command);
}

MU_TEST_SUITE(test_builtins) {
	MU_RUN_TEST(test_ft_is_builtin_should_return_true);
	MU_RUN_TEST(test_ft_is_builtin_should_return_false);
	MU_RUN_TEST(test_properly_sets_command_as_builtin);
}
